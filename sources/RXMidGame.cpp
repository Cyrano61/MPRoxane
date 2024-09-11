/*
 *  RXMidGame.cpp
 *  BitBoard
 *
 *  Created by Bruno Causse on 13/08/05.
 *  Copyright 2005-2024 personnel. All rights reserved.
 *
 */
 
#include <cstdlib>
#include <cmath>
#include <sstream>

#include "RXEngine.hpp"
#include "RXRoxane.hpp"




const int RXEngine::MG_SELECT = 0;


//const int RXEngine::MAX_DEPTH_USE_PROBCUT = 50;
const int RXEngine::MIN_DEPTH_USE_PROBCUT = 4; // DO NOT CHANGE

const int RXEngine::MIN_DEPTH_SPLITPOINT = 8;

const int RXEngine::MG_DEEP_TO_SHALLOW = 4;
const int RXEngine::MG_MOVING_WINDOW = 8; //4

const int RXEngine::PV_EXTENSION_DEPTH = 14; //
const int RXEngine::MIN_DEPTH_USE_PV_EXTENSION = 16;


void RXEngine::iterative_deepening(RXBBPatterns& sBoard, RXMove* list, int depth, const int max_depth) {
	
	set_type_search(MIDGAME);
	
	if(dependent_time)
		determine_move_time(sBoard.board);
	
	int eTime = get_current_time();
	
	do {
		
		time_startLevel= eTime;
		
		sBoard.board.n_nodes = 0;
		
		
		if(depth>MIN_DEPTH_USE_PV_EXTENSION) {
			
			use_pv_extension = true;
			
			if(abs(list->next->score) > 18*VALUE_DISC) {
				pv_extension = PV_EXTENSION_DEPTH-2;
			} else {
				pv_extension = PV_EXTENSION_DEPTH;
			}
			
		} else {
			use_pv_extension = false;
			
			pv_extension = 12;
		}

		aspiration_search(sBoard, depth, list);
		
		eTime = get_current_time();
		
		RXHashValue entry;
		if(hTable->get(sBoard.board, type_hashtable, entry) && entry.depth>=depth) {
			int type = EXACT;
			
			int score = list->next->score;
			
			if(entry.lower == entry.upper) {
				if(abort.load())
					type = INTERRUPT;
			} else if(list->next->score == entry.lower || entry.upper == MAX_SCORE) {
				type = SUPERIOR;
				score = entry.lower;
			} else if(list->next->score == entry.upper || entry.lower == MAX_SCORE){
				type = INFERIOR;
				score = entry.upper;
			}
			
			*log << display(sBoard.board, type, depth, score, eTime, eTime - time_startLevel) << std::endl;
		}
		
		best_answer.position = list->next->position;
		best_answer.score = list->next->score;
		best_answer.depth = list->next->depth;
		best_answer.selectivity = CONFIDENCE[list->next->selectivity];
		std::ostringstream buf;
		hTable->mainline(buf, sBoard.board, type_hashtable);
		best_answer.mainLine = buf.str();
		
		best_answer.nodes += sBoard.board.n_nodes;
		
		if(abort.load() )
			break;
		
		//update probable time for next depth
		
        time_nextLevel = pTime_next_level(sBoard.board, eTime - time_startLevel, depth, depth+2);;
		
		if(depth>6)			
			if(probable_timeout(time_nextLevel)) {
				abort.store(true);
                *log << "[" << get_current_time() << "] " << "        RXEngine ID : likely timeout" << std::endl;

				break;
			}
		
		//stop conditions EndGame
		if(fabs(list->next->score) >= ((MAX_SCORE-1) - 64*VALUE_DISC)) {
			break;
		}
		
		
		if(fabs(list->next->score)>48*VALUE_DISC && depth>=18 && sBoard.board.n_empties<38)
			break;
		
		
	} while((depth +=2)<=max_depth);
	
}


void RXEngine::aspiration_search(RXBBPatterns& sBoard, const int depth, RXMove* list) {
	
	const int s_alpha = (search_alpha <= -64*VALUE_DISC? -MAX_SCORE: search_alpha);
	const int s_beta  = (search_beta  >=  64*VALUE_DISC?  MAX_SCORE: search_beta);
	
	int alpha = std::max(s_alpha, std::min(s_beta-1, list->next->score - MG_MOVING_WINDOW*VALUE_DISC));
	int beta  = std::min(s_beta, std::max(s_alpha+1, list->next->score + MG_MOVING_WINDOW*VALUE_DISC));
	
	
	MG_PVS_root(sBoard, depth, alpha, beta, list);
	
	int left = 2;
	int right = 2;

	while (!abort.load()  && !(alpha < list->next->score && list->next->score < beta)) {
		
		if (list->next->score <= alpha) {

			if(alpha <= s_alpha)
				break;
								
			alpha = list->next->score - (MG_MOVING_WINDOW*left)*VALUE_DISC;
			left *=2;
			
		} else if (list->next->score >= beta) {
			
			if(beta >= s_beta)
				break;

			beta  = list->next->score + (MG_MOVING_WINDOW*right)*VALUE_DISC;
			right *=2;
		}
		
		
		alpha = std::max(s_alpha, std::min(s_beta-1, alpha));
		beta  = std::min(s_beta, std::max(s_alpha+1, beta ));

		MG_PVS_root(sBoard, depth, alpha, beta, list);

	};

}


 // avec la selectivite et de l'extension de recherche, on ne peut faire totalement confiance a
 // un coup etudie en null window (pas d'extension de recherche)
 // c.a.d. on ne profite pas de la recherche NWS pour trouver un meilleur coup sauf si score>beta.
 //
 // root
 
void RXEngine::MG_PVS_root(RXBBPatterns& sBoard, const int depth,  int alpha, int beta, RXMove* list) {		
	
	//assert(alpha>=-MAX_SCORE && beta<=MAX_SCORE);
		
	int selectivity = 0;				//1.1
			
	RXMove* iter = list->next;
	int bestmove = iter->position;
	
	int lower = alpha;
	int upper = beta;
	
	bool selective_cutoff = false;
	bool child_selective_cutoff = false;
	
	//first move
	first_move = true;
	
	sBoard.do_move(*iter);
	
	int bestscore = -MG_PVS_deep(0, sBoard, true, selectivity, depth-1, child_selective_cutoff, -upper, -lower, false);
	
	sBoard.undo_move(*iter);
	
	if(!abort.load()  && bestscore != -INTERRUPT_SEARCH) {
		
		
		if(search_client == RXSearch::kGGSMode) {	// GGS mode
			
			if(dependent_time && depth>13) {
				if(use_pv_extension && depth+pv_extension>=sBoard.board.n_empties && bestscore%VALUE_DISC == 0)
					manager->sendMsg(showBestmove(depth, true, 0, lower, upper, bestscore, bestmove));
				else	
					manager->sendMsg(showBestmove(depth, false, 0, lower, upper, bestscore, bestmove));
			}
		}
		
		if(bestscore > lower)
			lower = bestscore;
		
		if (child_selective_cutoff)
			selective_cutoff = true;
		
		//other moves
		first_move = false;
		int score;
		for(iter = iter->next; !abort.load()  && lower<upper && iter != NULL; iter = iter->next) {
			
			sBoard.do_move(*iter);
			
			//multi_PV pv == true ???
//			score = -MG_PVS_deep(0, sBoard, true, selectivity, depth-1, child_selective_cutoff, -lower-1, -lower, false);

			//simple_PV pv == false ???
			score = -MG_PVS_deep(0, sBoard, false, selectivity, depth-1, child_selective_cutoff, -lower-1, -lower, false);

			
			if(!abort.load()  && lower < score && score < upper) {
				
				if(search_client == RXSearch::kGGSMode) {	// GGS mode
					
					if(dependent_time && depth>13)
						manager->sendMsg("         " + RXMove::index_to_coord(iter->position) + " maybe better? ");
				}
				
				
				extra_time++;
				int _lower = child_selective_cutoff? lower : iter->score;
				score = -MG_PVS_deep(0, sBoard, true, selectivity, depth-1, child_selective_cutoff, -upper, -_lower, false);
				extra_time--;
				
				
			}
			
			
			
			sBoard.undo_move(*iter);
			
			if (!abort.load() && score != -INTERRUPT_SEARCH) {
				
				if(score > bestscore) {
					bestmove = iter->position;
					bestscore = score;
					
					if(search_client == RXSearch::kGGSMode) {	// GGS mode
						if(dependent_time && depth>13) {
							if(use_pv_extension && depth+pv_extension>=sBoard.board.n_empties && bestscore%VALUE_DISC == 0)
								manager->sendMsg(showBestmove(depth, true, 0, lower, upper, bestscore, bestmove));
							else	
								manager->sendMsg(showBestmove(depth, false, 0, lower, upper, bestscore, bestmove));
						}
					}
					
					if (bestscore > lower)
						lower = bestscore;
				}
			}
			
			if (child_selective_cutoff)
				selective_cutoff = true;
			
		}
		
		if(bestscore>=beta)
			selective_cutoff = child_selective_cutoff;
		
		
		//move to front bestmove
		list->sort_bestmove(bestmove);
		list->next->score = bestscore;		
		list->next->selectivity = selective_cutoff? MG_SELECT: NO_SELECT;
		list->next->depth = depth;
		
		hTable->update(sBoard.board.hashcode(), true, type_hashtable, selective_cutoff? MG_SELECT: NO_SELECT, depth, alpha, beta, bestscore, bestmove);
		
		
	}
	
}

int RXEngine::MG_PVS_deep(int threadID, RXBBPatterns& sBoard, const bool pv, const int selectivity, const int depth, bool& selective_cutoff, int alpha, int beta, const bool passed) {

	//assert(alpha>=-MAX_SCORE && beta<=MAX_SCORE);
	
	

	if(abort.load()  || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;

	if(threadID == 0)
		pthread_yield_np(); //process->yield();
	
	//time gestion
	if(dependent_time && get_current_dependentTime() > time_limit()) {
		abort.store(true);
		return INTERRUPT_SEARCH;
	}
			
	RXBitBoard& board = sBoard.board;
	selective_cutoff = false;

	int bestmove = NOMOVE;
	int lower = alpha;
	int upper = beta;
	
	
	//synchronized acces
	RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
	if(hTable->get(hash_code, type_hashtable, entry)) {
		
		if(!pv && entry.depth >= depth) {
			
			if(entry.lower > lower) {
				
				lower = entry.lower;
				if(lower >= upper) {
					
					if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
						selective_cutoff = true;
					
					return lower;
				}
			}
			
			if(entry.upper < upper) {
				
				upper = entry.upper;
				if(upper <= lower) {
					
					if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
						selective_cutoff = true;
					
					return  upper;
				}
			}
			
		}
		
		bestmove = entry.move;
	}

	//	IID
	if(pv && bestmove == NOMOVE && depth > 6) {
		bool child_selective_cutoff = false;
		
		MG_PVS_deep(threadID, sBoard, pv, selectivity, depth - 2, child_selective_cutoff, lower, upper, passed);

		if(abort.load() || thread_should_stop(threadID))
			return INTERRUPT_SEARCH;

		if(hTable->get(hash_code, type_hashtable, entry))
			bestmove = entry.move;
	}
	
	
	RXMove* list = threads[threadID]._move[board.n_empties];
	int n_Moves = 0;

	if(bestmove != PASS) {
		
				
		RXMove* move = list + 1;
		RXMove* previous = list;
	
		//ENHANCED TRANSPOSITION CUTOFF
		if(bestmove != NOMOVE) {
			board.n_nodes++;

			((board).*(board.generate_flips[bestmove]))(*move);
			
			//synchronized acces
			if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && !pv && entry.depth>=depth-1) {
				
				/*
				BE CARREFUL : (board.n_empties-1)-(depth-1) == board.n_empties-depth
				*/
				if(-entry.upper >= upper) {
					if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
					   selective_cutoff = true;
					return -entry.upper ;
				}
				
			}
			
			previous = previous->next = move++;
			n_Moves++;
		}
			
		//for all empty square
        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
		for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next) {
            if(bestmove != empties->position && (legal_movesBB & 1ULL<<empties->position)) {
                ((board).*(board.generate_flips[empties->position]))(*move);
					
				board.n_nodes++;
				
				move->score = 0;
				
				//synchronized acces
				if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && !pv && entry.depth>=depth-1) {
					
					move->score = -3*VALUE_DISC;

					/*
					BE CARREFUL : (board.n_empties-1)-(depth-1) == board.n_empties-depth
					*/
					if(-entry.upper >= upper) {
					   if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
							selective_cutoff = true;
						return -entry.upper ;
					}
					
					if(-entry.lower<=lower)
						move->score = 2*VALUE_DISC;
					

				}
				
				previous = previous->next = move++;
				n_Moves++;
	
			}
		}
				
		previous->next = NULL;
			
	}

	int bestscore = UNDEF_SCORE;
	bool child_selective_cutoff = false;
	bool pv_ext_flag = false;

	if (n_Moves == 0) {
			
		if (passed) {
			board.n_nodes--;
			bestscore = board.final_score();
			alpha = -(beta = +MAX_SCORE);
			bestmove = NOMOVE;
			pv_ext_flag = true;
		} else {
			board.do_pass();
			board.n_nodes++;
			
			pv_extension++;
			if(depth <= MG_DEEP_TO_SHALLOW)
				bestscore = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, true);
			else
				bestscore = -MG_PVS_deep(threadID, sBoard, pv, selectivity, depth-1, child_selective_cutoff, -upper, -lower, true);
			pv_extension--;

			board.do_pass();
			bestmove = PASS;
			
			if(child_selective_cutoff)
				selective_cutoff = true;
		}
		
	} else {

		if(pv && use_pv_extension && board.n_empties-1 <= pv_extension) {
				
			pv_ext_flag = true;
			
			if(bestmove != NOMOVE) {
				list = list->next;

				((board).*(board.generate_flips[bestmove]))(*list);
						
				board.do_move(*list);
				bestscore = -EG_pv_extension(threadID, board, pv, -upper, -lower, false);						
				board.undo_move(*list);

				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;
				
				if (bestscore>lower)
					lower = bestscore;

				n_Moves--;

			}
			
			if(lower<upper) {
										
				if(n_Moves>0) {	
						
					if(n_Moves>1) {
						
						//sort move
						const int p = board.player;
						const int o = p^1;
						
						//sort list by mobility
						for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
								
							board.n_nodes++;

							const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
								
                            iter->score +=  (RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC); // - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/4;
						}
								
						list->sort_by_score();		
					}
				
			
					int score = UNDEF_SCORE;
					for(RXMove* iter = list->next; lower<upper && iter != NULL; iter = iter->next) {
						
						board.do_move(*iter);
								
						if(bestscore == UNDEF_SCORE) {
							score = -EG_pv_extension(threadID, board, pv, -upper, -lower, false);						
						} else {
							
							//bug 2/10/2009 : avec -lower-1 ????? pas d'explication logique
							score = -EG_pv_extension(threadID, board, false, -lower-VALUE_DISC, -lower, false);
																	
							if(lower < score && score < upper)
								score = -EG_pv_extension(threadID, board, pv, -upper, -score, false);

						}
									
						board.undo_move(*iter);

						//interrupt search
						if(abort.load()  || thread_should_stop(threadID))
							return INTERRUPT_SEARCH;
						
						if (score>bestscore) {
							bestmove = iter->position;
							bestscore = score;
							if (bestscore>lower)
								lower = bestscore;
						}


					}
				}
			}

		} else {
			
			bool moves_sorting = false;
				
			if(bestmove != NOMOVE) {
				
				/* first move */
				list = list->next;

				((sBoard).*(sBoard.update_patterns[list->position][board.player]))(*list);

				sBoard.do_move(*list);
				
				if(depth <= MG_DEEP_TO_SHALLOW)
					bestscore = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
				else
					bestscore = -MG_PVS_deep(threadID, sBoard, pv, selectivity, depth-1, child_selective_cutoff, -upper, -lower, false);

				sBoard.undo_move(*list);

				
				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;

				//assert(bestscore != -INTERRUPT_SEARCH);
				
				bestmove = list->position;
				
				if(bestscore > lower)
					lower = bestscore;

				if (child_selective_cutoff)
					selective_cutoff = true;
				
				n_Moves--;
			}

			if(lower < upper) {
			
				if(!moves_sorting) {
					if(n_Moves > 1) {
						//sort					
					
						if(depth>=10) {
							
							int threshold_Alpha = -MAX_SCORE;
							int threshold_Beta  =  MAX_SCORE;
							probcut_bounds(board, 0, 4, 0, 0, threshold_Alpha, threshold_Beta); //selectivity 0 = 72%
							
							int _lower = std::max(-MAX_SCORE, lower+threshold_Alpha*2);

							if(_lower<= sBoard.get_score()) { // && eval_position<=(beta+threshold_ff_Beta*4)) { //alpha 95% / beta 99%

								//stable position -> sorting on evaluation

								for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {

									((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);

									//stable move -> sorting on evaluation
									sBoard.do_move(*iter);
                                    
                                    if(depth >= 26) {
                                        
                                        if((depth & 1) == 0)
                                            iter->score += PVS_check(threadID, sBoard, 4, -MAX_SCORE , -_lower, false);
                                        else
                                            iter->score += PVS_check(threadID, sBoard, 5, -MAX_SCORE , -_lower, false);
                                        
                                    } else if(depth >= 22) {
										
										if((depth & 1) == 0)
											iter->score += PVS_check(threadID, sBoard, 4, -MAX_SCORE , -_lower, false);
										else
											iter->score += PVS_last_three_ply(threadID, sBoard, -MAX_SCORE , -_lower, false);
										

									} else if(depth >= 18) {
										
										if((depth & 1) == 0)
											iter->score += alphabeta_last_two_ply(threadID, sBoard, -MAX_SCORE , -_lower, false);
										else
											iter->score += PVS_last_three_ply(threadID, sBoard, -MAX_SCORE , -_lower, false);
										
									} else  if((depth & 1) == 0) {
										
										iter->score += alphabeta_last_two_ply(threadID, sBoard, -MAX_SCORE , -_lower, false);
										
									} else {
										
										RXMove& lastMove = threads[threadID]._move[board.n_empties][1];
                                        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
										int bestscore1 = UNDEF_SCORE; //masquage
										for(RXSquareList* empties = board.empties_list->next; bestscore1<-_lower && empties->position != NOMOVE; empties = empties->next)
                                            if(legal_movesBB & 1ULL<<empties->position) { 
                                                ((board).*(board.generate_flips[empties->position]))(lastMove);
                                                ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(lastMove);
												board.n_nodes++;

												int score= -sBoard.get_score(lastMove);	
												if (score>bestscore1) {
													bestscore1 = score;
												}
															 
											}

										if(bestscore1 == UNDEF_SCORE) {
											//PASS
											sBoard.board.do_pass();
											iter->score -= sBoard.get_score();
											sBoard.board.do_pass();

										} else {
											iter->score += bestscore1;
										}
									}

									sBoard.undo_move(*iter);
								

								}
								
							} else {
													
								for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {
									board.n_nodes++;
									
									((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
									iter->score += sBoard.get_score(*iter);
								}
							}

						} else {
						
							for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {
								board.n_nodes++;
								
								((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
								iter->score += sBoard.get_score(*iter);
							}
							
						}
					
					} else if(n_Moves == 1) { 
						((sBoard).*(sBoard.update_patterns[list->next->position][board.player]))(*(list->next));
					}
				}
				
				if(bestscore == UNDEF_SCORE) { //first move

					RXMove* previous_move = list;
					RXMove* move = previous_move->next;
					
					RXMove* previous_iter = move;
					for(RXMove* iter = previous_iter->next ; iter != NULL; iter = (previous_iter = iter)->next) {
						if(iter->score < move->score) {
							move = iter;
							previous_move = previous_iter;
						}
					}

					if(previous_move != list) {
						//move to front
						previous_move->next = move->next;
						move->next = list->next;
						list->next = move;
					}
						
					bestmove = move->position;
					
					sBoard.do_move(*move);
					if(depth <= MG_DEEP_TO_SHALLOW)
						bestscore = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
					else
						bestscore = -MG_PVS_deep(threadID, sBoard, pv, selectivity, depth-1, child_selective_cutoff, -upper, -lower, false);
					sBoard.undo_move(*move);

					//interrupt search
					if(abort.load()  || thread_should_stop(threadID))
						return INTERRUPT_SEARCH;

					//assert(bestscore != -INTERRUPT_SEARCH);
					
					if(bestscore>lower)
						lower = bestscore;

					if (child_selective_cutoff)
						selective_cutoff = true;
						
					// next move
					list = list->next;
				}
				
				int score;
				for(;!abort.load()  && lower < upper && list->next != NULL; list = list->next) {
					
					RXMove* move = list->next;
					
					if(move->next != NULL) {	//more 1 move
					
						// Split? 
						if(activeThreads > 1 && depth>(MIN_DEPTH_SPLITPOINT-1) && !abort.load()
						   && !thread_should_stop(threadID) && idle_thread_exists(threadID)
						   && split(sBoard, pv, 0, depth, selectivity, selective_cutoff, child_selective_cutoff,
									lower, upper, bestscore, bestmove, list, threadID, RXSplitPoint::MID_PVS))
							
							break;
						
						
						RXMove* previous_move = list;

						RXMove* previous_iter = move;
						for(RXMove* iter = previous_iter->next ; iter != NULL; iter = (previous_iter = iter)->next) {
							if(iter->score < move->score) {
								move = iter;
								previous_move = previous_iter;
							}
						}
						
						if(previous_move != list) {
							//move to front
							previous_move->next = move->next;
							move->next = list->next;
							list->next = move;
						}
						
					}

					
					sBoard.do_move(*move);
					
					if(depth <= MG_DEEP_TO_SHALLOW) {
						score = -MG_PVS_shallow(threadID, sBoard, false, depth-1, -lower-1, -lower, false);
                        if(lower < score && score < upper) {
                            if(pv && use_pv_extension && board.n_empties-(depth-1)<=pv_extension) {
                                score = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
                            } else {
                                score = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -score, false);
                            }
                        }
					} else {
							
						score = -MG_NWS_XProbCut(threadID, sBoard, 0, selectivity, depth-1, child_selective_cutoff, -lower-1, false);

						if(lower < score && score < upper)
								score = -MG_PVS_deep(threadID, sBoard, pv, selectivity, depth-1, child_selective_cutoff, -upper, -lower, false);
						
					}
					
					sBoard.undo_move(*move);

					//interrupt search
					if(abort.load()  || thread_should_stop(threadID))
						return INTERRUPT_SEARCH;

					//assert(score != -INTERRUPT_SEARCH);
					
					if (score>bestscore) {
						bestmove = move->position;
						bestscore = score;
						if (bestscore>lower)
							lower = bestscore;
					}
					
					if ( child_selective_cutoff )
						selective_cutoff = true;

				 }
			}
		
		}

	}

	//interrupt search
	if(abort.load()  || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;

	//assert(bestscore != -INTERRUPT_SEARCH);
	
	if(bestscore>=beta)
		selective_cutoff = child_selective_cutoff;
	
	if(pv_ext_flag) {
		hTable->update(   hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta,  bestscore, bestmove);
		hTable_PV->update(hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta,  bestscore, bestmove);
	} else {
		hTable->update(   hash_code, pv, type_hashtable, selective_cutoff? MG_SELECT : NO_SELECT, depth, alpha, beta,  bestscore, bestmove);
		hTable_PV->update(hash_code, pv, type_hashtable, selective_cutoff? MG_SELECT : NO_SELECT, depth, alpha, beta,  bestscore, bestmove);
	}
		
	return bestscore;

}

// MG_SP_search_DEEP() is used to search from a PV split point.  This function
// is called by each thread working at the split point.  It is similar to
// the normal EG_PVS_deep() function, but simpler.  Because we have already
// probed the hash table and searched the first move before splitting, we
// don't have to repeat all this work in MG_SP_search_DEEP().  We also don't
// need to store anything to the hash table here:  This is taken care of
// after we return from the split point.

void RXEngine::MG_SP_search_DEEP(RXSplitPoint* sp, const unsigned int threadID) {
		
	
	RXBBPatterns& sBoard = sp->sBoardStack[threadID];
	sBoard = *(sp->sBoard); //operator=
	RXBitBoard& board = sBoard.board;
	board.n_nodes = 0;
	
	//here sp->beta is const
    while(sp->alpha < sp->beta && !abort.load()  && !thread_should_stop(threadID)) {
        
        pthread_mutex_lock(&(sp->lock));
        
        RXMove* move;
        if(sp->list != NULL && sp->list->next != NULL) {
            
            RXMove* previous_move = sp->list;
            move = previous_move->next;
            
            RXMove* previous_iter = move;
            for(RXMove* iter = previous_iter->next ; iter != NULL; iter = (previous_iter = iter)->next) {
                if(iter->score < move->score) {
                    move = iter;
                    previous_move = previous_iter;
                }
            }
            
            if(previous_move != sp->list) {
                //move to front
                previous_move->next = move->next;
                move->next = sp->list->next;
                sp->list->next = move;
            }
            
            sp->list = sp->list->next;
            
        } else {
            pthread_mutex_unlock(&(sp->lock));
            break;
        }
        
        
        bool child_selective_cutoff = sp->child_selective_cutoff;
        
        pthread_mutex_unlock(&(sp->lock));
        
        
        sBoard.do_move(*move);
        
        int score;
        int alpha = sp->alpha; //local copy
        
        if(sp->depth <= MG_DEEP_TO_SHALLOW) {
            
            score = -MG_PVS_shallow(threadID, sBoard, false, sp->depth-1, -alpha-1, -alpha, false);
            
            if(alpha < score && score < sp->beta) {
                if(sp->pv && use_pv_extension && board.n_empties-(sp->depth-1)<=pv_extension) {
                    score = -MG_PVS_shallow(threadID, sBoard, sp->pv, sp->depth-1, -sp->beta, -sp->alpha, false);
                } else {
                    score = -MG_PVS_shallow(threadID, sBoard, sp->pv, sp->depth-1, -sp->beta, -score, false);
                }
            }
        } else {
            
            //			if(sp->depth <=  MAX_DEPTH_USE_PROBCUT)
            //				score = -MG_NWS_XProbCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, sp->depth-1, child_selective_cutoff, -alpha-1, false);
            //			else
            //				score = -MG_PVS_deep(threadID, sBoard, false, sp->selectivity, sp->depth-1, child_selective_cutoff, -alpha-1, -alpha, false);
            //
            //			if(alpha < score && score < sp->beta)
            //				if(sp->depth <=  MAX_DEPTH_USE_PROBCUT)
            //					score = -MG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, sp->depth-1, child_selective_cutoff, -sp->beta, -sp->alpha, false);
            //				else
            //					score = -MG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, sp->depth-1, child_selective_cutoff, -sp->beta, child_selective_cutoff? -sp->alpha : -score, false);
            
            score = -MG_NWS_XProbCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, sp->depth-1, child_selective_cutoff, -alpha-1, false);
            
            if(alpha < score && score < sp->beta)
                score = -MG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, sp->depth-1, child_selective_cutoff, -sp->beta, -sp->alpha, false);
            
            //			do {
            //				alpha = sp->alpha;
            //				score = -MG_NWS_XProbCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, sp->depth-1, child_selective_cutoff, -alpha-1, false);
            //			} while (sp->alpha>alpha && score>alpha);
            //
            //			if(alpha < score && score < sp->beta)
            //					score = -MG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, sp->depth-1, child_selective_cutoff, -sp->beta, -sp->alpha, false);
            
        }
        
        sBoard.undo_move(*move);
        
        
        if(abort.load()  || thread_should_stop(threadID))
            break;
        
        sp->child_selective_cutoff = child_selective_cutoff;
        
        if(sp->child_selective_cutoff)
            sp->selective_cutoff = true;

        //first without mutex
        if((score > sp->bestscore) || (!sp->selective_cutoff && child_selective_cutoff)) {
 
 
            //update
            pthread_mutex_lock(&(sp->lock));
            
            sp->child_selective_cutoff = child_selective_cutoff;
            
            if(sp->child_selective_cutoff)
                sp->selective_cutoff = true;
            
            // New best move?
            if(score > sp->bestscore) {
                sp->bestscore = score;
                sp->bestmove = move->position;
                if(score > sp->alpha) {
                    
                    if(score >= sp->beta) {
                        sp->explored =true;
                    } else {
                        sp->alpha = score;
                    }
                }
            }
            
            pthread_mutex_unlock(&(sp->lock));
        }
    }
	
    pthread_mutex_lock(&(sp->lock));
	
	sp->sBoard->board.n_nodes += board.n_nodes;
	
    sp->slaves[threadID] = false;
	sp->n_Slaves--;
	
    pthread_mutex_unlock(&(sp->lock));
} 


int RXEngine::MG_PVS_shallow(int threadID, RXBBPatterns& sBoard, const bool pv, const int depth, int alpha, int beta, const bool passed) {

	//assert(alpha>=-MAX_SCORE && beta<=MAX_SCORE);
	
	

	RXBitBoard& board = sBoard.board;
	
	int bestmove = NOMOVE;
	int hashmove = NOMOVE;

	int upper = beta;
	int lower = alpha;
	
	//synchronized acces
	RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
	if(hTable->get(hash_code, type_hashtable, entry)) {

		if(!pv && entry.depth >= depth) {
			
			
			if(entry.lower > lower) {
								
				lower = entry.lower;
				if(lower >= upper) {
					return lower;
				}
			}
		
			if(entry.upper < upper) {
				
				upper = entry.upper;
				if(upper <= lower) {
					return  upper;
				}
			}
			
		}
		
		hashmove = entry.move;
	}

	int bestscore = UNDEF_SCORE;

	if(depth == 0) {
		/*previous move == PASS*/
		if(pv && use_pv_extension && board.n_empties <= pv_extension) {
			return EG_pv_extension(threadID, board, pv, lower, upper, true);			
		} else {			
			return sBoard.get_score();
		}
	}
		
	bool pv_ext_flag = false;

	if(hashmove != PASS) {

		RXMove* list = threads[threadID]._move[board.n_empties];
		RXMove* move = list + 1;

		
		if(pv && use_pv_extension && board.n_empties-1 <= pv_extension) {

			pv_ext_flag = true;
			
			if(hashmove != NOMOVE) {

				bestmove = hashmove;

				((board).*(board.generate_flips[bestmove]))(*move);
						
				board.do_move(*move);
				bestscore = -EG_pv_extension(threadID, board, pv, -upper, -lower, false);						
				board.undo_move(*move);
				
				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;
				
				if (bestscore>lower)
					lower = bestscore;

			}
			
			if(lower<upper) {
					
				//list moves
				RXMove* previous = list;
				int n_Moves = 0;
                const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);

				for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
                    if(bestmove != empties->position && (legal_movesBB & 1ULL<<empties->position)) {
                        ((board).*(board.generate_flips[empties->position]))(*move);
						previous = previous->next = move++;
						n_Moves++;
					}
								
				previous->next = NULL;
					
				if(n_Moves>0) {	
						
						
					if(n_Moves>1) {
						
						//sort move
						const int p = board.player;
						const int o = p^1;
						
						//sort list by mobility
						for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
								
							board.n_nodes++;

							const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                            const unsigned long long o_discs = board.discs[o] ^ iter->flipped;
								
                            iter->score = (RXBitBoard::get_mobility(o_discs, p_discs)<<2) - (RXBitBoard::get_corner_stability(p_discs)); // - (RXBitBoard::local_Parity(o_discs, p_discs, iter->position)^1);
						}
								
						list->sort_by_score();		
					}
				
			
					int score = UNDEF_SCORE;
					for(RXMove* iter = list->next; lower<upper && iter != NULL; iter = iter->next) {

						board.do_move(*iter);


						if(bestscore == UNDEF_SCORE) {
							score = -EG_pv_extension(threadID, board, pv, -upper, -lower, false);						
						} else {	
						
							// 2/10/2009 bug : - lower - 1 ??????
							score = -EG_pv_extension(threadID, board, false, -lower-VALUE_DISC, -lower, false);
																								
							if(lower < score && score < upper)
								score = -EG_pv_extension(threadID, board, pv, -upper, -score, false);

						}
									
						board.undo_move(*iter);

						//interrupt search
						if(abort.load()  || thread_should_stop(threadID))
							return INTERRUPT_SEARCH;
						
						if (score>bestscore) {
							bestmove = iter->position;
							bestscore = score;
							if (bestscore>lower)
								lower = bestscore;
						}


					}
				}
			}
			
			if(bestscore == UNDEF_SCORE) { // PASS
				board.do_pass();
				bestscore = -EG_pv_extension(threadID, board, pv, -upper, -lower, true);
				board.do_pass();
			}
				
			//interrupt search
			if(abort.load()  || thread_should_stop(threadID))
				return INTERRUPT_SEARCH;
			
		} else {
			
			if(depth == 1) {
			
				if(hashmove != NOMOVE) {

					bestmove = hashmove;

                    ((board).*(board.generate_flips[bestmove]))(*move);
                    ((sBoard).*(sBoard.update_patterns[bestmove][board.player]))(*move);
					board.n_nodes++;
					bestscore= -sBoard.get_score(*move);	

					if (bestscore>lower)
						lower = bestscore;
				}
				
                const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);

				for(RXSquareList* empties = board.empties_list->next; lower < upper &&  empties->position != NOMOVE; empties = empties->next) {
                    if(empties->position != hashmove && (legal_movesBB & 1ULL<<empties->position)) {
                        
                        ((board).*(board.generate_flips[empties->position ]))(*move);
                        ((sBoard).*(sBoard.update_patterns[empties->position ][board.player]))(*move);
						board.n_nodes++;
						int score= -sBoard.get_score(*move);
				
						if (score>bestscore) {
							bestmove = empties->position;
							bestscore = score;
							if (bestscore>lower)
								lower = bestscore;
						}
					}
				}
			
			} else {

				if(hashmove != NOMOVE) {
					
					bestmove = hashmove;

					((board).*(board.generate_flips[bestmove]))(*move);
					((sBoard).*(sBoard.update_patterns[bestmove][board.player]))(*move);

					sBoard.do_move(*move);
					
					bestscore = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
						
					sBoard.undo_move(*move);

					if (bestscore>lower)
						lower = bestscore;
									
				}
				
				if(lower<upper) {
					//sort before use pv-extension
					if(pv && use_pv_extension && board.n_empties-depth<=pv_extension) {

						RXMove* list = threads[threadID]._move[board.n_empties];
						RXMove *move = list + 1, *previous = list;
						int nMoves = 0;
						
                        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);

						for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
                            if(empties->position != hashmove && (legal_movesBB & 1ULL<<empties->position)) { ((board).*(board.generate_flips[empties->position]))(*move);
								previous = previous->next = move++;
								nMoves++;
							}
						
						previous->next = NULL;
						
						//sort on mobility
						if(nMoves>0) {	
							
							
							if(nMoves>1) {
							
								const int p = board.player;
								const int o = p^1;
							
								//sort list by mobility
								for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
									
									board.n_nodes++;

									const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                                    const unsigned long long o_discs = board.discs[o] ^ iter->flipped;
									
                                    iter->score = (RXBitBoard::get_mobility(o_discs, p_discs)<<2) - (RXBitBoard::get_corner_stability(p_discs)); // - (RXBitBoard::local_Parity(o_discs, p_discs, iter->position)^1);
								}
									
								list->sort_by_score();
							}

							int score;
							for(RXMove* iter = list->next;  lower < upper && iter != NULL; iter = iter->next) {
								
							
								((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
								sBoard.do_move(*iter);
								
								
								if(bestscore == UNDEF_SCORE) {
									score = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
								} else {
									score = -MG_PVS_shallow(threadID, sBoard, false, depth-1, -lower-1, -lower, false);

									if(lower < score && score < upper)
											score = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
										
								}
								
								sBoard.undo_move(*iter);

								
								
								if (score>bestscore) {
									bestmove = iter->position;
									bestscore = score;
									if (bestscore>lower)
										lower = bestscore;
								}


							}
						
						}
						
					} else {
					

						int score = UNDEF_SCORE;
                        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);

						for(RXSquareList* empties = board.empties_list->next; lower < upper && empties->position != NOMOVE; empties = empties->next) {
                            if (empties->position != hashmove && (legal_movesBB & 1ULL<<empties->position)) { ((board).*(board.generate_flips[empties->position]))(*move);
	
								((sBoard).*(sBoard.update_patterns[move->position][board.player]))(*move);
								sBoard.do_move(*move);
								
								
								if(bestscore == UNDEF_SCORE) {
									score = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, false);
								} else {
									
									score = -MG_PVS_shallow(threadID, sBoard, false, depth-1, -lower-1, -lower, false);

									if(lower < score && score < upper)
											score = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -score, false);
										
								}
								
								sBoard.undo_move(*move);

								if (score>bestscore) {
									bestmove = move->position;
									bestscore = score;
									if (bestscore>lower)
										lower = bestscore;
								}


							}
						}
					}
				}
			}
		}
	}
	
	if(bestscore == UNDEF_SCORE) {
		 
		if(passed) {
			board.n_nodes--;
			alpha = -MAX_SCORE;
			beta = MAX_SCORE;
			bestmove = NOMOVE;
			bestscore = sBoard.final_score();
			pv_ext_flag = true;
		} else {
			board.n_nodes++;
			board.do_pass();
			
			pv_extension++;
			bestscore = -MG_PVS_shallow(threadID, sBoard, pv, depth-1, -upper, -lower, true);
			pv_extension--;
			
			board.do_pass();
			bestmove = PASS;
								
		}
	}

	
	if(pv_ext_flag)
		hTable->update(hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta,  bestscore, bestmove);
	else
		hTable->update(hash_code, pv, type_hashtable, NO_SELECT, depth, alpha, beta,  bestscore, bestmove);

	return bestscore;

}


/*
Null Window Search  + XProbCut
*/
int RXEngine::MG_NWS_XProbCut(int threadID, RXBBPatterns& sBoard, const int pvDev, const int selectivity, const int depth, bool& selective_cutoff, int alpha, const bool passed) {

	//assert(alpha>=-MAX_SCORE);

	if(abort.load() || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;
	
	//time gestion
	if (dependent_time && get_current_dependentTime() > time_limit()) {
		abort.store(true);
		return INTERRUPT_SEARCH;
	}
	

	RXBitBoard& board = sBoard.board;
	selective_cutoff = false;
	
	int bestmove = NOMOVE;

	//synchronized acces
	RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
	if(hTable->get(hash_code, type_hashtable, entry)) {
	
		if(entry.depth >= depth) {
			
			if(entry.lower > alpha) {

				if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
					selective_cutoff = true;
				
				return entry.lower;
			}
		
			if(entry.upper <= alpha) {

				if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
					selective_cutoff = true;
				
				return  entry.upper;
			}
			
		}
		
		bestmove = entry.move;
	}
	
	
	//param mpc
	int lower_probcut, upper_probcut;
	probcut_bounds(board, selectivity, depth, pvDev, alpha, lower_probcut, upper_probcut);
	int probcut_depth = (depth/4)*2 + (depth&1);


	if(bestmove != NOMOVE && entry.selectivity >= selectivity && entry.depth>=probcut_depth) {
	
		if(entry.lower >= upper_probcut) {
			selective_cutoff = true;
			return alpha+1;
		}
			
//		if(entry.upper <= lower_probcut) {
//			selective_cutoff = true;
//			return  alpha;
//		}
	}

	
	RXMove* list = threads[threadID]._move[board.n_empties];
	int n_Moves = 0;

	if(bestmove != PASS) {
		
		if(bestmove != NOMOVE || depth > 10) { //ETC
				
			RXMove* move = list + 1;
			RXMove* previous = list;


		
			//ENHANCED TRANSPOSITION CUTOFF
			if(bestmove != NOMOVE) {
						
				board.n_nodes++;
									
				((board).*(board.generate_flips[bestmove]))(*move);
								
				//synchronized acces
				if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && entry.depth >= depth-1) {
					
					/*
					BE CARREFUL : (board.n_empties-1)-(depth-1) == board.n_empties-depth
					*/
					if(-entry.upper > alpha) {
						if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
							selective_cutoff = true;

						return -entry.upper ;
					}
				}
				
				previous = previous->next = move++;
				n_Moves++;

			}
				
			//for all empty square
            const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
			for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
                if(bestmove != empties->position && (legal_movesBB & 1ULL<<empties->position)) {
                    
                    ((board).*(board.generate_flips[empties->position]))(*move);
						
					board.n_nodes++;

					move->score = 0;
					
					//synchronized acces
					if( hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && entry.depth>=depth-1) {

						
						if(-entry.upper > alpha) {
							if(entry.selectivity != NO_SELECT || (use_pv_extension && board.n_empties-depth <= pv_extension && entry.depth < board.n_empties))
								selective_cutoff = true;

							return -entry.upper ;
						}
                        
                        move->score = -3*VALUE_DISC;

						if(-entry.lower<=alpha)
							move->score = 2*VALUE_DISC;
						
					}
					
					previous = previous->next = move++;
					n_Moves++;

				}

			previous->next = NULL;
			
		} else {
			
			n_Moves = board.moves_producing(list);
			
		}
				
	}

	int bestscore = UNDEF_SCORE;
	bool child_selective_cutoff = false;


	if(n_Moves == 0) {
		 //PASS
		if(passed) {
			board.n_nodes--;
			bestscore = sBoard.final_score();
			hTable->update(hash_code, false, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, -MAX_SCORE, MAX_SCORE,  bestscore, bestmove);
			return bestscore;
		} else {
			board.n_nodes++;
			board.do_pass();
			if(depth > MIN_DEPTH_USE_PROBCUT) {
				bestscore = -MG_NWS_XProbCut(threadID, sBoard, pvDev, selectivity, depth-1, child_selective_cutoff, -alpha-1, true);
			} else {
				bestscore = -PVS_last_three_ply(threadID, sBoard, -alpha-1, -alpha, true);
				if(use_pv_extension && board.n_empties-depth <= pv_extension)
					selective_cutoff = child_selective_cutoff = true;
			}

			board.do_pass();
			bestmove = PASS;
		}
		
	} else {

		//XProbcut
		if(probcut(threadID, false, sBoard, selectivity, probcut_depth, lower_probcut, upper_probcut, list, bestmove != NOMOVE) == true) {
			selective_cutoff = true;
			return alpha + 1;
		}

		//interrupt search
		if(abort.load() || thread_should_stop(threadID))
			return INTERRUPT_SEARCH;
		
		
		//fisrt move
		RXMove* move = list->next;
		
		sBoard.do_move(*move);
		
		if(depth > MIN_DEPTH_USE_PROBCUT) {
			bestscore = -MG_NWS_XProbCut(threadID, sBoard, pvDev, selectivity, depth-1, child_selective_cutoff, -alpha-1, false);
		} else {
			bestscore = -PVS_last_three_ply(threadID, sBoard, -alpha-1, -alpha, false);
			if(use_pv_extension && board.n_empties-depth <= pv_extension)
				child_selective_cutoff = true;
		}
		
		sBoard.undo_move(*move);
		
		//interrupt search
		if(abort.load() || thread_should_stop(threadID))
			return INTERRUPT_SEARCH;

		//assert(bestscore != -INTERRUPT_SEARCH);
		
		bestmove = move->position;
		list = list->next;
		
		if(child_selective_cutoff)	
			selective_cutoff = true;
		
		int score;
		for(RXMove* iter = list->next;!abort.load()  && bestscore<=alpha && iter != NULL; iter = iter->next, list = list->next) {
			
	//		//assert(bestscore >= -MAX_SCORE);
	//		if(bestscore<-MAX_SCORE)
	//			std::cout << "Error" << std::endl;
			
			// Split? 
			if(activeThreads > 1 && depth>MIN_DEPTH_SPLITPOINT && (list->next)->next != NULL && !abort.load()
			   && idle_thread_exists(threadID) && !thread_should_stop(threadID)
			   && split(sBoard, false, pvDev, depth, selectivity, selective_cutoff, child_selective_cutoff,
						alpha, (alpha+1), bestscore, bestmove, list, threadID, RXSplitPoint::MID_XPROBCUT))
				
				break;
			
			
			sBoard.do_move(*iter);
			
			if(depth > MIN_DEPTH_USE_PROBCUT) {
				score = -MG_NWS_XProbCut(threadID, sBoard, pvDev+1,selectivity, depth-1, child_selective_cutoff, -alpha-1, false);
			} else {
				score = -PVS_last_three_ply(threadID, sBoard, -alpha-1, -alpha, false);
				if(use_pv_extension && board.n_empties-depth <= pv_extension)
					selective_cutoff = child_selective_cutoff = true;
			}

			sBoard.undo_move(*iter);

			//interrupt search
			if(abort.load() || thread_should_stop(threadID))
				return INTERRUPT_SEARCH;
			
			//assert(score != -INTERRUPT_SEARCH);
			
			if (score>bestscore) {
				bestscore = score;
				bestmove = iter->position;
			}

			if(child_selective_cutoff)	
				selective_cutoff = true;

							 
		 }
	}
	

	//interrupt search
	if(abort.load()  || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;

	//assert(bestscore != -INTERRUPT_SEARCH);
	
	if(bestscore>alpha)
		selective_cutoff = child_selective_cutoff;
		
	hTable->update(hash_code, type_hashtable, selective_cutoff? MG_SELECT : NO_SELECT, depth, alpha, bestscore, bestmove);
	if(pvDev < 3)
		hTable_PV->update(hash_code, type_hashtable, selective_cutoff? MG_SELECT : NO_SELECT, depth, alpha, bestscore, bestmove);
	
	return bestscore;


}

// MG_SP_search_XEndcut() is used to search from a PV split point.  This function
// is called by each thread working at the split point.  It is similar to
// the normal EG_NWS_XEndCut() function, but simpler.  Because we have already
// probed the hash table and searched the first move before splitting, we
// don't have to repeat all this work in MG_SP_search_XEndcut().  We also don't
// need to store anything to the hash table here:  This is taken care of
// after we return from the split point.

void RXEngine::MG_SP_search_XEndcut(RXSplitPoint* sp, const unsigned int threadID) {
	
	//    assert(threadID >= 0 && threadID < activeThreads);
	//    assert(activeThreads > 1);	
	
	RXBBPatterns& sBoard = sp->sBoardStack[threadID];
	sBoard = *(sp->sBoard);                                 //operator=
	RXBitBoard& board = sBoard.board;
	board.n_nodes = 0;
	
	//here sp->alpha is const	
    while(sp->bestscore <= sp->alpha && !abort.load()  && !thread_should_stop(threadID)) {
		
        
        //verouillage du splitpoint
		pthread_mutex_lock(&(sp->lock));
		
        //attribution de move au thread
		RXMove* move;
		if(sp->list != NULL && sp->list->next != NULL) {
			
			move = sp->list->next;
			sp->list = sp->list->next;
			
		} else {
			pthread_mutex_unlock(&(sp->lock));
			break;
		}	
		
		
		bool child_selective_cutoff = sp->child_selective_cutoff;
		
      	pthread_mutex_unlock(&(sp->lock));
        
        //deverouillage de splitpoint
		
		int alpha = sp->alpha; //local copy
		
		int score;
		sBoard.do_move(*move);
		
		if(sp->depth > MIN_DEPTH_USE_PROBCUT) {
			score = -MG_NWS_XProbCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, sp->depth-1, child_selective_cutoff, -alpha-1, false);
		} else {
			score = -PVS_last_three_ply(threadID, sBoard, -alpha-1, -alpha, false);
			if(use_pv_extension && board.n_empties-sp->depth <= pv_extension)
				child_selective_cutoff = true;
		}
		
		sBoard.undo_move(*move);
		
      	if(abort.load()  || thread_should_stop(threadID))
			break;
		
 
        //first without mutex
        if((score > sp->bestscore) || (!sp->selective_cutoff && child_selective_cutoff)) {
                    
            //update
            pthread_mutex_lock(&(sp->lock));
            
            sp->child_selective_cutoff = child_selective_cutoff;

            if(sp->child_selective_cutoff)
                sp->selective_cutoff = true;
            
            // New best move?
            if(score > sp->bestscore) {
                sp->bestscore = score;
                sp->bestmove = move->position;
                if(score > sp->alpha) {
                    sp->explored =true;
                }
            }
            
            
            pthread_mutex_unlock(&(sp->lock));
        }
    }
	
    pthread_mutex_lock(&(sp->lock));
	
	sp->sBoard->board.n_nodes += board.n_nodes;
	
    sp->slaves[threadID] = false;
	sp->n_Slaves--;
	
    pthread_mutex_unlock(&(sp->lock));
} 


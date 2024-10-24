/*
 *  RXEndGame.cpp
 *  learn_01
 *
 *  Created by Bruno Causse on 11/06/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */
#include <iostream>
#include <iomanip>
#include <cmath>


#include "RXEngine.h"
#include "RXRoxane.h"

const bool RXEngine::USE_STABILITY = true;
const int RXEngine::HIGH_STABILITY_THRESOLD = 2400;
const int RXEngine::stability_threshold[] = { 6500, 6500, 6500, 6500, 6500, 4800, 3800, 3000, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400};

int RXEngine::EG_DEEP_TO_MEDIUM = 17;
const int RXEngine::EG_MEDIUM_HI_TO_LOW = 14; //12 (6'42) : 13 (6'25) : 14 (6'26)
const int RXEngine::EG_MEDIUM_TO_SHALLOW = 8; //

int RXEngine::MIN_DEPTH_USE_ENDCUT = 16;

const int RXEngine::MIN_EMPTIES_SPLITPOINT = 16;// std::max(EG_DEEP_TO_MEDIUM-1, MIN_EMPTIES_SPLITPOINT)


const int RXEngine::EG_HIGH_SELECT = 0;


/*!
 * \brief  Evaluate a position using a shallow Alphabeta.
 *
 * This function is used when there are few empty squares on the board. Here,
 * optimizations are in favour of speed instead of efficiency. A simple
 * alphabeta is used because of the low branching factor that makes PVS less
 * efficient.
 * \param board   board.
 * \param alpha   lower bound.
 * \param beta    upper bound.
 * \param passed  a flag indicating if previous move was a pass.
 * \return        the final score, as a disc difference.
 */

int RXEngine::EG_alphabeta_parity(int threadID, RXBitBoard& board, int alpha, int beta, bool passed) {

	int score, bestscore = UNDEF_SCORE;
	
	int opponent = board.player^1;
	
	/*
	if(USE_STABILITY) {
		if ( alpha >= stability_threshold[board.n_empties] ) {
				int stability_bound = 6400 - 2 * board.get_stability(board.player^1, (6500-alpha)/2);
				if ( stability_bound <= alpha )
					return alpha;
				if ( stability_bound < beta )
					beta = stability_bound + VALUE_DISC;
		}
	}
	*/
	
	RXMove& move = threads[threadID]._move[board.n_empties][1];

	const unsigned long long discs_opponent = board.discs[opponent];
	
	for (int parity = 1; parity >= 0; parity--) {
		for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next) {				
			if (board.parity[RXBitBoard::QUADRANT_ID[empties->position]] == parity && (discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((board).*(board.generate_flips[empties->position]))(move) ){ 
				board.n_nodes++;
				
				board.discs[board.player] |= (move.flipped | move.square);
				board.discs[opponent] ^= move.flipped;
			 
				board.n_empties--;
				//update/restore player
				board.player ^= 1;
				//update empties
				empties->previous->next = empties->next;
				empties->next->previous = empties->previous;
				
				//update/restore parity
				board.parity[RXBitBoard::QUADRANT_ID[empties->position]] ^= 1;
				
				if (board.n_empties == 4) {
					
					score = -board.final_score_4(-beta, -alpha, false);
					
				} else {
					
					score = -EG_alphabeta_parity(threadID, board, -beta, -alpha, false);
					
				}
				
				//update/restore player
				board.parity[RXBitBoard::QUADRANT_ID[empties->position]] ^= 1;
				
				//restore empties
				empties->previous->next = empties;
				empties->next->previous = empties;
				//update/restore parity
				board.player ^= 1;
				board.n_empties++;
										
				
				board.discs[board.player] ^= (move.flipped | move.square);
				board.discs[opponent] |= move.flipped;
				
				if (score > bestscore) {
					bestscore = score;
					if (bestscore > alpha) {
						alpha = bestscore;
						if (alpha >= beta) {
							return bestscore;
						}
					}
				}
			}
		}
	}

	 //if PASS
    if(bestscore == UNDEF_SCORE) {
        if(passed) {
            board.n_nodes--;
            bestscore = board.final_score();
        } else {
            //update/restore player
            board.player ^= 1;
            board.n_nodes++;
            bestscore = -EG_alphabeta_parity(threadID, board, -beta, -alpha, true);
            //update/restore player
            board.player ^= 1;
        }
    }
	
	return bestscore;
}


int RXEngine::EG_alphabeta_hash_parity(int threadID, RXBitBoard& board, const bool pv, int alpha, int beta, bool passed) {

	int score, bestscore = UNDEF_SCORE;
	int lower = alpha;
	int upper = beta;
		
	if(USE_STABILITY) {
		if ( alpha >= stability_threshold[board.n_empties] ) {
				int stability_bound = 6400 - 2 * board.get_stability(board.player^1, (6500-alpha)/2);
				if ( stability_bound <= alpha )
					return alpha;
			
				if ( stability_bound < beta )
					upper = stability_bound + VALUE_DISC;
			 
		}
	}
	
	int bestmove = NOMOVE; 
	int hashmove = NOMOVE;
	
	//synchronized acces
	RXHashValue entry;
	if(hTable->get(board, type_hashtable, entry)) {
	
		if(!pv && entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) {
		
			if (upper > entry.upper) {
				upper = entry.upper;
				if (upper <= lower) {
					return upper;
				}
			}
			if (lower < entry.lower) {
				lower = entry.lower;
				if (lower >= upper) {
					return lower;
				}
			}
		
		}
		
		hashmove = entry.move;
				
	}
	
	RXMove& move = threads[threadID]._move[board.n_empties][1];


	if(hashmove != PASS) {
	

		if(hashmove != NOMOVE) {

			((board).*(board.generate_move[hashmove]))(move);
												
			// first move
			board.do_move(move);
			bestscore = -EG_alphabeta_parity(threadID, board, -upper, -lower, false);
			board.undo_move(move);

			bestmove = hashmove;
			if (bestscore > lower)
				lower = bestscore;
			
		}
					
		if(lower < upper) {
		
			int opponent = board.player^1;
			const unsigned long long discs_opponent = board.discs[opponent];
	
			for (int parity = 1; lower < upper && parity >= 0; parity--) {
				for(RXSquareList* empties = board.empties_list->next; lower < upper && empties->position != NOMOVE; empties = empties->next) {
					if (empties->position != hashmove && board.parity[RXBitBoard::QUADRANT_ID[empties->position]] == parity && (discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((board).*(board.generate_flips[empties->position]))(move) ){ 
						board.n_nodes++;
						
						board.discs[board.player] |= (move.flipped | move.square);
						board.discs[opponent] ^= move.flipped;
					 
						board.n_empties--;
						//update/restore player
						board.player ^= 1;
						//update empties
						empties->previous->next = empties->next;
						empties->next->previous = empties->previous;
						//update/restore parity
						board.parity[RXBitBoard::QUADRANT_ID[empties->position]] ^= 1;

						score = -EG_alphabeta_parity(threadID, board, -upper, -lower, false);
						
						//update/restore parity
						board.parity[RXBitBoard::QUADRANT_ID[empties->position]] ^= 1;
						//restore empties
						empties->previous->next = empties;
						empties->next->previous = empties;
						//update/restore parity
						board.player ^= 1;
						board.n_empties++;
												
						
						board.discs[board.player] ^= (move.flipped | move.square);
						board.discs[opponent] |= move.flipped;
						
						if (score > bestscore) {
							bestmove = empties->position;
							bestscore = score;
							if (bestscore > lower) {
								lower = bestscore;
							}
						}
					}
				}
			}
		}
	}

	 //if PASS
	if (bestscore == UNDEF_SCORE) {
		if (passed) {
			board.n_nodes--;
			bestscore = board.final_score();
			alpha = -(beta = +MAX_SCORE);
			bestmove = NOMOVE;
		} else {
			board.do_pass();
			board.n_nodes++;
			bestscore = -EG_alphabeta_hash_parity(threadID, board, pv, -upper, -lower, true);
			board.do_pass();
			bestmove = PASS;
		}
	}
	

	hTable->update(board.hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
	
	return bestscore;
}


/*!
 * \brief Evaluate a position with a deep Principal Variation Search algorithm.
 *
 * This function is used when there are still many empty squares on the board. Move
 * ordering, hash table cutoff, etc. are used in
 * order to diminish the size of the tree to analyse, but at the expense of a
 * slower speed.
 *
 * \param board      board.
 * \param hash_table hash_table.
 * \param alpha      lower bound.
 * \param beta       upper bound.
 * \param passed     a flag indicating if previous move was a pass.
 * \return the final score, as a disc difference.
 */
int RXEngine::EG_PVS_hash_mobility(int threadID, RXBitBoard& board, const bool pv, int alpha, int beta, bool passed)
{

	int bestmove = NOMOVE;
	int lower = alpha;
	int upper = beta;
	
	if(USE_STABILITY) {
	
		/*	
			la stabilite calcul�e est inferieure ou egale a la stabilit� reelle
			donc le score_max_calcul� est surestim�.
			score_max<=score_max_calcul�<=alpha ==> coupure
			&
			score_max<=score_max_calcul�< beta  ==> diminution de la fenetre de recherche
		*/
			
			
		if ( alpha >= stability_threshold[board.n_empties] ) {
				int stability_bound = 6400 - 2 * board.get_stability(board.player^1, (6500-alpha)/2);
				if ( stability_bound <= alpha )
					return alpha;
			
				if ( stability_bound < beta )
					upper = std::max(beta, stability_bound + VALUE_DISC);
			 
		}
		
	}

	RXMove* list = threads[threadID]._move[board.n_empties];
	RXMove* move = list + 1;
	
	//synchronized acces
	RXHashValue entry;
	if(hTable->get(board, type_hashtable, entry)) {
	
		if(!pv && entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) {

		
			if (upper > entry.upper) {
				upper = entry.upper;
				if (upper <= lower) {
					return upper;
				}
			}
			if (lower < entry.lower) {
				lower = entry.lower;
				if (lower >= upper) {
					return lower;
				}
			}
			
		}
		
		bestmove = entry.move;
				
	}
	
	int bestscore = UNDEF_SCORE;

	if(bestmove != PASS) {

		if(bestmove != NOMOVE) {

			((board).*(board.generate_move[bestmove]))(*move);
												
			/* first move */
			board.do_move(*move);
			if (board.n_empties < EG_MEDIUM_TO_SHALLOW) {
				bestscore = -EG_alphabeta_hash_parity(threadID, board, pv, -upper, -lower, false);
			} else {
				bestscore = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -lower, false);
			}
			board.undo_move(*move);
			
			
			bestmove = move->position;
			if (bestscore > lower)
				lower = bestscore;
			
		}
			
		if(lower < upper) {

			//for all empty square
			RXMove* previous = list;
			int n_Moves = 0;
			const unsigned long long discs_opponent = board.discs[board.player^1];

			for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
				if(bestmove != empties->position && (discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((board).*(board.generate_move[empties->position]))(*move)) {
					previous = previous->next = move++;
					n_Moves++;
				}
						
			previous->next = NULL;
			
			if(n_Moves>0) {	
				
				
				if(n_Moves>1) {
				
					const int p = board.player;
					const int o = p^1;
				
					//sort list by mobility
					for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
						
						board.n_nodes++;

						const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
						const unsigned long long o_discs = board.discs[o] ^ iter->flipped;
						
						iter->score = (RXBitBoard::get_mobility(o_discs, p_discs)<<5) - (RXBitBoard::get_corner_stability(p_discs)<<2) - (board.parity[RXBitBoard::QUADRANT_ID[iter->position]]);
						
					}
						
					
				}
				
				
				if(bestmove == NOMOVE) {

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

					board.do_move(*move);
					if (board.n_empties < EG_MEDIUM_TO_SHALLOW) {
						bestscore = -EG_alphabeta_hash_parity(threadID, board, pv, -upper, -lower, false);
					} else {
						bestscore = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -lower, false);
					}
					board.undo_move(*move);
										
					bestmove = move->position;
					if (bestscore > lower)
						lower = bestscore;
						
					// next move
					list = list->next;

				}
				

				// other moves : try to refute the first/best one 
				int score;
				for(; lower < upper && list->next != NULL; list = list->next) {
					
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
					
					
					board.do_move(*move);
					
					if (board.n_empties < EG_MEDIUM_TO_SHALLOW) {
													
						score = -EG_alphabeta_hash_parity(threadID, board, pv, -upper, -lower, false);
												
					} else {
						score = -EG_PVS_hash_mobility(threadID, board, false, -lower - VALUE_DISC, -lower, false);
						if (lower < score && score < upper)
							score = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -score, false);
					}

					board.undo_move(*move);
					
					if (score > bestscore) {
						bestscore = score;
						bestmove = move->position;
						if (bestscore > lower)
							lower = bestscore;
					}
				}
			}
		}
	}
	

	if (bestscore == UNDEF_SCORE) {
		if (passed) {
			board.n_nodes--;
			bestscore = board.final_score();
			alpha = -(beta = +MAX_SCORE);
			bestmove = NOMOVE;
		} else {
			board.do_pass();
			board.n_nodes++;
			bestscore = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -lower, true);
			board.do_pass();
			bestmove = PASS;
		}
	}
			
	hTable->update(board.hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);

	return bestscore;
}

/*!
 * \brief Evaluate a position with a deep Principal Variation Search algorithm.
 *
 * This function is used when there are still many empty squares on the board. Move
 * ordering, hash table cutoff, enhanced transposition cutoff, etc. are used in
 * order to diminish the size of the tree to analyse, but at the expense of a
 * slower speed.
 *
 * \param board      board.
 * \param hash_table hash_table.
 * \param alpha      lower bound.
 * \param beta       upper bound.
 * \param passed     a flag indicating if previous move was a pass.
 * \return the final score, as a disc difference.
*/
int RXEngine::EG_PVS_ETC_mobility(int threadID, RXBitBoard& board, const bool pv, int alpha, int beta, bool passed)
{

//	assert(alpha>=-64*VALUE_DISC && beta<=64*VALUE_DISC);

	if(abort.load() || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;

	int bestmove = NOMOVE;
	int lower = alpha;
	int upper = beta;
	
	if(USE_STABILITY) {
	
		/*	
			la stabilite calcul�e est inferieure ou egale a la stabilit� reelle
			donc le score_max_calcul� est surestim�.
			score_max<=score_max_calcul�<=alpha ==> coupure
			&
			score_max<=score_max_calcul�< beta  ==> diminution de la fenetre de recherche
		*/
			
			
		if ( alpha >= stability_threshold[board.n_empties] ) {
				int stability_bound = 6400 - 2 * board.get_stability(board.player^1, (6500-alpha)/2);
				if ( stability_bound <= alpha )
					return alpha;
			
				if ( stability_bound < beta )
					upper = std::max(beta, stability_bound + VALUE_DISC);
			 
		}
		
	}
	
	//synchronized acces
	RXHashValue entry;
	if(hTable->get(board, type_hashtable, entry)) {
	
		if(!pv && entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) {

		
			if (upper > entry.upper) {
				upper = entry.upper;
				if (upper <= lower) {
					return upper;
				}
			}
			if (lower < entry.lower) {
				lower = entry.lower;
				if (lower >= upper) {
					return lower;
				}
			}
		
		}
		
		bestmove = entry.move;
				
	}
	
	int bestscore = UNDEF_SCORE;

	RXMove* list = threads[threadID]._move[board.n_empties];
	int n_Moves = 0;
	if(bestmove != PASS) {

		RXMove* move = list + 1;
		RXMove* previous = list;
		
		//ENHANCED TRANSPOSITION CUTOFF
		if(bestmove != NOMOVE) {
			board.n_nodes++;
									
			((board).*(board.generate_move[bestmove]))(*move);

			//synchronized acces				
			if(hTable->get(board.hash_code ^ move->hash_code, type_hashtable, entry) && !pv && entry.selectivity == NO_SELECT && entry.depth>=board.n_empties)
				
				if(-entry.upper >= upper) {
					return -entry.upper ;
				}

			previous = previous->next = move++;
			n_Moves++;
		}
		
		//for all empty square
		const unsigned long long discs_opponent = board.discs[board.player^1];
		for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
			if(bestmove != empties->position && (discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((board).*(board.generate_move[empties->position]))(*move)) {
				board.n_nodes++;
								
				//synchronized acces
				if(hTable->get(board.hash_code ^ move->hash_code, type_hashtable, entry) && !pv && entry.selectivity == NO_SELECT && entry.depth>=board.n_empties) {


					if(-entry.upper >= upper) {
						return -entry.upper ;
					}

				}	
				
				previous = previous->next = move++;
				n_Moves++;
		
			}
		
		previous->next = NULL;
				
	}
	
	if (n_Moves == 0) {
		if (passed) {
			board.n_nodes--;
			bestscore = board.final_score();
			alpha = -(beta = +MAX_SCORE);
			bestmove = NOMOVE;
		} else {
			board.do_pass();
			board.n_nodes++;
			bestscore = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -lower, true);
			board.do_pass();
			bestmove = PASS;
		}
	} else {
		
		
		if(bestmove != NOMOVE) {
			/* first move */
			list = list->next;

			board.do_move(*list);
			if (board.n_empties < EG_MEDIUM_HI_TO_LOW) {
				bestscore = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -lower, false);
			} else {
				bestscore = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -lower, false);
			}
			board.undo_move(*list);

			//interrupt search
			if(abort.load()  || thread_should_stop(threadID))
				return INTERRUPT_SEARCH;
			
			bestmove = list->position;
			if (bestscore > lower)
				lower = bestscore;
			
			n_Moves--;
		}
		
		
		if(lower < upper) {

			if(n_Moves>1) {
			
				const int p = board.player;
				const int o = p^1;
			
				//sort list by mobility
				for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
							
					board.n_nodes++;

					const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
					const unsigned long long o_discs = board.discs[o] ^ iter->flipped;
																					
					iter->score = (RXBitBoard::get_mobility(o_discs, p_discs)<<5) - (RXBitBoard::get_corner_stability(p_discs)<<2) - (board.parity[RXBitBoard::QUADRANT_ID[iter->position]]);
					
				}
									
			}
			
			if(bestmove == NOMOVE) {

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

				board.do_move(*move);
				if (board.n_empties < EG_MEDIUM_HI_TO_LOW) {
					bestscore = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -lower, false);
				} else {
					bestscore = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -lower, false);
				}
				board.undo_move(*move);

				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;
				
				bestmove = move->position;
				if (bestscore > lower)
					lower = bestscore;
					
				// next move
				list = list->next;

			}
			

			// other moves : try to refute the first/best one 
			int score;
//			for(;!abort.load() && lower < upper && list->next != NULL; list = list->next) {
			for(;lower < upper && list->next != NULL; list = list->next) {

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
				
				board.do_move(*move);
				if (board.n_empties < EG_MEDIUM_HI_TO_LOW) {
					score = -EG_PVS_hash_mobility(threadID, board, false, -lower - VALUE_DISC, -lower, false);
					if (lower < score && score < upper)
						score = -EG_PVS_hash_mobility(threadID, board, pv, -upper, -score, false);
					

				} else {
					score = -EG_PVS_ETC_mobility(threadID, board, false, -lower - VALUE_DISC, -lower, false);
					if (lower < score && score < upper)
						score = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -score, false);
										
					
				}
				board.undo_move(*move);
				
				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;
				
				if (score > bestscore) {
					bestscore = score;
					bestmove = move->position;
					if (bestscore > lower)
						lower = bestscore;
				}
			}
		}
	}

	//interrupt search
	if(abort.load()  || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;
	
	hTable->update(board.hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
	
	
	return bestscore;
}

int RXEngine::EG_PVS_deep(int threadID, RXBBPatterns& sBoard, const bool pv, const int selectivity, bool& selective_cutoff, int alpha, int beta, bool passed) {
	

	
//	assert(alpha>=-64*VALUE_DISC && beta<=64*VALUE_DISC);

	if(abort.load() || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;

	if(threadID == 0)
		pthread_yield_np(); //process->yield();
	
	
	//time gestion
	if(dependent_time && get_current_dependentTime() > time_limit()) {
		abort.store(true);
		return INTERRUPT_SEARCH;
	}

	int bestmove = NOMOVE;
	int lower = alpha;
	int upper = beta;
	
	
	RXBitBoard& board = sBoard.board;
	selective_cutoff = false;
		
	if(USE_STABILITY) {
	
		/*	
			la stabilite calcul�e est inferieure ou egale a la stabilit� reelle
			donc le score_max_calcul� est surestim�.
			score_max<=score_max_calcul�<=alpha ==> coupure
			&
			score_max<=score_max_calcul�< beta  ==> diminution de la fenetre de recherche
		*/
			
			
		if ( lower >= HIGH_STABILITY_THRESOLD ) {
				int stability_bound = 6400 - 2 * board.get_stability(board.player^1, (6500-alpha)/2);
				if ( stability_bound <= alpha )
					return alpha;
			
				if ( stability_bound < beta )
					upper = std::max(beta, stability_bound + VALUE_DISC);
			 
		}
	}
	
		
	bool hiProb_alphaCut = false;
	
	//synchronized acces
	RXHashValue entry;
	if(hTable->get(board, type_hashtable, entry)) {
	
	
			if(entry.depth >= board.n_empties) {
				if(!pv && entry.selectivity >= selectivity) {
				
				
					if (upper > entry.upper) {
						
						upper = entry.upper;
						
						if (upper <= lower) {
							if(entry.selectivity != NO_SELECT)
								selective_cutoff = true;
								
							return upper;
						}
					}
					
					if (lower < entry.lower) {
						
						lower = entry.lower;
											
						if (lower >= upper) {
							if(entry.selectivity != NO_SELECT)
								selective_cutoff = true;
								
							return lower;
						}
					}
				
				} else { //if(entry->selectivity == selectivity-1) {
				
					if(entry.upper<=lower)
						hiProb_alphaCut = true;
						
				}
			}
			
		
		bestmove = entry.move;

	}
	
		
//	IID & IIS
	if(pv && bestmove == NOMOVE && board.n_empties > 12) {
		bool child_selective_cutoff = false;

		if(selectivity > EG_HIGH_SELECT)
			EG_PVS_deep(threadID, sBoard, pv, selectivity-1, child_selective_cutoff, lower, upper, passed);
		else
			MG_PVS_deep(threadID, sBoard, pv, MG_SELECT, board.n_empties-10, child_selective_cutoff, lower, upper, passed);

		if(abort.load() || thread_should_stop(threadID))
			return INTERRUPT_SEARCH;

		if(hTable->get(board, type_hashtable, entry))
			bestmove = entry.move;
	}
		
		
	
	int score, bestscore = UNDEF_SCORE;

	RXMove* list = threads[threadID]._move[board.n_empties];
	int n_Moves = 0;
	if(bestmove != PASS) {

		RXMove* move = list + 1;
		RXMove* previous = list;
	
		//ENHANCED TRANSPOSITION CUTOFF
		if(bestmove != NOMOVE) {
			board.n_nodes++;
								
			((board).*(board.generate_move[bestmove]))(*move);
			
			//synchronized acces
			if(hTable->get(board.hash_code ^ move->hash_code, type_hashtable, entry) && !pv && entry.selectivity >= selectivity && entry.depth>=board.n_empties) {
							
				if(-entry.upper >= upper) {
					if(entry.selectivity != NO_SELECT)
						selective_cutoff = true;
						
					return -entry.upper ;
				}
			}
					
			previous = previous->next = move++;
			n_Moves++;
			
		}
		
		
		//for all empty square
		const unsigned long long discs_opponent = board.discs[board.player^1];
		for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
			if(bestmove != empties->position && (discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((board).*(board.generate_move[empties->position]))(*move)) {					
				board.n_nodes++;

				move->score = 0;
				
				//synchronized acces
				if(hTable->get(board.hash_code ^ move->hash_code, type_hashtable, entry) &&  entry.depth>=board.n_empties) {

					move->score = -3*VALUE_DISC;
			
					if(entry.selectivity >= selectivity) {
					
						if(-entry.upper >= upper) {
							
							if(pv) {
								
								move->score = -32*VALUE_DISC; // very good move
								
							} else {
								
								if(entry.selectivity != NO_SELECT)
									selective_cutoff = true;
									
								return -entry.upper ;
							}
							
						} else if(-entry.lower<=lower) {
							
							move->score += 5*VALUE_DISC;

						}

						
					}
					
					
				}									
				
				previous = previous->next = move++;
				n_Moves++;
	
			}
				
		previous->next = NULL;
				
		
	}
	
	bool child_selective_cutoff = false;
	
	if (n_Moves == 0) {
		if (passed) {
			board.n_nodes--;
			bestscore = board.final_score();
			alpha = -(beta = +MAX_SCORE);
			bestmove = NOMOVE;
		} else {
			board.do_pass();
			board.n_nodes++;
			bestscore = -EG_PVS_deep(threadID, sBoard, pv, selectivity, child_selective_cutoff, -upper, -lower, true);
			board.do_pass();
			bestmove = PASS;
			
			if(child_selective_cutoff)	
				selective_cutoff = true;

		}
	} else {
		
		bool moves_sorting = false;
		
		if(bestmove != NOMOVE) {

			
			/* use singular extension? */
			int selectivity_extension = 0;
			if(USE_SINGULAR_EXTENSION) {
				
				if (selectivity < NO_SELECT && board.n_empties > EG_DEEP_TO_MEDIUM) { //conditions
					
					if(n_Moves>1) {
						
						if(hTable->get(board, type_hashtable, entry)) { // retrieve hash entry
							
							
							if (entry.lower > -MAX_SCORE && entry.depth >= board.n_empties && entry.selectivity >= selectivity-1) { //enought good?
								
								const int sigma = static_cast<int> (PERCENTILE[entry.selectivity] * probcut_data[board.n_empties][board.n_empties]);
								
								const int reduced_depth = (board.n_empties & 1) + 2 * (board.n_empties / 4); //min 8
								const int alpha = entry.lower - sigma;
								
								sort_moves(threadID, true, sBoard, reduced_depth, alpha, alpha+1, list->next); //not sort bestmove
								moves_sorting = true;
								
								
								if (singular_move(threadID, sBoard, entry.selectivity, reduced_depth, alpha, list, bestmove)) {
									selectivity_extension = 1;
									
//									*log << "Endgame: singular extension n_empties: " << board.n_empties << " /selectivity : " << CONFIDENCE[selectivity] << "%" << std::endl;
								}
								
							}
						}
						
					} else {
						selectivity_extension = 1;
//						*log << "Endgame: Only 1 move at n_empties: " << board.n_empties << " /selectivity : " << CONFIDENCE[selectivity] << "%" << std::endl;
						
					}
					
				}
			}
			
			
			/* first move */
			list = list->next;

		
			if (board.n_empties <= EG_DEEP_TO_MEDIUM) {
				board.do_move(*list);
				bestscore = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -lower, false);
				board.undo_move(*list);
			} else {
				((sBoard).*(sBoard.update_patterns[list->position][board.player]))(*list);
				
				sBoard.do_move(*list);
				bestscore = -EG_PVS_deep(threadID, sBoard, pv, selectivity+selectivity_extension , child_selective_cutoff, -upper, -lower, false);
				sBoard.undo_move(*list);
				
			}


			//interrupt search
			if(abort.load() || thread_should_stop(threadID))
				return INTERRUPT_SEARCH;

			//assert(bestscore != -INTERRUPT_SEARCH);
			
			bestmove = list->position;
			if (bestscore > lower)
				lower = bestscore;

			if (child_selective_cutoff)
				selective_cutoff = true;
				
			n_Moves--;
		}
		
		if(lower < upper) {
			
			if(!moves_sorting) {

				if(n_Moves>1) {

					const int p = board.player;
					const int o = p^1;
					

					if(board.n_empties>=18 && !hiProb_alphaCut) { //18

						RXMove& lastMove = threads[threadID]._move[board.n_empties-1][1];
						
						int threshold_ff_Alpha = -MAX_SCORE;
						int threshold_ff_Beta  =  MAX_SCORE;
						probcut_bounds(board, 3, board.n_empties, 0, 0, threshold_ff_Alpha, threshold_ff_Beta); //selectivity 3 = 95%

						int eval_position = sBoard.get_score();
						
						int _lower = std::max(-MAX_SCORE, lower+threshold_ff_Alpha);

						if(_lower<= eval_position) { // && eval_position<=(beta+threshold_ff_Beta*2)) { //alpha 95% / beta 99%

							//stable position -> sorting on evaluation

							for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {

								((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
								
								//stable move -> sorting on evaluation
								sBoard.do_move(*iter);
								
								int eval_move = sBoard.get_score();

								if(eval_move <= -_lower) { //95%
									
									if(board.n_empties%2 == 0) {
										if(board.n_empties >= 26) { //26
											iter->score += PVS_check(threadID, sBoard, 6, -MAX_SCORE, -_lower, false);
										} else if(board.n_empties >= 22) {//22
											iter->score += PVS_check(threadID, sBoard, 4, -MAX_SCORE, -_lower, false);
										} else {
											iter->score += alphabeta_last_two_ply(threadID, sBoard, -MAX_SCORE, -_lower, false);							
										}
									} else {
										if(board.n_empties >= 25) {//25
											iter->score += PVS_check(threadID, sBoard, 5, -MAX_SCORE, -_lower, false);
										} else if(board.n_empties >= 21) {//21
											iter->score += PVS_last_three_ply(threadID, sBoard, -MAX_SCORE, -_lower, false);
										} else {
												
											int bestscore = UNDEF_SCORE; //masquage
											const unsigned long long discs_opponent = board.discs[board.player^1];
											for(RXSquareList* empties = board.empties_list->next; bestscore< -_lower && empties->position != NOMOVE; empties = empties->next) {
												if ((discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((sBoard).*(sBoard.generate_patterns[empties->position][board.player]))(lastMove)) {
													board.n_nodes++;

													int score = -sBoard.get_score(lastMove);	
													if (score>bestscore)
														bestscore = score;
											
																			 
												}
											}
														
														
											if(bestscore == UNDEF_SCORE) {
												//PASS
												sBoard.board.do_pass();
												iter->score -= sBoard.get_score();
												sBoard.board.do_pass();

											} else {
												iter->score += bestscore;
											}
													
										}
										
									}
						
									if(iter->score < -std::min(+MAX_SCORE, (beta+threshold_ff_Beta))) {
										iter->score /= 4; //4
										iter->score -= MAX_SCORE; //good move	"probable beta cut"	study in first
									}
								
								} else {
									
									iter->score += eval_move;
									iter->score += MAX_SCORE/2; //bad move
								}
								
								iter->score += board.get_mobility(board.discs[board.player], board.discs[board.player^1])*VALUE_DISC - (board.get_corner_stability(board.discs[board.player^1])*VALUE_DISC)/16;
																
								sBoard.undo_move(*iter);
									
							}
							
						} else {
												
							for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {
								((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
			
								board.n_nodes++;
								const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
								
								iter->score += sBoard.get_score(*iter) + 2*(RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC) - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/4;
							}
						}

					} else {
					
						//empties<18;
						
						for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {
							((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
							
							board.n_nodes++;
							const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
																						
							iter->score += sBoard.get_score(*iter) + 2*(RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC) - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/4;
						}

					}
				
				} else if(n_Moves == 1) { 
					((sBoard).*(sBoard.update_patterns[list->next->position][board.player]))(*(list->next));
				}
			}
			
			
			if(bestmove == NOMOVE) {

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
								
				
				if (board.n_empties <= EG_DEEP_TO_MEDIUM) {
					board.do_move(*move);
					bestscore = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -lower, false);
					board.undo_move(*move);
				} else {
					sBoard.do_move(*move);
					bestscore = -EG_PVS_deep(threadID, sBoard, pv, selectivity, child_selective_cutoff, -upper, -lower, false);
					sBoard.undo_move(*move);

				}


				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;
				
				//assert(bestscore != -INTERRUPT_SEARCH);
				
				bestmove = move->position;
				if (bestscore > lower)
					lower = bestscore;

				if ( child_selective_cutoff )
					selective_cutoff = true;

				// next move
				list = list->next;
					
			}
			

			//************************************************************************************************
            //dans la methode search sequentielle dans la boucle des autres moves
			//************************************************************************************************
            
					
			
			/* other moves : try to refute the first/best one */
			for(;!abort.load()  && lower < upper && list->next != NULL; list = list->next) {
				
				RXMove* move = list->next;
				
				if(move->next != NULL) { //more 1 move
				
					// Split? 
					if(activeThreads > 1 && board.n_empties>MIN_EMPTIES_SPLITPOINT && !abort.load()
					   && !thread_should_stop(threadID) && idle_thread_exists(threadID)
					   && split(sBoard, pv, 0, board.n_empties, selectivity, selective_cutoff, child_selective_cutoff,
								lower, upper, bestscore, bestmove, list, threadID, RXSplitPoint::END_PVS))
						
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
				if (board.n_empties+1 <= EG_DEEP_TO_MEDIUM) {
				
					score = -EG_PVS_ETC_mobility(threadID, board, false, -lower - VALUE_DISC, -lower, false);
					if (lower < score && score < upper)
						score = -EG_PVS_ETC_mobility(threadID, board, pv, -upper, -score, false);
					
				} else if(selectivity != NO_SELECT) {
				
					score = -EG_NWS_XEndCut(threadID, sBoard, 0, selectivity, child_selective_cutoff, -lower - VALUE_DISC, false);
					if (lower < score && score < upper)
							score = -EG_PVS_deep(threadID, sBoard, pv, selectivity, child_selective_cutoff, -upper, -lower, false); //-score
						
				} else {
				
					score = -EG_PVS_deep(threadID, sBoard, false, selectivity, child_selective_cutoff, -lower - VALUE_DISC, -lower, false);
					if (lower < score && score < upper)
						score = -EG_PVS_deep(threadID, sBoard, pv, selectivity, child_selective_cutoff, -upper, selectivity != NO_SELECT? -lower : -score, false);
						
				}
				sBoard.undo_move(*move);

				
				//interrupt search
				if(abort.load()  || thread_should_stop(threadID))
					return INTERRUPT_SEARCH;
				
				//assert(score != -INTERRUPT_SEARCH);
				
				if (score > bestscore) {
					bestscore = score;
					bestmove = move->position;
					if (bestscore > lower)
						lower = bestscore;
				}
				
				if ( child_selective_cutoff )
					selective_cutoff = true;
			}
			
		}
	}

	//interrupt search
	if(abort  || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;
	
	//assert(bestscore != -INTERRUPT_SEARCH);
	
	if(bestscore>=beta)
		selective_cutoff = child_selective_cutoff;
	
	
	hTable->update(   board.hash_code, pv, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
	hTable_PV->update(board.hash_code, pv, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);

	return bestscore;
}


// EG_SP_search_DEEP() is used to search from a PV split point.  This function
// is called by each thread working at the split point.  It is similar to
// the normal EG_PVS_deep() function, but simpler.  Because we have already
// probed the hash table and searched the first move before splitting, we
// don't have to repeat all this work in EG_SP_search_DEEP().  We also don't
// need to store anything to the hash table here:  This is taken care of
// after we return from the split point.

void RXEngine::EG_SP_search_DEEP(RXSplitPoint* sp, const unsigned int threadID) {
	
	//    assert(threadID >= 0 && threadID < activeThreads);
	//    assert(activeThreads > 1);
	
	
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
		
		if (board.n_empties+1 <= EG_DEEP_TO_MEDIUM) {
			
			
			score = -EG_PVS_ETC_mobility(threadID, board, false, -alpha - VALUE_DISC, -alpha, false);
			
			if (alpha < score && score < sp->beta)
				score = -EG_PVS_ETC_mobility(threadID, board, sp->pv, -sp->beta, -score, false);
			
		} else if(sp->selectivity != NO_SELECT) {
			
			
			score = -EG_NWS_XEndCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, false);
			
			if (alpha < score && score < sp->beta)
				score = -EG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, child_selective_cutoff, -sp->beta, -sp->alpha, false);
			
		} else {
			
			score = -EG_PVS_deep(threadID, sBoard, false, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, -alpha, false);
			
			if (alpha < score && score < sp->beta)
				score = -EG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, child_selective_cutoff, -sp->beta, sp->selectivity != NO_SELECT? -sp->alpha : -score, false);
			
		}
		
/*
 a tester (apporte peu/rien)
 */

//		int alpha;
//		
//		if (board.n_empties+1 <= EG_DEEP_TO_MEDIUM) {
//			
//			do {
//				alpha = sp->alpha;		
//				score = -EG_PVS_ETC_mobility(threadID, board, false, -alpha - VALUE_DISC, -alpha, false);
//			} while (sp->alpha>alpha && score>alpha);
//			
//			if (alpha < score && score < sp->beta)
//				score = -EG_PVS_ETC_mobility(threadID, board, sp->pv, -sp->beta, -score, false);
//			
//		} else if(sp->selectivity != NO_SELECT) {
//			
//			do {
//				alpha = sp->alpha;		
//				score = -EG_NWS_XEndCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, false);
//			} while (sp->alpha>alpha && score>alpha);
//			
//			if (alpha < score && score < sp->beta)
//				score = -EG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, child_selective_cutoff, -sp->beta, -sp->alpha, false);
//			
//		} else {
//			
//			do {
//				alpha = sp->alpha;		
//				score = -EG_PVS_deep(threadID, sBoard, false, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, -alpha, false);
//			} while (sp->alpha>alpha && score>alpha);
//			
//			if (alpha < score && score < sp->beta)
//				score = -EG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, child_selective_cutoff, -sp->beta, sp->selectivity != NO_SELECT? -sp->alpha : -score, false);
//			
//		}
		
		sBoard.undo_move(*move);
		
      	if(abort.load()  || thread_should_stop(threadID))
			break;
		
		//assert(score != -INTERRUPT_SEARCH);
		
		//update      
     	pthread_mutex_lock(&(sp->lock));
		
      	if(!abort.load()  && !thread_should_stop(threadID)) {
			
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
			
		}
		
		pthread_mutex_unlock(&(sp->lock));
    }
	
    pthread_mutex_lock(&(sp->lock));
	
	sp->sBoard->board.n_nodes += board.n_nodes;
	
	
    sp->slaves[threadID] = false;
	sp->n_Slaves--;
	
    pthread_mutex_unlock(&(sp->lock));
} 


/*
Null Window Search  + XProbCut
*/
int RXEngine::EG_NWS_XEndCut(int threadID, RXBBPatterns& sBoard, const int pvDev, const int selectivity, bool& selective_cutoff, int alpha, const bool passed) {

//	assert(alpha>=-64*VALUE_DISC);

	if(abort.load()  || thread_should_stop(threadID))
		return INTERRUPT_SEARCH;
	
	//time gestion
	if(dependent_time && get_current_dependentTime() > time_limit()) {
		abort.store(true);
		return INTERRUPT_SEARCH;
	}

	RXBitBoard& board = sBoard.board;
	selective_cutoff = false;
	
	int bestmove = NOMOVE;

	
	if(USE_STABILITY && board.n_empties<19) {
		if ( alpha >= HIGH_STABILITY_THRESOLD && alpha >= stability_threshold[board.n_empties] ) {
				int stability_bound = 6400 - 2 * board.get_stability(board.player^1, (6500-alpha)/2);
				if ( stability_bound <= alpha )
					return alpha;
		}
	}
	
	
	//synchronized acces
	RXHashValue entry;
	if(hTable->get(board, type_hashtable, entry)) {
		
		if(entry.selectivity >= selectivity && entry.depth>=board.n_empties) {


			if(entry.lower > alpha) {
				if(entry.selectivity != NO_SELECT)
					selective_cutoff = true;
					
				return entry.lower;
			}
			
			if(entry.upper <= alpha) {
				if(entry.selectivity != NO_SELECT)
					selective_cutoff = true;
					
				return  entry.upper;
			}
			

		}
		
		bestmove = entry.move;
		
	}

	
	//param mpc
	int lower_probcut, upper_probcut;
	int probcut_depth = (board.n_empties/4)*2 + (board.n_empties&1);
	probcut_bounds(board, selectivity, board.n_empties, pvDev, alpha, lower_probcut, upper_probcut);
	
	if(selectivity < NO_SELECT) {
		
		if(bestmove != NOMOVE && entry.selectivity >= selectivity && entry.depth>=probcut_depth) {
		
			if(entry.lower >= upper_probcut) {
				selective_cutoff = true;
				return alpha+VALUE_DISC;
			}
				
//			if(entry.upper <= lower_probcut) {
//				selective_cutoff = true;
//				return  alpha;
//			}
		}
	}
	
	
	RXMove* list = threads[threadID]._move[board.n_empties];
	int n_Moves = 0;

	if(bestmove != PASS) {
		
		RXMove* move = list + 1;
		RXMove* previous = list;
	
		//ENHANCED TRANSPOSITION CUTOFF
		if(bestmove != NOMOVE) {
					
			board.n_nodes++;
								
			((board).*(board.generate_move[bestmove]))(*move);
			
			//synchronized acces
			if(hTable->get(board.hash_code ^ move->hash_code, type_hashtable, entry) && entry.selectivity >= selectivity && entry.depth >= board.n_empties) {
			
				if(-entry.upper > alpha) {
					if(entry.selectivity != NO_SELECT)
						selective_cutoff = true;
						
					return -entry.upper;
				}
				
			}
				
			previous = previous->next = move++;
			n_Moves++;

		}
			
		//for all empty square
		const unsigned long long discs_opponent = board.discs[board.player^1];
		for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
			if(bestmove != empties->position && (discs_opponent & RXBitBoard::NEIGHBOR[empties->position]) && ((board).*(board.generate_move[empties->position]))(*move)) {
					
				board.n_nodes++;

				move->score = 0;
				
				//synchronized acces
				if(hTable->get(board.hash_code ^ move->hash_code, type_hashtable, entry) && entry.selectivity >= selectivity && entry.depth>=board.n_empties) {
				
					move->score = -3*VALUE_DISC;

					if(-entry.upper > alpha) {
						if(entry.selectivity != NO_SELECT)
							selective_cutoff = true;
							
						return -entry.upper;
					}

					if(-entry.lower<=alpha)
						move->score += 5*VALUE_DISC;
					
				}					
				
				previous = previous->next = move++;
				n_Moves++;

			}

		previous->next = NULL;
		
		
	}

	int bestscore = UNDEF_SCORE;
	bool child_selective_cutoff = false;
	
	if(n_Moves == 0) {
		 //PASS
		if(passed) {
			board.n_nodes--;
			bestscore = sBoard.final_score();
			hTable->update(board.hash_code, false, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, -MAX_SCORE, MAX_SCORE,  bestscore, bestmove);
			return bestscore;
		} else {
			board.n_nodes++;
			board.do_pass();
			bestscore = -EG_NWS_XEndCut(threadID, sBoard, pvDev, selectivity, child_selective_cutoff, -alpha-VALUE_DISC, true);
			board.do_pass();
			bestmove = PASS;
			
			if(child_selective_cutoff)	
				selective_cutoff = true;

		}
		
	} else {
		
		if (selectivity < NO_SELECT) {
			//XProbcut
			if(probcut(threadID, true, sBoard, selectivity, probcut_depth, lower_probcut, upper_probcut, list, bestmove != NOMOVE) == true) {
				selective_cutoff = true;
				return alpha + VALUE_DISC;
			}
		
			//interrupt search
			if(abort.load()  || thread_should_stop(threadID))
				return INTERRUPT_SEARCH;
		
		} else {
			sort_moves(threadID, true, sBoard, probcut_depth, lower_probcut, upper_probcut, list);
		}

		
		
		//fisrt move
		RXMove* move = list->next;
		
		if(board.n_empties<=MIN_DEPTH_USE_ENDCUT) {
			board.do_move(*move);
			bestscore = -EG_PVS_ETC_mobility(threadID, board, false, -alpha-VALUE_DISC, -alpha, false);
			board.undo_move(*move);
		} else {
			sBoard.do_move(*move);
			bestscore = -EG_NWS_XEndCut(threadID, sBoard, pvDev, selectivity, child_selective_cutoff, -alpha-VALUE_DISC, false);
			sBoard.undo_move(*move);
		}

		//interrupt search
		if(abort.load()  || thread_should_stop(threadID))
			return INTERRUPT_SEARCH;

		//assert(bestscore != -INTERRUPT_SEARCH);
		
		bestmove = move->position;
		list = list->next;
		
		if(child_selective_cutoff)	
			selective_cutoff = true;
		
		
		int score;
		for(RXMove* iter = list->next; !abort.load()  && bestscore<=alpha && iter != NULL; iter = iter->next, list = list->next) {

//			//assert(bestscore >= -MAX_SCORE);
//			if(bestscore<-MAX_SCORE)
//				std::cout << "Error" << std::endl;

			
			 if(activeThreads > 1 
				&& board.n_empties>MIN_EMPTIES_SPLITPOINT && (list->next)->next != NULL
				&& !abort.load()   && idle_thread_exists(threadID) && !thread_should_stop(threadID)
				&& split(sBoard, false, pvDev, board.n_empties, selectivity, selective_cutoff, child_selective_cutoff,
						alpha, (alpha + VALUE_DISC), bestscore, bestmove, list, threadID, RXSplitPoint::END_XPROBCUT))
				
				break;
			
			
			if(board.n_empties<=MIN_DEPTH_USE_ENDCUT) {
				board.do_move(*iter);
				score = -EG_PVS_ETC_mobility(threadID, board, false, -alpha-VALUE_DISC, -alpha, false);
				board.undo_move(*iter);
			} else {
				sBoard.do_move(*iter);
				score = -EG_NWS_XEndCut(threadID, sBoard, pvDev+1, selectivity, child_selective_cutoff, -alpha-VALUE_DISC, false);
				sBoard.undo_move(*iter);
			}

			//interrupt search
			if(abort.load()  ||thread_should_stop(threadID))
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
			
	hTable->update(board.hash_code, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, bestscore, bestmove);
	if(pvDev < 3)
		hTable_PV->update(board.hash_code, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, bestscore, bestmove);
		
	return bestscore;


}

// EG_SP_search_XEndcut() is used to search from a PV split point.  This function
// is called by each thread working at the split point.  It is similar to
// the normal EG_NWS_XEndCut() function, but simpler.  Because we have already
// probed the hash table and searched the first move before splitting, we
// don't have to repeat all this work in EG_SP_search_XEndcut().  We also don't
// need to store anything to the hash table here:  This is taken care of
// after we return from the split point.

void RXEngine::EG_SP_search_XEndcut(RXSplitPoint* sp, const unsigned int threadID) {
	
	//    assert(threadID >= 0 && threadID < activeThreads);
	//    assert(activeThreads > 1);	
	
	RXBBPatterns& sBoard = sp->sBoardStack[threadID];
	sBoard = *(sp->sBoard); //operator=
	RXBitBoard& board = sBoard.board;
	board.n_nodes = 0;
	
	//here sp->alpha is const	
    while(sp->bestscore <= sp->alpha && !abort.load()  && !thread_should_stop(threadID)) {
		
		pthread_mutex_lock(&(sp->lock));
		
		RXMove* move;
		if(sp->list != NULL && sp->list->next != NULL) {
			
			move = sp->list->next;
			sp->list = sp->list->next;
			
		} else {
			pthread_mutex_unlock(&(sp->lock));
			break;
		}	
		
		
		//bool child_selective_cutoff = sp->child_selective_cutoff;
		
      	pthread_mutex_unlock(&(sp->lock));
		
		int alpha = sp->alpha; //local copy
		
		bool child_selective_cutoff = false;
		int score;
		if(board.n_empties<=MIN_DEPTH_USE_ENDCUT) {
			board.do_move(*move);
			score = -EG_PVS_ETC_mobility(threadID, board, false, -alpha-VALUE_DISC, -alpha, false);
			board.undo_move(*move);
		} else {
			sBoard.do_move(*move);
			score = -EG_NWS_XEndCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, child_selective_cutoff, -alpha-VALUE_DISC, false);
			sBoard.undo_move(*move);
		}
		
		
      	if(abort.load() || thread_should_stop(threadID))
			break;
		
		//assert(score != -INTERRUPT_SEARCH);
		
		//update      
     	pthread_mutex_lock(&(sp->lock));
		
      	if(!abort.load() && !thread_should_stop(threadID)) {
			
			sp->child_selective_cutoff = child_selective_cutoff;
			
      		if(sp->child_selective_cutoff)
				sp->selective_cutoff = true;
			
      		// New best move?
     		if(score > sp->bestscore) {
        		sp->bestscore = score;
				sp->bestmove = move->position;
       			if(score > sp->alpha) {
					sp->explored = true;
				}
      		}
			
		}
		
		pthread_mutex_unlock(&(sp->lock));
    }
	
    pthread_mutex_lock(&(sp->lock));
	
	sp->sBoard->board.n_nodes += board.n_nodes;
	
    sp->slaves[threadID] = false;
	sp->n_Slaves--;
	
    pthread_mutex_unlock(&(sp->lock));
} 

/*!
 * \brief Principal Variation Search algorithm at the root of the tree.
 *
 * This function solves the position provided within the limits set by the alpha
 * and beta bounds. The list parameter is updated so that the bestmove is the
 * first of the list when the search ended.
 *
 * \param sBoard      	sBoard.
 * \param selectivity 	selectivity.
 * \param alpha      	lower bound.
 * \param beta       	upper bound.
 * \param list   		List of legal moves (should actually contain moves !).
*/
void RXEngine::EG_PVS_root(RXBBPatterns& sBoard, const int selectivity, int alpha, int beta, RXMove* list)
{
	
	//	assert(alpha>=-64*VALUE_DISC && beta<=64*VALUE_DISC);
	
	
	/*
	 *log << "[" << alpha << " ; " << beta << "]" << std::endl;
	 */
	
	RXMove* iter = list->next;
	
	int bestmove = iter->position;
	
	RXBitBoard& board = sBoard.board;
	
	int lower = alpha;
	int upper = beta;
	
	bool selective_cutoff = false;
	bool child_selective_cutoff = false;
	
	/* first move */
	first_move = true;
	
	sBoard.do_move(*iter);
	
	
	int bestscore;
	if (board.n_empties == 0) {
		bestscore = -board.final_score();
	} else if (board.n_empties == 1) {
		bestscore = -board.final_score_1();
	} else if (board.n_empties == 2) {
		bestscore = -board.final_score_2(-upper, -lower, false);
	} else if (board.n_empties == 3) {
		bestscore = -board.final_score_3(-upper, -lower, false);
	} else if (board.n_empties == 4) {
		bestscore = -board.final_score_4(-upper, -lower, false);
	} else if (board.n_empties < EG_MEDIUM_TO_SHALLOW) {
		bestscore = -EG_alphabeta_parity(0, board, -upper, -lower, false);
	} else if (board.n_empties < EG_MEDIUM_HI_TO_LOW) {
		bestscore = -EG_PVS_hash_mobility(0, board, true, -upper, -lower, false);
	} else  if (board.n_empties < EG_DEEP_TO_MEDIUM) {
		bestscore = -EG_PVS_ETC_mobility(0, board, true, -upper, -lower, false);
	} else {
		bestscore = -EG_PVS_deep(0, sBoard, true, selectivity, child_selective_cutoff, -upper, -lower, false);
	}
	
	sBoard.undo_move(*iter);
	
	if(!abort.load()  && bestscore != -INTERRUPT_SEARCH) {
		
		if(search_client == RXSearch::kGGSMode) {	// GGS mode
			
			if(dependent_time && board.n_empties>19)
				manager->sendMsg(showBestmove(board.n_empties, false, selectivity, lower, upper, bestscore, bestmove));
		}
		
		if (bestscore > lower)
			lower = bestscore;
		
		if (child_selective_cutoff)
			selective_cutoff = true;
		
		/* other moves : try to refute the first/best one */
		int score;
		first_move = false;
		
		for (iter = iter->next; !abort.load()  && lower < upper && iter != NULL; iter = iter->next) {
			
//			if(activeThreads > 1 && iter->next != NULL && board.n_empties > EG_DEEP_TO_MEDIUM
//			   && !abort.load() && idle_thread_exists(0) && !thread_should_stop(0)
//			   && split(sBoard, true, 0, board.n_empties, selectivity, selective_cutoff, child_selective_cutoff,
//						lower, upper, bestscore, bestmove, iter, 0, RXSplitPoint::END_ROOT)) {
//				
//				
//				break;
//			}
			
			
			sBoard.do_move(*iter);
			
			if (board.n_empties == 1) {
				score = -board.final_score_1();
			} else if (board.n_empties == 2) {
				score = -board.final_score_2(-upper, -lower, false);
			} else if (board.n_empties == 3) {
				score = -board.final_score_3(-upper, -lower, false);
			} else if (board.n_empties == 4) {
				score = -board.final_score_4(-upper, -lower, false);
			} else {
				
//				//multi_pv PV == true
//				if (board.n_empties < EG_MEDIUM_TO_SHALLOW)
//					score = -EG_alphabeta_parity(0, board, -lower - VALUE_DISC, -lower, false);
//				else if (board.n_empties < EG_MEDIUM_HI_TO_LOW)
//					score = -EG_PVS_hash_mobility(0, board, true, -lower - VALUE_DISC, -lower, false);
//				else if (board.n_empties < EG_DEEP_TO_MEDIUM)
//					score = -EG_PVS_ETC_mobility(0, board, true, -lower - VALUE_DISC, -lower, false); //multi-PV pv == true ????
//				else
//					score = -EG_PVS_deep(0, sBoard, true, selectivity, child_selective_cutoff, -lower - VALUE_DISC, -lower, false); //multi-PV pv == true ????

				//simple_pv PV == false
				if (board.n_empties < EG_MEDIUM_TO_SHALLOW)
					score = -EG_alphabeta_parity(0, board, -lower - VALUE_DISC, -lower, false);
				else if (board.n_empties < EG_MEDIUM_HI_TO_LOW)
					score = -EG_PVS_hash_mobility(0, board, false, -lower - VALUE_DISC, -lower, false);
				else if (board.n_empties < EG_DEEP_TO_MEDIUM)
					score = -EG_PVS_ETC_mobility(0, board, false, -lower - VALUE_DISC, -lower, false); //simple-PV pv == false ????
				else
					score = -EG_PVS_deep(0, sBoard, false, selectivity, child_selective_cutoff, -lower - VALUE_DISC, -lower, false); //simple-PV pv == false ????
				
				
				if (!abort.load()  && lower < score && score < upper) {
					
					if(search_client == RXSearch::kGGSMode) {	// GGS mode
						
						if(dependent_time && board.n_empties>19)
							manager->sendMsg("         " + RXMove::index_to_coord(iter->position) + " is better? ");
						
					}
					
					if (board.n_empties < EG_MEDIUM_TO_SHALLOW)
						score = -EG_alphabeta_parity(0, board, -upper, -score, false);
					else if (board.n_empties < EG_MEDIUM_HI_TO_LOW)
						score = -EG_PVS_hash_mobility(0, board, true, -upper, -score, false);
					else if (board.n_empties < EG_DEEP_TO_MEDIUM)
						score = -EG_PVS_ETC_mobility(0, board, true, -upper, -score, false);
					else {
						extra_time++;
						
						if(selectivity != NO_SELECT)
							score = -EG_PVS_deep(0, sBoard, true, selectivity, child_selective_cutoff, -upper, child_selective_cutoff? -lower : -score, false);
						else
							score = -EG_PVS_deep(0, sBoard, true, selectivity, child_selective_cutoff, -upper, -score, false);
						
						extra_time--;
					}
					
					
				}
				
				
				
			}
			
			
			
			sBoard.undo_move(*iter);
			
			
			if (!abort.load()  && score != -INTERRUPT_SEARCH) {
				
				if(score > bestscore) {
					bestmove = iter->position;
					bestscore = score;
					
					if(search_client == RXSearch::kGGSMode)	// GGS mode
						if(dependent_time && board.n_empties>19)
							manager->sendMsg(showBestmove(board.n_empties, false, selectivity, lower, upper, bestscore, bestmove));
					
					if (bestscore > lower)
						lower = bestscore;
				}
			}
			
			if (child_selective_cutoff)
				selective_cutoff = true;
			
			
		}
		
		extra_time = 0;
		
		if(bestscore>=beta)
			selective_cutoff = child_selective_cutoff;
		
		list->sort_bestmove(bestmove);
		list->next->score = bestscore;
		list->next->selectivity = selective_cutoff? selectivity : NO_SELECT;
		list->next->depth = board.n_empties;
		
		
		hTable->update(sBoard.board.hash_code, true, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
		
		
	}
	
}

// EG_SP_search_root() is used to search from a PV split point.  This function
// is called by each thread working at the split point.  It is similar to
// the normal EG_PVS_root() function, but simpler.  Because we have already
// probed the hash table and searched the first move before splitting, we
// don't have to repeat all this work in EG_SP_search_DEEP().  We also don't
// need to store anything to the hash table here:  This is taken care of
// after we return from the split point.

void RXEngine::EG_SP_search_root(RXSplitPoint* sp, const unsigned int threadID) {
	
	//    assert(threadID >= 0 && threadID < activeThreads);
	//    assert(activeThreads > 1);
	
	
	RXBBPatterns& sBoard = sp->sBoardStack[threadID];
	sBoard = *(sp->sBoard); //operator=
	RXBitBoard& board = sBoard.board;
	board.n_nodes = 0;
	
	//here sp->beta is const
    while(sp->alpha < sp->beta && !abort.load() && !thread_should_stop(threadID)) {
		
      	pthread_mutex_lock(&(sp->lock));
		
		
		RXMove* move;
		if(sp->list != NULL) {
			
			
			move = sp->list;
			sp->list = sp->list->next;
			
			
		} else {
			pthread_mutex_unlock(&(sp->lock));
			break;
		}	
		
		
		bool child_selective_cutoff = sp->child_selective_cutoff;
		
      	pthread_mutex_unlock(&(sp->lock));
		
		
		sBoard.do_move(*move);
		
		int alpha = sp->alpha; //local copy
		
		int score = -EG_PVS_deep(threadID, sBoard, false, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, -alpha, false);
		
		if (!abort.load()  && alpha < score && score < sp->beta) {
			
			extra_time++;
			
			if(dependent_time && board.n_empties>19)
				manager->sendMsg("         " + RXMove::index_to_coord(move->position) + " is better? ");
			
			if(sp->selectivity != NO_SELECT)
				score = -EG_PVS_deep(threadID, sBoard, true, sp->selectivity, child_selective_cutoff, -sp->beta, (child_selective_cutoff? -sp->alpha : -score), false);
			else
				score = -EG_PVS_deep(threadID, sBoard, true, sp->selectivity, child_selective_cutoff, -sp->beta, -score, false);
			
			extra_time--; //thread-safe?
			
		}
		
		sBoard.undo_move(*move);
		
      	if(abort.load() || thread_should_stop(threadID))
			break;
		
		//assert(score != -INTERRUPT_SEARCH);
		
		//update      
     	pthread_mutex_lock(&(sp->lock));
		
      	if(!abort.load() && !thread_should_stop(threadID)) {
			
			sp->child_selective_cutoff = child_selective_cutoff;
			
      		if(sp->child_selective_cutoff)
				sp->selective_cutoff = true;
			
      		// New best move?
     		if(score > sp->bestscore) {
        		sp->bestscore = score;
				sp->bestmove = move->position;
				
				if(dependent_time && board.n_empties>19)
					manager->sendMsg(showBestmove(board.n_empties, false, sp->selectivity, sp->alpha, sp->beta, sp->bestscore, sp->bestmove));
				
       			if(score > sp->alpha) {
					
          			if(score >= sp->beta) {
						sp->explored = true;
          			} else {
						sp->alpha = score;
					}
					
				}
      		}
			
		}
		
		pthread_mutex_unlock(&(sp->lock));
    }
	
    pthread_mutex_lock(&(sp->lock));
	
	sp->sBoard->board.n_nodes += board.n_nodes;
	
    sp->slaves[threadID] = false;
	sp->n_Slaves--;
	
    pthread_mutex_unlock(&(sp->lock));
} 

/*!
 * \brief Driver for solver.
 *
 * This function reduced and moved the search window
 *
 * \param sBoard      	sBoard.
 * \param selectivity 	selectivity.
 * \param list   		List of legal moves (should actually contain moves !).
*/

void RXEngine::EG_driver(RXBBPatterns& sBoard, int selectivity, int end_selectivity, RXMove* list) {
	
	set_type_search(ENDGAME);
	
	int modulo = list->next->score % (2*VALUE_DISC);
	if( modulo != 0) {
		list->next->score -= modulo;
		if(modulo > VALUE_DISC)
			list->next->score += 2*VALUE_DISC;
	}
	
	list->next->score = std::min(64*VALUE_DISC, std::max(-64*VALUE_DISC, list->next->score));
	
	
	int s_alpha = search_alpha;
	if(s_alpha<0) {
		if(s_alpha%(2*VALUE_DISC) != 0)
			s_alpha -= 2*VALUE_DISC + s_alpha%(2*VALUE_DISC);
	} else {
		s_alpha -= s_alpha%(2*VALUE_DISC);
	}
	
	int s_beta  = search_beta;
	if(s_beta <0) {
		s_beta  -= s_beta%(2*VALUE_DISC);
	} else {
		if(s_beta%(2*VALUE_DISC) != 0)
			s_beta  += 2*VALUE_DISC - s_beta%(2*VALUE_DISC);
	}
	
	s_alpha = std::max(-64*VALUE_DISC, s_alpha);
	s_beta  = std::min( 64*VALUE_DISC, s_beta);
	
	
	for(; !abort.load()  && selectivity <= end_selectivity; selectivity++) {
		
		selectivity = std::max(std::min(NO_SELECT, 26-sBoard.board.n_empties), std::max(EG_HIGH_SELECT, selectivity));
		

//	for(selectivity = 1 ; !abort.load()  && selectivity <= NO_SELECT; selectivity+=(NO_SELECT-1)) {
		
		set_select_search(selectivity);
		
		if(dependent_time)
			determine_move_time(sBoard.board);
	
		
		MIN_DEPTH_USE_ENDCUT = std::min(18, 21-selectivity);
		EG_DEEP_TO_MEDIUM = MIN_DEPTH_USE_ENDCUT;
		
		int eTime_start_level = get_current_time();
		
		time_startLevel = eTime_start_level;
		
		
		sBoard.board.n_nodes = 0;
		
				
		int alpha = std::max(s_alpha, std::min(s_beta-VALUE_DISC, list->next->score - VALUE_DISC));
		int beta  = std::min(s_beta, std::max(s_alpha+VALUE_DISC, list->next->score + VALUE_DISC));
		
		//always even window
		if(alpha<0) {
			if(alpha%(2*VALUE_DISC) != 0)
				alpha -= 2*VALUE_DISC + alpha%(2*VALUE_DISC) ;
		} else {
			alpha -= alpha%(2*VALUE_DISC);
		}
		
		if(beta <0) {
			beta  -= beta%(2*VALUE_DISC);
		} else {
			if(beta%(2*VALUE_DISC) != 0)
				beta  += 2*VALUE_DISC - beta%(2*VALUE_DISC);
		}
		
		EG_PVS_root(sBoard, selectivity, alpha, beta, list);
		
		int left = 2;
		int right = 2;
		
		while (!abort.load()  && !(alpha < list->next->score && list->next->score < beta)) {
			
			if (list->next->score <= alpha) {
				
				if(alpha <= s_alpha)
					break;
								
				left *=2;
				
				alpha = list->next->score - left*VALUE_DISC;
				
			} else if (list->next->score >= beta) {
				
				if(beta >= s_beta)
					break;
				
				right *=2;
				
				beta  = list->next->score + right*VALUE_DISC;
			}
			
			
			alpha = std::max(s_alpha, std::min(s_beta-VALUE_DISC, alpha));
			beta  = std::min(s_beta, std::max(s_alpha+VALUE_DISC, beta ));
			
			//always even window
			if(alpha<0) {
				if(alpha%(2*VALUE_DISC) != 0)
					alpha -= 2*VALUE_DISC + alpha%(2*VALUE_DISC) ;
			} else {
				alpha -= alpha%(2*VALUE_DISC);
			}
			
			if(beta <0) {
				beta  -= beta%(2*VALUE_DISC);
			} else {
				if(beta%(2*VALUE_DISC) != 0)
					beta  += 2*VALUE_DISC - beta%(2*VALUE_DISC);
			}
			
			EG_PVS_root(sBoard, selectivity, alpha, beta, list);
			
		};
		
		
		extra_time = 0;
		
		//check PV at 100%
		if(!abort.load() && selectivity == NO_SELECT && s_alpha < list->next->score && list->next->score < s_beta) {
			RXSearch::t_client save_client = search_client;
			search_client = RXSearch::kPrivate;
			check_PV(search_sBoard, list->next->score, list->next->score-VALUE_DISC, list->next->score+VALUE_DISC);
			search_client = save_client;
		}
		
		best_answer.position = list->next->position;
		best_answer.score = list->next->score;
		best_answer.depth = list->next->depth;
		best_answer.selectivity = CONFIDENCE[list->next->selectivity];
		std::ostringstream buf;
		hTable->mainline(buf, sBoard.board, type_hashtable);
		best_answer.mainLine = buf.str();
		
		best_answer.nodes += sBoard.board.n_nodes;
		
		
		int eTime = get_current_time();
		
		
		//unsynchronized acces
		RXHashValue entry;
		if(hTable->get(sBoard.board, type_hashtable, entry) && entry.selectivity>=selectivity) {
			int type = EXACT;
			
			int score = list->next->score;
			if(entry.lower == entry.upper) {
				if(abort.load())
					type = INTERRUPT;
			} else if(list->next->score == entry.lower || entry.upper ==  MAX_SCORE) {
				type = SUPERIOR;
				score = entry.lower;
			} else if(list->next->score == entry.upper || entry.lower == -MAX_SCORE){
				type = INFERIOR;
				score = entry.upper;
			}
			
			
			
            //*log << display(sBoard.board, type, selectivity, list->next->score, eTime, eTime - eTime_start_level) << std::endl;
            *log << display(sBoard.board, type, selectivity, score, eTime, eTime - eTime_start_level) << std::endl;
            
		}
		
		if(abort.load() )
			break;
		
		int pTime = pTime_next_level(sBoard.board, eTime - eTime_start_level);
		time_nextLevel = pTime;
		
		if(probable_timeout(pTime)) {
			abort.store(true);
			break;
		}
		
		
		
	}
	
}


/*!
 * \brief Extension of research until the solution.
 *
 * This function prepare parameters for solver
 *
 * \param sBoard      	sBoard.
 * \param alpha      	lower bound.
 * \param beta       	upper bound.
 * \param passed		true if precedent move is PASS.
 * \return        		the final score, as a disc difference * VALUEDISC.
*/

int RXEngine::EG_pv_extension(int threadID, RXBitBoard& board, const bool pv, int alpha, int beta, bool passed) {
				 	
//		int lower =  static_cast<int>(floor(static_cast<float>(alpha)/VALUE_DISC));
//		if(lower %2 != 0)
//			lower--;
//		lower *= VALUE_DISC;
//		
//		lower = std::max(-64*VALUE_DISC, std::min(63*VALUE_DISC, lower));
//		
//		int upper =  static_cast<int>(ceil(static_cast<float>(beta)/VALUE_DISC));
//		if(upper %2 != 0)
//			upper++;
//		upper *= VALUE_DISC;
//
//		upper = std::min(64*VALUE_DISC, std::max(-63*VALUE_DISC, upper));
//
//		if(board.n_empties+1 < EG_MEDIUM_HI_TO_LOW)
//			return EG_PVS_hash_mobility(threadID, board, pv, lower, upper, passed);
//		else
//			return EG_PVS_ETC_mobility(threadID, board, pv,lower, upper, passed);

	if(board.n_empties+1 < EG_MEDIUM_HI_TO_LOW)
		return EG_PVS_hash_mobility(threadID, board, pv, alpha, beta, passed);
	else
		return EG_PVS_ETC_mobility(threadID, board, pv, alpha, beta, passed);
	
	
}

void RXEngine::check_PV(RXBBPatterns& sBoard, const int score, const int alpha, const int beta) {
	
	RXBitBoard& board = sBoard.board;
	
	if(board.n_empties>6) { //hash limit
		
		//move in hash
		int movePV = NOMOVE;
		RXHashValue entry;
		if(hTable->get(board, type_hashtable, entry)) {
			
			if(entry.depth >= board.n_empties && entry.selectivity == NO_SELECT) {
				
				if(entry.lower ==  entry.upper) {
					movePV = entry.move;
				} else if(entry.lower == score && entry.upper >= beta) {
					if(!(alpha < entry.lower && entry.lower < beta))
						movePV = entry.move;
				} else if(entry.upper == score && entry.lower <= alpha) {
					if(!(alpha < entry.upper && entry.upper < beta))
						movePV = entry.move;
				}
				
			}
		}
		
		//find move
		if (movePV == NOMOVE) {
			
			int lower = alpha;
			int upper = beta;
			
			if(score <= lower)
				upper = lower + VALUE_DISC;
			
			if (score >= upper)
				lower = upper - VALUE_DISC;
			
			
			RXMove list[32];
			int n_moves = board.moves_producing(list);
			
			int value = UNDEF_SCORE;
			if(n_moves>0) {
				for(RXMove* iter = list->next; iter != NULL; iter= iter->next)
					((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
				
				EG_PVS_root(sBoard, NO_SELECT, lower, upper, list);
				movePV = list->next->position;
				value  = list->next->score;
			} else {
				board.do_pass();
				n_moves = board.moves_producing(list);
				if(n_moves>0) {
					for(RXMove* iter = list->next; iter != NULL; iter = iter->next)
						((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
					
					EG_PVS_root(sBoard, NO_SELECT, lower, upper, list);
					movePV = PASS;
					value = -list->next->score;
				}
				board.do_pass();				
			}
			
			if(movePV != NOMOVE)
				hTable->update(board.hash_code, true, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, value, movePV);
			
			
		}
		
		if(movePV != NOMOVE) {
			
			//check value;
			RXHashValue entry;
			if(hTable->get(board, type_hashtable, entry)) {
				
				if(entry.depth >= board.n_empties && entry.selectivity == NO_SELECT) {
					
					
					if(entry.lower>=beta) {
						if (entry.upper<entry.lower) {
							manager->sendMsg("ERROR ON PV 1\n");
						}
					} else if(entry.upper<=alpha) {
						if(entry.upper<entry.lower) {
							manager->sendMsg("ERROR ON PV 2\n");
						}
					} else if(!(alpha < entry.lower && entry.upper < beta && entry.lower == entry.upper && entry.lower == score)) {
						
						std::ostringstream buffer;
						buffer << "[ " << alpha << " ; " << beta << " ] ";
						buffer << "[ " << entry.lower << " ; " << entry.upper << " ] ";
						buffer << "score : " << score << " move : " << RXMove::index_to_coord(entry.move) << std::endl;
						
						manager->sendMsg(buffer.str());
						
						manager->sendMsg("ERROR ON PV 3\n");
					}
					
				}
				
			} else {
				manager->sendMsg("ERROR ON PV 4\n");
			}
			
			RXMove move;
			
			if(movePV == PASS)
				board.do_pass();
			else {
				((board).*(board.generate_move[movePV]))(move);
				((sBoard).*(sBoard.update_patterns[movePV][board.player]))(move);
				sBoard.do_move(move);
			}
			
			check_PV(sBoard, -score, -beta, -alpha);
			
			if(movePV == PASS)
				board.do_pass();
			else
				sBoard.undo_move(move);
			
		}
	}
	
}

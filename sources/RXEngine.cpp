/*
 *  RXEngine.cpp
 *  BitBoard
 *
 *  Created by Bruno Causse on 10/08/05.
 *  Copyright 2005-2024 personnel. All rights reserved.
 *
 */
#include <iomanip>
#include <cmath>
//#include <algorithm>
#include <fstream>
#include <sstream>
#include <sys/time.h>



#include "RXEngine.hpp"
#include "RXRoxane.hpp"

const int RXEngine::CHECK_TO_LAST_THREE = 4; // DO NOT CHANGE


const int RXEngine::HASHTABLE = 0;
const int RXEngine::INFERIOR = 1;
const int RXEngine::EXACT = 2;
const int RXEngine::SUPERIOR = 3;
const int RXEngine::INTERRUPT = 4;
const int RXEngine::GGS_MSG = 5;

const int RXEngine::CONFIDENCE[]   = {  72,   84,   91,   95,   98,   100}; // 99
//const float RXEngine::PERCENTILE[] = {1.1f, 1.4f, 1.8f, 2.3f, 2.9f};		//  3.6f
const float RXEngine::PERCENTILE[] = {1.2f, 1.45f, 1.8f, 2.3f, 2.9f};
const int RXEngine::NO_SELECT = 5;

const int RXEngine::DEPTH_BOOSTER = 4;

const bool RXEngine::USE_SINGULAR_EXTENSION = false;
const bool RXEngine::USE_SINGULAR_PROBCUT   = false;


std::vector< std::vector<int> >  RXEngine::probcut_data;

extern "C"
void* init_threadHelper(void* pt)  {
    
    RXEngine* engine = (RXEngine*)(pt);
    
    engine->idle_loop();
    
    return NULL;
    
}

extern "C"
void* init_pthreadMain(void* pt)  {
    
    RXEngine* engine = (RXEngine*)(pt);
    
    engine->run();
    
    return NULL;
    
}


RXEngine::RXEngine(RXRoxane* _manager, std::string filename, int maxThread):
manager(_manager), THREAD_MAX(maxThread),
select_search(0), allThreadsShouldExit(false), allThreadsShouldSleep(true),
threads(maxThread, RXThread(maxThread, ACTIVE_SPLITPOINT_MAX)) {
    
    pthread_mutex_init(&MP_sync, NULL);
    pthread_mutex_init(&mutex, NULL);
    
    init_threads();
    
    hTable_shallow = new RXHashShallow(19);
    
    log = new std::ofstream(filename.c_str());
    
    
}


RXEngine::~RXEngine() {
    
    //order inverted
    
    if (log && log->is_open())
        log->close();
    
    delete log;
    
    delete hTable_shallow;
    
    stop_threads();
    
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&MP_sync);
    
}

void RXEngine::probcut_coefficients() {
    
    probcut_data.resize(60);
    
    for (int n_empties = 59; n_empties>0; n_empties--) {
        
        probcut_data[n_empties].resize(n_empties+1);
        
        int x = 64 - n_empties;
        
        int coeff_14 = static_cast<int>(round(0.1756*x*x - 3.17*x + 311)); //depth 14 probcut_depth 6
        int coeff_15 = static_cast<int>(round(0.1306*x*x - 2.45*x + 291)); //depth 15 probcut_depth 7
        int coeff_16 = static_cast<int>(round(0.1867*x*x - 3.69*x + 265)); //depth 16 probcut_depth 8
        int coeff_17 = static_cast<int>(round(0.1551*x*x - 2.77*x + 243)); //depth 17 probcut_depth 9
        
        
        switch(n_empties) {
                
            case 59: probcut_data[n_empties][59] = coeff_15 - 47;
            case 58: probcut_data[n_empties][58] = coeff_14 - 47;
                
            case 57: probcut_data[n_empties][57] = coeff_17 - 46;
            case 56: probcut_data[n_empties][56] = coeff_16 - 46;
            case 55: probcut_data[n_empties][55] = coeff_15 - 46;
            case 54: probcut_data[n_empties][54] = coeff_14 - 46;
                
            case 53: probcut_data[n_empties][53] = coeff_17 - 45;
            case 52: probcut_data[n_empties][52] = coeff_16 - 45;
            case 51: probcut_data[n_empties][51] = coeff_15 - 45;
            case 50: probcut_data[n_empties][50] = coeff_14 - 45;
                
            case 49: probcut_data[n_empties][49] = coeff_17 - 44;
            case 48: probcut_data[n_empties][48] = coeff_16 - 44;
            case 47: probcut_data[n_empties][47] = coeff_15 - 44;
            case 46: probcut_data[n_empties][46] = coeff_14 - 44;
                
            case 45: probcut_data[n_empties][45] = coeff_17 - 42;
            case 44: probcut_data[n_empties][44] = coeff_16 - 42;
            case 43: probcut_data[n_empties][43] = coeff_15 - 42;
            case 42: probcut_data[n_empties][42] = coeff_14 - 42;
                
            case 41: probcut_data[n_empties][41] = coeff_17 - 39;
            case 40: probcut_data[n_empties][40] = coeff_16 - 39;
            case 39: probcut_data[n_empties][39] = coeff_15 - 39;
            case 38: probcut_data[n_empties][38] = coeff_14 - 39;
                
            case 37: probcut_data[n_empties][37] = coeff_17 - 35;
            case 36: probcut_data[n_empties][36] = coeff_16 - 35;
            case 35: probcut_data[n_empties][35] = coeff_15 - 35;
            case 34: probcut_data[n_empties][34] = coeff_14 - 35;
                
            case 33: probcut_data[n_empties][33] = coeff_17 - 30;
            case 32: probcut_data[n_empties][32] = coeff_16 - 30;
            case 31: probcut_data[n_empties][31] = coeff_15 - 30;
            case 30: probcut_data[n_empties][30] = coeff_14 - 30;
                
            case 29: probcut_data[n_empties][29] = coeff_17 - 24;
            case 28: probcut_data[n_empties][28] = coeff_16 - 24;
            case 27: probcut_data[n_empties][27] = coeff_15 - 24;
            case 26: probcut_data[n_empties][26] = coeff_14 - 24;
                
            case 25: probcut_data[n_empties][25] = coeff_17 - 17;
            case 24: probcut_data[n_empties][24] = coeff_16 - 17;
            case 23: probcut_data[n_empties][23] = coeff_15 - 17;
            case 22: probcut_data[n_empties][22] = coeff_14 - 17;
                
            case 21: probcut_data[n_empties][21] = coeff_17 - 9;
            case 20: probcut_data[n_empties][20] = coeff_16 - 9;
            case 19: probcut_data[n_empties][19] = coeff_15 - 9;
            case 18: probcut_data[n_empties][18] = coeff_14 - 9;
                
            case 17: probcut_data[n_empties][17] = coeff_17;
            case 16: probcut_data[n_empties][16] = coeff_16;
            case 15: probcut_data[n_empties][15] = coeff_15;
            case 14: probcut_data[n_empties][14] = coeff_14;
                
            case 13: probcut_data[n_empties][13] = coeff_17 + 10;
            case 12: probcut_data[n_empties][12] = coeff_16 + 10;
            case 11: probcut_data[n_empties][11] = coeff_15 + 10;
            case 10: probcut_data[n_empties][10] = coeff_14 + 10 + 20; // malus
                
            case  9: probcut_data[n_empties][ 9] = coeff_17 + 21;
            case  8: probcut_data[n_empties][ 8] = coeff_16 + 21;
            case  7: probcut_data[n_empties][ 7] = coeff_15 + 21;
            case  6: probcut_data[n_empties][ 6] = coeff_14 + 21 + 30; // malus
                
            case  5: probcut_data[n_empties][ 5] = coeff_17 + 50;
            case  4: probcut_data[n_empties][ 4] = coeff_16 + 50;
            case  3: probcut_data[n_empties][ 3] = coeff_15 + 50;
            case  2: probcut_data[n_empties][ 2] = MAX_SCORE;
                
            case  1: probcut_data[n_empties][ 1] = MAX_SCORE;
            case  0: probcut_data[n_empties][ 0] = MAX_SCORE;
        }
        
    }
    
}


unsigned int RXEngine::confidence_to_selectivity(int c) {
    if(1<=c && c<=99)
        for(int i = 0; i<NO_SELECT; i++)
            if(CONFIDENCE[i] >= c)
                return i;
    
    return NO_SELECT;
}

unsigned int RXEngine::selectivity_to_confidence(int s) {
    if(0<=s && s<=NO_SELECT)
        return CONFIDENCE[s];
    
    return CONFIDENCE[NO_SELECT];
}

/*
 singular extension
 
 
 conditions
 n_moves > 0
 depth >=2
 
 no hash
 
 */
bool RXEngine::singular_move(int threadID, RXBBPatterns& sBoard, const int selectivity, const int depth, int alpha, RXMove* list, const int position) {
    
    
    bool child_selective_cutoff = false; //dunny
    RXMove& lastMove = threads[threadID]._move[sBoard.board.n_empties-1][1];
    
    int score = -MAX_SCORE;
    for(RXMove* iter = list->next;!abort.load() && iter != NULL; iter = iter->next) {
        
        if(iter->position != position) {
            
            sBoard.do_move(*iter);
            
            if(depth > MIN_DEPTH_USE_PROBCUT) {
                score = -MG_NWS_XProbCut(threadID, sBoard, 0, selectivity, depth-1, child_selective_cutoff, -alpha-1, false);
            } else if(depth == 4 ){
                score = -PVS_last_three_ply(threadID, sBoard, -alpha-1, -alpha, false);
            } else if(depth == 3) {
                score = -alphabeta_last_two_ply(threadID, sBoard, -alpha-1, -alpha, false);
            } else {
                
                RXBitBoard& board = sBoard.board;
                
                int bestscore = UNDEF_SCORE; //masquage
                
                const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
                for(RXSquareList* empties = board.empties_list->next;bestscore < -alpha && empties->position != NOMOVE; empties = empties->next) { //*2
                    if(legal_movesBB & 1ULL<<empties->position) {
                        ((board).*(board.generate_flips[empties->position]))(lastMove);
                        ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(lastMove);
                        board.n_nodes++;
                        
                        score = -sBoard.get_score(lastMove);
                        if (score>bestscore) {
                            bestscore = score;
                        }
                        
                    }
                }
                
                
                if(bestscore == UNDEF_SCORE) {
                    //PASS
                    sBoard.board.do_pass();
                    score = -sBoard.get_score();
                    sBoard.board.do_pass();
                } else {
                    score = bestscore;
                }
            }
            
            
            sBoard.undo_move(*iter);
        }
        
        
        if (abort.load() || score>alpha || thread_should_stop(threadID))
            return false;
        
        
    }
    
    
    return true;
    
    
}


void RXEngine::sort_moves(int threadID, const bool endgame, RXBBPatterns& sBoard, const int depth, const int alpha, const int beta, RXMove* list) {
    
    RXBitBoard& board = sBoard.board;
    
    //sort moves list
    if(list->next != NULL) {
        
        RXMove* iter = list->next;
        
        if(iter->next != NULL) {
            
            const int p = board.player;
            const int o = p^1;
            
            if(depth>3) {
                
                int lower_probcut = -MAX_SCORE;
                int upper_probcut  =  MAX_SCORE;
                probcut_bounds(board, 0, 4, 0, 0, lower_probcut, upper_probcut); //selectivity 72%
                
                int _alpha = std::max(-MAX_SCORE, alpha+lower_probcut);
                
                if(_alpha<= sBoard.get_score()) { //~95%
                    
                    
                    RXMove& lastMove = threads[threadID]._move[board.n_empties-1][1];
                    
                    for(; iter != NULL; iter = iter->next) {
                        ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                        
                        sBoard.do_move(*iter);
                        
                        if(depth>13) {
                            
                            if((depth & 1) == 0)
                                iter->score += PVS_check(threadID, sBoard, 4, -MAX_SCORE, -_alpha, false);
                            else
                                iter->score += PVS_last_three_ply(threadID, sBoard, -MAX_SCORE, -_alpha, false);
                            
                        } else if(depth>6) {
                            
                            if((depth & 1) == 0)
                                iter->score += alphabeta_last_two_ply(threadID, sBoard, -MAX_SCORE, -_alpha, false);
                            else
                                iter->score += PVS_last_three_ply(threadID, sBoard, -MAX_SCORE, -_alpha, false);//*2
                            
                        } else {
                            
                            if((depth & 1) == 0) {
                                
                                iter->score += alphabeta_last_two_ply(threadID, sBoard, -MAX_SCORE, -_alpha, false);
                                
                            } else {
                                
                                int bestscore = UNDEF_SCORE; //masquage
                                
                                const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
                                for(RXSquareList* empties = board.empties_list->next;bestscore < -_alpha && empties->position != NOMOVE; empties = empties->next) { //*2
                                    if(legal_movesBB & 1ULL<<empties->position) { 
                                        ((board).*(board.generate_flips[empties->position]))(lastMove);
                                        ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(lastMove);
                                        board.n_nodes++;
                                        
                                        int score = -sBoard.get_score(lastMove);
                                        if (score>bestscore) {
                                            bestscore = score;
                                        }
                                        
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
                        
                        
                        if(iter->score < -(beta + upper_probcut)) { //95%
                            if(endgame)
                                iter->score /= 4; //16
                            iter->score -= MAX_SCORE; //good move	"probable beta cut"	study in first
                        }
                        
                        //test PVS_Check
                        if(endgame)
                            iter->score += board.get_mobility(board.discs[board.player], board.discs[board.player^1])*VALUE_DISC - (board.get_corner_stability(board.discs[board.player^1])*VALUE_DISC)/16;
                        
                        sBoard.undo_move(*iter);
                        
                    }
                    
                    
                } else {
                    
                    for(; iter != NULL; iter = iter->next) {
                        board.n_nodes++;
                        
                        ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                        iter->score += sBoard.get_score(*iter);
                        
                        if(endgame) {
                            
                            const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                            
                            iter->score += 2*(RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC) - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/8;
                            
                        }
                        
                        
                    }
                }
                
            } else {
                
                for(; iter != NULL; iter = iter->next) {
                    board.n_nodes++;
                    
                    ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                    iter->score += sBoard.get_score(*iter);
                    
                    if(endgame) {
                        
                        const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                        
                        iter->score += 2*(RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC) - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/8;
                        
                    }
                }
            }
            
            list->sort_by_score();
            
        } else {
            ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
        }
        
    }
    
}

bool RXEngine::probcut(int threadID, const bool endgame, RXBBPatterns& sBoard, const int selectivity, const int depth, const int lower_probcut, const int upper_probcut, RXMove* list, const bool hashMove) {
    
    RXBitBoard& board = sBoard.board;
    
    
    int static_eval = sBoard.get_score();
    
    RXMove* list1 = list;
    
    int bestscore = UNDEF_SCORE;
    
    
    if(hashMove) {
        list1 = list1->next;
        
        ((sBoard).*(sBoard.update_patterns[list1->position][board.player]))(*list1);
        
        if(static_eval>lower_probcut) {
            
            bool selectif_cutoff = false;
            bool child_selective_cutoff = false;
            
            
            sBoard.do_move(*list1);
            
            if(depth == 2) {
                
                RXMove& lastMove = threads[threadID]._move[board.n_empties][1];
                
                int bestscore_1 = UNDEF_SCORE;
                
                const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
                for(RXSquareList* empties = board.empties_list->next; bestscore_1 < -upper_probcut+1 && empties->position != NOMOVE; empties = empties->next)
                    if(legal_movesBB & 1ULL<<empties->position) {
                        ((board).*(board.generate_flips[empties->position]))(lastMove);
                        ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(lastMove);
                        
                        board.n_nodes++;
                        
                        int score= -sBoard.get_score(lastMove);
                        if (score>bestscore_1)
                            bestscore_1 = score;
                        
                    }
                
                if(bestscore_1 == UNDEF_SCORE) {
                    //PASS
                    sBoard.board.do_pass();
                    bestscore_1 = -sBoard.get_score();
                    sBoard.board.do_pass();
                }
                
                bestscore = -bestscore_1;
                
            } else if(depth == 3) {
                bestscore = -alphabeta_last_two_ply(threadID, sBoard, -upper_probcut, -upper_probcut+1, false);
            } else if(depth == 4) {
                bestscore = -PVS_last_three_ply(threadID, sBoard, -upper_probcut, -upper_probcut+1, false);
            } else {
                bestscore = -MG_NWS_XProbCut(threadID, sBoard, 0, selectivity, depth-1, child_selective_cutoff, -upper_probcut, false); // pvDev = 0
            }
            
            sBoard.undo_move(*list1);
            
            //interrupt search
            if(abort.load() || thread_should_stop(threadID))
                return false;
            
            if(bestscore >= upper_probcut) { //beta cut
                
                selectif_cutoff=child_selective_cutoff;
                
                hTable->update(board.hashcode(), type_hashtable, selectif_cutoff? MG_SELECT:NO_SELECT, depth, upper_probcut-1, bestscore, list1->position);
                return true;
            }
        }
        
    }
    
    sort_moves(threadID, endgame, sBoard, depth, lower_probcut, upper_probcut, list1);
    
    if(static_eval>lower_probcut) {
        
        //beta prob cut
        for(RXMove* iter = list1->next; iter != NULL; iter = iter->next) {
            
            bool selectif_cutoff = false;
            bool child_selective_cutoff = false;
            
            sBoard.do_move(*iter);
            
            if(depth == 2) {
                RXMove& lastMove = threads[threadID]._move[board.n_empties][1];
                
                int bestscore_1 = UNDEF_SCORE;
                
                const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
                for(RXSquareList* empties = board.empties_list->next; bestscore_1 < -upper_probcut+1 && empties->position != NOMOVE; empties = empties->next)
                    if(legal_movesBB & 1ULL<<empties->position) {
                        ((board).*(board.generate_flips[empties->position]))(lastMove);
                        ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(lastMove);
                        board.n_nodes++;
                        
                        
                        int score= -sBoard.get_score(lastMove);
                        if (score> bestscore_1) {
                            bestscore_1 = score;
                        }
                        
                        
                    }
                
                if(bestscore_1 == UNDEF_SCORE) {
                    //PASS
                    sBoard.board.do_pass();
                    bestscore_1 = -sBoard.get_score();
                    sBoard.board.do_pass();
                }
                
                bestscore = -bestscore_1;
                
            } else if(depth == 3) {
                bestscore = -alphabeta_last_two_ply(threadID, sBoard, -upper_probcut, -upper_probcut+1, false);
            } else if(depth == 4) {
                bestscore = -PVS_last_three_ply(threadID, sBoard, -upper_probcut, -upper_probcut+1, false);
            } else {
                bestscore = -MG_NWS_XProbCut(threadID, sBoard, 0, selectivity, depth-1, child_selective_cutoff, -upper_probcut, false); // pvDev = 0
            }
            
            sBoard.undo_move(*iter);
            
            //interrupt search
            if(abort.load() || thread_should_stop(threadID))
                return false;
            
            if(bestscore >= upper_probcut) { //beta cut
                
                //				/* singular probcut */
                //				if(USE_SINGULAR_PROBCUT) {
                //
                //					if (depth > 4) {
                //
                //						if(singular_move(threadID, sBoard, selectivity, depth, (upper_probcut+lower_probcut)/2, list, iter->position)) { //(upper_probcut+lower_probcut)/2 == alpha
                //
                ////							*log << "singular probcut" << std::endl;
                //
                //							/* move first position */
                //							list->sort_bestmove(iter->position);
                //
                //							return NO_CUT;
                //						}
                //
                //
                //					}
                //
                //
                //				}
                
                
                selectif_cutoff=child_selective_cutoff;
                
                hTable->update(board.hashcode(), type_hashtable, selectif_cutoff? MG_SELECT:NO_SELECT, depth, upper_probcut-1, bestscore, iter->position);
                return true;
            }
            
        }
    }
    
    return false;
    
    
}


int RXEngine::PVS_check(int threadID, RXBBPatterns& sBoard, int depth, int alpha, int beta, bool passed) {
    
    
    //	assert(alpha>=-MAX_SCORE && beta<=MAX_SCORE);
    
    RXBitBoard& board = sBoard.board;
    
    int bestmove = NOMOVE;
    int hashmove = NOMOVE;
    
    int upper = beta;
    int lower = alpha;
    
    //synchronized access
    RXHashValue entry;
    if(hTable_shallow->get(board, entry)) {
        if(entry.depth >= depth) {
            
            if (upper > entry.upper) {
                upper = entry.upper;
                if (upper <= lower)
                    return upper;
            }
            
            if (lower < entry.lower) {
                lower = entry.lower;
                if (lower >= upper)
                    return lower;
            }
            
        }
        
        hashmove = entry.move;
    }
    
    
    
    
    int bestscore = UNDEF_SCORE;
    
    if(hashmove != PASS) {
        
        RXMove* list = threads[threadID]._move[board.n_empties];
        int n_moves = 0;
        
        if(hashmove != NOMOVE) {
            
            RXMove& move = list[1];
            ((board).*(board.generate_flips[hashmove]))(move);
            ((sBoard).*(sBoard.update_patterns[hashmove][board.player]))(move);
            
            //first move
            sBoard.do_move(move);
            if(depth == CHECK_TO_LAST_THREE)
                bestscore = -PVS_last_three_ply(threadID, sBoard, -upper, -lower, false);
            else
                bestscore = -PVS_check(threadID, sBoard, depth-1, -upper, -lower, false);
            sBoard.undo_move(move);
            
            bestmove = hashmove;
            
            if(bestscore>lower)
                lower = bestscore;
        }
        
        
        if(lower < upper ) {
            
            
            if(bestmove != NOMOVE) {
                RXSquareList* empty = board.position_to_empties[bestmove];
                empty->previous->next = empty->next;
                n_moves = board.moves_producing(list);
                empty->previous->next = empty;
            } else {
                n_moves = board.moves_producing(list);
            }
            
            if(n_moves != 0) {
                
                RXMove* iter = list->next;
                
                if(n_moves > 1) {
                    
                    if(depth>5) {
                        
                        int lower_probcut = -MAX_SCORE;
                        int upper_probcut  =  MAX_SCORE;
                        probcut_bounds(board, 0, 4, 0, 0, lower_probcut, upper_probcut); //72%
                        
                        int eval_position = sBoard.get_score();
                        int _lower = std::max(-MAX_SCORE, lower+lower_probcut*2);
                        
                        if(_lower<= eval_position) { //~95%
                            
                            RXMove& lastMove = threads[threadID]._move[board.n_empties-1][1];
                            
                            for(; iter != NULL; iter = iter->next) {
                                ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                                
                                sBoard.do_move(*iter);
                                
                                //								int eval_move = sBoard.get_score();
                                //
                                //								if(eval_move <= -_lower) {
                                
                                if(depth>9) {
                                    
                                    iter->score = alphabeta_last_two_ply(threadID, sBoard, -MAX_SCORE, -_lower, false);
                                    
                                } else {
                                    
                                    int bestscore = UNDEF_SCORE; //masquage
                                    const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
                                    for(RXSquareList* empties = board.empties_list->next; bestscore < -_lower && empties->position != NOMOVE; empties = empties->next) {
                                        if(legal_movesBB & 1ULL<<empties->position) { 
                                            ((board).*(board.generate_flips[empties->position]))(lastMove);
                                            ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(lastMove);
                                            board.n_nodes++;
                                            
                                            int score = -sBoard.get_score(lastMove);
                                            if (score>bestscore) {
                                                bestscore = score;
                                            }
                                            
                                        }
                                    }
                                    
                                    
                                    if(bestscore == UNDEF_SCORE) {
                                        //PASS
                                        sBoard.board.do_pass();
                                        iter->score = -sBoard.get_score();
                                        sBoard.board.do_pass();
                                        
                                    } else {
                                        iter->score = bestscore;
                                    }
                                    
                                }
                                
                                
                                //								} else {
                                //
                                //									iter->score = eval_move + MAX_SCORE/2; //bad move
                                //
                                //								}
                                
                                sBoard.undo_move(*iter);
                                
                            }
                            
                            
                        } else {
                            
                            for(; iter != NULL; iter = iter->next) {
                                ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                                
                                board.n_nodes++;
                                iter->score = sBoard.get_score(*iter);
                            }
                        }
                        
                    } else {
                        
                        for(; iter != NULL; iter = iter->next) {
                            ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                            
                            board.n_nodes++;
                            iter->score = sBoard.get_score(*iter);
                        }
                    }
                    
                } else {
                    ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
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
                    
                    sBoard.do_move(*move);
                    if(depth == CHECK_TO_LAST_THREE)
                        bestscore = -PVS_last_three_ply(threadID, sBoard, -upper, -lower, false);
                    else
                        bestscore = -PVS_check(threadID, sBoard, depth-1, -upper, -lower, false);
                    sBoard.undo_move(*move);
                    
                    bestmove = move->position;
                    if(bestscore>lower)
                        lower = bestscore;
                    
                    // next move
                    list = list->next;
                }
                
                //other moves
                int score = UNDEF_SCORE;
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
                    
                    sBoard.do_move(*move);
                    
                    if(depth == CHECK_TO_LAST_THREE) {
                        score = -PVS_last_three_ply(threadID, sBoard, -lower-1, -lower, false);
                        if(lower < score && score < upper)
                            score = -PVS_last_three_ply(threadID, sBoard, -upper, -score, false);
                    } else {
                        score = -PVS_check(threadID, sBoard, depth-1, -lower-1, -lower, false);
                        if(lower < score && score < upper)
                            score = -PVS_check(threadID, sBoard, depth-1, -upper, -score, false);
                    }
                    
                    sBoard.undo_move(*move);
                    
                    if(score>bestscore) {
                        bestscore = score;
                        bestmove = move->position;
                        if(bestscore>lower)
                            lower = bestscore;
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
        } else {
            board.n_nodes++;
            board.do_pass();
            if(depth == CHECK_TO_LAST_THREE)
                bestscore = -PVS_last_three_ply(threadID, sBoard, -upper, -lower, true);
            else
                bestscore = -PVS_check(threadID, sBoard, depth-1, -upper, -lower, true);
            board.do_pass();
            bestmove = PASS;
        }
    }
    
    hTable_shallow->update(board.hashcode(), depth, alpha, beta, bestscore, bestmove);
    
    return bestscore;
    
}




int RXEngine::PVS_last_three_ply(int threadID, RXBBPatterns& sBoard, int alpha, int beta, bool passed) {
    
    //	if(alpha<-MAX_SCORE || beta>MAX_SCORE) {
    //		std::cout	<< "Error" << '\n'
    //		<< "alpha : " << alpha << '\n'
    //		<< "beta  : " << beta << std::endl;
    //
    //	}
    //
    //	assert(alpha>=-MAX_SCORE && beta<=MAX_SCORE);
    
    RXBitBoard& board = sBoard.board;
    
    int bestmove = NOMOVE;
    int hashmove = NOMOVE;
    
    int upper = beta;
    int lower = alpha;
    
    //synchronized access
    RXHashValue entry;
    if (hTable_shallow->get(board, entry)) {
        if(entry.depth >= 3) {
            
            if (upper > entry.upper) {
                upper = entry.upper;
                if (upper <= lower)
                    return upper;
            }
            
            if (lower < entry.lower) {
                lower = entry.lower;
                if (lower >= upper)
                    return lower;
            }
            
        }
        
        hashmove = entry.move;
    } /*else if(hTable->get_sync(board, type_hashtable, entry)) {
       hashmove = entry.move;
       }*/
    
    int bestscore = UNDEF_SCORE;
    
    if (hashmove != PASS) {
        
        RXMove& move = threads[threadID]._move[board.n_empties][1];
        RXSquareList* empties = board.empties_list->next;
        
        //const unsigned long long discs_opponent = board.discs[board.player^1];
        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
        
        
        //fisrt move
        if(hashmove != NOMOVE) {
            
            bestmove = hashmove;
            ((board).*(board.generate_flips[bestmove]))(move);
            ((sBoard).*(sBoard.update_patterns[bestmove][board.player]))(move);
            
            sBoard.do_move(move);
            bestscore = -alphabeta_last_two_ply(threadID, sBoard, -upper, -lower, false);
            sBoard.undo_move(move);
            
            if(bestscore>lower)
                lower = bestscore;
            
        } else {
            
            
            do {
                if(legal_movesBB & 1ULL<<empties->position) {
                    ((board).*(board.generate_flips[empties->position]))(move);
                    ((sBoard).*(sBoard.update_patterns[move.position][board.player]))(move);
                    
                    sBoard.do_move(move);
                    bestscore = -alphabeta_last_two_ply(threadID, sBoard, -upper, -lower, false);
                    sBoard.undo_move(move);
                    
                    bestmove = empties->position;
                    if(bestscore>lower)
                        lower = bestscore;
                    
                }
                
                empties = empties->next;
                
            } while(bestscore == UNDEF_SCORE && empties->position != NOMOVE);
        }
        
        //other moves
        int score = UNDEF_SCORE;
        for(; lower<upper && empties->position != NOMOVE; empties = empties->next) {
            if(empties->position != hashmove && (legal_movesBB & 1ULL<<empties->position)) {
                
                ((board).*(board.generate_flips[empties->position]))(move);
                ((sBoard).*(sBoard.update_patterns[move.position][board.player]))(move);
                
                sBoard.do_move(move);
                score = -alphabeta_last_two_ply(threadID, sBoard, -lower-1, -lower, false);
                if(lower < score && score < upper)
                    score = -alphabeta_last_two_ply(threadID, sBoard, -upper, -score, false);
                
                sBoard.undo_move(move);
                
                if(score>bestscore) {
                    bestscore = score;
                    bestmove = empties->position;
                    if(bestscore>lower)
                        lower = bestscore;
                    
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
        } else {
            board.n_nodes++;
            board.do_pass();
            bestscore = -alphabeta_last_two_ply(threadID, sBoard, -upper, -lower, true);
            board.do_pass();
            bestmove = PASS;
        }
    }
    
    hTable_shallow->update(board.hashcode(), 3, alpha, beta, bestscore, bestmove);
    
    return bestscore;
    
}



int RXEngine::alphabeta_last_two_ply(int threadID, RXBBPatterns& sBoard, int alpha, int beta, bool passed) {
    
    RXBitBoard& board = sBoard.board;
    
    int bestscore = UNDEF_SCORE;
    
    RXMove& move = threads[threadID]._move[board.n_empties][1];
    RXMove& lastMove = threads[threadID]._move[board.n_empties - 1][1];
    
    
    //other moves
    const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
    for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next) {
        if(legal_movesBB & 1ULL<<empties->position) {
            ((board).*(board.generate_flips[empties->position]))(move);
            ((sBoard).*(sBoard.update_patterns[empties->position][board.player]))(move);
            
            int opponent = board.player ^ 1;
            
            board.discs[board.player] |= (move.flipped | move.square);
            board.discs[opponent] ^= move.flipped;
            
            board.n_empties--;
            
            board.n_nodes++;
            board.player = opponent;
            
            empties->previous->next = empties->next;
            
            move.undo_pattern = sBoard.pattern;
            sBoard.pattern = move.pattern;
            
            //*************************************************************************************************
            // Last ply
            //*************************************************************************************************
            int bestscore_1 = UNDEF_SCORE;
            const unsigned long long legal_movesBB_1 = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
            for(RXSquareList* empties_1 = board.empties_list->next; bestscore_1 < -alpha && empties_1->position != NOMOVE; empties_1 = empties_1->next) {
                if(legal_movesBB_1 & 1ULL<<empties_1->position) {
                    ((board).*(board.generate_flips[empties_1->position]))(lastMove);
                    ((sBoard).*(sBoard.update_patterns[empties_1->position][board.player]))(lastMove);
                    board.n_nodes++;
                    
                    int score = -sBoard.get_score(lastMove);
                    if(score>bestscore_1) {
                        bestscore_1 = score;
                    }
                }
            }
            
            if(bestscore_1 == UNDEF_SCORE) {
                //PASS
                sBoard.board.do_pass();
                bestscore_1 = -sBoard.get_score();
                sBoard.board.do_pass();
                
            }
            /***************************************************************************************************/
            
            int score = -bestscore_1;
            
            opponent = board.player ^ 1;
            
            sBoard.pattern = move.undo_pattern;
            
            empties->previous->next = empties;
            
            board.n_empties++;
            
            board.discs[opponent] ^= (move.flipped | move.square);
            board.discs[board.player] |= move.flipped;
            
            board.player = opponent;
            
            if(score>=beta)
                return score;
            
            if(score>bestscore) {
                bestscore = score;
                if(bestscore>alpha)
                    alpha = bestscore;
            }
        }
    }
    
    if(bestscore == UNDEF_SCORE) {	//PASS
        
        if(passed) {
            board.n_nodes--;
            bestscore = sBoard.final_score();
        } else {
            board.n_nodes++;
            
            board.player ^=1;
            //*************************************************************************************************
            // Last ply
            //*************************************************************************************************
            int bestscore_1 = UNDEF_SCORE;
            const unsigned long long legal_movesBB_1 = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
            for(RXSquareList* empties_1 = board.empties_list->next; bestscore_1 < -alpha && empties_1->position != NOMOVE; empties_1 = empties_1->next) {
                if(legal_movesBB_1 & 1ULL<<empties_1->position) {
                    ((board).*(board.generate_flips[empties_1->position]))(lastMove);
                    ((sBoard).*(sBoard.update_patterns[empties_1->position][board.player]))(lastMove);
                    board.n_nodes++;
                    
                    int score = -sBoard.get_score(lastMove);
                    if(score>bestscore_1)
                        bestscore_1 = score;
                }
            }
            
            if(bestscore_1 == UNDEF_SCORE) {		//PASS
                board.n_nodes--;
                bestscore_1 = sBoard.final_score();
            }
            /***************************************************************************************************/
            bestscore = -bestscore_1;
            
            board.player^=1;
        }
    }
    
    
    return bestscore;
    
}

std::string RXEngine::variationPrincipal(RXBitBoard& board, int depth) const {
    return hTable->line2String(board, depth, type_hashtable);
}

std::string RXEngine::showPV(RXBitBoard& board, int depthLine) const {
    std::ostringstream buffer;
    
    // unsynchronized acces
    RXHashValue entry;
    if(hTable->get(board, type_hashtable, entry)) {
        
        int depth = static_cast<int>(entry.depth);
        if(depth>board.n_empties)
            depth = board.n_empties;
        
        buffer << " " << depth << "@" << CONFIDENCE[entry.selectivity];
        
        bool pv_ext = false;
        if(depth!=board.n_empties && depth>MIN_DEPTH_USE_PV_EXTENSION && depth+pv_extension>=board.n_empties) {
            if(entry.lower == entry.upper && entry.lower%VALUE_DISC == 0) {
                pv_ext = true;
            } else if(entry.lower == -MAX_SCORE &&  entry.upper%VALUE_DISC == 0) {
                pv_ext = true;
            } else if(entry.lower%VALUE_DISC == 0) {
                pv_ext = true;
            }
        }
        
        if(entry.selectivity != NO_SELECT)
            buffer <<  (pv_ext? "+":" ");
        
        buffer << "  " << RXMove::index_to_coord(entry.move);
        
        int score;
        if(entry.lower == entry.upper) {
            buffer << " == ";
            score = entry.lower;
        } else if(entry.lower == -MAX_SCORE) {
            buffer << " <= ";
            score = entry.upper;
        } else {
            buffer << " >= ";
            score = entry.lower;
        }
        
        buffer << std::fixed << std::showpos << std::setprecision(0) << ((float)score)/VALUE_DISC;
        
        buffer << "  Pv : " << hTable->line2String(board, depthLine, type_hashtable);
    }
    
    return buffer.str();
    
}

std::string RXEngine::showHashmove(const RXBitBoard& board, RXHashValue& entry) const {
    
    std::ostringstream buffer;
    
    int depth = static_cast<int>(entry.depth);
    if(depth>board.n_empties)
        depth = board.n_empties;
    
    buffer << "[" << depth << "@" << CONFIDENCE[entry.selectivity];
    
    bool pv_ext = false;
    if(depth!=board.n_empties && depth>MIN_DEPTH_USE_PV_EXTENSION && depth+RXEngine::PV_EXTENSION_DEPTH>=board.n_empties) {
        if(entry.lower == entry.upper && entry.lower%(2*VALUE_DISC) == 0) {
            pv_ext = true;
        } else if(entry.lower == -MAX_SCORE &&  entry.upper%(2*VALUE_DISC) == 0) {
            pv_ext = true;
        } else if(entry.lower%(2*VALUE_DISC) == 0) {
            pv_ext = true;
        }
    }
    
    if(entry.selectivity != NO_SELECT)
        buffer <<  (pv_ext? "+":" ");
    
    buffer << "] " << RXMove::index_to_coord(entry.move);
    
    int score;
    if(entry.lower == entry.upper) {
        buffer << " == ";
        score = entry.lower;
    } else if(entry.lower == -MAX_SCORE) {
        buffer << " <= ";
        score = entry.upper;
    } else {
        buffer << " >= ";
        score = entry.lower;
    }
    
    buffer << std::fixed << std::showpos << std::setprecision(0) << ((float)score)/VALUE_DISC;
    
    
    return buffer.str();
    
}

std::string RXEngine::showBestmove(const int depth, const bool pv_ext, const int selectivity, const int alpha, const int beta, const int score, const int bestmove) const {
    
    std::ostringstream buffer;
    
    buffer << " " << depth << "@" << CONFIDENCE[selectivity];
    
    if(selectivity != NO_SELECT)
        buffer << (pv_ext? "+":" ");
    
    
    buffer << "  " << RXMove::index_to_coord(bestmove);
    
    if(score<=alpha)
        buffer << " <= ";
    else if (beta <= score)
        buffer << " >= ";
    else
        buffer << " == ";
    
    buffer << std::fixed << std::showpos << std::setprecision(0) << ((float)score)/VALUE_DISC;
    
    
    return buffer.str();
    
}

std::string RXEngine::display(RXBitBoard& board, const int type, const int allowed_display, int score, const int time, const int time_level) {
    
    std::ostringstream buffer;
    std::locale loc(std::locale(),new My_punct);
    buffer.imbue(loc);
    
    
    //unsynchronized acces
    RXHashValue entry;
    if( hTable->get(board, type_hashtable, entry) && ((entry.depth >= board.n_empties && entry.selectivity >= allowed_display) || (entry.depth < board.n_empties && entry.depth >= allowed_display))) {
        
        int depth = (entry.depth >= board.n_empties? board.n_empties : entry.depth);
        
        buffer << (type == HASHTABLE? "[":" ");
        buffer <<std::fixed << std::setw(2) << depth ;
        if(entry.selectivity != NO_SELECT) {
            buffer << "@" << std::setw(2) << CONFIDENCE[entry.selectivity];
            
            bool pv_ext = false;
            if(depth!=board.n_empties && depth>MIN_DEPTH_USE_PV_EXTENSION && depth+pv_extension>=board.n_empties) {
                if(entry.lower == entry.upper && entry.lower%VALUE_DISC == 0) {
                    pv_ext = true;
                } else if(entry.lower == -MAX_SCORE &&  entry.upper%VALUE_DISC == 0) {
                    pv_ext = true;
                } else if(entry.lower%VALUE_DISC == 0) {
                    pv_ext = true;
                }
            }
            
            if(entry.selectivity != NO_SELECT)
                buffer <<  (pv_ext? "+":" ");
            
            
        } else
            buffer << "    ";
        
        buffer << (type == HASHTABLE? "]|":" |");
        
        int _type = type;
        
        if(type == HASHTABLE || type == GGS_MSG) {
            if(entry.upper == entry.lower) {
                score = entry.upper;
                _type = EXACT;
            } else if(entry.upper == MAX_SCORE) {
                score = entry.lower;
                _type = SUPERIOR;
            } else {
                score = entry.upper;
                _type = INFERIOR;
            }
        }
        
        
        if(entry.depth < board.n_empties) { //midGame
            if(score >= MAX_SCORE-64*VALUE_DISC)
                score -= MAX_SCORE-64*VALUE_DISC;
            else if (score <= -MAX_SCORE+64*VALUE_DISC)
                score += MAX_SCORE-64*VALUE_DISC;
        }
        
        switch(_type) {
            case INFERIOR:
                buffer << "<=";
                break;
            case SUPERIOR:
                buffer << ">=";
                break;
            case INTERRUPT:
                buffer << " #";
                break;
            default:
                buffer << "  ";
                break;
        }
        
        buffer << std::showpos << std::setprecision(0) << std::setw(3) << (float)score/VALUE_DISC << "  | ";
        
        buffer << std::noshowpos << variationPrincipal(board, 12) << "| ";
        
        if(type != GGS_MSG) {
            if(type == HASHTABLE) {
                buffer << "00:00:00.00 |                |          |";
            } else {
                buffer << toHMS(time/1000.0) << " | ";
                
                buffer << std::noshowpos << std::setprecision(0) << std::setw(14) << board.n_nodes << " | ";
                
                unsigned long long speed = 0;
                if(time_level>0)
                    speed = board.n_nodes/time_level;
                if (board.n_nodes > 500000) {
                    buffer << std::setw(8) << (time_level == 0 ? ' ': speed) << " |";
                } else {
                    buffer << std::setw(8) << " N/A" << " |";
                }
            }
        }
        
    }
    
    return buffer.str();
    
}



void RXEngine::stop(std::string msg) {
    
    abort.store(true);
    
    if (manager->getEngine(BLACK) == this)
        *log << "[" << get_current_time() << "] " << "        RXEngine BLACK : stop : " << msg << std::endl;
    else
        *log << "[" << get_current_time() << "] " << "        RXEngine WHITE : stop : " << msg << std::endl;
    
    
    //wait end main thread
    if(pthreadMain[0] != NULL) {
        pthread_join(pthreadMain[0], NULL);
        pthreadMain[0] = NULL;
    }
    
    hash_code_search = 0;
    
    
}


void RXEngine::resume() {
    
    resume_flag.store(true);
    
    stop("resume");
    
    hTable_shallow->reset();
}




/* synchronized method */
void RXEngine::get_move(RXSearch& s) {
    
    pthread_mutex_lock(&mutex);
    
    resume_flag.store(false);
    
    dependentTime_start = get_system_time();
    dependent_time = s.dependent_time;
    
    
    
    RXBBPatterns& sBoard = s.sBoard;
    RXBitBoard& board = sBoard.board;
    
    activeThreads = std::min<unsigned int>(std::max<unsigned int>(1, s.nThreads), THREAD_MAX);
    
    time_match = s.tMatch;
    time_remaining = s.tRemaining;
    
    
    if(board.hashcode() == hash_code_search) {
        //continuation search
        new_search = false;
        
        determine_move_time(board);
        
        //DEGUG
        *log << "[" << get_current_time() << "] " << "        RXEngine : dependent time : " << (dependent_time ? "true":"false" )<< std::endl;
        
        //interrupt search if time limit < probable time search
        if(time_limit() < (time_nextLevel - (get_current_time() - time_startLevel))) {
            *log  << "        interrupt search: likely timeout\n" <<  std::endl;
            abort.store(true);
        }
        
    } else {
        
        //new position : new search
        
        
        //kill current search
        stop("new position");
        
        new_search = true;
        
        //restart
        time_start = dependentTime_start;;
        
        //copy
        search_sBoard = sBoard; //utility?
        
        
        search_client      = s.clientMode;
        search_alpha       = std::max(-MAX_SCORE, std::min( MAX_SCORE-1, s.alpha));
        search_beta        = std::min(+MAX_SCORE, std::max(-MAX_SCORE+1, s.beta));
        search_selectivity = std::max(0, std::min(NO_SELECT, s.selectivity));
        search_depth       = std::max(2, std::min(board.n_empties, s.depth));
        
        
        hTable = s.htable;
        main_PV = s.main_PV;
        expected_PV = s.expected_PV;
        
        if(hTable->is_shared()) {
            type_hashtable = RXHashTable::HASH_SHARED;
        } else if(board.player == BLACK) {
            type_hashtable = RXHashTable::HASH_BLACK;
        } else { //color white
            type_hashtable = RXHashTable::HASH_WHITE;
        }
        
        
        hTable_PV = main_PV;
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        
        if(!resume_flag.load() && pthread_create(pthreadMain, &attr, init_pthreadMain, (void*)(this)) != 0)
            std::cout << "Echec: Thread main engine" << std::endl;
        
        pthread_attr_destroy(&attr);
        
    }
    
    
    //wait end search
    if(pthreadMain[0] != NULL) {
        pthread_join(pthreadMain[0], NULL);
        pthreadMain[0] = NULL;
    }
    
    //affectation answer
    s.bestMove = best_answer;
    s.bestMove.tElapsed = get_current_dependentTime()/1000.0;
    
    
    if(search_sBoard.board.n_empties > 19) {
        int speed = 0;
        if(time_search != 0)
            speed = static_cast<int>(s.bestMove.nodes/time_search) ; //*1000)
        
        std::ostringstream buffer;
        
        std::locale loc(std::locale(),new My_punct);
        buffer.imbue(loc);
        
        
        buffer	<< showPV(search_sBoard.board, 6);
        manager->sendMsg(buffer.str());
        
        buffer.str("");
        buffer << "Ts : " << toHMS(time_search/1000.0) << "   Tm : " << toHMS(s.bestMove.tElapsed);
        manager->sendMsg(buffer.str());
        
        buffer.str("");
        buffer << "nodes : " << std::setw(14) << s.bestMove.nodes;
        manager->sendMsg(buffer.str());
        
        buffer.str("");
        buffer << "speed : " << std::setw(14);
        if(s.bestMove.nodes > 500000) {
            buffer << static_cast<int>(speed) << " kN/s";
        } else {
            buffer << "N/A";
            
        }
        manager->sendMsg(buffer.str());
        
    }
    
    
    *log << "I play " << RXMove::index_to_coord(s.bestMove.position) << std::endl;
    *log << "evaluation " << (s.bestMove.score/VALUE_DISC) <<  std::endl;
    *log << "time " << toHMS(s.bestMove.tElapsed) <<  std::endl;
    
    hash_code_search = 0;
    
    //************************************************************************************************
    //                                  here one thread only
    //************************************************************************************************
    
    if(!resume_flag.load() && s.search_on_opponent_time == true && board.n_empties>18) {
        
        
        dependent_time = false;
        
        
        RXMove& move = threads[0]._move[board.n_empties][1];
        
        //play best move
        if(s.bestMove.position == PASS) {
            sBoard.board.do_pass();
        } else {
            
            ((sBoard.board).*(sBoard.board.generate_flips[s.bestMove.position]))(move);
            ((sBoard).*(sBoard.update_patterns[move.position][board.player]))(move);
            
            sBoard.do_move(move);
            
        }
        
        
        //copy
        search_sBoard = sBoard;
        
        if(!hTable->is_shared()) {
            
            // 17/07/2009
            //pas d'anticipation si le score n'est pas exacte
            
            RXHashValue entry;
            if(hTable->get(search_sBoard.board, type_hashtable, entry) && entry.move != NOMOVE && entry.upper == entry.lower) {
                
                if(entry.move == PASS) {
                    search_sBoard.board.do_pass();
                } else {
                    RXMove& answer = threads[0]._move[board.n_empties][1];
                    ((sBoard.board).*(sBoard.board.generate_flips[entry.move]))(answer);
                    ((sBoard).*(sBoard.update_patterns[answer.position][board.player]))(answer);
                    
                    sBoard.do_move(answer);
                    search_sBoard = sBoard;
                    sBoard.undo_move(answer);
                    
                }
                
            }
        }
        
        
        hash_code_search = search_sBoard.board.hashcode();
        
        hTable_PV = expected_PV;
        
        time_start = get_system_time();
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        
        if(!resume_flag.load() && pthread_create(pthreadMain, &attr, init_pthreadMain, (void*)(this)) != 0)
            std::cout << "Echec: Thread main engine" << std::endl;
        
        pthread_attr_destroy(&attr);
        
        
        
        if(s.bestMove.position == PASS) {
            sBoard.board.do_pass();
        } else {
            sBoard.undo_move(move);
        }
        
    }
    
    //***********************************************************************************************
    
    pthread_mutex_unlock(&mutex);
}


void RXEngine::run() {
    
    time_search = get_system_time();
    
    abort.store(false);
    
    // Wake up sleeping threads:
    wake_sleeping_threads();
    
    
    
    *log	<< "---------------------------------------------------------------------------------------------------\n"
    << search_sBoard
    << std::endl;
    //DEGUG
    *log << "[" << get_current_time() << "] " << "        RXEngine : dependent time : " << (dependent_time ? "true":"false" )<< std::endl;
    
    
    RXBitBoard& board = search_sBoard.board;
    root_player = board.player;
    
    
    best_answer.nodes = 0;
    board.n_nodes = 0;
    time_nextLevel = 0;
    
    RXMove* list = threads[0]._move[board.n_empties];
    int n_moves = board.moves_producing(list);
    
    if(n_moves == 0) {	//PASS
        
        best_answer.position = PASS;
        best_answer.score = 0;
        
    } else if(n_moves == 1) { //FORCED
        
        best_answer.position = list->next->position;
        best_answer.score = 0;
        
        
    } else {
        
        *log << "  depth | score | principal variation                 | time        |      nodes (N) |     kN/s |" << std::endl;
        
        int depth = 2;
        int selectivity = MG_SELECT;
        
        RXMove* list1 = list;
        
        
        RXHashValue entry_PV;
        unsigned long long hash_code = board.hashcode();
        if(expected_PV->get(hash_code, type_hashtable, entry_PV)) {
            RXHashValue entry;
            if(!hTable->get(board, type_hashtable, entry)) {
                *log << "        expected_PV -> hash :-)" << std::endl;
                hTable->copyPV(expected_PV, type_hashtable, board, type_hashtable);
            }
        }
        
        if(main_PV->get(hash_code, type_hashtable, entry_PV)) {
            RXHashValue entry;
            if(!hTable->get(board, type_hashtable, entry)) {
                *log << "        main_PV -> hash :-)" << std::endl;
                hTable->copyPV(main_PV, type_hashtable, board, type_hashtable);
            }
        }
        
        RXHashValue entry;
        if(hTable->get(hash_code, type_hashtable, entry)) {
            
            best_answer.position = entry.move;
            list->sort_bestmove(entry.move);
            
            list1 = list->next;
            ((search_sBoard).*(search_sBoard.update_patterns[list1->position][search_sBoard.board.player]))(*list1);
            
            *log << display(board, HASHTABLE) << std::endl;
            
            if(dependent_time && search_sBoard.board.n_empties> 19 && entry.depth>13)
                manager->sendMsg(showHashmove(board, entry));
            
            depth = std::max(2, +entry.depth);
            
            if(search_sBoard.board.n_empties - entry.depth <= 0) //endgame
                selectivity = std::min(NO_SELECT, +entry.selectivity);
            
            if(entry.upper == entry.lower) {
                
                list1->score = entry.upper;
                
                if(search_alpha<list1->score && list1->score<search_beta) {
                    if(search_sBoard.board.n_empties - depth <= 0) //endgame
                        selectivity = std::min(NO_SELECT, selectivity+1);
                    else
                        depth = std::min(search_sBoard.board.n_empties, depth+2);
                }
                
                
            } else {
                
                if(entry.upper == MAX_SCORE) {
                    list1->score = entry.lower;
                    
                    if(list1->score>=search_beta) {
                        if(search_sBoard.board.n_empties - depth <= 0) //endgame
                            selectivity = std::min(NO_SELECT, selectivity+1);
                        else
                            depth = std::min(search_sBoard.board.n_empties, depth+2);
                    }
                    
                } else if(entry.lower == -MAX_SCORE) {
                    list1->score = entry.upper;
                    
                    if(list1->score<=search_alpha) {
                        if(search_sBoard.board.n_empties - depth <= 0) //endgame
                            selectivity = std::min(NO_SELECT, selectivity+1);
                        else
                            depth = std::min(search_sBoard.board.n_empties, depth+2);
                    } else {
                        //reset search
                        //						std::cout << "hash [-inf;score] reset search" << std::endl;
                        depth = 2;
                        selectivity = MG_SELECT;
                    }
                    
                    
                    
                } else
                    list1->score = (entry.upper+entry.lower)/2;
                
            }
            
            
        }
        
        for(RXMove* iter = list1->next; iter != NULL; iter = iter->next) {
            
            ((search_sBoard).*(search_sBoard.update_patterns[iter->position][search_sBoard.board.player]))(*iter);
            
            search_sBoard.do_move(*iter);
            if(search_sBoard.board.n_empties%2 == BLACK)
                iter->score = alphabeta_last_two_ply(0, search_sBoard, -MAX_SCORE, MAX_SCORE, false);
            else
                iter->score = PVS_last_three_ply(0, search_sBoard, -MAX_SCORE, MAX_SCORE, false);
            search_sBoard.undo_move(*iter);
            
        }
        list1->sort_by_score();
        list1->next->score = 0;
        
        
        best_answer.position = list->next->position;
        best_answer.score = list->next->score;
        
        extra_time = 0;
        
        //		for(unsigned int i = 1; i < activeThreads; i++)
        //			assert(thread_is_available(i, 0));
        //
        hTable_shallow->new_search(search_sBoard.board.n_empties);
        
        hTable_PV->new_search(search_sBoard.board.player, search_sBoard.board.n_empties);
        
        hTable->new_search(search_sBoard.board.player, search_sBoard.board.n_empties);
        hTable->protectPV(search_sBoard.board);
        
        
        int max_depth;
        if(search_depth <= search_sBoard.board.n_empties-10) {
            depth = std::min(depth, search_depth);
            max_depth = search_depth;
        } else {
            depth = std::min(depth, search_sBoard.board.n_empties);
            max_depth = search_sBoard.board.n_empties-10;
        }
        
        //normalisation de depth
        if(depth%2 == (search_sBoard.board.n_empties%2 == 1 ? 0 : 1))
            depth++;
        
        //normalisation de max_depth
        if(max_depth%2 == (search_sBoard.board.n_empties%2 == 1? 0:1))
            max_depth++;
        
        
        
        if(depth<=max_depth) {
            iterative_deepening(search_sBoard, list, depth, max_depth);
        }
        
        if (!abort.load() && search_depth > (search_sBoard.board.n_empties-10)) {
            //coherence selectivty et end_selectivity
            int end_selectivity = search_depth < search_sBoard.board.n_empties? 0:search_selectivity;
            
            EG_driver(search_sBoard, std::min(selectivity, end_selectivity), end_selectivity, list);
        }
        
        
    }
    
    
    //sleeping threads
    allThreadsShouldSleep = true;
    
    abort.store(true);
    *log << "[" << get_current_time() << "] " << "        RXEngine : end search" << std::endl;
    
    
    time_search = get_system_time() - time_search;
    
}


//monothread
bool RXEngine::probable_timeout(double probable_time_next_level) const {
    
    if(dependent_time) {
        
        double tElapsed_dependent = get_current_dependentTime() ;
        double time_for_move = time_move;
        
        if ((tElapsed_dependent + probable_time_next_level) > 3*time_for_move)
            return true;
        
        if(tElapsed_dependent > (6*time_for_move/10)) //40%
            if ((tElapsed_dependent + probable_time_next_level) > 2*time_for_move/3)
                return true;
    }
    
    return false;
}

//monothread
int RXEngine::pTime_next_level(RXBitBoard& board, int time_level, int depth, int next_depth) const {
    
    int probable_Time_next_level;
    
    if(board.n_empties>(depth+10)) {
        if(depth<7 || time_level == 0)
            return 0;
        
        double width = std::max(pow(board.n_nodes, 1.0/depth), 1.85);
        double newNodes = pow(width, next_depth);
        
        probable_Time_next_level = static_cast<int>(newNodes/(board.n_nodes/time_level));
        
        
    } else {	//endgame
        
        switch(CONFIDENCE[get_select_search()]) {
            case 72:
            case 84:
            case 91:
                probable_Time_next_level = time_level * 3;
                break;
                
            case 95:
            case 98:
                probable_Time_next_level = time_level * 5;
                break;
                
            case 99:
            default:
                probable_Time_next_level = time_level * 7;
        }
        
        
        
    }
    
    return probable_Time_next_level;
}


//monothread
void RXEngine::determine_move_time(RXBitBoard& board) {
    
    static const int coeff_32[] = { 1, 2, 4, 6, 8, 12, 16, 24, 32};
    
    int tSafety = time_match/10;
    tSafety = std::min(45*1000, tSafety);
    int index = std::min(8, (board.n_empties/4));
    tSafety = std::max(4*1000, (coeff_32[index]*tSafety)/32);
    
    
    int tElasped = get_current_dependentTime();
    //track bug
    assert(tElasped>=0);
    
    int tRemaining = (time_remaining - tSafety) - tElasped;
    int tMove;
    
    if(get_type_search() != ENDGAME && board.n_empties>30) {
        //Midgame mode
        int rMoves = static_cast<int>(floor(((board.n_empties-23)+1)/2.0)); //last 25 moves == few time
        tMove = static_cast<int>((1+(rMoves-1)/14.0)*tRemaining / rMoves);
        
        if(new_search) {	// new research
            if(time_match == time_remaining) // first move
                tMove *= 3;
            else
                tMove *= 2;
        }
        
    } else {
        //EndGame mode
        int selectivity = get_select_search();
        double confidence = CONFIDENCE[selectivity]/100.0;
        tMove = static_cast<int>(tRemaining*(confidence*confidence)*0.7);
        if(new_search) 	// new research
            tMove *= 2;							// * 1,5
    }
    
    if(board.n_empties>34)
        tMove = std::max(2*tMove/3, tSafety/6);
    
    //security
    tMove = std::max(1000, tMove);
    tMove = std::min(80*tRemaining/100, tMove);
    int tExtra = std::min(tMove, ((tRemaining+tSafety)-tMove)/2);
    
    time_move = tMove + tElasped;
    //track bug
    assert(time_remaining>time_move);
    
    extratime_move = tExtra;
    
    tRemaining += tSafety;
    
    
    *log		<< "\n"
    << "        tr: " << toHMS(tRemaining/1000.0) << " "
    << "tm: " << toHMS(tMove/1000.0) << " "
    << "xt: " << toHMS(tExtra/1000.0) << "\n"
    << "        stop before       : " << toHMS((tRemaining - tMove)/1000.0) << "   : " << toHMS((tRemaining - (tMove+tExtra))/1000.0) << "\n"
    << std::endl;
    
    new_search = false;
}


void RXEngine::writeLog(std::string s) {
    *log << s << std::endl;
}


/// init_threads() is called during startup.  It launches all helper threads,
// and initializes the split point stack and the global locks and condition
// objects.

void RXEngine::init_threads() {
    
    volatile unsigned int i;
    
    pthread_t pthread[1]; //pointeur
    
    
    for(i = 0; i < THREAD_MAX; i++) {
        
        threads[i].activeSplitPoints = 0;
        threads[i].state = RXThread::INITIALIZING;
        
    }
    
    threads[0].state = RXThread::SEARCHING;
    
    // Launch the helper threads:
    // RXEngine idThread est passé en paramettre avec (void*)(this)
    for(idThread= 1; idThread < THREAD_MAX; idThread++) {
        
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        
        if(pthread_create(pthread, &attr, init_threadHelper, (void*)(this)) != 0)
            std::cout << "Echec: Thread helper engine" << std::endl;
        
        pthread_attr_destroy(&attr);
        
        // Wait until the thread has finished launching:
        while(threads[idThread].state == RXThread::INITIALIZING)
            ;
    }
}


// stop_threads() is called when the program exits.  It makes all the
// helper threads exit cleanly.

void RXEngine::stop_threads() {
    
    activeThreads = THREAD_MAX; 	// kill all threads
    
    //important: before wake up
    allThreadsShouldExit = true;
    
    wake_sleeping_threads();
    
    for(unsigned int i = 1; i < THREAD_MAX; i++) {
        while(threads[i].state != RXThread::TERMINATED)
            ;
    }
    
}


// idle_loop() is where the threads are parked when they have no work to do.
// The parameter "waitSp", if non-NULL, is a pointer to an active SplitPoint
// object for which the current thread is the master.
// active waiting : infini loop, fast wake up
// passive waiting : condition wake up

void  RXEngine::idle_loop() {
    idle_loop(idThread, NULL);
}


void RXEngine::idle_loop(unsigned int threadID, RXSplitPoint* waitSp) {
    
    
    while(true) {
        
        if(allThreadsShouldExit) {
            threads[threadID].state = RXThread::TERMINATED;
            break;
        }
        
        // If we are not thinking, wait for a condition to be signaled instead
        // of wasting CPU time polling for work:
        while (  allThreadsShouldSleep
               || threadID >= activeThreads
               || threads[threadID].state == RXThread::INITIALIZING
               || threads[threadID].state == RXThread::AVAILABLE ) {
            
            
            pthread_mutex_lock(&(threads[threadID].lock));
            
            if(threads[threadID].state == RXThread::INITIALIZING)
                threads[threadID].state = RXThread::AVAILABLE;
            
            
            if (allThreadsShouldExit || (waitSp && waitSp->n_Slaves == 0)) {
                pthread_mutex_unlock(&(threads[threadID].lock));
                break;
            }
            
            if(   allThreadsShouldSleep
               || threadID >= activeThreads
               || threads[threadID].state == RXThread::AVAILABLE) {
                
                pthread_cond_wait(&(threads[threadID].cond), &(threads[threadID].lock));
            }
            
            pthread_mutex_unlock(&(threads[threadID].lock));
        }
        
        
        
        if(threads[threadID].state == RXThread::WORKISWAITING) {
            
            pthread_mutex_lock(&(threads[threadID].lock));
            
            threads[threadID].state = RXThread::SEARCHING;
            RXSplitPoint* splitPoint = threads[threadID].splitPoint;
            
            pthread_mutex_unlock(&(threads[threadID].lock));
            
            
            //functions callback
            switch (splitPoint->CBSearch) {
                    
                    
                case RXSplitPoint::MID_PVS:
                    MG_SP_search_DEEP(splitPoint, threadID);
                    break;
                    
                case RXSplitPoint::MID_XPROBCUT:
                    MG_SP_search_XEndcut(splitPoint, threadID);
                    break;
                    
                case RXSplitPoint::END_ROOT:
                    EG_SP_search_root(splitPoint, threadID);
                    break;
                    
                case RXSplitPoint::END_PVS:
                    EG_SP_search_DEEP(splitPoint, threadID);
                    break;
                    
                case RXSplitPoint::END_XPROBCUT:
                    EG_SP_search_XEndcut(splitPoint, threadID);
                    break;
            }
            
            pthread_mutex_lock(&(threads[threadID].lock));
            threads[threadID].state = RXThread::AVAILABLE;
            pthread_mutex_unlock(&(threads[threadID].lock));
            
            // dois je proteger l'acces ??
            pthread_mutex_lock(&threads[splitPoint->master].lock);
            if (threadID != splitPoint->master && threads[splitPoint->master].state == RXThread::AVAILABLE) {
                wake_sleeping_thread(splitPoint->master);
            }
            pthread_mutex_unlock(&threads[splitPoint->master].lock);
            
            
        }
        
        
        
        // If this thread is the master of a split point and all threads have
        // finished their work at this split point, return from the idle loop:
        
        // attente active des slaves threads
        
        //		unsigned int i = 0;
        //		while( waitSp && i < activeThreads && !waitSp->slaves[i])
        //			i++;
        //
        //		if (i == activeThreads) {
        
        
        
        //n_Slaves without mutex
        if (waitSp && waitSp->n_Slaves == 0) {
            
            pthread_mutex_lock(&(waitSp->lock));
            threads[threadID].state = RXThread::SEARCHING;
            pthread_mutex_unlock(&(waitSp->lock));
            
            break;
        }
        
        
    }
    
    
}

// wake_sleeping_threads() wakes up all sleeping threads (passive waiting) when it is time
// to start a new search from the root (active waiting).

void RXEngine::wake_sleeping_threads() {
    
    allThreadsShouldSleep = false;
    
    for (unsigned int i = 0; i<activeThreads; i++) {
        pthread_mutex_lock(&(threads[i].lock));
        wake_sleeping_thread(i);
        pthread_mutex_unlock(&(threads[i].lock));
    }
}


void RXEngine::wake_sleeping_thread(unsigned int threadID) {
    
    
    assert(allThreadsShouldSleep == false);
    
    pthread_cond_signal(&(threads[threadID].cond));
    
    
}

// idle_thread_exists() tries to find an idle thread which is available as
// a slave for the thread with threadID "master".

bool RXEngine::idle_thread_exists(int master) {
    
    //    assert(master >= 0 && master < activeThreads);
    //    assert(activeThreads > 1);
    
    for(unsigned int i = 0; i < activeThreads; i++)
        if(thread_is_available(i, master))
            return true;
    return false;
}

// thread_is_available() checks whether the thread with threadID "slave" is
// available to help the thread with threadID "master" at a split point.  An
// obvious requirement is that "slave" must be idle.  With more than two
// threads, this is not by itself sufficient:  If "slave" is the master of
// some active split point, it is only available as a slave to the other
// threads which are busy searching the split point at the top of "slave"'s
// split point stack (the "helpful master concept" in YBWC terminology).


// Si la methode est appeler directement depuis split()
// elle est synchronisée avec MP_Sync
// si la methode est appelé depuis idle_thread_exists()
// la methode est non synchronisée
bool RXEngine::thread_is_available(int slave, int master) {
    
    //    assert(slave >= 0 && slave < activeThreads);
    //    assert(master >= 0 && master < activeThreads);
    //    assert(activeThreads > 1);
    
    
    if(slave == master || threads[slave].state != RXThread::AVAILABLE) {
        return false;
    }
    
    // the "helpful master concept" in YBWC terminology
    // cas particulier 2 threads
    if(activeThreads == 2) {
        return true;
    }
    
    //copy local (argh... bug 25/01/2010)
    const unsigned int localActiveSplitPoints = threads[slave].activeSplitPoints;
    
    //Apply the "helpful master" concept if possible.
    if(localActiveSplitPoints == 0 || threads[slave].splitPointStack[localActiveSplitPoints-1].slaves[master]) {
        
        return true;
    }
    
    return false;
}



// split() does the actual work of distributing the work at a node between
// several threads.  If it does not succeed in splitting the node (because no
// idle threads are available, or because we have no unused split point
// objects), the function immediately returns false.  If splitting is
// possible, a SplitPoint object is initialized with all the data that must
// be copied to the helper threads (the current position and,
// alpha, beta, the search depth, etc.), and we tell our helper threads that
// they have been assigned work.  This will cause them to instantly leave
// their idle loops and call sp_search().  When all threads have returned
// from sp_search (or, equivalently, when splitPoint->cpus becomes 0),
// split() returns true.


//bool RXEngine::split(RXBBPatterns& sBoard, bool pv, int pvDev,
//					 int depth, int selectivity, bool& selective_cutoff, bool& child_selective_cutoff,
//					 int alpha, int beta, int& bestscore, int& bestmove,
//					 RXMove* list, unsigned int master, RXSplitPoint::t_callBackSearch callback) {
//
//
//	//	assert(bestscore >= -MAX_SCORE); // && *bestscore <= *alpha);	possible in aspiration window
//	//	assert(alpha < beta);
//	//	assert(beta <= MAX_SCORE);
//	//
//	//	assert(master >= 0 && master < activeThreads);
//	//	assert(activeThreads > 1);
//
//	MP_sync.lock();
//
//
//	// If no other thread is available to help us, or if we have too many
//	// active split points, don't split:
//	if(!idle_thread_exists(master) || threads[master].activeSplitPoints >= ACTIVE_SPLITPOINT_MAX) {
//
//		MP_sync.unlock();
//		return false;
//	}
//
//	// Pick the next available split point object from the split point stack:
//	RXSplitPoint& splitPoint = threads[master].splitPointStack[threads[master].activeSplitPoints];
//
//	threads[master].activeSplitPoints++;
//
//	splitPoint.parent = threads[master].splitPoint;
//
//
//	// Initialize the split point object:
//
//	splitPoint.explored = false;
//
//	splitPoint.sBoard = &sBoard; // pointer on sBoard
//	splitPoint.list = list;
//
//	splitPoint.depth = depth;
//	splitPoint.pv = pv;
//	splitPoint.pvDev = pvDev;
//	splitPoint.selectivity = selectivity;
//	splitPoint.alpha = alpha;
//	splitPoint.beta = beta;
//
//	splitPoint.selective_cutoff = selective_cutoff;
//	splitPoint.child_selective_cutoff = child_selective_cutoff;
//	splitPoint.bestscore = bestscore;
//	splitPoint.bestmove = bestmove;
//
//
//	splitPoint.CBSearch = callback;
//
//	splitPoint.master = master;
//
//	for(unsigned int i = 0; i < activeThreads; i++)
//		splitPoint.slaves[i] = false;
//
//
//	// add thread
//	unsigned int nWorker = 1;
//	for(unsigned int i = 0; i < activeThreads && nWorker < THREAD_PER_SPLITPOINT_MAX; i++)
//		if(thread_is_available(i, master)) {
//
//			threads[i].state = RXThread::RESERVED;
//
//			splitPoint.slaves[i] = true;
//			nWorker++;
//		}
//
//	MP_sync.unlock();
//
//	// Tell the threads that they have work to do.  This will make them leave
//	// their idle loop.
//
//	for(unsigned int i = 0; i < activeThreads; i++)
//		if(i == master || splitPoint.slaves[i]) {
//
//			threads[i].splitPoint = &splitPoint;
//			threads[i].state = RXThread::WORKISWAITING;
//
//		}
//
//
//	// Everything is set up.  The master thread enters the idle loop, from
//	// which it will instantly launch a search, because its workIsWaiting
//	// slot is 'true'.  We send the split point as a second parameter to the
//	// idle loop, which means that the main thread will return from the idle
//	// loop when all threads have finished their work at this split point
//	// (i.e. when // splitPoint->n_Slaves == 0).
//	idle_loop(master, &splitPoint);
//
//	// We have returned from the idle loop, which means that all threads are
//	// finished.  Update bestvalue, and return:
//	MP_sync.lock();
//
//	//update return value
//	bestscore = splitPoint.bestscore;
//	bestmove = splitPoint.bestmove;
//	selective_cutoff = splitPoint.selective_cutoff;
//	child_selective_cutoff = splitPoint.child_selective_cutoff;
//
//
//	threads[master].activeSplitPoints--;
//
//	threads[master].splitPoint = splitPoint.parent;
//
//
//	MP_sync.unlock();
//
//	return true;
//}
//

bool RXEngine::split(RXBBPatterns& sBoard, bool pv, int pvDev,
                     int depth, int selectivity, bool& selective_cutoff, bool& child_selective_cutoff,
                     int alpha, int beta, int& bestscore, int& bestmove,
                     RXMove* list, unsigned int master, RXSplitPoint::t_callBackSearch callback) {
    
    
    
    pthread_mutex_lock(&MP_sync);
    
    if (threads[master].activeSplitPoints >= ACTIVE_SPLITPOINT_MAX) {
        pthread_mutex_unlock(&MP_sync);
        return false;
    }
    
    // Pick the next available split point object from the split point stack:
    RXSplitPoint& splitPoint = threads[master].splitPointStack[threads[master].activeSplitPoints];
    splitPoint.n_Slaves = 1;
    
    pthread_mutex_unlock(&MP_sync);
    
    // add thread
    for(unsigned int i = 0; i < activeThreads; i++) {
        
        //first without mutex
        if(splitPoint.n_Slaves < THREAD_PER_SPLITPOINT_MAX && thread_is_available(i, master)) {
            
            pthread_mutex_lock(&MP_sync);
            
            //second control with mutex
            if(splitPoint.n_Slaves < THREAD_PER_SPLITPOINT_MAX && thread_is_available(i, master)) {
                
                
                pthread_mutex_lock(&(threads[i].lock));
                
                threads[i].state = RXThread::RESERVED;
                
                pthread_mutex_unlock(&(threads[i].lock));
                
                splitPoint.slaves[i] = true;
                splitPoint.n_Slaves++;
            }
            
            pthread_mutex_unlock(&MP_sync);
        }
        
    }
    
    pthread_mutex_lock(&MP_sync);
    
    if(splitPoint.n_Slaves == 1) {
        pthread_mutex_unlock(&MP_sync);
        return false;
    }
    
    threads[master].activeSplitPoints++;
    splitPoint.parent = threads[master].splitPoint;
    
    splitPoint.explored = false;
    
    pthread_mutex_unlock(&MP_sync);
    
    
    // sans synchronisation
    // Initialize the split point object:
    
    splitPoint.sBoard = &sBoard; // pointer on sBoard
    splitPoint.list = list;
    
    splitPoint.depth = depth;
    splitPoint.pv = pv;
    splitPoint.pvDev = pvDev;
    splitPoint.selectivity = selectivity;
    splitPoint.alpha = alpha;
    splitPoint.beta = beta;
    
    splitPoint.selective_cutoff = selective_cutoff;
    splitPoint.child_selective_cutoff = child_selective_cutoff;
    splitPoint.bestscore = bestscore;
    splitPoint.bestmove = bestmove;
    
    splitPoint.CBSearch = callback;
    
    splitPoint.master = master;
    
    
    // Tell the threads that they have work to do.  This will make them leave
    // their idle loop.
    
    for(unsigned int i = 0; i < activeThreads; i++)
        if(i == master || splitPoint.slaves[i]) {
            
            pthread_mutex_lock(&threads[i].lock);
            
            threads[i].splitPoint = &splitPoint;
            threads[i].state = RXThread::WORKISWAITING;
            
            if (i != master) {
                wake_sleeping_thread(i);
            }
            pthread_mutex_unlock(&threads[i].lock);
            
        }
    
    
    // Everything is set up.  The master thread enters the idle loop, from
    // which it will instantly launch a search, because its workIsWaiting
    // slot is 'true'.  We send the split point as a second parameter to the
    // idle loop, which means that the main thread will return from the idle
    // loop when all threads have finished their work at this split point
    // (i.e. when // splitPoint->n_Slaves == 0).
    idle_loop(master, &splitPoint);
    
    
    // We have returned from the idle loop, which means that all threads are
    // finished.  Update bestvalue, and return:
    
    //update return value
    bestscore = splitPoint.bestscore;
    bestmove = splitPoint.bestmove;
    selective_cutoff = splitPoint.selective_cutoff;
    child_selective_cutoff = splitPoint.child_selective_cutoff;
    
    
    pthread_mutex_lock(&MP_sync);
    
    threads[master].splitPoint = splitPoint.parent;
    threads[master].activeSplitPoints--;
    
    pthread_mutex_unlock(&MP_sync);
    
    
    return true;
}


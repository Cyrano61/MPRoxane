/*
 *  RXEndGame.cpp
 *  learn_01
 *
 *  Created by B Causse on 11/06/05.
 *  Copyleft 2005-2024 personnel.
 *
 */
#include <iostream>
#include <iomanip>
#include <cmath>


#include "RXEngine.hpp"
#include "RXRoxane.hpp"



const bool RXEngine::USE_STABILITY = true;
const bool RXEngine::USE_ENHANCED_STABLILITY = true;

const int RXEngine::stability_threshold[] =
{   6500, 6500, 6500, 6500,  400,  600,  800, 1000,
    2000, 2200, 2400, 2600, 2800, 3000, 3200, 3400,
    2400, 3600, 3800, 4000, 4000, 4200, 4200, 4400,
    4400, 4600, 4600, 4800, 4800, 5000, 5200, 5200,
    5400, 5400, 5600, 5600, 5800, 5800, 6000, 6000,
    6200, 6200, 6500, 6500, 6500, 6500, 6500, 6500,
    6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500,
    6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500};

int RXEngine::EG_DEEP_TO_MEDIUM = 17;           //standart 17
int RXEngine::EG_MEDIUM_HI_TO_LOW = 14;         //[12 (6'42) : 13 (6'25) : standard 14 (6'26)]
const int RXEngine::EG_MEDIUM_TO_SHALLOW = 8;   //Constant 8

int RXEngine::MIN_DEPTH_USE_ENDCUT = 16;        //16
const int RXEngine::EG_HIGH_SELECT = 0;

const bool RXEngine::USE_POTENTIAL_MOBILITY = true;


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
    
    
    if(USE_STABILITY) {//} && board.n_empties > 5) {
        if ( alpha >= stability_threshold[board.n_empties]) {
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= alpha )
                return stability_bound;
            if ( stability_bound < beta )
                beta = stability_bound + VALUE_DISC;
        }
    }
    
    RXMove& move = threads[threadID]._move[board.n_empties][1];
    
    const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
    
    for (int parity = 1; parity >= 0; parity--) {
        for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next) {
            
            if ((legal_movesBB & 1ULL<<empties->position) && board.local_Parity(empties->position) == parity) { ((board).*(board.generate_flips[empties->position]))(move);
                board.n_nodes++;
                
                board.discs[board.player] |= (move.flipped | move.square);
                board.discs[opponent] ^= move.flipped;
                
                board.n_empties--;
                //update/restore player
                board.player ^= 1;
                //update empties
                empties->previous->next = empties->next;
                empties->next->previous = empties->previous;
                
                
                if (board.n_empties == 4) {
                    
                    score = -board.final_score_4(-beta, -alpha, false);
                    
                } else {
                    
                    score = -EG_alphabeta_parity(threadID, board, -beta, -alpha, false);
                    
                }
                
                
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
    
    int bestmove = NOMOVE;
    int hashmove = NOMOVE;
    
    //synchronized acces
    RXHashValue entry;
    unsigned long long  hash_code = board.hashcode();
    if(hTable->get(hash_code, type_hashtable, entry)) {
        
        if(entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) { // !pv &&
            
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
    
    if(USE_STABILITY  && hashmove == NOMOVE) {
        
        if ( upper >= stability_threshold[board.n_empties] ) {
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= lower )
                return stability_bound;
            
            if ( stability_bound < upper )
                upper = stability_bound + VALUE_DISC;
            
        }
    }
    
    RXMove move = threads[threadID]._move[board.n_empties][1];

    if(hashmove != PASS) {
        
        if(hashmove != NOMOVE) {
            
            ((board).*(board.generate_flips[hashmove]))(move);
            
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
            const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
            
            for (int parity = 1; lower < upper && parity >= 0; parity--) {
                for(RXSquareList* empties = board.empties_list->next; lower < upper && empties->position != NOMOVE; empties = empties->next) {
                    if (empties->position != hashmove && (legal_movesBB & 1ULL<<empties->position) &&  board.local_Parity(empties->position) == parity) { ((board).*(board.generate_flips[empties->position]))(move);
                        board.n_nodes++;
                        
                        board.discs[board.player] |= (move.flipped | move.square);
                        board.discs[opponent] ^= move.flipped;
                        
                        board.n_empties--;
                        //update/restore player
                        board.player ^= 1;
                        //update empties
                        empties->previous->next = empties->next;
                        empties->next->previous = empties->previous;
                        
                        score = -EG_alphabeta_parity(threadID, board, -upper, -lower, false);
                        
                        //restore empties
                        empties->previous->next = empties;
                        empties->next->previous = empties;
                        
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
    
    
    hTable->update(hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
    
    return bestscore;
}

int RXEngine::EG_alphabeta_hash_mobility(int threadID, RXBitBoard& board, const bool pv, int alpha, int beta, bool passed) {

    int bestscore = UNDEF_SCORE;
    int lower = alpha;
    int upper = beta;
    
    int bestmove = NOMOVE;
    int hashmove = NOMOVE;

    //synchronized acces
    RXHashValue entry;
    unsigned long long  hash_code = board.hashcode();
    if(hTable->get(hash_code, type_hashtable, entry)) {
        
        if(entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) { // !pv &&
            
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
    
    if(USE_STABILITY  && hashmove == NOMOVE) {
        
        if ( upper >= stability_threshold[board.n_empties] ) {
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= lower )
                return stability_bound;
            
            if ( stability_bound < upper )
                upper = stability_bound + VALUE_DISC;
            
        }
    }
    
    RXMove* list = threads[threadID]._move[board.n_empties];
    RXMove* move = list + 1;


    if(hashmove != PASS) {
        
        if(hashmove != NOMOVE) {
            
            ((board).*(board.generate_flips[hashmove]))(*move);
            
            // first move
            board.do_move(*move);
            bestscore = -EG_alphabeta_parity(threadID, board, -upper, -lower, false);
            board.undo_move(*move);
            
            bestmove = hashmove;
            if (bestscore > lower)
                lower = bestscore;
            
        }
        
        if(lower < upper) {

            const int p = board.player;
            const int o = p^1;

            //for all empty square
            RXMove* previous = list;
            int n_Moves = 0;
            const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[p], board.discs[o]);

            for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
                if(hashmove != empties->position && (legal_movesBB & 1ULL<<empties->position)) {

                    ((board).*(board.generate_flips[empties->position]))(*move);

                    board.n_nodes++;

                    const unsigned long long p_discs = board.discs[p] | (move->flipped | move->square);
                    const unsigned long long o_discs = board.discs[o] ^ move->flipped;

                    move->score = RXBitBoard::count_potential_moves(o_discs, p_discs) - (RXBitBoard::local_Parity(o_discs, p_discs, move->position)^1); // - (RXBitBoard::get_corner_stability(p_discs));
                    
                    previous = previous->next = move++;
                    n_Moves++;
                }

            previous->next = NULL;

            if(n_Moves>0) {

                if(bestmove == NOMOVE) {

                    RXMove* previous_move = list;
                    RXMove* move = previous_move->next;

                    if (n_Moves>1) {
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

                    board.do_move(*move);
                    bestscore = -EG_alphabeta_parity(threadID, board, -upper, -lower, false);
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
                    score = -EG_alphabeta_parity(threadID, board, -upper, -lower, false);
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
    
    
    hTable->update(hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
    
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
    
    
    RXMove* list = threads[threadID]._move[board.n_empties];
    RXMove* move = list + 1;
    
    //synchronized acces
    RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
    if(hTable->get(hash_code, type_hashtable, entry)) {
        
        if(entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) { // !pv &&
            
            
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
    
    if(USE_STABILITY  && bestmove == NOMOVE) {
        
        /*
         calculated stability is less than or equal to the real stability
         stability_bound is overestimated.
         score_max <= Stability_bound <= alpha ==> cutoff
         &
         score_max<=stability_bound < beta  ==> adjustment search window
         */

        
        if ( upper >= stability_threshold[board.n_empties] ) {
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= lower )
                return stability_bound;
            
            if ( stability_bound < upper )
                upper = stability_bound + VALUE_DISC;
            
        }
        
    }
    
    int bestscore = UNDEF_SCORE;
    
    if(bestmove != PASS) {
        
        if(bestmove != NOMOVE) {
            
            ((board).*(board.generate_flips[bestmove]))(*move);
            
            /* first move */
            board.do_move(*move);
            if (board.n_empties < EG_MEDIUM_TO_SHALLOW) {
                if(USE_POTENTIAL_MOBILITY)
                    bestscore = -EG_alphabeta_hash_mobility(threadID, board, pv, -upper, -lower, false);
                else
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
                    
                    const int p = board.player;
                    const int o = p^1;
                    
                    //sort list by mobility
                    for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
                        
                        board.n_nodes++;
                        
                        const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                        const unsigned long long o_discs = board.discs[o] ^ iter->flipped;
                        
                        iter->score = (RXBitBoard::get_mobility(o_discs, p_discs)<<5) - (RXBitBoard::get_corner_stability(p_discs)<<2) - (RXBitBoard::local_Parity(o_discs, p_discs, iter->position)^1);

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
                        if(USE_POTENTIAL_MOBILITY)
                            bestscore = -EG_alphabeta_hash_mobility(threadID, board, pv, -upper, -lower, false);
                        else
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
                        if(USE_POTENTIAL_MOBILITY)
                            score = -EG_alphabeta_hash_mobility(threadID, board, pv, -upper, -lower, false);
                        else
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
    
    hTable->update(hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
    
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
 * \param sBoard      sBoard : just for conformity with split method.
 * \param hash_table hash_table.
 * \param alpha      lower bound.
 * \param beta       upper bound.
 * \param passed     a flag indicating if previous move was a pass.
 * \return the final score, as a disc difference.
 */
int RXEngine::EG_PVS_ETC_mobility(int threadID, RXBBPatterns& sBoard, const bool pv, int alpha, int beta, bool passed)
{
    
    //	assert(alpha>=-64*VALUE_DISC && beta<=64*VALUE_DISC);
    
    if(abort.load() || thread_should_stop(threadID))
        return INTERRUPT_SEARCH;
    
    RXBitBoard& board = sBoard.board;
    
    int bestmove = NOMOVE;
    int lower = alpha;
    int upper = beta;
    
    RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
    if(hTable->get(hash_code, type_hashtable, entry)) {
        
        if(entry.selectivity == NO_SELECT && entry.depth >= board.n_empties) { // !pv &&
            
            
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
    
    if(USE_STABILITY && bestmove == NOMOVE) {
        
        /*
         calculated stability is less than or equal to the real stability
         stability_bound is overestimated.
         score_max <= Stability_bound <= alpha ==> cutoff
         &
         score_max<=stability_bound < beta  ==> adjustment search window
         */
        if (  upper >= stability_threshold[board.n_empties] ) { // (pv ? beta : alpha)
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= lower )
                return stability_bound;
            
            if ( stability_bound < upper )
                upper = stability_bound + VALUE_DISC;
            
        }
        
    }
    
    //synchronized acces
    
    int bestscore = UNDEF_SCORE;
    
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
            if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && !pv && entry.selectivity == NO_SELECT && entry.depth>=board.n_empties)
                
                if(-entry.upper >= upper) {
                    return -entry.upper ;
                }
            
            previous = previous->next = move++;
            n_Moves++;
        }
        
        //for all empty square
        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
        for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
            if(bestmove != empties->position && (legal_movesBB & 1ULL<<empties->position)){
                
                ((board).*(board.generate_flips[empties->position]))(*move);
                board.n_nodes++;
                
                if ( USE_ENHANCED_STABLILITY && upper <= -stability_threshold[board.n_empties-1]  ) {
                    const unsigned long long d_player = board.discs[board.player] | (move->flipped | move->square);
                    int stability_bound = 2 * board.get_stability_opponent(board.discs[board.player^1] ^ move->flipped, d_player) - 6400;
                    if ( stability_bound > upper ) {
                        return stability_bound;
                    }
                }

                
                move->score = 0; //not in Hash
                
                //synchronized acces
                if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && entry.depth>=board.n_empties) {
                                        
                    move->score = -2*VALUE_DISC; //in hash
                    
                    if(-entry.upper >= upper) {
                        
                        if (!pv && entry.selectivity == NO_SELECT)
                            return -entry.upper ;
                        
                        //very exceptional case
                        move->score = -16*VALUE_DISC; //probably good move
                        
                    } else if(-entry.lower <= lower) {
                        move->score = 3*VALUE_DISC; //probably bad move
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
            bestscore = -EG_PVS_ETC_mobility(threadID,sBoard, pv, -upper, -lower, true);
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
                bestscore = -EG_PVS_ETC_mobility(threadID, sBoard, pv, -upper, -lower, false);
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
                
                //calc answer move->score
                for(RXMove* iter = list->next; iter != NULL; iter = iter->next) {
                    
                    board.n_nodes++;
                    
                    const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                    const unsigned long long o_discs = board.discs[o] ^ iter->flipped;
                    
                    //score for try : mobility * VALUE_DISC - corner_stability * 8
                    iter->score += 2*(RXBitBoard::get_mobility(o_discs, p_discs)*VALUE_DISC) - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC/10);// - (RXBitBoard::local_Parity(o_discs, p_discs, iter->position)^1);
                    
                }
                
            }
            
            if(bestmove == NOMOVE) {
                
                //find moves with worst answer
                
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
                    bestscore = -EG_PVS_ETC_mobility(threadID, sBoard, pv, -upper, -lower, false);
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
            
//            //unused: only for conformity with split method
//            bool selective_cutoff= false;
//            bool child_selective_cutoff = false;
            
            // other moves : try to refute the first/best one
            int score;
            for(;lower < upper && list->next != NULL; list = list->next) {

                //find moves with worst answer
                
//                // Split? not efficient : unused
//                if(activeThreads > 1  && !abort.load() && (list->next)->next != NULL && board.n_empties>=EG_MEDIUM_HI_TO_LOW
//                   && !thread_should_stop(threadID) && idle_thread_exists(threadID)
//                   && split(sBoard, pv, 0, board.n_empties, NO_SELECT, selective_cutoff, child_selective_cutoff,
//                            lower, upper, bestscore, bestmove, list, threadID, RXSplitPoint::END_ETC_MOBILITY))
//                    
//                    break;
                
                
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
                    score = -EG_PVS_ETC_mobility(threadID, sBoard, false, -lower - VALUE_DISC, -lower, false);
                    if (lower < score && score < upper)
                        score = -EG_PVS_ETC_mobility(threadID, sBoard, pv, -upper, -score, false);
                    
                    
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
    
    hTable->update(hash_code, pv, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
    
    
    return bestscore;
}

// EG_SP_search_ETC_Mobility() is used to search from a PV split point.  This function
// is called by each thread working at the split point.  It is similar to
// the normal EG_PVS_ETC_Mobility() function, but simpler.  Because we have already
// probed the hash table and searched the first move before splitting, we
// don't have to repeat all this work in EG_SP_search_ETC_Mobility().  We also don't
// need to store anything to the hash table here:  This is taken care of
// after we return from the split point.

void RXEngine::EG_SP_search_ETC_Mobility(RXSplitPoint* sp, const unsigned int threadID) {
    
    
    RXBBPatterns& sBoard = sp->sBoardStack[threadID];
    sBoard = *(sp->sBoard); //operator=
    RXBitBoard& board = sBoard.board;
    board.n_nodes = 0;
    
    
    //here sp->beta is const
    while(sp->alpha < sp->beta && !abort.load()  && !thread_should_stop(threadID)) {
        
        pthread_mutex_lock(&(sp->lock));
        
        RXMove* move;
        if(sp->list != NULL && sp->list->next != NULL) {
            
            move = sp->list->next;
            sp->list = sp->list->next;
            
        } else {
            pthread_mutex_unlock(&(sp->lock));
            break;
        }

        pthread_mutex_unlock(&(sp->lock));
        
        board.do_move(*move);
                
        int alpha = sp->alpha; //local copy
        
        int score = -EG_PVS_ETC_mobility(threadID, sBoard, false, -alpha - VALUE_DISC, -alpha, false);
        
        if (alpha < score && score < sp->beta)
            score = -EG_PVS_ETC_mobility(threadID, sBoard, sp->pv, -sp->beta, -score, false);
        
        board.undo_move(*move);
        
        if(abort.load()  || thread_should_stop(threadID))
            break;
        
        
        //first without mutex
        if(score > sp->bestscore) {
            
            //update
            pthread_mutex_lock(&(sp->lock));
                        
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




int RXEngine::EG_PVS_deep(int threadID, RXBBPatterns& sBoard, const bool pv, const int selectivity, bool& selective_cutoff, int alpha, int beta, bool passed) {
    
    
    if(abort.load() || thread_should_stop(threadID))
        return INTERRUPT_SEARCH;
    
//    if(threadID == 0)
//        pthread_yield_np(); //process->yield();
    
    
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
    
    
    //synchronized acces
    RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
    if(hTable->get(hash_code, type_hashtable, entry)) {
        
        
        if(entry.depth >= board.n_empties) {
            if(entry.selectivity >= selectivity) { // !pv &&
                
                
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
                
            }
        }
        
        
        bestmove = entry.move;
        
    }
    
    if(USE_STABILITY  && bestmove == NOMOVE) {
        
        /*
         calculated stability is less than or equal to the real stability
         stability_bound is overestimated.
         score_max <= Stability_bound <= alpha ==> cutoff
         &
         score_max<=stability_bound < beta  ==> adjustment search window
         */
        
        
        if ( upper >= stability_threshold[board.n_empties]  ) {
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= lower )
                return stability_bound;
            
            if ( stability_bound < upper )
                upper = stability_bound + VALUE_DISC;
            
        }
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
        
        if(hTable->get(hash_code, type_hashtable, entry))
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
            
            ((board).*(board.generate_flips[bestmove]))(*move);
            
            //synchronized acces
            if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && !pv && entry.selectivity >= selectivity && entry.depth>=board.n_empties) {
                
                if(-entry.upper >= upper) {
                    if(entry.selectivity != NO_SELECT)
                        selective_cutoff = true;
                    
                    return -entry.upper ;
                }
            }
            
            previous = previous->next = move++;
            n_Moves++;
            
        }
        
        
        //for other move
        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
        for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
            if(bestmove != empties->position && (legal_movesBB & 1ULL<<empties->position)){
                
                ((board).*(board.generate_flips[empties->position]))(*move);
                board.n_nodes++;
                
                if (USE_ENHANCED_STABLILITY && upper <= -stability_threshold[board.n_empties-1]  ) {
                    const unsigned long long d_player = board.discs[board.player] | (move->flipped | move->square);
                    int stability_bound = 2 * board.get_stability_opponent(board.discs[board.player^1] ^ move->flipped, d_player) - 6400;
                    if ( stability_bound > upper ) {
                        return stability_bound;
                    }
                }

                
                move->score = 0;    //not in hash
                
                //synchronized acces
                if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) &&  entry.depth>=board.n_empties) {
                    
                    move->score = -3*VALUE_DISC;    //in hash
 
                    if(-entry.upper >= upper) {
 
                        if(!pv && entry.selectivity >= selectivity) {
                            
                            if(entry.selectivity != NO_SELECT)
                                selective_cutoff = true;
                            
                            return -entry.upper ;
                        }
                        
                        move->score = -10*VALUE_DISC; //probably very good move
                        
                    } else if(-entry.lower <= lower) {
                        move->score = 2*VALUE_DISC; // probably bad move
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
        
        
        if(bestmove != NOMOVE) {
            
            /* first move */
            list = list->next;
            
            
            if (board.n_empties <= EG_DEEP_TO_MEDIUM) {
                board.do_move(*list);
                bestscore = -EG_PVS_ETC_mobility(threadID, sBoard, pv, -upper, -lower, false);
                board.undo_move(*list);
            } else {
                ((sBoard).*(sBoard.update_patterns[list->position][board.player]))(*list);
                
                sBoard.do_move(*list);
                bestscore = -EG_PVS_deep(threadID, sBoard, pv, selectivity , child_selective_cutoff, -upper, -lower, false);
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
            
            if(n_Moves>1) {
                
                const int p = board.player;
                const int o = p^1;
                
                if(board.n_empties>=(pv? 18:20)) { //18 pv 2O other
                    
                    int threshold_ff_Alpha = -MAX_SCORE;
                    int threshold_ff_Beta  =  MAX_SCORE;
                    probcut_bounds(board, std::min(3, selectivity), board.n_empties, 0, 0, threshold_ff_Alpha, threshold_ff_Beta); //selectivity 3 = 91%
                    
                    
                    int _lower = std::max(-MAX_SCORE, lower+threshold_ff_Alpha);
                    
                    if(_lower<= sBoard.get_score()) { // && sBoard.get_score()<=(beta+threshold_ff_Beta*2)) { //alpha 95% / beta 99%
                        
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
                                        
                                        RXMove& lastMove = threads[threadID]._move[board.n_empties-1][1];

                                        
                                        int bestscore = UNDEF_SCORE; //masquage
                                        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
                                        for(RXSquareList* empties = board.empties_list->next; bestscore< -_lower && empties->position != NOMOVE; empties = empties->next) {
                                            if ((legal_movesBB & 1ULL<<empties->position)){
                                                
                                                ((board).*(board.generate_flips[empties->position ]))(lastMove);
                                                ((sBoard).*(sBoard.update_patterns[empties->position ][board.player]))(lastMove);
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
                                    iter->score /= 2; //4
                                    iter->score -= MAX_SCORE/2; //good move	"probable beta cut"	study in first
                                }
                                
                            } else {
                                
                                iter->score += eval_move/2;
                                iter->score += MAX_SCORE/2; //bad move
                            }
                            
                            iter->score += RXBitBoard::get_mobility(board.discs[board.player], board.discs[board.player^1])*VALUE_DISC;// - (board.get_corner_stability(board.discs[board.player^1])*VALUE_DISC)/16;
                            
                            sBoard.undo_move(*iter);
                            
                        }
                        
                    } else {
                        
                        for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {
                            ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                            
                            board.n_nodes++;
                            const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                            
                            iter->score += sBoard.get_score(*iter) + 2*(RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC); // - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/4;
                        }
                    }
                    
                } else {
                    
                    //empties<18;
                    
                    for(RXMove* iter = list->next; iter!=NULL; iter = iter->next) {
                        ((sBoard).*(sBoard.update_patterns[iter->position][board.player]))(*iter);
                        
                        board.n_nodes++;
                        const unsigned long long p_discs = board.discs[p] | (iter->flipped | iter->square);
                        
                        //test 1 : score + 2*mobility_adv
                        iter->score += sBoard.get_score(*iter) + 2*(RXBitBoard::get_mobility(board.discs[o] ^ iter->flipped, p_discs)*VALUE_DISC); // - (RXBitBoard::get_corner_stability(p_discs)*VALUE_DISC)/4;
                    }
                    
                }
                
            } else if(n_Moves == 1) {
                ((sBoard).*(sBoard.update_patterns[list->next->position][board.player]))(*(list->next));
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
                    bestscore = -EG_PVS_ETC_mobility(threadID, sBoard, pv, -upper, -lower, false);
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
                    if(activeThreads > 1  && !abort.load()
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
                    
                    score = -EG_PVS_ETC_mobility(threadID, sBoard, false, -lower - VALUE_DISC, -lower, false);
                    if (lower < score && score < upper)
                        score = -EG_PVS_ETC_mobility(threadID, sBoard, pv, -upper, -score, false);
                    
                } else if(selectivity != NO_SELECT) {
                    
                    score = -EG_NWS_XEndCut(threadID, sBoard, 0, selectivity, child_selective_cutoff, -lower - VALUE_DISC, false);
                    if (lower < score && score < upper)
                        score = -EG_PVS_deep(threadID, sBoard, pv, selectivity, child_selective_cutoff, -upper, -lower, false); //-score
                    
                } else {
                    
                    score = -EG_PVS_deep(threadID, sBoard, false, NO_SELECT, child_selective_cutoff, -lower - VALUE_DISC, -lower, false);
                    if (lower < score && score < upper)
                        score = -EG_PVS_deep(threadID, sBoard, pv, NO_SELECT, child_selective_cutoff, -upper, -score, false);
                    
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
    
    
    hTable->update(   hash_code, pv, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
    hTable_PV->update(hash_code, pv, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
    
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
    
    
    RXBBPatterns& sBoard = sp->sBoardStack[threadID];
    sBoard = *(sp->sBoard); //operator=
    RXBitBoard& board = sBoard.board;
    board.n_nodes = 0;
    
    
    //here sp->beta is const
    while(sp->alpha < sp->beta && !abort.load()  && !thread_should_stop(threadID)) {
        
        pthread_mutex_lock(&(sp->lock));
        
        RXMove* move;
        if(sp->list != NULL && sp->list->next != NULL) {
            
            move = sp->list->next;
            sp->list = sp->list->next;
            
        } else {
            pthread_mutex_unlock(&(sp->lock));
            break;
        }

        
//        RXMove* move;
//        if(sp->list != NULL && sp->list->next != NULL) {
//            
//            RXMove* previous_move = sp->list;
//            move = previous_move->next;
//            
//            RXMove* previous_iter = move;
//            for(RXMove* iter = previous_iter->next ; iter != NULL; iter = (previous_iter = iter)->next) {
//                if(iter->score < move->score) {
//                    move = iter;
//                    previous_move = previous_iter;
//                }
//            }
//            
//            if(previous_move != sp->list) {
//                //move to front
//                previous_move->next = move->next;
//                move->next = sp->list->next;
//                sp->list->next = move;
//            }
//            
//            sp->list = sp->list->next;
//            
//            
//        } else {
//            pthread_mutex_unlock(&(sp->lock));
//            break;
//        }
       
        
        bool child_selective_cutoff = sp->child_selective_cutoff;
        
        pthread_mutex_unlock(&(sp->lock));
        
        
        
        sBoard.do_move(*move);
        
        int score;
        
        int alpha = sp->alpha; //local copy
        
        if (board.n_empties+1 <= EG_DEEP_TO_MEDIUM) {
            
            score = -EG_PVS_ETC_mobility(threadID, sBoard, false, -alpha - VALUE_DISC, -alpha, false);
            
            if (alpha < score && score < sp->beta)
                score = -EG_PVS_ETC_mobility(threadID, sBoard, sp->pv, -sp->beta, -score, false);
            
        } else if(sp->selectivity != NO_SELECT) {
            
            score = -EG_NWS_XEndCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, false);
            
            if (alpha < score && score < sp->beta)
                score = -EG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, child_selective_cutoff, -sp->beta, -sp->alpha, false);
            
        } else {
            
            score = -EG_PVS_deep(threadID, sBoard, false, sp->selectivity, child_selective_cutoff, -alpha - VALUE_DISC, -alpha, false);
            
            if (alpha < score && score < sp->beta)
                score = -EG_PVS_deep(threadID, sBoard, sp->pv, sp->selectivity, child_selective_cutoff, -sp->beta, sp->selectivity != NO_SELECT? -sp->alpha : -score, false);
            
        }
        
        
        sBoard.undo_move(*move);
        
        if(abort.load()  || thread_should_stop(threadID))
            break;
        
        //assert(score != -INTERRUPT_SEARCH);
        
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
    
    
    //synchronized acces
    RXHashValue entry;
    const unsigned long long hash_code = board.hashcode();
    if(hTable->get(hash_code, type_hashtable, entry)) {
        
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
    
    if(USE_STABILITY  && bestmove == NOMOVE) {
        if ( alpha >= stability_threshold[board.n_empties] ) {
            int stability_bound = 6400 - 2 * board.get_stability(board.player^1);
            if ( stability_bound <= alpha )
                return stability_bound;
        }
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
            
//            if(entry.upper <= lower_probcut) {
//                selective_cutoff = true;
//                return  alpha;
//            }
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
            
            ((board).*(board.generate_flips[bestmove]))(*move);
            
            //synchronized acces
            if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && entry.selectivity >= selectivity && entry.depth >= board.n_empties) {
                
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
        const unsigned long long legal_movesBB = RXBitBoard::get_legal_moves(board.discs[board.player], board.discs[board.player^1]);
        for(RXSquareList* empties = board.empties_list->next; empties->position != NOMOVE; empties = empties->next)
            if(bestmove != empties->position && (legal_movesBB & 1ULL<<empties->position)){
                
                ((board).*(board.generate_flips[empties->position]))(*move);
                board.n_nodes++;
                
                if (USE_ENHANCED_STABLILITY && alpha <= -stability_threshold[board.n_empties-1]  ) {
                    const unsigned long long d_player = board.discs[board.player] | (move->flipped | move->square);
                    int stability_bound = 2 * board.get_stability_opponent(board.discs[board.player^1] ^ move->flipped, d_player) - 6400;
                    if ( stability_bound > alpha ) {
                        return stability_bound; // alpha
                    }
                }

                
                move->score = 0;
                
                //synchronized acces
                if(hTable->get(board.hashcode_after_move(move), type_hashtable, entry) && entry.depth>=board.n_empties) {
                    
                    move->score = -3*VALUE_DISC;

                    if(-entry.upper > alpha) {
                        
                        if(entry.selectivity >= selectivity ) {
                            if(entry.selectivity != NO_SELECT)
                                selective_cutoff = true;
                            
                            return -entry.upper;
                        }
                        
                        move->score = -16*VALUE_DISC;
                        
                    }else if(-entry.lower<=alpha) {
                        
                        move->score += 5*VALUE_DISC;
                        
                    }
                    
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
            hTable->update(hash_code, false, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, -MAX_SCORE, MAX_SCORE,  bestscore, bestmove);
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
            bestscore = -EG_PVS_ETC_mobility(threadID, sBoard, false, -alpha-VALUE_DISC, -alpha, false);
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
               && (list->next)->next != NULL && !thread_should_stop(threadID)
               && !abort.load() && idle_thread_exists(threadID)
               && split(sBoard, false, pvDev, board.n_empties, selectivity, selective_cutoff, child_selective_cutoff,
                        alpha, (alpha + VALUE_DISC), bestscore, bestmove, list, threadID, RXSplitPoint::END_XPROBCUT))
                
                break;
            
            
            if(board.n_empties<=MIN_DEPTH_USE_ENDCUT) {
                board.do_move(*iter);
                score = -EG_PVS_ETC_mobility(threadID, sBoard, false, -alpha-VALUE_DISC, -alpha, false);
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
    
    hTable->update(hash_code, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, bestscore, bestmove);
    if(pvDev < 3)
        hTable_PV->update(hash_code, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, bestscore, bestmove);
    
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
            score = -EG_PVS_ETC_mobility(threadID, sBoard, false, -alpha-VALUE_DISC, -alpha, false);
            board.undo_move(*move);
        } else {
            sBoard.do_move(*move);
            score = -EG_NWS_XEndCut(threadID, sBoard, sp->pvDev+1, sp->selectivity, child_selective_cutoff, -alpha-VALUE_DISC, false);
            sBoard.undo_move(*move);
        }
        
        
        if(abort.load() || thread_should_stop(threadID))
            break;
        
        
        //first without mutex
        if((score > sp->bestscore) || (!sp->selective_cutoff && child_selective_cutoff)) {
            
            pthread_mutex_lock(&(sp->lock));
            
            //update SplitPoint
            
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
            
            
            pthread_mutex_unlock(&(sp->lock));
        }
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
        bestscore = -EG_PVS_ETC_mobility(0, sBoard, true, -upper, -lower, false);
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
            
//            if(activeThreads > 1 && iter->next != NULL && board.n_empties >= EG_DEEP_TO_MEDIUM
//               && !abort.load() && idle_thread_exists(0) && !thread_should_stop(0)
//               && split(sBoard, true, 0, board.n_empties, selectivity, selective_cutoff, child_selective_cutoff,
//                        lower, upper, bestscore, bestmove, iter, 0, RXSplitPoint::END_ROOT)) {
//                
//                
//                break;
//            }
            
            
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
                //					score = -EG_PVS_ETC_mobility(0, sBoard, true, -lower - VALUE_DISC, -lower, false); //multi-PV pv == true ????
                //				else
                //					score = -EG_PVS_deep(0, sBoard, true, selectivity, child_selective_cutoff, -lower - VALUE_DISC, -lower, false); //multi-PV pv == true ????
                
                //simple_pv PV == false
                if (board.n_empties < EG_MEDIUM_TO_SHALLOW)
                    score = -EG_alphabeta_parity(0, board, -lower - VALUE_DISC, -lower, false);
                else if (board.n_empties < EG_MEDIUM_HI_TO_LOW)
                    score = -EG_PVS_hash_mobility(0, board, false, -lower - VALUE_DISC, -lower, false);
                else if (board.n_empties < EG_DEEP_TO_MEDIUM)
                    score = -EG_PVS_ETC_mobility(0, sBoard, false, -lower - VALUE_DISC, -lower, false); //simple-PV pv == false ????
                else
                    score = -EG_PVS_deep(0, sBoard, false, selectivity, child_selective_cutoff, -lower - VALUE_DISC, -lower, false); //simple-PV pv == false ????
                
                
                if (!abort.load()  && lower < score && score < upper) {
                    
                    if(search_client == RXSearch::kGGSMode) {	// GGS mode
                        
                        if(dependent_time && board.n_empties>19)
                            manager->sendMsg("         " + RXMove::index_to_coord(iter->position) + " maybe better? ");
                        
                    }
                    
                    if (board.n_empties < EG_MEDIUM_TO_SHALLOW)
                        score = -EG_alphabeta_parity(0, board, -upper, -score, false);
                    else if (board.n_empties < EG_MEDIUM_HI_TO_LOW)
                        score = -EG_PVS_hash_mobility(0, board, true, -upper, -score, false);
                    else if (board.n_empties < EG_DEEP_TO_MEDIUM)
                        score = -EG_PVS_ETC_mobility(0, sBoard, true, -upper, -score, false);
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
        
        
        hTable->update(sBoard.board.hashcode(), true, type_hashtable, selective_cutoff? selectivity : NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, bestscore, bestmove);
        
        
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
                manager->sendMsg("         " + RXMove::index_to_coord(move->position) + " maybe better? ");
            
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
            
            pthread_mutex_unlock(&(sp->lock));
        }
        
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
    
//    //VERSION FOR RECORD FFORUM-40-59
//    selectivity = 1;
//    for(; !abort.load()  && selectivity <= end_selectivity; selectivity+=4) {
    for(; !abort.load()  && selectivity <= end_selectivity; selectivity++) {

        selectivity = std::max(std::min(NO_SELECT, 26-sBoard.board.n_empties), std::max(EG_HIGH_SELECT, selectivity));
        
        set_select_search(selectivity);
        
        if(dependent_time)
            determine_move_time(sBoard.board);
        
        //unused
        //MIN_DEPTH_USE_ENDCUT = std::min(18, 21-selectivity); //standard 18/21
        //EG_DEEP_TO_MEDIUM = (selectivity>3 ? 17:18);
        
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
        
        //high score >= 56 skip selectivity stage
        if (selectivity != 0 && abs(alpha) > 55*VALUE_DISC ) {
            selectivity = std::max(EG_HIGH_SELECT, ++selectivity);
            if (abs(alpha) > 61*VALUE_DISC )
                selectivity = NO_SELECT;
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
            
            //search window has always peers limits
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
        
        time_nextLevel = pTime_next_level(sBoard.board, eTime - eTime_start_level);
        
        if(probable_timeout(time_nextLevel)) {
            abort.store(true);
            *log << "        EG Driver : likely timeout" << std::endl;
            
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

int RXEngine::EG_pv_extension(int threadID, RXBBPatterns& sBoard, const bool pv, int alpha, int beta, bool passed) {
    
    if(sBoard.board.n_empties+1 < EG_MEDIUM_HI_TO_LOW)
        return EG_PVS_hash_mobility(threadID, sBoard.board, pv, alpha, beta, passed);
    else
        return EG_PVS_ETC_mobility(threadID, sBoard, pv, alpha, beta, passed);
    
    
}

void RXEngine::check_PV(RXBBPatterns& sBoard, const int score, const int alpha, const int beta) {
    
    RXBitBoard& board = sBoard.board;
    
    if(board.n_empties>6) { //hash limit
        
        //move in hash
        int movePV = NOMOVE;
        RXHashValue entry;
        const unsigned long long hash_code = board.hashcode();
        if(hTable->get(hash_code, type_hashtable, entry)) {
            
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
                hTable->update(hash_code, true, type_hashtable, NO_SELECT, DEPTH_BOOSTER+board.n_empties, alpha, beta, value, movePV);
            
            
        }
        
        if(movePV != NOMOVE) {
            
            //check value;
            RXHashValue entry;
            if(hTable->get(hash_code, type_hashtable, entry)) {
                
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
                ((board).*(board.generate_flips[movePV]))(move);
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

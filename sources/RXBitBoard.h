/*
 *  RXBitBoard.h
 *  Roxane
 *
 *  Created by Bruno Causse on 27/06/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#ifndef RXBITBOARD_H
#define RXBITBOARD_H

#include <iostream>
#include <string>

#include "RXConstantes.h"
#include "RXMove.h"
#include "RXSquareList.h"
#include "RXTools.h"


class RXBitBoard {

	friend class RXRoxane;
	friend class RXHashTable;
	friend class RXHashShallow;
	friend class RXEngine;
	friend class RXBBPatterns;
	friend class RXEvaluation;

	public :
	
	//neighborhood for each square
	static const unsigned long long NEIGHBOR[];
	// presorted squares
	static const int PRESORTED_POSITION[];
	/*! a quadrant id for each square */
	static const int QUADRANT_ID[];
			
	static const unsigned char COUNT_A[];
	static const unsigned char COUNT_B[];
	static const unsigned char COUNT_C[];
	static const unsigned char COUNT_D[];
	static const unsigned char COUNT_E[];
	static const unsigned char COUNT_F[];
	static const unsigned char COUNT_G[];
	static const unsigned char COUNT_H[];


	unsigned long long discs[2];
	unsigned long long hash_code;
	int player;
	int n_empties;
	int parity[4];
	RXSquareList empties_list[62];
	RXSquareList *position_to_empties[64];
	mutable unsigned long long n_nodes;
	
	void set_disc(const int position, const int color);
	
	//public :
		
		unsigned long long get_n_nodes() const {
			return n_nodes;
		}
	
		RXBitBoard();
	
		//constructeur par copie
		RXBitBoard(const RXBitBoard& src);
		
		RXBitBoard& operator=(const RXBitBoard& src);
	
		void build(const std::string& init);
	
		friend std::ostream& operator<<(std::ostream& os, RXBitBoard& board);

		bool squareIsEmpty(const int position) const;
		bool isPassed();
		bool isEndGame();

		// move functions
		#define func(pos)	static bool do_flips_##pos(unsigned long long& discs_player, unsigned long long& discs_opponent); \
							static int count_flips_##pos(const unsigned long long& discs_player); \
							bool generate_flips_##pos(RXMove& move) const; \
							bool generate_move_##pos(RXMove& move) const


	
		func(A1); func(B1); func(C1); func(D1); func(E1); func(F1); func(G1); func(H1);
		func(A2); func(B2); func(C2); func(D2); func(E2); func(F2); func(G2); func(H2);
		func(A3); func(B3); func(C3); func(D3); func(E3); func(F3); func(G3); func(H3);
		func(A4); func(B4); func(C4);					  func(F4); func(G4); func(H4);
		func(A5); func(B5); func(C5);					  func(F5); func(G5); func(H5);
		func(A6); func(B6); func(C6); func(D6); func(E6); func(F6); func(G6); func(H6);
		func(A7); func(B7); func(C7); func(D7); func(E7); func(F7); func(G7); func(H7);
		func(A8); func(B8); func(C8); func(D8); func(E8); func(F8); func(G8); func(H8);
		#undef func

	
		typedef bool (*type_do_flips)(unsigned long long& discs_player, unsigned long long& discs_opponent);
		static type_do_flips const do_flips[];

		typedef int (*type_count_flips)(const unsigned long long& discs_player);
		static type_count_flips const count_flips[];
	

		bool (RXBitBoard::*generate_flips[64])(RXMove& move) const;
		void init_generate_flips();
		
		bool (RXBitBoard::*generate_move[64])(RXMove& move) const;
		void init_generate_move();
		
		/* bool check_move(const int position, const int color) const; */

		int moves_producing(RXMove* start) const;

		static int get_mobility(const unsigned long long discs_player, const unsigned long long discs_opponent);
		static int get_corner_stability(const unsigned long long& discs_player);
		int get_stability(const int color, const int n_stables_cut) const;
		static int	get_border(const unsigned long long  p_discs, const unsigned long long  o_discs);
		
		void do_move(const RXMove& move);
		void undo_move(const RXMove& move);
		void do_pass();

		int final_score() const;
		int final_score_1() const;
		int final_score_2(int alpha, const int beta, const bool passed);
		int final_score_2(const unsigned long long discs_player, const unsigned long long discs_opponent, const int alpha, const int beta, const bool passed, const int idSquare1, const int idSquare2);
		int final_score_3(int alpha, const int beta, const bool passed);
		int final_score_3(const unsigned long long discs_player, const unsigned long long discs_opponent, int alpha, const int beta, const bool passed, const int idSquare1, const int idSquare2, const int idSquare3);
		int	final_score_4(int alpha, const int beta, const bool passed);
		int	final_score_4(const unsigned long long discs_player, const unsigned long long discs_opponent, int alpha, const int beta, const bool passed, const int idSquare1, const int idSquare2, const int idSquare3, const int idSquare4);

		std::string cassio_script() const;

		/* DEBUG */
		void print_empties_list() const;
		static void print_64bits(unsigned long long n);
		
		/* test */
		//static unsigned long long cntbset(unsigned long long n);
		//void build(const unsigned long long disc_player, const unsigned long long disc_opp, const int color);

		
};

inline int RXBitBoard::moves_producing(RXMove* start) const {
	
	RXMove *list = start + 1, *previous = start;
	int nMoves = 0;
	
	const unsigned long long discs_opponent = discs[player^1];
	for(RXSquareList* empties = empties_list->next; empties->position != NOMOVE; empties = empties->next)
		if((discs_opponent & NEIGHBOR[empties->position]) && ((this)->*(generate_move[empties->position]))(*list)) {
			list->score = 0;
			previous = previous->next = list++;
			nMoves++;
		}
	
	previous->next = NULL;	
	return nMoves;
}






inline void RXBitBoard::do_move(const RXMove& move) {
	
	discs[player] |= (move.flipped | move.square);
	player ^=1;
	discs[player] ^= move.flipped;
	
	n_empties--;

	hash_code ^= move.hash_code;

	parity[QUADRANT_ID[move.position]] ^= 1;
	
	const RXSquareList *remove = position_to_empties[move.position];
	remove->previous->next = remove->next;
	remove->next->previous = remove->previous;
		
	n_nodes++;
}

inline void RXBitBoard::undo_move(const RXMove& move) {

	RXSquareList *insert = position_to_empties[move.position];
	insert->previous->next = insert;
	insert->next->previous = insert;

	parity[QUADRANT_ID[move.position]] ^= 1;

	hash_code ^= move.hash_code;
	
	n_empties++;
	
	discs[player] |= move.flipped;
	player ^=1;
	discs[player] ^= (move.flipped | move.square);

}

inline void RXBitBoard::do_pass() {

	hash_code ^= 0xBB20B460D4D95138ULL;
	player ^= 1;
}


inline int RXBitBoard::get_mobility(const unsigned long long p_discs, const unsigned long long o_discs) {


	const unsigned long long inner_o_discs = o_discs & 0x7E7E7E7E7E7E7E7EULL;

 
	/* direction W */
	unsigned long long 
	flipped  = (p_discs >> 1) & inner_o_discs;
	flipped |= (flipped >> 1) & inner_o_discs;

	unsigned long long adjacent_o_discs = inner_o_discs & (inner_o_discs >> 1);

	flipped |= (flipped >> 2) & adjacent_o_discs;
	flipped |= (flipped >> 2) & adjacent_o_discs;

	unsigned long long legals = flipped >> 1;


//	/* direction _E*/
//	flipped  = (p_discs << 1) & inner_o_discs;
//	flipped |= (flipped << 1) & inner_o_discs;
//
//	adjacent_o_discs = inner_o_discs & (inner_o_discs << 1);
//  
//	flipped |= (flipped << 2) & adjacent_o_discs;
//	flipped |= (flipped << 2) & adjacent_o_discs;
//
//	legals |= flipped << 1;
	
	/* direction _E */
    flipped = (p_discs << 1);
    legals |= ((flipped + inner_o_discs) & ~flipped);


	/* direction S */
	flipped  = (p_discs >>  8) & o_discs;
	flipped |= (flipped >>  8) & o_discs;

	adjacent_o_discs = o_discs & (o_discs >> 8);

	flipped |= (flipped >> 16) & adjacent_o_discs;
	flipped |= (flipped >> 16) & adjacent_o_discs;

	legals |= flipped >> 8;


 	/* direction N */
	flipped  = (p_discs <<  8) & o_discs;
	flipped |= (flipped <<  8) & o_discs;

	adjacent_o_discs = o_discs & (o_discs << 8);

	flipped |= (flipped << 16) & adjacent_o_discs;
	flipped |= (flipped << 16) & adjacent_o_discs;

	legals |= flipped << 8;


	/* direction NE */
	flipped  = (p_discs >>  7) & inner_o_discs;
	flipped |= (flipped >>  7) & inner_o_discs;

	adjacent_o_discs = inner_o_discs & (inner_o_discs >> 7);

	flipped |= (flipped >> 14) & adjacent_o_discs;
	flipped |= (flipped >> 14) & adjacent_o_discs;

	legals |= flipped >> 7;


	/* direction SW */
	flipped  = (p_discs <<  7) & inner_o_discs;
	flipped |= (flipped <<  7) & inner_o_discs;

	adjacent_o_discs = inner_o_discs & (inner_o_discs << 7);

	flipped |= (flipped << 14) & adjacent_o_discs;
	flipped |= (flipped << 14) & adjacent_o_discs;

	legals |= flipped << 7;


	/* direction NW */
	flipped  = (p_discs >>  9) & inner_o_discs;
	flipped |= (flipped >>  9) & inner_o_discs;

	adjacent_o_discs = inner_o_discs & (inner_o_discs >> 9);

	flipped |= (flipped >> 18) & adjacent_o_discs;
	flipped |= (flipped >> 18) & adjacent_o_discs;

	legals |= flipped >> 9;


	/* direction SE */
	flipped  = (p_discs <<  9) & inner_o_discs;
	flipped |= (flipped <<  9) & inner_o_discs;

	adjacent_o_discs = inner_o_discs & (inner_o_discs << 9);

	flipped |= (flipped << 18) & adjacent_o_discs;
	flipped |= (flipped << 18) & adjacent_o_discs;

	legals |= flipped << 9;



	legals &= ~(p_discs | o_discs);

    if(legals == 0)
        return 0;	

	unsigned long long b;
	b  = legals - ((legals >> 1) & 0x1555555555555515ULL) + (legals & 0x0100000000000001ULL);
	b  = ((b >> 2) & 0x3333333333333333ULL) + (b & 0x3333333333333333ULL);
	b  = ((b >> 4) + b) & 0x0f0f0f0f0f0f0f0fULL;
	b *= 0x0101010101010101ULL;
	
	return  static_cast<int>(b >> 56);
	
//	/* bonus corners */
//
//	legals |= (legals & 0x8000000000000000ULL) >> 27;
//	legals |= (legals & 0x0000000000000001ULL) << 27;
//	legals |= (legals & 0x0100000000000000ULL) >> 21;
//	legals |= (legals & 0x0000000000000080ULL) << 21;
//
//	return __builtin_popcountll(legals);

}



inline int RXBitBoard::get_corner_stability(const unsigned long long& discs_player) {
	unsigned long long nStables = 0ULL;
	
	if(discs_player & 0X8000000000000000ULL) {
		nStables++;
		nStables += ((discs_player >> 62) & 0x0000000000000001ULL);
		nStables += ((discs_player >> 55) & 0x0000000000000001ULL);
	}
	if(discs_player & 0X0000000000000080ULL) {
		nStables++;
		nStables += ((discs_player >> 15) & 0x0000000000000001ULL);
		nStables += ((discs_player >> 6)  & 0x0000000000000001ULL);
	}
	if(discs_player & 0X0100000000000000ULL) {
		nStables++;
		nStables += ((discs_player >> 57) & 0x0000000000000001ULL);
		nStables += ((discs_player >> 48) & 0x0000000000000001ULL);
	}
	if(discs_player & 0X0000000000000001ULL) {
		nStables++;
		nStables += ((discs_player >> 8) & 0x0000000000000001ULL);
		nStables += ((discs_player >> 1) & 0x0000000000000001ULL);
	}

	return static_cast<unsigned int>(nStables);
}


inline int RXBitBoard::get_stability(const int color, const int n_stables_cut) const {

	unsigned long long filled = discs[BLACK] | discs[WHITE];

	unsigned long long left_right = filled;
	left_right &= left_right >> 4;
	left_right &= left_right >> 2;
	left_right &= left_right >> 1;
	left_right &= 0x0101010101010101ULL;

	left_right = (left_right << 8) - left_right; //*=255
	left_right |= 0x8181818181818181ULL;
	
	unsigned long long up_down = filled;
	up_down &= (up_down >> 32) | (up_down << 32);
	up_down &= (up_down >> 16) | (up_down << 16);
	up_down &= (up_down >>  8) & (up_down <<  8);

	up_down |= 0xFF000000000000FFULL;
	
	
	unsigned long long diag_a = filled;
	diag_a &= ((diag_a>>28) & 0x00000000F0F0F0F0ULL) | ((diag_a<<28) & 0x0F0F0F0F00000000ULL) | 0xF0F0F0F00F0F0F0FULL;
	diag_a &= ((diag_a>>14) & 0x0000FCFCFCFCFCFCULL) | ((diag_a<<14) & 0x3F3F3F3F3F3F0000ULL) | 0xC0C0000000000303ULL;
	diag_a &= (diag_a>> 7) & (diag_a<< 7);
	
	diag_a |= 0xFF818181818181FFULL;
	
	unsigned long long diag_b = filled;
	//diag_b &= ((diag_b>>36) & 0x000000000F0F0F0FULL) | ((diag_b<<36) & 0xF0F0F0F000000000ULL) | 0x0F0F0F0FF0F0F0F0ULL;	
	diag_b &= (diag_b>>36) | (diag_b<<36) | 0x0F0F0F0FF0F0F0F0ULL;
	diag_b &= ((diag_b>>18) & 0x00003F3F3F3F3F3FULL) | ((diag_b<<18) & 0xFCFCFCFCFCFC0000ULL) | 0x030300000000C0C0ULL;
	diag_b &= (diag_b>> 9) & (diag_b<< 9);
	
	diag_b |= 0xFF818181818181FFULL;
	

	
	unsigned long long stable = left_right & up_down & diag_a & diag_b & discs[color];

	if(stable == 0)
		return 0;
		

	int result = VALUE_DISC * __builtin_popcountll(stable);
	if(result>=n_stables_cut)
		return result;
	

	unsigned long long old_stable, dir_1, dir_2, dir_3, dir_4;

	do {

		old_stable = stable;

		dir_1 = (stable << 1) | (stable >> 1 ) | left_right;
		dir_2 = (stable << 8) | (stable >> 8 ) | up_down;
		dir_3 = (stable << 7) | (stable >> 7 ) | diag_a;
		dir_4 = (stable << 9) | (stable >> 9 ) | diag_b;

		stable = dir_1 & dir_2 & dir_3 & dir_4 & discs[color];

	} while(stable != old_stable);
	

    if(stable == 0)
        return 0;
		
	return VALUE_DISC * __builtin_popcountll(stable);

}

inline int RXBitBoard::get_border(const unsigned long long  p_discs, const unsigned long long  o_discs) {
	
	unsigned long long border
	        = (0x7E7E7E7E7E7E7E7EULL & p_discs) << 1;
	border |= (0x7E7E7E7E7E7E7E7EULL & p_discs) >> 1;
	border |= (0x00FFFFFFFFFFFF00ULL & p_discs) << 8;
	border |= (0x00FFFFFFFFFFFF00ULL & p_discs) >> 8;
	border |= (0x007E7E7E7E7E7E00ULL & p_discs) << 9;
	border |= (0x007E7E7E7E7E7E00ULL & p_discs) >> 9;
	border |= (0x007E7E7E7E7E7E00ULL & p_discs) << 7;
	border |= (0x007E7E7E7E7E7E00ULL & p_discs) >> 7;
	
	border &= ~(p_discs | o_discs);
			
	return __builtin_popcountll(border);
	
}


inline int RXBitBoard::final_score_2(int alpha, const int beta, const bool passed) {
	return final_score_2(discs[player], discs[player^1], alpha/VALUE_DISC, beta/VALUE_DISC, passed,  empties_list->next->position,  empties_list->next->next->position)*VALUE_DISC;
}


inline int RXBitBoard::final_score_2(const unsigned long long discs_player, const unsigned long long discs_opponent, const int alpha, const int beta, const bool passed, const int idSquare1, const int idSquare2) {
	
	unsigned long long d_player = discs_player;
	unsigned long long d_opponent = discs_opponent;
			
	int n_flips, bestscore = UNDEF_SCORE;
		
	// try to play on the first available square
	if((d_opponent & NEIGHBOR[idSquare1]) && (do_flips[idSquare1](d_player, d_opponent))) {
		n_nodes++;
		
		bestscore = 62 - 2*__builtin_popcountll(d_opponent);

		
		
		n_flips = count_flips[idSquare2](d_opponent);
		if(n_flips !=0) {
			bestscore -= n_flips;
		} else {
			if(bestscore >= 0) {
				bestscore += 2;
				if(bestscore < beta) {
					bestscore += count_flips[idSquare2](d_player);
				}
			} else {
				if(bestscore < beta) {
					n_flips = count_flips[idSquare2](d_player);

					if(n_flips != 0)
						bestscore += n_flips + 2;
				}
			}
		}

		if(bestscore >= beta)
			return bestscore;

		d_player = discs_player;
		d_opponent = discs_opponent;
			
	}
								
	// if needed, try to play on the second & last available square
	if((d_opponent & NEIGHBOR[idSquare2]) && (do_flips[idSquare2](d_player, d_opponent))) {
		n_nodes++;
		
		int score = 62 - 2*__builtin_popcountll(d_opponent);

		
		n_flips = count_flips[idSquare1](d_opponent);
		if(n_flips !=0) {
			score -= n_flips;
		} else {
			if(score >= 0) {
				score += 2;
				if(score < beta) {
					score += count_flips[idSquare1](d_player);
				}
			} else {
				if(score < beta) {
					n_flips = count_flips[idSquare1](d_player);
					if(n_flips != 0)
						score += n_flips + 2;
				}
			}
		}

		if(score > bestscore)
			return score;
			
		return bestscore;

	}

	// if no move were available
	if(bestscore == UNDEF_SCORE) {
		if (passed) {
			n_nodes--;
			bestscore = 62 - 2*__builtin_popcountll(discs_opponent);
			if(bestscore>0)
				bestscore+=2;
			else if (bestscore<0)
				bestscore-=2;
								
		} else {
			n_nodes++;
			bestscore = -final_score_2(discs_opponent, discs_player, -beta, -alpha, true, idSquare1, idSquare2);
		}
	}
				
	return bestscore;
}



inline int RXBitBoard::final_score_3(int alpha, const int beta, const bool passed) {
	return final_score_3(discs[player], discs[player^1], alpha/VALUE_DISC, beta/VALUE_DISC, passed,  empties_list->next->position,  empties_list->next->next->position,  empties_list->next->next->next->position)*VALUE_DISC;
}

inline int RXBitBoard::final_score_3(const unsigned long long discs_player, const unsigned long long discs_opponent, int alpha, const int beta, const bool passed, const int idSquare1, const int idSquare2, const int idSquare3) {

	int score, bestscore = UNDEF_SCORE;
	
	unsigned long long d_player = discs_player;
	unsigned long long d_opponent = discs_opponent;
		
	if ((d_opponent & NEIGHBOR[idSquare1]) && (do_flips[idSquare1](d_player, d_opponent))){ 
		n_nodes++;
		
		bestscore = -final_score_2(d_opponent, d_player, -beta, -alpha, false, idSquare2, idSquare3);
										
		if(bestscore>=beta)
			return bestscore;

		if(bestscore>alpha)
			alpha = bestscore;
		
		d_player = discs_player;
		d_opponent = discs_opponent;

	}

	if ((d_opponent & NEIGHBOR[idSquare2]) && (do_flips[idSquare2](d_player, d_opponent))){ 
		n_nodes++;
		
		score = -final_score_2(d_opponent, d_player, -beta, -alpha, false, idSquare1, idSquare3);
		
		if(score>=beta)
			return score;
			
		if (score > bestscore) {
			bestscore = score;
			if (bestscore > alpha)
				alpha = bestscore;
		}
		
		d_player = discs_player;
		d_opponent = discs_opponent;
		
	}
	
	if ((d_opponent & NEIGHBOR[idSquare3]) && (do_flips[idSquare3](d_player, d_opponent))){ 
		n_nodes++;
		
		score = -final_score_2(d_opponent, d_player, -beta, -alpha, false, idSquare1, idSquare2);
		
		if(score > bestscore)
			return score;
			
		return bestscore;
	}

	// if no _move3 were available
	if(bestscore == UNDEF_SCORE) {
		if (passed) {
			n_nodes--;
			bestscore = 61-2*__builtin_popcountll(discs_opponent);
			if(bestscore>0)
				bestscore+=3;
			else if (bestscore<0)
				bestscore-=3;
								
		} else {
			n_nodes++;
			bestscore = -final_score_3(d_opponent, d_player, -beta, -alpha, true, idSquare1, idSquare2, idSquare3);
		}
	}
	
	return bestscore;
}

inline int RXBitBoard::final_score_4(int alpha, const int beta, const bool passed) {
	
	int diffPions = 2*__builtin_popcountll(discs[player]) - 60;
	
	if (alpha >= 5000 || (alpha >= 0 && (diffPions*VALUE_DISC <= alpha - 2400))) {
		
		int stability_bound = 6400 - 2 * get_stability(player^1, (6500-alpha)/2);
		if ( stability_bound <= alpha )
			return stability_bound; //alpha
		
	} else if (beta <= -5000 || (beta <= 0 && (diffPions*VALUE_DISC >= beta + 2400))) {
		
		int stability_bound = -6400 + 2 * get_stability(player, (6500+beta)/2);
		if ( stability_bound >= beta )
			return stability_bound; //beta
		
	}
	
	int sq_1 = empties_list->next->position;
	int sq_2 = empties_list->next->next->position;
	int sq_3 = empties_list->next->next->next->position;
	int sq_4 = empties_list->next->next->next->next->position;
	
//	if(parity[RXBitBoard::QUADRANT_ID[sq_1]] == 0) {
//		
//		if(parity[RXBitBoard::QUADRANT_ID[sq_2]] == 1) {
//			
//			if(parity[RXBitBoard::QUADRANT_ID[sq_3]] == 1) {
//				int temp = sq_1;
//				sq_1 = sq_2;
//				sq_2 = sq_3;
//				sq_3 = temp;
//			} else {
//				int temp = sq_1;
//				sq_1 = sq_2;
//				sq_2 = sq_4;
//				sq_4 = sq_3;
//				sq_3 = temp;
//			}
//			
//		} else {
//			
//			if(parity[RXBitBoard::QUADRANT_ID[sq_3]] == 1) {
//				int temp = sq_1;
//				sq_1 = sq_3;
//				sq_3 = temp;
//				temp = sq_2;
//				sq_2 = sq_4;
//				sq_4 = temp;
//			}
//		}
//		
//		
//	} else {
//		
//		if(parity[RXBitBoard::QUADRANT_ID[sq_2]] == 0) {
//			
//			if(parity[RXBitBoard::QUADRANT_ID[sq_3]] == 1) {
//				int temp = sq_2;
//				sq_2 = sq_3;
//				sq_3 = temp;
//			} else {
//				int temp = sq_2;
//				sq_2 = sq_4;
//				sq_4 = sq_3;
//				sq_3 = temp;
//			}
//			
//		}
//		
//		
//	}
	
	
	return final_score_4(discs[player], discs[player^1], alpha/VALUE_DISC, beta/VALUE_DISC, passed, sq_1,  sq_2, sq_3, sq_4)*VALUE_DISC;
}

inline int RXBitBoard::final_score_4(const unsigned long long discs_player, const unsigned long long discs_opponent, int alpha, const int beta, const bool passed, const int idSquare1, const int idSquare2, const int idSquare3, const int idSquare4) {

		
	int score, bestscore = UNDEF_SCORE;
		
	unsigned long long d_player = discs_player;
	unsigned long long d_opponent = discs_opponent;
	
	if ((d_opponent & NEIGHBOR[idSquare1]) && (do_flips[idSquare1](d_player, d_opponent))){ 
		n_nodes++;
			 
		bestscore = -final_score_3(d_opponent, d_player, -beta, -alpha, false, idSquare2, idSquare3, idSquare4);
				
		if(bestscore>=beta)
			return bestscore;

		if(bestscore>alpha)
			alpha = bestscore;
		
		d_player = discs_player;
		d_opponent = discs_opponent;
		
	}

	if ((d_opponent & NEIGHBOR[idSquare2]) && (do_flips[idSquare2](d_player, d_opponent))){ 
		n_nodes++;
		
		score = -final_score_3(d_opponent, d_player, -beta, -alpha, false, idSquare1, idSquare3, idSquare4);
		
		if(score>=beta)
			return score;
			
		if (score > bestscore) {
			bestscore = score;
			if (bestscore > alpha)
				alpha = bestscore;
		}

		d_player = discs_player;
		d_opponent = discs_opponent;
		
	}
	
	if ((d_opponent & NEIGHBOR[idSquare3]) && (do_flips[idSquare3](d_player, d_opponent))) {
		n_nodes++;
		
		score = -final_score_3(d_opponent, d_player, -beta, -alpha, false, idSquare1, idSquare2, idSquare4);
		
		if(score>=beta)
			return score;
			
		if (score > bestscore) {
			bestscore = score;
			if (bestscore > alpha)
				alpha = bestscore;
		}

		d_player = discs_player;
		d_opponent = discs_opponent;
		
	}

	if ((d_opponent & NEIGHBOR[idSquare4]) && (do_flips[idSquare4](d_player, d_opponent))){ 
		n_nodes++;
		
		score = -final_score_3(d_opponent, d_player, -beta, -alpha, false, idSquare1, idSquare2, idSquare3);

		if(score > bestscore)
			return score;
			
		return bestscore;
			
	}

	// if no _move4 were available
	if(bestscore == UNDEF_SCORE) {
		if (passed) {
			n_nodes--;
			bestscore = 60-2*__builtin_popcountll(discs_opponent);
			if(bestscore>0)
				bestscore+=4;
			else if (bestscore<0)
				bestscore-=4;
								
		} else {
			n_nodes++;
			bestscore = -final_score_4(d_opponent, d_player, -beta, -alpha, true, idSquare1, idSquare2, idSquare3, idSquare4);
		}
	}
	
	return bestscore;
}

	
#endif

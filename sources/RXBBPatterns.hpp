/*
 *  RXBBPatterns.hpp
 *  Roxane
 *
 *  Created by Bruno Causse on 31/07/05.
 *  Copyright 2005-2024 personnel. All rights reserved.
 *
 */

#ifndef RXBBPATTERN_HPP
#define RXBBPATTERN_HPP

#include <cmath>

#include "RXConstantes.hpp"
#include "RXBitBoard.hpp"
#include "RXPattern.hpp"
#include "RXEvaluation.hpp"


class RXBBPatterns {

	friend class RXRoxane;
	friend class RXEngine;

	static const int QUANTA = VALUE_DISC;
							  
	void set_BLACK(const int pos);
	void set_WHITE(const int pos);

	RXBitBoard board;
	RXPattern* pattern;

	public :


		RXBBPatterns();
	
		//constructeur par copie
		RXBBPatterns(const RXBBPatterns& src);
			
		RXBBPatterns& operator=(const RXBBPatterns& src);
		
		~RXBBPatterns();
	
		void build(const std::string& init);
		void copy_pattern(const RXPattern* src);

		void do_move(RXMove& move);
		void undo_move(const RXMove& move);
				
		// move functions
		#define func(pos)   void update_patterns_BLACK_##pos(RXMove& move) const; \
							void update_patterns_WHITE_##pos(RXMove& move) const
							
		func(A1); func(B1); func(C1); func(D1); func(E1); func(F1); func(G1); func(H1);
		func(A2); func(B2); func(C2); func(D2); func(E2); func(F2); func(G2); func(H2);
		func(A3); func(B3); func(C3); func(D3); func(E3); func(F3); func(G3); func(H3);
		func(A4); func(B4); func(C4);			          func(F4); func(G4); func(H4);
		func(A5); func(B5); func(C5);			          func(F5); func(G5); func(H5);
		func(A6); func(B6); func(C6); func(D6); func(E6); func(F6); func(G6); func(H6);
		func(A7); func(B7); func(C7); func(D7); func(E7); func(F7); func(G7); func(H7);
		func(A8); func(B8); func(C8); func(D8); func(E8); func(F8); func(G8); func(H8);
		#undef func


		void (RXBBPatterns::*update_patterns[64][2])(RXMove& move) const;
		void init_update_patterns();
		
		double get_n_nodes() const { return board.get_n_nodes(); }
		int get_n_empties() const { return board.n_empties; }

		int final_score() const;
		int get_score() const;
		int get_score(RXMove& move) const;

		/* DEBUG */
		friend std::ostream& operator<<(std::ostream& os, RXBBPatterns& sBoard);
		
};


inline void RXBBPatterns::do_move(RXMove& move) {
	board.do_move(move);
	move.undo_pattern = pattern;
	pattern = move.pattern;
}

inline void RXBBPatterns::undo_move(const RXMove& move) {
	pattern = move.undo_pattern;
	board.undo_move(move);
}


inline int RXBBPatterns::final_score() const {
	int score = board.final_score();
	if(score<0)
		return (-MAX_SCORE) + (score + 64*VALUE_DISC);
	return (MAX_SCORE) + (score-64*VALUE_DISC);
}

inline void RXBBPatterns::copy_pattern(const RXPattern* src) {
	
	pattern->diag_5a = src->diag_5a;
	pattern->diag_5b = src->diag_5b;
	pattern->diag_5c = src->diag_5c;
	pattern->diag_5d = src->diag_5d;

	pattern->diag_6a = src->diag_6a;
	pattern->diag_6b = src->diag_6b;
	pattern->diag_6c = src->diag_6c;
	pattern->diag_6d = src->diag_6d;
	
	pattern->diag_7a = src->diag_7a;
	pattern->diag_7b = src->diag_7b;
	pattern->diag_7c = src->diag_7c;
	pattern->diag_7d = src->diag_7d;
	
	pattern->diag_8a = src->diag_8a;
	pattern->diag_8b = src->diag_8b;
	
	pattern->hv_4a = src->hv_4a;
	pattern->hv_4b = src->hv_4b;
	pattern->hv_4c = src->hv_4c;
	pattern->hv_4d = src->hv_4d;
	
	pattern->hv_3a = src->hv_3a;
	pattern->hv_3b = src->hv_3b;
	pattern->hv_3c = src->hv_3c;
	pattern->hv_3d = src->hv_3d;
	
	pattern->hv_2a = src->hv_2a;
	pattern->hv_2b = src->hv_2b;
	pattern->hv_2c = src->hv_2c;
	pattern->hv_2d = src->hv_2d;
	
	pattern->corner2x5a = src->corner2x5a;
	pattern->corner2x5b = src->corner2x5b;
	pattern->corner2x5c = src->corner2x5c;
	pattern->corner2x5d = src->corner2x5d;
	pattern->corner2x5e = src->corner2x5e;
	pattern->corner2x5f = src->corner2x5f;
	pattern->corner2x5g = src->corner2x5g;
	pattern->corner2x5h = src->corner2x5h;

	pattern->edge64a = src->edge64a;
	pattern->edge64b = src->edge64b;
	pattern->edge64c = src->edge64c;
	pattern->edge64d = src->edge64d;

	pattern->corner11a = src->corner2x5a;
	pattern->corner11b = src->corner2x5b;
	pattern->corner11c = src->corner2x5c;
	pattern->corner11d = src->corner2x5d;
	
	pattern->edge2XCa = src->edge2XCa;
	pattern->edge2XCb = src->edge2XCb;
	pattern->edge2XCc = src->edge2XCc;
	pattern->edge2XCd = src->edge2XCd;
	


}


inline int RXBBPatterns::get_score() const {
	
	const int stage = 60-board.n_empties;
	
	const unsigned long long filled = (board.discs[BLACK] | board.discs[WHITE]);
	
	int eval;
	const short* value;
	const short* value_b;
		
	if(board.player == BLACK) {

		value = RXEvaluation::DIAG_5[stage];
		eval  = value[pattern->diag_5a];
		eval += value[pattern->diag_5b];
		eval += value[pattern->diag_5c];
		eval += value[pattern->diag_5d];

		value = RXEvaluation::DIAG_6[stage];
		eval += value[pattern->diag_6a];
		eval += value[pattern->diag_6b];
		eval += value[pattern->diag_6c];
		eval += value[pattern->diag_6d];

		value = RXEvaluation::DIAG_7[stage];
		eval += value[pattern->diag_7a];
		eval += value[pattern->diag_7b];
		eval += value[pattern->diag_7c];
		eval += value[pattern->diag_7d];

		value = RXEvaluation::DIAG_8[stage];
		eval += value[pattern->diag_8a];
		eval += value[pattern->diag_8b];

		value = RXEvaluation::HV_4[stage];
		eval += value[pattern->hv_4a];
		eval += value[pattern->hv_4b];
		eval += value[pattern->hv_4c];
		eval += value[pattern->hv_4d];

		value = RXEvaluation::HV_3[stage];
		eval += value[pattern->hv_3a];
		eval += value[pattern->hv_3b];
		eval += value[pattern->hv_3c];
		eval += value[pattern->hv_3d];

		value = RXEvaluation::HV_2[stage];
		eval += value[pattern->hv_2a];
		eval += value[pattern->hv_2b];
		eval += value[pattern->hv_2c];
		eval += value[pattern->hv_2d];

		value = RXEvaluation::CORNER_11[stage];
		eval += value[pattern->corner11a];
		eval += value[pattern->corner11b];
		eval += value[pattern->corner11c];
		eval += value[pattern->corner11d];
		
		value = RXEvaluation::CORNER_2x5[stage];
		eval += value[pattern->corner2x5a];
		eval += value[pattern->corner2x5b];
		eval += value[pattern->corner2x5c];
		eval += value[pattern->corner2x5d];
		eval += value[pattern->corner2x5e];
		eval += value[pattern->corner2x5f];
		eval += value[pattern->corner2x5g];
		eval += value[pattern->corner2x5h];

		value = RXEvaluation::EDGE_2XC[stage];
		value_b = RXEvaluation::EDGE_6_4[stage];
		if(filled & 0x8142000000000000ULL)	//A1 H1 B2 G2
			eval += value[pattern->edge2XCa];
		else
			eval += value_b[pattern->edge64a];

		if(filled & 0x0102000000000201ULL) //H1 G2 G7 H8
			eval += value[pattern->edge2XCb];
		else
			eval += value_b[pattern->edge64b];

		if(filled & 0x0000000000004281ULL)	//B7 G7 A8 H8
			eval += value[pattern->edge2XCc];
		else
			eval += value_b[pattern->edge64c];

		if(filled & 0x8040000000004080ULL)	//A1 B2 B7 A8
			eval += value[pattern->edge2XCd];
		else
			eval += value_b[pattern->edge64d];

	 } else {
	 
		value = RXEvaluation::DIAG_5[stage];
		eval  = value[-pattern->diag_5a];
		eval += value[-pattern->diag_5b];
		eval += value[-pattern->diag_5c];
		eval += value[-pattern->diag_5d];
		
		value = RXEvaluation::DIAG_6[stage];
		eval += value[-pattern->diag_6a];
		eval += value[-pattern->diag_6b];
		eval += value[-pattern->diag_6c];
		eval += value[-pattern->diag_6d];

		value = RXEvaluation::DIAG_7[stage];
		eval += value[-pattern->diag_7a];
		eval += value[-pattern->diag_7b];
		eval += value[-pattern->diag_7c];
		eval += value[-pattern->diag_7d];

		value = RXEvaluation::DIAG_8[stage];
		eval += value[-pattern->diag_8a];
		eval += value[-pattern->diag_8b];

		value = RXEvaluation::HV_4[stage];
		eval += value[-pattern->hv_4a];
		eval += value[-pattern->hv_4b];
		eval += value[-pattern->hv_4c];
		eval += value[-pattern->hv_4d];

		value = RXEvaluation::HV_3[stage];
		eval += value[-pattern->hv_3a];
		eval += value[-pattern->hv_3b];
		eval += value[-pattern->hv_3c];
		eval += value[-pattern->hv_3d];

		value = RXEvaluation::HV_2[stage];
		eval += value[-pattern->hv_2a];
		eval += value[-pattern->hv_2b];
		eval += value[-pattern->hv_2c];
		eval += value[-pattern->hv_2d];

		value = RXEvaluation::CORNER_11[stage];
		eval += value[-pattern->corner11a];
		eval += value[-pattern->corner11b];
		eval += value[-pattern->corner11c];
		eval += value[-pattern->corner11d];
		
		value = RXEvaluation::CORNER_2x5[stage];
		eval += value[-pattern->corner2x5a];
		eval += value[-pattern->corner2x5b];
		eval += value[-pattern->corner2x5c];
		eval += value[-pattern->corner2x5d];
		eval += value[-pattern->corner2x5e];
		eval += value[-pattern->corner2x5f];
		eval += value[-pattern->corner2x5g];
		eval += value[-pattern->corner2x5h];

		value = RXEvaluation::EDGE_2XC[stage];
		value_b = RXEvaluation::EDGE_6_4[stage];
		if(filled & 0x8142000000000000ULL)	//A1 H1 B2 G2
			eval += value[-pattern->edge2XCa];
		else
			eval += value_b[-pattern->edge64a];

		if(filled & 0x0102000000000201ULL) //H1 G2 G7 H8
			eval += value[-pattern->edge2XCb];
		else
			eval += value_b[-pattern->edge64b];

		if(filled & 0x0000000000004281ULL)	//B7 G7 A8 H8
			eval += value[-pattern->edge2XCc];
		else
			eval += value_b[-pattern->edge64c];

		if(filled & 0x8040000000004080ULL)	//A1 B2 B7 A8
			eval += value[-pattern->edge2XCd];
		else
			eval += value_b[-pattern->edge64d];
			
	}
	
//	return eval >> 3;//div 8
	
	

	// theorie des quantas
	eval >>= 3; 
	if(eval < 0)
		return QUANTA * ((eval+1 -QUANTA/2)/QUANTA);
	else
		return QUANTA * ((eval   +QUANTA/2)/QUANTA);


}


inline int RXBBPatterns::get_score(RXMove& move) const {

	const RXPattern* const p = move.pattern;
	
	const int stage = 61-board.n_empties;
	
	const unsigned long long filled = (board.discs[BLACK] | board.discs[WHITE] | move.square);
	
	int eval;
	const short* value;
	const short* value_b;

	if(board.player == WHITE) {

		value = RXEvaluation::DIAG_5[stage];
		eval  = value[p->diag_5a];
		eval += value[p->diag_5b];
		eval += value[p->diag_5c];
		eval += value[p->diag_5d];

		value = RXEvaluation::DIAG_6[stage];
		eval += value[p->diag_6a];
		eval += value[p->diag_6b];
		eval += value[p->diag_6c];
		eval += value[p->diag_6d];

		value = RXEvaluation::DIAG_7[stage];
		eval += value[p->diag_7a];
		eval += value[p->diag_7b];
		eval += value[p->diag_7c];
		eval += value[p->diag_7d];

		value = RXEvaluation::DIAG_8[stage];
		eval += value[p->diag_8a];
		eval += value[p->diag_8b];

		value = RXEvaluation::HV_4[stage];
		eval += value[p->hv_4a];
		eval += value[p->hv_4b];
		eval += value[p->hv_4c];
		eval += value[p->hv_4d];

		value = RXEvaluation::HV_3[stage];
		eval += value[p->hv_3a];
		eval += value[p->hv_3b];
		eval += value[p->hv_3c];
		eval += value[p->hv_3d];

		value = RXEvaluation::HV_2[stage];
		eval += value[p->hv_2a];
		eval += value[p->hv_2b];
		eval += value[p->hv_2c];
		eval += value[p->hv_2d];

		value = RXEvaluation::CORNER_11[stage];
		eval += value[p->corner11a];
		eval += value[p->corner11b];
		eval += value[p->corner11c];
		eval += value[p->corner11d];
		
		value = RXEvaluation::CORNER_2x5[stage];
		eval += value[p->corner2x5a];
		eval += value[p->corner2x5b];
		eval += value[p->corner2x5c];
		eval += value[p->corner2x5d];
		eval += value[p->corner2x5e];
		eval += value[p->corner2x5f];
		eval += value[p->corner2x5g];
		eval += value[p->corner2x5h];
		
		value = RXEvaluation::EDGE_2XC[stage];
		value_b = RXEvaluation::EDGE_6_4[stage];
		if(filled & 0x8142000000000000ULL)	//A1 H1 B2 G2
			eval += value[p->edge2XCa];
		else
			eval += value_b[p->edge64a];

		if(filled & 0x0102000000000201ULL) //H1 G2 G7 H8
			eval += value[p->edge2XCb];
		else
			eval += value_b[p->edge64b];

		if(filled & 0x0000000000004281ULL)	//B7 G7 A8 H8
			eval += value[p->edge2XCc];
		else
			eval += value_b[p->edge64c];

		if(filled & 0x8040000000004080ULL)	//A1 B2 B7 A8
			eval += value[p->edge2XCd];
		else
			eval += value_b[p->edge64d];
		
	 } else {
	 
		value = RXEvaluation::DIAG_5[stage];
		eval  = value[-p->diag_5a];
		eval += value[-p->diag_5b];
		eval += value[-p->diag_5c];
		eval += value[-p->diag_5d];

		value = RXEvaluation::DIAG_6[stage];
		eval += value[-p->diag_6a];
		eval += value[-p->diag_6b];
		eval += value[-p->diag_6c];
		eval += value[-p->diag_6d];

		value = RXEvaluation::DIAG_7[stage];
		eval += value[-p->diag_7a];
		eval += value[-p->diag_7b];
		eval += value[-p->diag_7c];
		eval += value[-p->diag_7d];

		value = RXEvaluation::DIAG_8[stage];
		eval += value[-p->diag_8a];
		eval += value[-p->diag_8b];

		value = RXEvaluation::HV_4[stage];
		eval += value[-p->hv_4a];
		eval += value[-p->hv_4b];
		eval += value[-p->hv_4c];
		eval += value[-p->hv_4d];

		value = RXEvaluation::HV_3[stage];
		eval += value[-p->hv_3a];
		eval += value[-p->hv_3b];
		eval += value[-p->hv_3c];
		eval += value[-p->hv_3d];

		value = RXEvaluation::HV_2[stage];
		eval += value[-p->hv_2a];
		eval += value[-p->hv_2b];
		eval += value[-p->hv_2c];
		eval += value[-p->hv_2d];

		value = RXEvaluation::CORNER_11[stage];
		eval += value[-p->corner11a];
		eval += value[-p->corner11b];
		eval += value[-p->corner11c];
		eval += value[-p->corner11d];
		
		value = RXEvaluation::CORNER_2x5[stage];
		eval += value[-p->corner2x5a];
		eval += value[-p->corner2x5b];
		eval += value[-p->corner2x5c];
		eval += value[-p->corner2x5d];
		eval += value[-p->corner2x5e];
		eval += value[-p->corner2x5f];
		eval += value[-p->corner2x5g];
		eval += value[-p->corner2x5h];
		
		value = RXEvaluation::EDGE_2XC[stage];
		value_b = RXEvaluation::EDGE_6_4[stage];
		if(filled & 0x8142000000000000ULL)	//A1 H1 B2 G2
			eval += value[-p->edge2XCa];
		else
			eval += value_b[-p->edge64a];

		if(filled & 0x0102000000000201ULL) //H1 G2 G7 H8
			eval += value[-p->edge2XCb];
		else
			eval += value_b[-p->edge64b];

		if(filled & 0x0000000000004281ULL)	//B7 G7 A8 H8
			eval += value[-p->edge2XCc];
		else
			eval += value_b[-p->edge64c];

		if(filled & 0x8040000000004080ULL)	//A1 B2 B7 A8
			eval += value[-p->edge2XCd];
		else
			eval += value_b[-p->edge64d];
		
	}
	
//	return eval >> 3;//div 8


	// theorie des quantas
	eval >>= 3; 
	if(eval <  0)
		return QUANTA * ((eval+1 -QUANTA/2)/QUANTA);
	else
		return QUANTA * ((eval   +QUANTA/2)/QUANTA);
		

}





#endif

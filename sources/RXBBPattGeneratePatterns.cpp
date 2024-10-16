/*
 *  RXBBPattGeneratePatterns.cpp
 *  Roxane
 *
 *  Created by Bruno Causse on 06/08/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#include "RXBBPatterns.h"
#include "RXTools.h"


bool RXBBPatterns::generate_patterns_BLACK_A1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000201008040201ULL;
	opp_discs = (discs_opponent & 0X0040201008040200ULL) | 0X7FBFDFEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X8000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X8000000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_A1();

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_D4();
				case 27:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_B2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000808080808080ULL;
	opp_discs = (discs_opponent & 0X0080808080808000ULL) | 0X7F7F7F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X8000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X8000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A1();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_A7();
				case 48:
					p.flip_BLACK_A6();
				case 40:
					p.flip_BLACK_A5();
				case 32:
					p.flip_BLACK_A4();
				case 24:
					p.flip_BLACK_A3();
				default:
					p.flip_BLACK_A2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X3F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X8000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X8000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_BLACK_G1();
				case 6:
					p.flip_BLACK_F1();
				case 5:
					p.flip_BLACK_E1();
				case 4:
					p.flip_BLACK_D1();
				case 3:
					p.flip_BLACK_C1();
				default:
					p.flip_BLACK_B1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000100804020100ULL;
	opp_discs = (discs_opponent & 0X0020100804020000ULL) | 0X3FDFEFF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X4000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X4000000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_B1();

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_E4();
				case 28:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_C2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000404040404040ULL;
	opp_discs = (discs_opponent & 0X0040404040404000ULL) | 0X3FBFBFBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X4000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X4000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B1();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_B6();
				case 41:
					p.flip_BLACK_B5();
				case 33:
					p.flip_BLACK_B4();
				case 25:
					p.flip_BLACK_B3();
				default:
					p.flip_BLACK_B2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X1F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X4000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X4000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_BLACK_G1();
				case 6:
					p.flip_BLACK_F1();
				case 5:
					p.flip_BLACK_E1();
				case 4:
					p.flip_BLACK_D1();
				default:
					p.flip_BLACK_C1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000202020202020ULL;
	opp_discs = (discs_opponent & 0X0020202020202000ULL) | 0X1FDFDFDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X2000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X2000000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_C1();

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_C6();
				case 42:
					p.flip_BLACK_C5();
				case 34:
					p.flip_BLACK_C4();
				case 26:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_C2();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000080402010000ULL;
	opp_discs = (discs_opponent & 0X0010080402000000ULL) | 0X1FEFF7FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X2000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C1();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_F4();
				case 29:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_D2();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C1();
		}

		p.flip_BLACK_B2();
	}

	/* direction _E */
	my_discs = discs_player & 0X0F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X2000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_BLACK_G1();
				case 6:
					p.flip_BLACK_F1();
				case 5:
					p.flip_BLACK_E1();
				default:
					p.flip_BLACK_D1();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X4000000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C1();
		}

		p.flip_BLACK_B1();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_D1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000101010101010ULL;
	opp_discs = (discs_opponent & 0X0010101010101000ULL) | 0X0FEFEFEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X1000000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_D1();

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_D5();
				case 35:
					p.flip_BLACK_D4();
				case 27:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_D2();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000040201000000ULL;
	opp_discs = (discs_opponent & 0X0008040200000000ULL) | 0X0FF7FBFC00000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D1();
		}

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_BLACK_G4();
				case 30:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_E2();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000408000000000ULL;
	opp_discs = (discs_opponent & 0X0020400000000000ULL) | 0X0FDF800000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D1();
		}

		switch(_cntlzll(my_discs)) {
				case 24:
					p.flip_BLACK_B3();
				default:
					p.flip_BLACK_C2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0700000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X1000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_BLACK_G1();
				case 6:
					p.flip_BLACK_F1();
				default:
					p.flip_BLACK_E1();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XC000000000000000ULL;
	r = (discs_opponent + 0X2000000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B1();
				default:
					p.flip_BLACK_C1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_E1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000080808080808ULL;
	opp_discs = (discs_opponent & 0X0008080808080800ULL) | 0X07F7F7F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0800000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_E1();

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_E4();
				case 28:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_E2();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000020100000000ULL;
	opp_discs = (discs_opponent & 0X0004020000000000ULL) | 0X07FBFC0000000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E1();
		}

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_BLACK_G3();
				default:
					p.flip_BLACK_F2();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000204080000000ULL;
	opp_discs = (discs_opponent & 0X0010204000000000ULL) | 0X07EFDF8000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E1();
		}

		switch(_cntlzll(my_discs)) {
				case 32:
					p.flip_BLACK_B4();
				case 25:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_D2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0300000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0800000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_BLACK_G1();
				default:
					p.flip_BLACK_F1();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XE000000000000000ULL;
	r = (discs_opponent + 0X1000000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B1();
				case 0X4000000000000000ULL:
					p.flip_BLACK_C1();
				default:
					p.flip_BLACK_D1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000040404040404ULL;
	opp_discs = (discs_opponent & 0X0004040404040400ULL) | 0X03FBFBFBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0400000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0400000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_F1();

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_F4();
				case 29:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_F2();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F1();
		}

		p.flip_BLACK_G2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000102040800000ULL;
	opp_discs = (discs_opponent & 0X0008102040000000ULL) | 0X03F7EFDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0400000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F1();
		}

		switch(_cntlzll(my_discs)) {
				case 40:
					p.flip_BLACK_B5();
				case 33:
					p.flip_BLACK_C4();
				case 26:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_E2();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0200000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F1();
		}

		p.flip_BLACK_G1();
	}

	/* direction _W */
	my_discs = discs_player & 0XF000000000000000ULL;
	r = (discs_opponent + 0X0800000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B1();
				case 0X4000000000000000ULL:
					p.flip_BLACK_C1();
				case 0X2000000000000000ULL:
					p.flip_BLACK_D1();
				default:
					p.flip_BLACK_E1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000081020408000ULL;
	opp_discs = (discs_opponent & 0X0004081020400000ULL) | 0X01FBF7EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0200000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0200000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_G1();

		switch(_cntlzll(my_discs)) {
				case 48:
					p.flip_BLACK_B6();
				case 41:
					p.flip_BLACK_C5();
				case 34:
					p.flip_BLACK_D4();
				case 27:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_F2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XF800000000000000ULL;
	r = (discs_opponent + 0X0400000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0200000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B1();
				case 0X4000000000000000ULL:
					p.flip_BLACK_C1();
				case 0X2000000000000000ULL:
					p.flip_BLACK_D1();
				case 0X1000000000000000ULL:
					p.flip_BLACK_E1();
				default:
					p.flip_BLACK_F1();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000020202020202ULL;
	opp_discs = (discs_opponent & 0X0002020202020200ULL) | 0X01FDFDFDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0200000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0200000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G1();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_G4();
				case 30:
					p.flip_BLACK_G3();
				default:
					p.flip_BLACK_G2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000040810204080ULL;
	opp_discs = (discs_opponent & 0X0002040810204000ULL) | 0X00FDFBF7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0100000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0100000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_H1();

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_C6();
				case 42:
					p.flip_BLACK_D5();
				case 35:
					p.flip_BLACK_E4();
				case 28:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_G2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XFC00000000000000ULL;
	r = (discs_opponent + 0X0200000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0100000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B1();
				case 0X4000000000000000ULL:
					p.flip_BLACK_C1();
				case 0X2000000000000000ULL:
					p.flip_BLACK_D1();
				case 0X1000000000000000ULL:
					p.flip_BLACK_E1();
				case 0X0800000000000000ULL:
					p.flip_BLACK_F1();
				default:
					p.flip_BLACK_G1();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000010101010101ULL;
	opp_discs = (discs_opponent & 0X0001010101010100ULL) | 0X00FEFEFEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0100000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0100000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H1();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_H7();
				case 55:
					p.flip_BLACK_H6();
				case 47:
					p.flip_BLACK_H5();
				case 39:
					p.flip_BLACK_H4();
				case 31:
					p.flip_BLACK_H3();
				default:
					p.flip_BLACK_H2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000002010080402ULL;
	opp_discs = (discs_opponent & 0X0000402010080400ULL) | 0X007FBFDFEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0080000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0080000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_A2();

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_D5();
				case 35:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_B3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000008080808080ULL;
	opp_discs = (discs_opponent & 0X0000808080808000ULL) | 0X007F7F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0080000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0080000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A2();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_A7();
				case 48:
					p.flip_BLACK_A6();
				case 40:
					p.flip_BLACK_A5();
				case 32:
					p.flip_BLACK_A4();
				default:
					p.flip_BLACK_A3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X003F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0080000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0080000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_BLACK_G2();
				case 14:
					p.flip_BLACK_F2();
				case 13:
					p.flip_BLACK_E2();
				case 12:
					p.flip_BLACK_D2();
				case 11:
					p.flip_BLACK_C2();
				default:
					p.flip_BLACK_B2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000001008040201ULL;
	opp_discs = (discs_opponent & 0X0000201008040200ULL) | 0X003FDFEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0040000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0040000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_B2();

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_C3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000004040404040ULL;
	opp_discs = (discs_opponent & 0X0000404040404000ULL) | 0X003FBFBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0040000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0040000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B2();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_B6();
				case 41:
					p.flip_BLACK_B5();
				case 33:
					p.flip_BLACK_B4();
				default:
					p.flip_BLACK_B3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X001F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0040000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0040000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_BLACK_G2();
				case 14:
					p.flip_BLACK_F2();
				case 13:
					p.flip_BLACK_E2();
				case 12:
					p.flip_BLACK_D2();
				default:
					p.flip_BLACK_C2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000002020202020ULL;
	opp_discs = (discs_opponent & 0X0000202020202000ULL) | 0X001FDFDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0020000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0020000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_C2();

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_C6();
				case 42:
					p.flip_BLACK_C5();
				case 34:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_C3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000804020100ULL;
	opp_discs = (discs_opponent & 0X0000100804020000ULL) | 0X001FEFF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0020000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C2();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_D3();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C2();
		}

		p.flip_BLACK_B3();
	}

	/* direction _E */
	my_discs = discs_player & 0X000F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0020000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_BLACK_G2();
				case 14:
					p.flip_BLACK_F2();
				case 13:
					p.flip_BLACK_E2();
				default:
					p.flip_BLACK_D2();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X0080000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C2();
		}

		p.flip_BLACK_B2();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_D2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000001010101010ULL;
	opp_discs = (discs_opponent & 0X0000101010101000ULL) | 0X000FEFEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0010000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_D2();

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_D5();
				case 35:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_D3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000402010000ULL;
	opp_discs = (discs_opponent & 0X0000080402000000ULL) | 0X000FF7FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D2();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_E3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000004080000000ULL;
	opp_discs = (discs_opponent & 0X0000204000000000ULL) | 0X000FDF8000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D2();
		}

		switch(_cntlzll(my_discs)) {
				case 32:
					p.flip_BLACK_B4();
				default:
					p.flip_BLACK_C3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0007000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0010000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_BLACK_G2();
				case 14:
					p.flip_BLACK_F2();
				default:
					p.flip_BLACK_E2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00C0000000000000ULL;
	r = (discs_opponent + 0X0020000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B2();
				default:
					p.flip_BLACK_C2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_E2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000000808080808ULL;
	opp_discs = (discs_opponent & 0X0000080808080800ULL) | 0X0007F7F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0008000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_E2();

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_E3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000201000000ULL;
	opp_discs = (discs_opponent & 0X0000040200000000ULL) | 0X0007FBFC00000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E2();
		}

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_BLACK_G4();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000002040800000ULL;
	opp_discs = (discs_opponent & 0X0000102040000000ULL) | 0X0007EFDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E2();
		}

		switch(_cntlzll(my_discs)) {
				case 40:
					p.flip_BLACK_B5();
				case 33:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_D3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0003000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0008000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_BLACK_G2();
				default:
					p.flip_BLACK_F2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00E0000000000000ULL;
	r = (discs_opponent + 0X0010000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C2();
				default:
					p.flip_BLACK_D2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000000404040404ULL;
	opp_discs = (discs_opponent & 0X0000040404040400ULL) | 0X0003FBFBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0004000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0004000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_F2();

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F2();
		}

		p.flip_BLACK_G3();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000001020408000ULL;
	opp_discs = (discs_opponent & 0X0000081020400000ULL) | 0X0003F7EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0004000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F2();
		}

		switch(_cntlzll(my_discs)) {
				case 48:
					p.flip_BLACK_B6();
				case 41:
					p.flip_BLACK_C5();
				case 34:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_E3();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0001000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F2();
		}

		p.flip_BLACK_G2();
	}

	/* direction _W */
	my_discs = discs_player & 0X00F0000000000000ULL;
	r = (discs_opponent + 0X0008000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_D2();
				default:
					p.flip_BLACK_E2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000000810204080ULL;
	opp_discs = (discs_opponent & 0X0000040810204000ULL) | 0X0001FBF7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0002000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0002000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_G2();

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_C6();
				case 42:
					p.flip_BLACK_D5();
				case 35:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00F8000000000000ULL;
	r = (discs_opponent + 0X0004000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0002000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_E2();
				default:
					p.flip_BLACK_F2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000202020202ULL;
	opp_discs = (discs_opponent & 0X0000020202020200ULL) | 0X0001FDFDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0002000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0002000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G2();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_G4();
				default:
					p.flip_BLACK_G3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000000408102040ULL;
	opp_discs = (discs_opponent & 0X0000020408102000ULL) | 0X0000FDFBF7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0001000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0001000000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_H2();

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_G3();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00FC000000000000ULL;
	r = (discs_opponent + 0X0002000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0001000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_F2();
				default:
					p.flip_BLACK_G2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000101010101ULL;
	opp_discs = (discs_opponent & 0X0000010101010100ULL) | 0X0000FEFEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0001000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0001000000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H2();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_H7();
				case 55:
					p.flip_BLACK_H6();
				case 47:
					p.flip_BLACK_H5();
				case 39:
					p.flip_BLACK_H4();
				default:
					p.flip_BLACK_H3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00003F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000800000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000800000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_A3();

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_BLACK_G3();
				case 22:
					p.flip_BLACK_F3();
				case 21:
					p.flip_BLACK_E3();
				case 20:
					p.flip_BLACK_D3();
				case 19:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_B3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A3();
		}

		p.flip_BLACK_B2();
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000020100804ULL;
	opp_discs = (discs_opponent & 0X0000004020100800ULL) | 0X00007FBFDFEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000800000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A3();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_B4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0080000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A3();
		}

		p.flip_BLACK_A2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000080808080ULL;
	opp_discs = (discs_opponent & 0X0000008080808000ULL) | 0X00007F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000800000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A3();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_A7();
				case 48:
					p.flip_BLACK_A6();
				case 40:
					p.flip_BLACK_A5();
				default:
					p.flip_BLACK_A4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00001F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000400000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000400000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_B3();

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_BLACK_G3();
				case 22:
					p.flip_BLACK_F3();
				case 21:
					p.flip_BLACK_E3();
				case 20:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_C3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B3();
		}

		p.flip_BLACK_C2();
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000010080402ULL;
	opp_discs = (discs_opponent & 0X0000002010080400ULL) | 0X00003FDFEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000400000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B3();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_C4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X4000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B3();
		}

		p.flip_BLACK_B2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000040404040ULL;
	opp_discs = (discs_opponent & 0X0000004040404000ULL) | 0X00003FBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000400000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B3();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_B6();
				case 41:
					p.flip_BLACK_B5();
				default:
					p.flip_BLACK_B4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000008040201ULL;
	opp_discs = (discs_opponent & 0X0000001008040200ULL) | 0X00001FEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000200000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000200000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_C3();

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_D4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000020202020ULL;
	opp_discs = (discs_opponent & 0X0000002020202000ULL) | 0X00001FDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000200000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_C6();
				case 42:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_C4();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X00000F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000200000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_BLACK_G3();
				case 22:
					p.flip_BLACK_F3();
				case 21:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_D3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		p.flip_BLACK_D2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		p.flip_BLACK_C2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		p.flip_BLACK_B2();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		p.flip_BLACK_B4();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C3();
		}

		p.flip_BLACK_B3();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_D3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000004020100ULL;
	opp_discs = (discs_opponent & 0X0000000804020000ULL) | 0X00000FF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000100000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_D3();

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_E4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000010101010ULL;
	opp_discs = (discs_opponent & 0X0000001010101000ULL) | 0X00000FEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_D4();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000070000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000100000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_BLACK_G3();
				case 22:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_E3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		p.flip_BLACK_E2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		p.flip_BLACK_D2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X4000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		p.flip_BLACK_C2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000040800000ULL;
	opp_discs = (discs_opponent & 0X0000002040000000ULL) | 0X00000FDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		switch(_cntlzll(my_discs)) {
				case 40:
					p.flip_BLACK_B5();
				default:
					p.flip_BLACK_C4();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X0000C00000000000ULL;
	r = (discs_opponent + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_D3();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B3();
				default:
					p.flip_BLACK_C3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_E3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000002010000ULL;
	opp_discs = (discs_opponent & 0X0000000402000000ULL) | 0X000007FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000080000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_E3();

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G5();
				default:
					p.flip_BLACK_F4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000008080808ULL;
	opp_discs = (discs_opponent & 0X0000000808080800ULL) | 0X000007F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_E4();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000030000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000080000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_BLACK_G3();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0200000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		p.flip_BLACK_F2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		p.flip_BLACK_E2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		p.flip_BLACK_D2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000020408000ULL;
	opp_discs = (discs_opponent & 0X0000001020400000ULL) | 0X000007EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		switch(_cntlzll(my_discs)) {
				case 48:
					p.flip_BLACK_B6();
				case 41:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_D4();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X0000E00000000000ULL;
	r = (discs_opponent + 0X0000100000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_E3();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_D3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {

		legal = true;
		move.square = 0X0000040000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_F3();

		p.flip_BLACK_G4();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000004040404ULL;
	opp_discs = (discs_opponent & 0X0000000404040400ULL) | 0X000003FBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000040000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_F4();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		p.flip_BLACK_G3();
	}

	/* direction NE */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		p.flip_BLACK_G2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		p.flip_BLACK_F2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		p.flip_BLACK_E2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000010204080ULL;
	opp_discs = (discs_opponent & 0X0000000810204000ULL) | 0X000003F7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000040000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_C6();
				case 42:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_E4();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X0000F00000000000ULL;
	r = (discs_opponent + 0X0000080000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F3();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_E3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000F80000000000ULL;
	r = (discs_opponent + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000020000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_G3();

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000008102040ULL;
	opp_discs = (discs_opponent & 0X0000000408102000ULL) | 0X000001FBF7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000020000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G3();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_F4();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G3();
		}

		p.flip_BLACK_F2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000002020202ULL;
	opp_discs = (discs_opponent & 0X0000000202020200ULL) | 0X000001FDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000020000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G3();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_G5();
				default:
					p.flip_BLACK_G4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0200000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G3();
		}

		p.flip_BLACK_G2();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000FC0000000000ULL;
	r = (discs_opponent + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000010000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_H3();

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_G3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000004081020ULL;
	opp_discs = (discs_opponent & 0X0000000204081000ULL) | 0X000000FDFBF7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000010000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H3();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_G4();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H3();
		}

		p.flip_BLACK_G2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000001010101ULL;
	opp_discs = (discs_opponent & 0X0000000101010100ULL) | 0X000000FEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000010000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H3();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_H7();
				case 55:
					p.flip_BLACK_H6();
				case 47:
					p.flip_BLACK_H5();
				default:
					p.flip_BLACK_H4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0001000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H3();
		}

		p.flip_BLACK_H2();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X0000003F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000008000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000008000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_A4();

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_BLACK_G4();
				case 30:
					p.flip_BLACK_F4();
				case 29:
					p.flip_BLACK_E4();
				case 28:
					p.flip_BLACK_D4();
				case 27:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_B4();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X1020000000000000ULL;
	opp_discs = (discs_opponent & 0X0020400000000000ULL) | 0X0FDF800000000000ULL;
	r = (opp_discs + 0X0000400000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A4();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_BLACK_C2();
				default:
					p.flip_BLACK_B3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000201008ULL;
	opp_discs = (discs_opponent & 0X0000000040201000ULL) | 0X0000007FBFDFE000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000008000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A4();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_B5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080000000000000ULL;
	opp_discs = (discs_opponent & 0X0080800000000000ULL) | 0X7F7F000000000000ULL;
	r = (opp_discs + 0X0000800000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A4();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_A2();
				default:
					p.flip_BLACK_A3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000808080ULL;
	opp_discs = (discs_opponent & 0X0000000080808000ULL) | 0X0000007F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000008000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A4();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_A7();
				case 48:
					p.flip_BLACK_A6();
				default:
					p.flip_BLACK_A5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X0000001F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000004000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000004000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_B4();

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_BLACK_G4();
				case 30:
					p.flip_BLACK_F4();
				case 29:
					p.flip_BLACK_E4();
				case 28:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_C4();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0810000000000000ULL;
	opp_discs = (discs_opponent & 0X0010200000000000ULL) | 0X07EFC00000000000ULL;
	r = (opp_discs + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B4();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_BLACK_D2();
				default:
					p.flip_BLACK_C3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000100804ULL;
	opp_discs = (discs_opponent & 0X0000000020100800ULL) | 0X0000003FDFEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000004000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B4();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_C5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040000000000000ULL;
	opp_discs = (discs_opponent & 0X0040400000000000ULL) | 0X3FBF800000000000ULL;
	r = (opp_discs + 0X0000400000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B4();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_B2();
				default:
					p.flip_BLACK_B3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000404040ULL;
	opp_discs = (discs_opponent & 0X0000000040404000ULL) | 0X0000003FBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000004000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B4();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_B7();
				case 49:
					p.flip_BLACK_B6();
				default:
					p.flip_BLACK_B5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000000080402ULL;
	opp_discs = (discs_opponent & 0X0000000010080400ULL) | 0X0000001FEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000002000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000002000000000ULL;
		p = *pattern; //copy
		p.set_BLACK_C4();

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_D5();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000202020ULL;
	opp_discs = (discs_opponent & 0X0000000020202000ULL) | 0X0000001FDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000002000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_C5();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000002000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_BLACK_G4();
				case 30:
					p.flip_BLACK_F4();
				case 29:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_D4();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0408000000000000ULL;
	opp_discs = (discs_opponent & 0X0008100000000000ULL) | 0X03F7E00000000000ULL;
	r = (opp_discs + 0X0000100000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_E2();
				default:
					p.flip_BLACK_D3();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020000000000000ULL;
	opp_discs = (discs_opponent & 0X0020200000000000ULL) | 0X1FDFC00000000000ULL;
	r = (opp_discs + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_C2();
				default:
					p.flip_BLACK_C3();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0080000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		p.flip_BLACK_B3();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		p.flip_BLACK_B5();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C4();
		}

		p.flip_BLACK_B4();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {

		legal = true;
		move.square = 0X0000000400000000ULL;
		p = *pattern; //copy
		p.set_BLACK_F4();

		p.flip_BLACK_G5();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000040404ULL;
	opp_discs = (discs_opponent & 0X0000000004040400ULL) | 0X00000003FBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000400000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_F5();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		p.flip_BLACK_G4();
	}

	/* direction NE */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0001000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		p.flip_BLACK_G3();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404000000000000ULL;
	opp_discs = (discs_opponent & 0X0004040000000000ULL) | 0X03FBF80000000000ULL;
	r = (opp_discs + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_F2();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X2010000000000000ULL;
	opp_discs = (discs_opponent & 0X0010080000000000ULL) | 0X1FEFF00000000000ULL;
	r = (opp_discs + 0X0000080000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_D2();
				default:
					p.flip_BLACK_E3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000102040ULL;
	opp_discs = (discs_opponent & 0X0000000008102000ULL) | 0X00000003F7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000400000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_C7();
				case 50:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_E5();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000F000000000ULL;
	r = (discs_opponent + 0X0000000800000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F4();
		}

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_E4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X000000F800000000ULL;
	r = (discs_opponent + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000200000000ULL;
		p = *pattern; //copy
		p.set_BLACK_G4();

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_F4();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000081020ULL;
	opp_discs = (discs_opponent & 0X0000000004081000ULL) | 0X00000001FBF7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000200000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G4();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_F5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X1008000000000000ULL;
	opp_discs = (discs_opponent & 0X0008040000000000ULL) | 0X0FF7F80000000000ULL;
	r = (opp_discs + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G4();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_BLACK_E2();
				default:
					p.flip_BLACK_F3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000020202ULL;
	opp_discs = (discs_opponent & 0X0000000002020200ULL) | 0X00000001FDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000200000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G4();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_G6();
				default:
					p.flip_BLACK_G5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202000000000000ULL;
	opp_discs = (discs_opponent & 0X0002020000000000ULL) | 0X01FDFC0000000000ULL;
	r = (opp_discs + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G4();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_G2();
				default:
					p.flip_BLACK_G3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X000000FC00000000ULL;
	r = (discs_opponent + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000100000000ULL;
		p = *pattern; //copy
		p.set_BLACK_H4();

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_E4();
				case 0X0000000800000000ULL:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_G4();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000040810ULL;
	opp_discs = (discs_opponent & 0X0000000002040800ULL) | 0X00000000FDFBF000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000100000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H4();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_G5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0804000000000000ULL;
	opp_discs = (discs_opponent & 0X0004020000000000ULL) | 0X07FBFC0000000000ULL;
	r = (opp_discs + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H4();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_BLACK_F2();
				default:
					p.flip_BLACK_G3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000010101ULL;
	opp_discs = (discs_opponent & 0X0000000001010100ULL) | 0X00000000FEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000100000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H4();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_H7();
				case 55:
					p.flip_BLACK_H6();
				default:
					p.flip_BLACK_H5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101000000000000ULL;
	opp_discs = (discs_opponent & 0X0001010000000000ULL) | 0X00FEFE0000000000ULL;
	r = (opp_discs + 0X0000010000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H4();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_H2();
				default:
					p.flip_BLACK_H3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X000000003F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000080000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000080000000ULL;
		p = *pattern; //copy
		p.set_BLACK_A5();

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_D5();
				case 35:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_B5();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0810200000000000ULL;
	opp_discs = (discs_opponent & 0X0010204000000000ULL) | 0X07EFDF8000000000ULL;
	r = (opp_discs + 0X0000004000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A5();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_B4();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000002010ULL;
	opp_discs = (discs_opponent & 0X0000000000402000ULL) | 0X000000007FBFC000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000080000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A5();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_BLACK_C7();
				default:
					p.flip_BLACK_B6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080800000000000ULL;
	opp_discs = (discs_opponent & 0X0080808000000000ULL) | 0X7F7F7F0000000000ULL;
	r = (opp_discs + 0X0000008000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A5();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_A2();
				case 0X0080000000000000ULL:
					p.flip_BLACK_A3();
				default:
					p.flip_BLACK_A4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000008080ULL;
	opp_discs = (discs_opponent & 0X0000000000808000ULL) | 0X000000007F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000080000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_BLACK_A5();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_BLACK_A7();
				default:
					p.flip_BLACK_A6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X000000001F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000040000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000040000000ULL;
		p = *pattern; //copy
		p.set_BLACK_B5();

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_E5();
				case 36:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_C5();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0408100000000000ULL;
	opp_discs = (discs_opponent & 0X0008102000000000ULL) | 0X03F7EFC000000000ULL;
	r = (opp_discs + 0X0000002000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B5();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_C4();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000001008ULL;
	opp_discs = (discs_opponent & 0X0000000000201000ULL) | 0X000000003FDFE000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000040000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B5();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_BLACK_D7();
				default:
					p.flip_BLACK_C6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040400000000000ULL;
	opp_discs = (discs_opponent & 0X0040404000000000ULL) | 0X3FBFBF8000000000ULL;
	r = (opp_discs + 0X0000004000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B5();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_B3();
				default:
					p.flip_BLACK_B4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000004040ULL;
	opp_discs = (discs_opponent & 0X0000000000404000ULL) | 0X000000003FBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000040000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_BLACK_B5();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_BLACK_B7();
				default:
					p.flip_BLACK_B6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000000000804ULL;
	opp_discs = (discs_opponent & 0X0000000000100800ULL) | 0X000000001FEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000020000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000020000000ULL;
		p = *pattern; //copy
		p.set_BLACK_C5();

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_E7();
				default:
					p.flip_BLACK_D6();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000002020ULL;
	opp_discs = (discs_opponent & 0X0000000000202000ULL) | 0X000000001FDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000020000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_C7();
				default:
					p.flip_BLACK_C6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000020000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_BLACK_G5();
				case 38:
					p.flip_BLACK_F5();
				case 37:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_D5();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0204080000000000ULL;
	opp_discs = (discs_opponent & 0X0004081000000000ULL) | 0X01FBF7E000000000ULL;
	r = (opp_discs + 0X0000001000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_D4();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020200000000000ULL;
	opp_discs = (discs_opponent & 0X0020202000000000ULL) | 0X1FDFDFC000000000ULL;
	r = (opp_discs + 0X0000002000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_C3();
				default:
					p.flip_BLACK_C4();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		p.flip_BLACK_B4();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000000008000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		p.flip_BLACK_B6();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_BLACK_C5();
		}

		p.flip_BLACK_B5();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000000000100ULL) != 0)) {

		legal = true;
		move.square = 0X0000000004000000ULL;
		p = *pattern; //copy
		p.set_BLACK_F5();

		p.flip_BLACK_G6();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000404ULL;
	opp_discs = (discs_opponent & 0X0000000000040400ULL) | 0X0000000003FBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000004000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_BLACK_F7();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		p.flip_BLACK_G5();
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		p.flip_BLACK_G4();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404040000000000ULL;
	opp_discs = (discs_opponent & 0X0004040400000000ULL) | 0X03FBFBF800000000ULL;
	r = (opp_discs + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_F4();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X4020100000000000ULL;
	opp_discs = (discs_opponent & 0X0020100800000000ULL) | 0X3FDFEFF000000000ULL;
	r = (opp_discs + 0X0000000800000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_D3();
				default:
					p.flip_BLACK_E4();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000001020ULL;
	opp_discs = (discs_opponent & 0X0000000000081000ULL) | 0X0000000003F7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000004000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_BLACK_D7();
				default:
					p.flip_BLACK_E6();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000F0000000ULL;
	r = (discs_opponent + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_BLACK_F5();
		}

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_BLACK_B5();
				case 0X0000000040000000ULL:
					p.flip_BLACK_C5();
				case 0X0000000020000000ULL:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_E5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X00000000F8000000ULL;
	r = (discs_opponent + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000002000000ULL;
		p = *pattern; //copy
		p.set_BLACK_G5();

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_BLACK_B5();
				case 0X0000000040000000ULL:
					p.flip_BLACK_C5();
				case 0X0000000020000000ULL:
					p.flip_BLACK_D5();
				case 0X0000000010000000ULL:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_F5();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000000810ULL;
	opp_discs = (discs_opponent & 0X0000000000040800ULL) | 0X0000000001FBF000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000002000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G5();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_BLACK_E7();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X2010080000000000ULL;
	opp_discs = (discs_opponent & 0X0010080400000000ULL) | 0X1FEFF7F800000000ULL;
	r = (opp_discs + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G5();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_E3();
				default:
					p.flip_BLACK_F4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000202ULL;
	opp_discs = (discs_opponent & 0X0000000000020200ULL) | 0X0000000001FDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000002000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G5();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_BLACK_G7();
				default:
					p.flip_BLACK_G6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020000000000ULL;
	opp_discs = (discs_opponent & 0X0002020200000000ULL) | 0X01FDFDFC00000000ULL;
	r = (opp_discs + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_BLACK_G5();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_G3();
				default:
					p.flip_BLACK_G4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X00000000FC000000ULL;
	r = (discs_opponent + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000001000000ULL;
		p = *pattern; //copy
		p.set_BLACK_H5();

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_BLACK_B5();
				case 0X0000000040000000ULL:
					p.flip_BLACK_C5();
				case 0X0000000020000000ULL:
					p.flip_BLACK_D5();
				case 0X0000000010000000ULL:
					p.flip_BLACK_E5();
				case 0X0000000008000000ULL:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_G5();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000000408ULL;
	opp_discs = (discs_opponent & 0X0000000000020400ULL) | 0X0000000000FDF800ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000001000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H5();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_BLACK_F7();
				default:
					p.flip_BLACK_G6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X1008040000000000ULL;
	opp_discs = (discs_opponent & 0X0008040200000000ULL) | 0X0FF7FBFC00000000ULL;
	r = (opp_discs + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H5();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_F3();
				default:
					p.flip_BLACK_G4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000101ULL;
	opp_discs = (discs_opponent & 0X0000000000010100ULL) | 0X0000000000FEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000001000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H5();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_H7();
				default:
					p.flip_BLACK_H6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010000000000ULL;
	opp_discs = (discs_opponent & 0X0001010100000000ULL) | 0X00FEFEFE00000000ULL;
	r = (opp_discs + 0X0000000100000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_BLACK_H5();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_H2();
				case 0X0001000000000000ULL:
					p.flip_BLACK_H3();
				default:
					p.flip_BLACK_H4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00000000003F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000800000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000800000ULL;
		p = *pattern; //copy
		p.set_BLACK_A6();

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_D6();
				case 43:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_B6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0408102000000000ULL;
	opp_discs = (discs_opponent & 0X0008102040000000ULL) | 0X03F7EFDF80000000ULL;
	r = (opp_discs + 0X0000000040000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_BLACK_A6();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_B5();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_BLACK_A6();
		}

		p.flip_BLACK_B7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808000000000ULL;
	opp_discs = (discs_opponent & 0X0080808080000000ULL) | 0X7F7F7F7F00000000ULL;
	r = (opp_discs + 0X0000000080000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_BLACK_A6();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_A2();
				case 0X0080000000000000ULL:
					p.flip_BLACK_A3();
				case 0X0000800000000000ULL:
					p.flip_BLACK_A4();
				default:
					p.flip_BLACK_A5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000008000ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_BLACK_A6();
		}

		p.flip_BLACK_A7();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00000000001F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000400000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000400000ULL;
		p = *pattern; //copy
		p.set_BLACK_B6();

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_E6();
				case 44:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_C6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0204081000000000ULL;
	opp_discs = (discs_opponent & 0X0004081020000000ULL) | 0X01FBF7EFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_BLACK_B6();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_C5();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_BLACK_B6();
		}

		p.flip_BLACK_C7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404000000000ULL;
	opp_discs = (discs_opponent & 0X0040404040000000ULL) | 0X3FBFBFBF80000000ULL;
	r = (opp_discs + 0X0000000040000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_BLACK_B6();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_B4();
				default:
					p.flip_BLACK_B5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000040ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_BLACK_B6();
		}

		p.flip_BLACK_B7();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000200000ULL;
		p = *pattern; //copy
		p.set_BLACK_C6();

		p.flip_BLACK_D7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		p.flip_BLACK_C7();
	}

	/* direction _E */
	my_discs = discs_player & 0X00000000000F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000200000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F6();
				case 45:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_D6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0102040800000000ULL;
	opp_discs = (discs_opponent & 0X0002040810000000ULL) | 0X00FDFBF7E0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_F3();
				case 0X0000040000000000ULL:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_D5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020202000000000ULL;
	opp_discs = (discs_opponent & 0X0020202020000000ULL) | 0X1FDFDFDFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_C5();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		p.flip_BLACK_B5();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		p.flip_BLACK_B7();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_BLACK_C6();
		}

		p.flip_BLACK_B6();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_D6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000100000ULL;
		p = *pattern; //copy
		p.set_BLACK_D6();

		p.flip_BLACK_E7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		p.flip_BLACK_D7();
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000070000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000100000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G6();
				case 46:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_E6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0001020400000000ULL;
	opp_discs = (discs_opponent & 0X0000020408000000ULL) | 0X0000FDFBF0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		switch(r) {
				case 0X0001000000000000ULL:
					p.flip_BLACK_G3();
				case 0X0000020000000000ULL:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_E5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X1010101000000000ULL;
	opp_discs = (discs_opponent & 0X0010101010000000ULL) | 0X0FEFEFEFE0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_D5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804000000000ULL;
	opp_discs = (discs_opponent & 0X0000004020000000ULL) | 0X00007FBFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B4();
				default:
					p.flip_BLACK_C5();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000040ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		p.flip_BLACK_C7();
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000C00000ULL;
	r = (discs_opponent + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_BLACK_D6();
		}

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_BLACK_B6();
				default:
					p.flip_BLACK_C6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_E6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000002ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000080000ULL;
		p = *pattern; //copy
		p.set_BLACK_E6();

		p.flip_BLACK_F7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		p.flip_BLACK_E7();
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000030000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000080000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_BLACK_G6();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010200000000ULL;
	opp_discs = (discs_opponent & 0X0000000204000000ULL) | 0X000000FDF8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		switch(r) {
				case 0X0000010000000000ULL:
					p.flip_BLACK_G4();
				default:
					p.flip_BLACK_F5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0808080800000000ULL;
	opp_discs = (discs_opponent & 0X0008080808000000ULL) | 0X07F7F7F7F0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_E5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0080402000000000ULL;
	opp_discs = (discs_opponent & 0X0000402010000000ULL) | 0X007FBFDFE0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C4();
				default:
					p.flip_BLACK_D5();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		p.flip_BLACK_D7();
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000E00000ULL;
	r = (discs_opponent + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_BLACK_E6();
		}

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_BLACK_B6();
				case 0X0000000000400000ULL:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_D6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000040000ULL;
		p = *pattern; //copy
		p.set_BLACK_F6();

		p.flip_BLACK_G7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		p.flip_BLACK_F7();
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		p.flip_BLACK_G6();
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		p.flip_BLACK_G5();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404040400000000ULL;
	opp_discs = (discs_opponent & 0X0004040404000000ULL) | 0X03FBFBFBF8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_F3();
				case 0X0000040000000000ULL:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_F5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X8040201000000000ULL;
	opp_discs = (discs_opponent & 0X0040201008000000ULL) | 0X7FBFDFEFF0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_D4();
				default:
					p.flip_BLACK_E5();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		p.flip_BLACK_E7();
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000F00000ULL;
	r = (discs_opponent + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_BLACK_F6();
		}

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_BLACK_B6();
				case 0X0000000000400000ULL:
					p.flip_BLACK_C6();
				case 0X0000000000200000ULL:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_E6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000000000F80000ULL;
	r = (discs_opponent + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000020000ULL;
		p = *pattern; //copy
		p.set_BLACK_G6();

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_BLACK_B6();
				case 0X0000000000400000ULL:
					p.flip_BLACK_C6();
				case 0X0000000000200000ULL:
					p.flip_BLACK_D6();
				case 0X0000000000100000ULL:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_BLACK_G6();
		}

		p.flip_BLACK_F7();
	}

	/* direction NW */
	my_discs = discs_player & 0X4020100800000000ULL;
	opp_discs = (discs_opponent & 0X0020100804000000ULL) | 0X3FDFEFF7F8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_BLACK_G6();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_E4();
				default:
					p.flip_BLACK_F5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000002ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_BLACK_G6();
		}

		p.flip_BLACK_G7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020200000000ULL;
	opp_discs = (discs_opponent & 0X0002020202000000ULL) | 0X01FDFDFDFC000000ULL;
	r = (opp_discs + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_BLACK_G6();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_G3();
				case 0X0000020000000000ULL:
					p.flip_BLACK_G4();
				default:
					p.flip_BLACK_G5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000000000FC0000ULL;
	r = (discs_opponent + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000010000ULL;
		p = *pattern; //copy
		p.set_BLACK_H6();

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_BLACK_B6();
				case 0X0000000000400000ULL:
					p.flip_BLACK_C6();
				case 0X0000000000200000ULL:
					p.flip_BLACK_D6();
				case 0X0000000000100000ULL:
					p.flip_BLACK_E6();
				case 0X0000000000080000ULL:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_G6();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_BLACK_H6();
		}

		p.flip_BLACK_G7();
	}

	/* direction NW */
	my_discs = discs_player & 0X2010080400000000ULL;
	opp_discs = (discs_opponent & 0X0010080402000000ULL) | 0X1FEFF7FBFC000000ULL;
	r = (opp_discs + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_BLACK_H6();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_F4();
				default:
					p.flip_BLACK_G5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000100ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_BLACK_H6();
		}

		p.flip_BLACK_H7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010100000000ULL;
	opp_discs = (discs_opponent & 0X0001010101000000ULL) | 0X00FEFEFEFE000000ULL;
	r = (opp_discs + 0X0000000001000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_BLACK_H6();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_H2();
				case 0X0001000000000000ULL:
					p.flip_BLACK_H3();
				case 0X0000010000000000ULL:
					p.flip_BLACK_H4();
				default:
					p.flip_BLACK_H5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0204081020000000ULL;
	opp_discs = (discs_opponent & 0X0004081020400000ULL) | 0X01FBF7EFDF800000ULL;
	r = (opp_discs + 0X0000000000400000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000008000ULL;
		p = *pattern; //copy
		p.set_BLACK_A7();

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_B6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808080000000ULL;
	opp_discs = (discs_opponent & 0X0080808080800000ULL) | 0X7F7F7F7F7F000000ULL;
	r = (opp_discs + 0X0000000000800000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000008000ULL;
			p = *pattern; //copy
			p.set_BLACK_A7();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_A2();
				case 0X0080000000000000ULL:
					p.flip_BLACK_A3();
				case 0X0000800000000000ULL:
					p.flip_BLACK_A4();
				case 0X0000008000000000ULL:
					p.flip_BLACK_A5();
				default:
					p.flip_BLACK_A6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000003F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000008000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000008000ULL;
			p = *pattern; //copy
			p.set_BLACK_A7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_D7();
				case 51:
					p.flip_BLACK_C7();
				default:
					p.flip_BLACK_B7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0102040810000000ULL;
	opp_discs = (discs_opponent & 0X0002040810200000ULL) | 0X00FDFBF7EFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000004000ULL;
		p = *pattern; //copy
		p.set_BLACK_B7();

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_F3();
				case 0X0000040000000000ULL:
					p.flip_BLACK_E4();
				case 0X0000000800000000ULL:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_C6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404040000000ULL;
	opp_discs = (discs_opponent & 0X0040404040400000ULL) | 0X3FBFBFBFBF800000ULL;
	r = (opp_discs + 0X0000000000400000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000004000ULL;
			p = *pattern; //copy
			p.set_BLACK_B7();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_B5();
				default:
					p.flip_BLACK_B6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000001F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000004000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000004000ULL;
			p = *pattern; //copy
			p.set_BLACK_B7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_E7();
				case 52:
					p.flip_BLACK_D7();
				default:
					p.flip_BLACK_C7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X2020202020000000ULL;
	opp_discs = (discs_opponent & 0X0020202020200000ULL) | 0X1FDFDFDFDFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000002000ULL;
		p = *pattern; //copy
		p.set_BLACK_C7();

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_C6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0001020408000000ULL;
	opp_discs = (discs_opponent & 0X0000020408100000ULL) | 0X0000FDFBF7E00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_BLACK_C7();
		}

		switch(r) {
				case 0X0001000000000000ULL:
					p.flip_BLACK_G3();
				case 0X0000020000000000ULL:
					p.flip_BLACK_F4();
				case 0X0000000400000000ULL:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_D6();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_BLACK_C7();
		}

		p.flip_BLACK_B6();
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000002000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_BLACK_C7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F7();
				case 53:
					p.flip_BLACK_E7();
				default:
					p.flip_BLACK_D7();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000008000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_BLACK_C7();
		}

		p.flip_BLACK_B7();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_D7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X1010101010000000ULL;
	opp_discs = (discs_opponent & 0X0010101010100000ULL) | 0X0FEFEFEFEFE00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000001000ULL;
		p = *pattern; //copy
		p.set_BLACK_D7();

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_D6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010204000000ULL;
	opp_discs = (discs_opponent & 0X0000000204080000ULL) | 0X000000FDFBF00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_BLACK_D7();
		}

		switch(r) {
				case 0X0000010000000000ULL:
					p.flip_BLACK_G4();
				case 0X0000000200000000ULL:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_E6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000008040000000ULL;
	opp_discs = (discs_opponent & 0X0000000040200000ULL) | 0X0000007FBFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_BLACK_D7();
		}

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_BLACK_B5();
				default:
					p.flip_BLACK_C6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000700ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000001000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_BLACK_D7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G7();
				case 54:
					p.flip_BLACK_F7();
				default:
					p.flip_BLACK_E7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000C000ULL;
	r = (discs_opponent + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_BLACK_D7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_BLACK_B7();
				default:
					p.flip_BLACK_C7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_E7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0808080808000000ULL;
	opp_discs = (discs_opponent & 0X0008080808080000ULL) | 0X07F7F7F7F7F00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000800ULL;
		p = *pattern; //copy
		p.set_BLACK_E7();

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_E4();
				case 0X0000000800000000ULL:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_E6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000102000000ULL;
	opp_discs = (discs_opponent & 0X0000000002040000ULL) | 0X00000000FDF80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_BLACK_E7();
		}

		switch(r) {
				case 0X0000000100000000ULL:
					p.flip_BLACK_G5();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804020000000ULL;
	opp_discs = (discs_opponent & 0X0000004020100000ULL) | 0X00007FBFDFE00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_BLACK_E7();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_C5();
				default:
					p.flip_BLACK_D6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000300ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000800ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_BLACK_E7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_BLACK_G7();
				default:
					p.flip_BLACK_F7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000E000ULL;
	r = (discs_opponent + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_BLACK_E7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_BLACK_B7();
				case 0X0000000000004000ULL:
					p.flip_BLACK_C7();
				default:
					p.flip_BLACK_D7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0404040404000000ULL;
	opp_discs = (discs_opponent & 0X0004040404040000ULL) | 0X03FBFBFBFBF80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000400ULL;
		p = *pattern; //copy
		p.set_BLACK_F7();

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_F3();
				case 0X0000040000000000ULL:
					p.flip_BLACK_F4();
				case 0X0000000400000000ULL:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_BLACK_F7();
		}

		p.flip_BLACK_G6();
	}

	/* direction NW */
	my_discs = discs_player & 0X0080402010000000ULL;
	opp_discs = (discs_opponent & 0X0000402010080000ULL) | 0X007FBFDFEFF00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_BLACK_F7();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_D5();
				default:
					p.flip_BLACK_E6();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000100ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_BLACK_F7();
		}

		p.flip_BLACK_G7();
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000F000ULL;
	r = (discs_opponent + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_BLACK_F7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_BLACK_B7();
				case 0X0000000000004000ULL:
					p.flip_BLACK_C7();
				case 0X0000000000002000ULL:
					p.flip_BLACK_D7();
				default:
					p.flip_BLACK_E7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X8040201008000000ULL;
	opp_discs = (discs_opponent & 0X0040201008040000ULL) | 0X7FBFDFEFF7F80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000200ULL;
		p = *pattern; //copy
		p.set_BLACK_G7();

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_E5();
				default:
					p.flip_BLACK_F6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020202000000ULL;
	opp_discs = (discs_opponent & 0X0002020202020000ULL) | 0X01FDFDFDFDFC0000ULL;
	r = (opp_discs + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000200ULL;
			p = *pattern; //copy
			p.set_BLACK_G7();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_G3();
				case 0X0000020000000000ULL:
					p.flip_BLACK_G4();
				case 0X0000000200000000ULL:
					p.flip_BLACK_G5();
				default:
					p.flip_BLACK_G6();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000F800ULL;
	r = (discs_opponent + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000200ULL;
			p = *pattern; //copy
			p.set_BLACK_G7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_BLACK_B7();
				case 0X0000000000004000ULL:
					p.flip_BLACK_C7();
				case 0X0000000000002000ULL:
					p.flip_BLACK_D7();
				case 0X0000000000001000ULL:
					p.flip_BLACK_E7();
				default:
					p.flip_BLACK_F7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X4020100804000000ULL;
	opp_discs = (discs_opponent & 0X0020100804020000ULL) | 0X3FDFEFF7FBFC0000ULL;
	r = (opp_discs + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000100ULL;
		p = *pattern; //copy
		p.set_BLACK_H7();

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_E4();
				case 0X0000000800000000ULL:
					p.flip_BLACK_F5();
				default:
					p.flip_BLACK_G6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010101000000ULL;
	opp_discs = (discs_opponent & 0X0001010101010000ULL) | 0X00FEFEFEFEFE0000ULL;
	r = (opp_discs + 0X0000000000010000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000100ULL;
			p = *pattern; //copy
			p.set_BLACK_H7();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_H2();
				case 0X0001000000000000ULL:
					p.flip_BLACK_H3();
				case 0X0000010000000000ULL:
					p.flip_BLACK_H4();
				case 0X0000000100000000ULL:
					p.flip_BLACK_H5();
				default:
					p.flip_BLACK_H6();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000FC00ULL;
	r = (discs_opponent + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000100ULL;
			p = *pattern; //copy
			p.set_BLACK_H7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_BLACK_B7();
				case 0X0000000000004000ULL:
					p.flip_BLACK_C7();
				case 0X0000000000002000ULL:
					p.flip_BLACK_D7();
				case 0X0000000000001000ULL:
					p.flip_BLACK_E7();
				case 0X0000000000000800ULL:
					p.flip_BLACK_F7();
				default:
					p.flip_BLACK_G7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_A8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0102040810200000ULL;
	opp_discs = (discs_opponent & 0X0002040810204000ULL) | 0X00FDFBF7EFDF8000ULL;
	r = (opp_discs + 0X0000000000004000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000080ULL;
		p = *pattern; //copy
		p.set_BLACK_A8();

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_F3();
				case 0X0000040000000000ULL:
					p.flip_BLACK_E4();
				case 0X0000000800000000ULL:
					p.flip_BLACK_D5();
				case 0X0000000010000000ULL:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_B7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808080800000ULL;
	opp_discs = (discs_opponent & 0X0080808080808000ULL) | 0X7F7F7F7F7F7F0000ULL;
	r = (opp_discs + 0X0000000000008000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000080ULL;
			p = *pattern; //copy
			p.set_BLACK_A8();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_A2();
				case 0X0080000000000000ULL:
					p.flip_BLACK_A3();
				case 0X0000800000000000ULL:
					p.flip_BLACK_A4();
				case 0X0000008000000000ULL:
					p.flip_BLACK_A5();
				case 0X0000000080000000ULL:
					p.flip_BLACK_A6();
				default:
					p.flip_BLACK_A7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000003FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000080ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000080ULL;
			p = *pattern; //copy
			p.set_BLACK_A8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G8();
				case 62:
					p.flip_BLACK_F8();
				case 61:
					p.flip_BLACK_E8();
				case 60:
					p.flip_BLACK_D8();
				case 59:
					p.flip_BLACK_C8();
				default:
					p.flip_BLACK_B8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_B8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0001020408100000ULL;
	opp_discs = (discs_opponent & 0X0000020408102000ULL) | 0X0000FDFBF7EFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000040ULL;
		p = *pattern; //copy
		p.set_BLACK_B8();

		switch(r) {
				case 0X0001000000000000ULL:
					p.flip_BLACK_G3();
				case 0X0000020000000000ULL:
					p.flip_BLACK_F4();
				case 0X0000000400000000ULL:
					p.flip_BLACK_E5();
				case 0X0000000008000000ULL:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_C7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404040400000ULL;
	opp_discs = (discs_opponent & 0X0040404040404000ULL) | 0X3FBFBFBFBFBF8000ULL;
	r = (opp_discs + 0X0000000000004000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000040ULL;
			p = *pattern; //copy
			p.set_BLACK_B8();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_B5();
				case 0X0000000040000000ULL:
					p.flip_BLACK_B6();
				default:
					p.flip_BLACK_B7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000001FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000040ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000040ULL;
			p = *pattern; //copy
			p.set_BLACK_B8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G8();
				case 62:
					p.flip_BLACK_F8();
				case 61:
					p.flip_BLACK_E8();
				case 60:
					p.flip_BLACK_D8();
				default:
					p.flip_BLACK_C8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_C8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X2020202020200000ULL;
	opp_discs = (discs_opponent & 0X0020202020202000ULL) | 0X1FDFDFDFDFDFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000020ULL;
		p = *pattern; //copy
		p.set_BLACK_C8();

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_BLACK_C2();
				case 0X0020000000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_C5();
				case 0X0000000020000000ULL:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_C7();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010204080000ULL;
	opp_discs = (discs_opponent & 0X0000000204081000ULL) | 0X000000FDFBF7E000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_BLACK_C8();
		}

		switch(r) {
				case 0X0000010000000000ULL:
					p.flip_BLACK_G4();
				case 0X0000000200000000ULL:
					p.flip_BLACK_F5();
				case 0X0000000004000000ULL:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_D7();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_BLACK_C8();
		}

		p.flip_BLACK_B7();
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000000FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000020ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_BLACK_C8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G8();
				case 62:
					p.flip_BLACK_F8();
				case 61:
					p.flip_BLACK_E8();
				default:
					p.flip_BLACK_D8();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000000040ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_BLACK_C8();
		}

		p.flip_BLACK_B8();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_D8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X1010101010100000ULL;
	opp_discs = (discs_opponent & 0X0010101010101000ULL) | 0X0FEFEFEFEFEFE000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000010ULL;
		p = *pattern; //copy
		p.set_BLACK_D8();

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_BLACK_D2();
				case 0X0010000000000000ULL:
					p.flip_BLACK_D3();
				case 0X0000100000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_D5();
				case 0X0000000010000000ULL:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_D7();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000102040000ULL;
	opp_discs = (discs_opponent & 0X0000000002040800ULL) | 0X00000000FDFBF000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_BLACK_D8();
		}

		switch(r) {
				case 0X0000000100000000ULL:
					p.flip_BLACK_G5();
				case 0X0000000002000000ULL:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_E7();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000000080400000ULL;
	opp_discs = (discs_opponent & 0X0000000000402000ULL) | 0X000000007FBFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_BLACK_D8();
		}

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_BLACK_B6();
				default:
					p.flip_BLACK_C7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000007ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000010ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_BLACK_D8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G8();
				case 62:
					p.flip_BLACK_F8();
				default:
					p.flip_BLACK_E8();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000C0ULL;
	r = (discs_opponent + 0X0000000000000020ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_BLACK_D8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_BLACK_B8();
				default:
					p.flip_BLACK_C8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_E8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0808080808080000ULL;
	opp_discs = (discs_opponent & 0X0008080808080800ULL) | 0X07F7F7F7F7F7F000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000008ULL;
		p = *pattern; //copy
		p.set_BLACK_E8();

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_BLACK_E2();
				case 0X0008000000000000ULL:
					p.flip_BLACK_E3();
				case 0X0000080000000000ULL:
					p.flip_BLACK_E4();
				case 0X0000000800000000ULL:
					p.flip_BLACK_E5();
				case 0X0000000008000000ULL:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_E7();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000001020000ULL;
	opp_discs = (discs_opponent & 0X0000000000020400ULL) | 0X0000000000FDF800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_BLACK_E8();
		}

		switch(r) {
				case 0X0000000001000000ULL:
					p.flip_BLACK_G6();
				default:
					p.flip_BLACK_F7();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000008040200000ULL;
	opp_discs = (discs_opponent & 0X0000000040201000ULL) | 0X0000007FBFDFE000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_BLACK_E8();
		}

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_BLACK_B5();
				case 0X0000000040000000ULL:
					p.flip_BLACK_C6();
				default:
					p.flip_BLACK_D7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000003ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000008ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_BLACK_E8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_BLACK_G8();
				default:
					p.flip_BLACK_F8();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000E0ULL;
	r = (discs_opponent + 0X0000000000000010ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_BLACK_E8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_BLACK_B8();
				case 0X0000000000000040ULL:
					p.flip_BLACK_C8();
				default:
					p.flip_BLACK_D8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_F8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0404040404040000ULL;
	opp_discs = (discs_opponent & 0X0004040404040400ULL) | 0X03FBFBFBFBFBF800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000004ULL;
		p = *pattern; //copy
		p.set_BLACK_F8();

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_BLACK_F2();
				case 0X0004000000000000ULL:
					p.flip_BLACK_F3();
				case 0X0000040000000000ULL:
					p.flip_BLACK_F4();
				case 0X0000000400000000ULL:
					p.flip_BLACK_F5();
				case 0X0000000004000000ULL:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_F7();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_BLACK_F8();
		}

		p.flip_BLACK_G7();
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804020100000ULL;
	opp_discs = (discs_opponent & 0X0000004020100800ULL) | 0X00007FBFDFEFF000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_BLACK_F8();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_BLACK_B4();
				case 0X0000004000000000ULL:
					p.flip_BLACK_C5();
				case 0X0000000020000000ULL:
					p.flip_BLACK_D6();
				default:
					p.flip_BLACK_E7();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000000002ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_BLACK_F8();
		}

		p.flip_BLACK_G8();
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000F0ULL;
	r = (discs_opponent + 0X0000000000000008ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_BLACK_F8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_BLACK_B8();
				case 0X0000000000000040ULL:
					p.flip_BLACK_C8();
				case 0X0000000000000020ULL:
					p.flip_BLACK_D8();
				default:
					p.flip_BLACK_E8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_G8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X0080402010080000ULL;
	opp_discs = (discs_opponent & 0X0000402010080400ULL) | 0X007FBFDFEFF7F800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000002ULL;
		p = *pattern; //copy
		p.set_BLACK_G8();

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_BLACK_B3();
				case 0X0000400000000000ULL:
					p.flip_BLACK_C4();
				case 0X0000002000000000ULL:
					p.flip_BLACK_D5();
				case 0X0000000010000000ULL:
					p.flip_BLACK_E6();
				default:
					p.flip_BLACK_F7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020202020000ULL;
	opp_discs = (discs_opponent & 0X0002020202020200ULL) | 0X01FDFDFDFDFDFC00ULL;
	r = (opp_discs + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000002ULL;
			p = *pattern; //copy
			p.set_BLACK_G8();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_BLACK_G2();
				case 0X0002000000000000ULL:
					p.flip_BLACK_G3();
				case 0X0000020000000000ULL:
					p.flip_BLACK_G4();
				case 0X0000000200000000ULL:
					p.flip_BLACK_G5();
				case 0X0000000002000000ULL:
					p.flip_BLACK_G6();
				default:
					p.flip_BLACK_G7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000F8ULL;
	r = (discs_opponent + 0X0000000000000004ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000002ULL;
			p = *pattern; //copy
			p.set_BLACK_G8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_BLACK_B8();
				case 0X0000000000000040ULL:
					p.flip_BLACK_C8();
				case 0X0000000000000020ULL:
					p.flip_BLACK_D8();
				case 0X0000000000000010ULL:
					p.flip_BLACK_E8();
				default:
					p.flip_BLACK_F8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_BLACK_H8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[BLACK];
	const unsigned long long discs_opponent = board.discs[WHITE];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X8040201008040000ULL;
	opp_discs = (discs_opponent & 0X0040201008040200ULL) | 0X7FBFDFEFF7FBFC00ULL;
	r = (opp_discs + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000001ULL;
		p = *pattern; //copy
		p.set_BLACK_H8();

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_BLACK_B2();
				case 0X0040000000000000ULL:
					p.flip_BLACK_C3();
				case 0X0000200000000000ULL:
					p.flip_BLACK_D4();
				case 0X0000001000000000ULL:
					p.flip_BLACK_E5();
				case 0X0000000008000000ULL:
					p.flip_BLACK_F6();
				default:
					p.flip_BLACK_G7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010101010000ULL;
	opp_discs = (discs_opponent & 0X0001010101010100ULL) | 0X00FEFEFEFEFEFE00ULL;
	r = (opp_discs + 0X0000000000000100ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000001ULL;
			p = *pattern; //copy
			p.set_BLACK_H8();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_BLACK_H2();
				case 0X0001000000000000ULL:
					p.flip_BLACK_H3();
				case 0X0000010000000000ULL:
					p.flip_BLACK_H4();
				case 0X0000000100000000ULL:
					p.flip_BLACK_H5();
				case 0X0000000001000000ULL:
					p.flip_BLACK_H6();
				default:
					p.flip_BLACK_H7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000FCULL;
	r = (discs_opponent + 0X0000000000000002ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000001ULL;
			p = *pattern; //copy
			p.set_BLACK_H8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_BLACK_B8();
				case 0X0000000000000040ULL:
					p.flip_BLACK_C8();
				case 0X0000000000000020ULL:
					p.flip_BLACK_D8();
				case 0X0000000000000010ULL:
					p.flip_BLACK_E8();
				case 0X0000000000000008ULL:
					p.flip_BLACK_F8();
				default:
					p.flip_BLACK_G8();
		}
	}

	return legal;

}



bool RXBBPatterns::generate_patterns_WHITE_A1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000201008040201ULL;
	opp_discs = (discs_opponent & 0X0040201008040200ULL) | 0X7FBFDFEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X8000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X8000000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_A1();

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_D4();
				case 27:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_B2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000808080808080ULL;
	opp_discs = (discs_opponent & 0X0080808080808000ULL) | 0X7F7F7F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X8000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X8000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A1();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_A7();
				case 48:
					p.flip_WHITE_A6();
				case 40:
					p.flip_WHITE_A5();
				case 32:
					p.flip_WHITE_A4();
				case 24:
					p.flip_WHITE_A3();
				default:
					p.flip_WHITE_A2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X3F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X8000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X8000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_WHITE_G1();
				case 6:
					p.flip_WHITE_F1();
				case 5:
					p.flip_WHITE_E1();
				case 4:
					p.flip_WHITE_D1();
				case 3:
					p.flip_WHITE_C1();
				default:
					p.flip_WHITE_B1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000100804020100ULL;
	opp_discs = (discs_opponent & 0X0020100804020000ULL) | 0X3FDFEFF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X4000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X4000000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_B1();

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_E4();
				case 28:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_C2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000404040404040ULL;
	opp_discs = (discs_opponent & 0X0040404040404000ULL) | 0X3FBFBFBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X4000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X4000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B1();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_B6();
				case 41:
					p.flip_WHITE_B5();
				case 33:
					p.flip_WHITE_B4();
				case 25:
					p.flip_WHITE_B3();
				default:
					p.flip_WHITE_B2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X1F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X4000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X4000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_WHITE_G1();
				case 6:
					p.flip_WHITE_F1();
				case 5:
					p.flip_WHITE_E1();
				case 4:
					p.flip_WHITE_D1();
				default:
					p.flip_WHITE_C1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000202020202020ULL;
	opp_discs = (discs_opponent & 0X0020202020202000ULL) | 0X1FDFDFDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X2000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X2000000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_C1();

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_C6();
				case 42:
					p.flip_WHITE_C5();
				case 34:
					p.flip_WHITE_C4();
				case 26:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_C2();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000080402010000ULL;
	opp_discs = (discs_opponent & 0X0010080402000000ULL) | 0X1FEFF7FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X2000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C1();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_F4();
				case 29:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_D2();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C1();
		}

		p.flip_WHITE_B2();
	}

	/* direction _E */
	my_discs = discs_player & 0X0F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X2000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_WHITE_G1();
				case 6:
					p.flip_WHITE_F1();
				case 5:
					p.flip_WHITE_E1();
				default:
					p.flip_WHITE_D1();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X4000000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X2000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C1();
		}

		p.flip_WHITE_B1();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_D1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000101010101010ULL;
	opp_discs = (discs_opponent & 0X0010101010101000ULL) | 0X0FEFEFEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X1000000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_D1();

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_D5();
				case 35:
					p.flip_WHITE_D4();
				case 27:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_D2();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000040201000000ULL;
	opp_discs = (discs_opponent & 0X0008040200000000ULL) | 0X0FF7FBFC00000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D1();
		}

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_WHITE_G4();
				case 30:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_E2();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000408000000000ULL;
	opp_discs = (discs_opponent & 0X0020400000000000ULL) | 0X0FDF800000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D1();
		}

		switch(_cntlzll(my_discs)) {
				case 24:
					p.flip_WHITE_B3();
				default:
					p.flip_WHITE_C2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0700000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X1000000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_WHITE_G1();
				case 6:
					p.flip_WHITE_F1();
				default:
					p.flip_WHITE_E1();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XC000000000000000ULL;
	r = (discs_opponent + 0X2000000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X1000000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B1();
				default:
					p.flip_WHITE_C1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_E1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000080808080808ULL;
	opp_discs = (discs_opponent & 0X0008080808080800ULL) | 0X07F7F7F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0800000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_E1();

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_E4();
				case 28:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_E2();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000020100000000ULL;
	opp_discs = (discs_opponent & 0X0004020000000000ULL) | 0X07FBFC0000000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E1();
		}

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_WHITE_G3();
				default:
					p.flip_WHITE_F2();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000204080000000ULL;
	opp_discs = (discs_opponent & 0X0010204000000000ULL) | 0X07EFDF8000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E1();
		}

		switch(_cntlzll(my_discs)) {
				case 32:
					p.flip_WHITE_B4();
				case 25:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_D2();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0300000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0800000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E1();
		}

		switch(_cntlzll(my_discs)) {
				case 7:
					p.flip_WHITE_G1();
				default:
					p.flip_WHITE_F1();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XE000000000000000ULL;
	r = (discs_opponent + 0X1000000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0800000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B1();
				case 0X4000000000000000ULL:
					p.flip_WHITE_C1();
				default:
					p.flip_WHITE_D1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000040404040404ULL;
	opp_discs = (discs_opponent & 0X0004040404040400ULL) | 0X03FBFBFBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0400000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0400000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_F1();

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_F4();
				case 29:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_F2();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F1();
		}

		p.flip_WHITE_G2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000102040800000ULL;
	opp_discs = (discs_opponent & 0X0008102040000000ULL) | 0X03F7EFDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0400000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F1();
		}

		switch(_cntlzll(my_discs)) {
				case 40:
					p.flip_WHITE_B5();
				case 33:
					p.flip_WHITE_C4();
				case 26:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_E2();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0200000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F1();
		}

		p.flip_WHITE_G1();
	}

	/* direction _W */
	my_discs = discs_player & 0XF000000000000000ULL;
	r = (discs_opponent + 0X0800000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0400000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B1();
				case 0X4000000000000000ULL:
					p.flip_WHITE_C1();
				case 0X2000000000000000ULL:
					p.flip_WHITE_D1();
				default:
					p.flip_WHITE_E1();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000081020408000ULL;
	opp_discs = (discs_opponent & 0X0004081020400000ULL) | 0X01FBF7EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0200000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0200000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_G1();

		switch(_cntlzll(my_discs)) {
				case 48:
					p.flip_WHITE_B6();
				case 41:
					p.flip_WHITE_C5();
				case 34:
					p.flip_WHITE_D4();
				case 27:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_F2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XF800000000000000ULL;
	r = (discs_opponent + 0X0400000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0200000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B1();
				case 0X4000000000000000ULL:
					p.flip_WHITE_C1();
				case 0X2000000000000000ULL:
					p.flip_WHITE_D1();
				case 0X1000000000000000ULL:
					p.flip_WHITE_E1();
				default:
					p.flip_WHITE_F1();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000020202020202ULL;
	opp_discs = (discs_opponent & 0X0002020202020200ULL) | 0X01FDFDFDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0200000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0200000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G1();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_G4();
				case 30:
					p.flip_WHITE_G3();
				default:
					p.flip_WHITE_G2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H1(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000040810204080ULL;
	opp_discs = (discs_opponent & 0X0002040810204000ULL) | 0X00FDFBF7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0100000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0100000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_H1();

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_C6();
				case 42:
					p.flip_WHITE_D5();
				case 35:
					p.flip_WHITE_E4();
				case 28:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_G2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0XFC00000000000000ULL;
	r = (discs_opponent + 0X0200000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0100000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H1();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B1();
				case 0X4000000000000000ULL:
					p.flip_WHITE_C1();
				case 0X2000000000000000ULL:
					p.flip_WHITE_D1();
				case 0X1000000000000000ULL:
					p.flip_WHITE_E1();
				case 0X0800000000000000ULL:
					p.flip_WHITE_F1();
				default:
					p.flip_WHITE_G1();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000010101010101ULL;
	opp_discs = (discs_opponent & 0X0001010101010100ULL) | 0X00FEFEFEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0100000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0100000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H1();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_H7();
				case 55:
					p.flip_WHITE_H6();
				case 47:
					p.flip_WHITE_H5();
				case 39:
					p.flip_WHITE_H4();
				case 31:
					p.flip_WHITE_H3();
				default:
					p.flip_WHITE_H2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000002010080402ULL;
	opp_discs = (discs_opponent & 0X0000402010080400ULL) | 0X007FBFDFEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0080000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0080000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_A2();

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_D5();
				case 35:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_B3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000008080808080ULL;
	opp_discs = (discs_opponent & 0X0000808080808000ULL) | 0X007F7F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0080000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0080000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A2();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_A7();
				case 48:
					p.flip_WHITE_A6();
				case 40:
					p.flip_WHITE_A5();
				case 32:
					p.flip_WHITE_A4();
				default:
					p.flip_WHITE_A3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X003F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0080000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0080000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_WHITE_G2();
				case 14:
					p.flip_WHITE_F2();
				case 13:
					p.flip_WHITE_E2();
				case 12:
					p.flip_WHITE_D2();
				case 11:
					p.flip_WHITE_C2();
				default:
					p.flip_WHITE_B2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000001008040201ULL;
	opp_discs = (discs_opponent & 0X0000201008040200ULL) | 0X003FDFEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0040000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0040000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_B2();

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_C3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000004040404040ULL;
	opp_discs = (discs_opponent & 0X0000404040404000ULL) | 0X003FBFBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0040000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0040000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B2();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_B6();
				case 41:
					p.flip_WHITE_B5();
				case 33:
					p.flip_WHITE_B4();
				default:
					p.flip_WHITE_B3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X001F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0040000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0040000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_WHITE_G2();
				case 14:
					p.flip_WHITE_F2();
				case 13:
					p.flip_WHITE_E2();
				case 12:
					p.flip_WHITE_D2();
				default:
					p.flip_WHITE_C2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000002020202020ULL;
	opp_discs = (discs_opponent & 0X0000202020202000ULL) | 0X001FDFDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0020000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0020000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_C2();

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_C6();
				case 42:
					p.flip_WHITE_C5();
				case 34:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_C3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000804020100ULL;
	opp_discs = (discs_opponent & 0X0000100804020000ULL) | 0X001FEFF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0020000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C2();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_D3();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C2();
		}

		p.flip_WHITE_B3();
	}

	/* direction _E */
	my_discs = discs_player & 0X000F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0020000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_WHITE_G2();
				case 14:
					p.flip_WHITE_F2();
				case 13:
					p.flip_WHITE_E2();
				default:
					p.flip_WHITE_D2();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X0080000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0020000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C2();
		}

		p.flip_WHITE_B2();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_D2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000001010101010ULL;
	opp_discs = (discs_opponent & 0X0000101010101000ULL) | 0X000FEFEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0010000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_D2();

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_D5();
				case 35:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_D3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000402010000ULL;
	opp_discs = (discs_opponent & 0X0000080402000000ULL) | 0X000FF7FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D2();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_E3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000004080000000ULL;
	opp_discs = (discs_opponent & 0X0000204000000000ULL) | 0X000FDF8000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D2();
		}

		switch(_cntlzll(my_discs)) {
				case 32:
					p.flip_WHITE_B4();
				default:
					p.flip_WHITE_C3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0007000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0010000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_WHITE_G2();
				case 14:
					p.flip_WHITE_F2();
				default:
					p.flip_WHITE_E2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00C0000000000000ULL;
	r = (discs_opponent + 0X0020000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0010000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B2();
				default:
					p.flip_WHITE_C2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_E2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000000808080808ULL;
	opp_discs = (discs_opponent & 0X0000080808080800ULL) | 0X0007F7F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0008000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_E2();

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_E3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000201000000ULL;
	opp_discs = (discs_opponent & 0X0000040200000000ULL) | 0X0007FBFC00000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E2();
		}

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_WHITE_G4();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000002040800000ULL;
	opp_discs = (discs_opponent & 0X0000102040000000ULL) | 0X0007EFDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E2();
		}

		switch(_cntlzll(my_discs)) {
				case 40:
					p.flip_WHITE_B5();
				case 33:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_D3();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0003000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0008000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E2();
		}

		switch(_cntlzll(my_discs)) {
				case 15:
					p.flip_WHITE_G2();
				default:
					p.flip_WHITE_F2();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00E0000000000000ULL;
	r = (discs_opponent + 0X0010000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0008000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C2();
				default:
					p.flip_WHITE_D2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction S */
	my_discs = discs_player & 0X0000000404040404ULL;
	opp_discs = (discs_opponent & 0X0000040404040400ULL) | 0X0003FBFBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0004000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0004000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_F2();

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F2();
		}

		p.flip_WHITE_G3();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000001020408000ULL;
	opp_discs = (discs_opponent & 0X0000081020400000ULL) | 0X0003F7EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0004000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F2();
		}

		switch(_cntlzll(my_discs)) {
				case 48:
					p.flip_WHITE_B6();
				case 41:
					p.flip_WHITE_C5();
				case 34:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_E3();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0001000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F2();
		}

		p.flip_WHITE_G2();
	}

	/* direction _W */
	my_discs = discs_player & 0X00F0000000000000ULL;
	r = (discs_opponent + 0X0008000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0004000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_D2();
				default:
					p.flip_WHITE_E2();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000000810204080ULL;
	opp_discs = (discs_opponent & 0X0000040810204000ULL) | 0X0001FBF7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0002000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0002000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_G2();

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_C6();
				case 42:
					p.flip_WHITE_D5();
				case 35:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00F8000000000000ULL;
	r = (discs_opponent + 0X0004000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0002000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_E2();
				default:
					p.flip_WHITE_F2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000202020202ULL;
	opp_discs = (discs_opponent & 0X0000020202020200ULL) | 0X0001FDFDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0002000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0002000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G2();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_G4();
				default:
					p.flip_WHITE_G3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H2(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SW */
	my_discs = discs_player & 0X0000000408102040ULL;
	opp_discs = (discs_opponent & 0X0000020408102000ULL) | 0X0000FDFBF7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0001000000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0001000000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_H2();

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_G3();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00FC000000000000ULL;
	r = (discs_opponent + 0X0002000000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0001000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H2();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_F2();
				default:
					p.flip_WHITE_G2();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000101010101ULL;
	opp_discs = (discs_opponent & 0X0000010101010100ULL) | 0X0000FEFEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0001000000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0001000000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H2();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_H7();
				case 55:
					p.flip_WHITE_H6();
				case 47:
					p.flip_WHITE_H5();
				case 39:
					p.flip_WHITE_H4();
				default:
					p.flip_WHITE_H3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00003F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000800000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000800000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_A3();

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_WHITE_G3();
				case 22:
					p.flip_WHITE_F3();
				case 21:
					p.flip_WHITE_E3();
				case 20:
					p.flip_WHITE_D3();
				case 19:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_B3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A3();
		}

		p.flip_WHITE_B2();
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000020100804ULL;
	opp_discs = (discs_opponent & 0X0000004020100800ULL) | 0X00007FBFDFEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000800000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A3();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_B4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0080000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A3();
		}

		p.flip_WHITE_A2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000080808080ULL;
	opp_discs = (discs_opponent & 0X0000008080808000ULL) | 0X00007F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000800000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000800000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A3();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_A7();
				case 48:
					p.flip_WHITE_A6();
				case 40:
					p.flip_WHITE_A5();
				default:
					p.flip_WHITE_A4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00001F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000400000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000400000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_B3();

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_WHITE_G3();
				case 22:
					p.flip_WHITE_F3();
				case 21:
					p.flip_WHITE_E3();
				case 20:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_C3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B3();
		}

		p.flip_WHITE_C2();
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000010080402ULL;
	opp_discs = (discs_opponent & 0X0000002010080400ULL) | 0X00003FDFEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000400000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B3();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_C4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X4000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B3();
		}

		p.flip_WHITE_B2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000040404040ULL;
	opp_discs = (discs_opponent & 0X0000004040404000ULL) | 0X00003FBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000400000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000400000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B3();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_B6();
				case 41:
					p.flip_WHITE_B5();
				default:
					p.flip_WHITE_B4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000008040201ULL;
	opp_discs = (discs_opponent & 0X0000001008040200ULL) | 0X00001FEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000200000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000200000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_C3();

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_D4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000020202020ULL;
	opp_discs = (discs_opponent & 0X0000002020202000ULL) | 0X00001FDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000200000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_C6();
				case 42:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_C4();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X00000F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000200000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_WHITE_G3();
				case 22:
					p.flip_WHITE_F3();
				case 21:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_D3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		p.flip_WHITE_D2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		p.flip_WHITE_C2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		p.flip_WHITE_B2();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		p.flip_WHITE_B4();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000200000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C3();
		}

		p.flip_WHITE_B3();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_D3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000004020100ULL;
	opp_discs = (discs_opponent & 0X0000000804020000ULL) | 0X00000FF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000100000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_D3();

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_E4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000010101010ULL;
	opp_discs = (discs_opponent & 0X0000001010101000ULL) | 0X00000FEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_D4();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000070000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000100000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_WHITE_G3();
				case 22:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_E3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		p.flip_WHITE_E2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		p.flip_WHITE_D2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X4000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		p.flip_WHITE_C2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000040800000ULL;
	opp_discs = (discs_opponent & 0X0000002040000000ULL) | 0X00000FDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		switch(_cntlzll(my_discs)) {
				case 40:
					p.flip_WHITE_B5();
				default:
					p.flip_WHITE_C4();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X0000C00000000000ULL;
	r = (discs_opponent + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000100000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_D3();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B3();
				default:
					p.flip_WHITE_C3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_E3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000002010000ULL;
	opp_discs = (discs_opponent & 0X0000000402000000ULL) | 0X000007FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000080000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_E3();

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G5();
				default:
					p.flip_WHITE_F4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000008080808ULL;
	opp_discs = (discs_opponent & 0X0000000808080800ULL) | 0X000007F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_E4();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000030000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000080000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		switch(_cntlzll(my_discs)) {
				case 23:
					p.flip_WHITE_G3();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0200000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		p.flip_WHITE_F2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		p.flip_WHITE_E2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		p.flip_WHITE_D2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000020408000ULL;
	opp_discs = (discs_opponent & 0X0000001020400000ULL) | 0X000007EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		switch(_cntlzll(my_discs)) {
				case 48:
					p.flip_WHITE_B6();
				case 41:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_D4();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X0000E00000000000ULL;
	r = (discs_opponent + 0X0000100000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000080000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_E3();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_D3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {

		legal = true;
		move.square = 0X0000040000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_F3();

		p.flip_WHITE_G4();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000004040404ULL;
	opp_discs = (discs_opponent & 0X0000000404040400ULL) | 0X000003FBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000040000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_F4();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		p.flip_WHITE_G3();
	}

	/* direction NE */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		p.flip_WHITE_G2();
	}

	/* direction N_ */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		p.flip_WHITE_F2();
	}

	/* direction NW */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		p.flip_WHITE_E2();
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000010204080ULL;
	opp_discs = (discs_opponent & 0X0000000810204000ULL) | 0X000003F7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000040000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_C6();
				case 42:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_E4();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X0000F00000000000ULL;
	r = (discs_opponent + 0X0000080000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000040000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F3();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_E3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000F80000000000ULL;
	r = (discs_opponent + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000020000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_G3();

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000008102040ULL;
	opp_discs = (discs_opponent & 0X0000000408102000ULL) | 0X000001FBF7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000020000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G3();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_F4();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G3();
		}

		p.flip_WHITE_F2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000002020202ULL;
	opp_discs = (discs_opponent & 0X0000000202020200ULL) | 0X000001FDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000020000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G3();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_G5();
				default:
					p.flip_WHITE_G4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0200000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000020000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G3();
		}

		p.flip_WHITE_G2();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H3(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000FC0000000000ULL;
	r = (discs_opponent + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000010000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_H3();

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_G3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000004081020ULL;
	opp_discs = (discs_opponent & 0X0000000204081000ULL) | 0X000000FDFBF7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000010000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H3();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_G4();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H3();
		}

		p.flip_WHITE_G2();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000001010101ULL;
	opp_discs = (discs_opponent & 0X0000000101010100ULL) | 0X000000FEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000010000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H3();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_H7();
				case 55:
					p.flip_WHITE_H6();
				case 47:
					p.flip_WHITE_H5();
				default:
					p.flip_WHITE_H4();
		}
	}

	/* direction N_ */
	if(((discs_opponent & 0X0001000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000010000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H3();
		}

		p.flip_WHITE_H2();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X0000003F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000008000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000008000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_A4();

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_WHITE_G4();
				case 30:
					p.flip_WHITE_F4();
				case 29:
					p.flip_WHITE_E4();
				case 28:
					p.flip_WHITE_D4();
				case 27:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_B4();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X1020000000000000ULL;
	opp_discs = (discs_opponent & 0X0020400000000000ULL) | 0X0FDF800000000000ULL;
	r = (opp_discs + 0X0000400000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A4();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_WHITE_C2();
				default:
					p.flip_WHITE_B3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000201008ULL;
	opp_discs = (discs_opponent & 0X0000000040201000ULL) | 0X0000007FBFDFE000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000008000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A4();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_B5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080000000000000ULL;
	opp_discs = (discs_opponent & 0X0080800000000000ULL) | 0X7F7F000000000000ULL;
	r = (opp_discs + 0X0000800000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A4();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_A2();
				default:
					p.flip_WHITE_A3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000808080ULL;
	opp_discs = (discs_opponent & 0X0000000080808000ULL) | 0X0000007F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000008000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000008000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A4();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_A7();
				case 48:
					p.flip_WHITE_A6();
				default:
					p.flip_WHITE_A5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X0000001F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000004000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000004000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_B4();

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_WHITE_G4();
				case 30:
					p.flip_WHITE_F4();
				case 29:
					p.flip_WHITE_E4();
				case 28:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_C4();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0810000000000000ULL;
	opp_discs = (discs_opponent & 0X0010200000000000ULL) | 0X07EFC00000000000ULL;
	r = (opp_discs + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B4();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_WHITE_D2();
				default:
					p.flip_WHITE_C3();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000100804ULL;
	opp_discs = (discs_opponent & 0X0000000020100800ULL) | 0X0000003FDFEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000004000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B4();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_C5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040000000000000ULL;
	opp_discs = (discs_opponent & 0X0040400000000000ULL) | 0X3FBF800000000000ULL;
	r = (opp_discs + 0X0000400000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B4();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_B2();
				default:
					p.flip_WHITE_B3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000404040ULL;
	opp_discs = (discs_opponent & 0X0000000040404000ULL) | 0X0000003FBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000004000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000004000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B4();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_B7();
				case 49:
					p.flip_WHITE_B6();
				default:
					p.flip_WHITE_B5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000000080402ULL;
	opp_discs = (discs_opponent & 0X0000000010080400ULL) | 0X0000001FEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000002000000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000002000000000ULL;
		p = *pattern; //copy
		p.set_WHITE_C4();

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_D5();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000202020ULL;
	opp_discs = (discs_opponent & 0X0000000020202000ULL) | 0X0000001FDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000002000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_C5();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000002000000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		switch(_cntlzll(my_discs)) {
				case 31:
					p.flip_WHITE_G4();
				case 30:
					p.flip_WHITE_F4();
				case 29:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_D4();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0408000000000000ULL;
	opp_discs = (discs_opponent & 0X0008100000000000ULL) | 0X03F7E00000000000ULL;
	r = (opp_discs + 0X0000100000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_E2();
				default:
					p.flip_WHITE_D3();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020000000000000ULL;
	opp_discs = (discs_opponent & 0X0020200000000000ULL) | 0X1FDFC00000000000ULL;
	r = (opp_discs + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_C2();
				default:
					p.flip_WHITE_C3();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0080000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		p.flip_WHITE_B3();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		p.flip_WHITE_B5();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000002000000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C4();
		}

		p.flip_WHITE_B4();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {

		legal = true;
		move.square = 0X0000000400000000ULL;
		p = *pattern; //copy
		p.set_WHITE_F4();

		p.flip_WHITE_G5();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000040404ULL;
	opp_discs = (discs_opponent & 0X0000000004040400ULL) | 0X00000003FBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000400000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_F5();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		p.flip_WHITE_G4();
	}

	/* direction NE */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0001000000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		p.flip_WHITE_G3();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404000000000000ULL;
	opp_discs = (discs_opponent & 0X0004040000000000ULL) | 0X03FBF80000000000ULL;
	r = (opp_discs + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_F2();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X2010000000000000ULL;
	opp_discs = (discs_opponent & 0X0010080000000000ULL) | 0X1FEFF00000000000ULL;
	r = (opp_discs + 0X0000080000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_D2();
				default:
					p.flip_WHITE_E3();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000102040ULL;
	opp_discs = (discs_opponent & 0X0000000008102000ULL) | 0X00000003F7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000400000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_C7();
				case 50:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_E5();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000F000000000ULL;
	r = (discs_opponent + 0X0000000800000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000400000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F4();
		}

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_E4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X000000F800000000ULL;
	r = (discs_opponent + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000200000000ULL;
		p = *pattern; //copy
		p.set_WHITE_G4();

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_F4();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000081020ULL;
	opp_discs = (discs_opponent & 0X0000000004081000ULL) | 0X00000001FBF7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000200000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G4();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_F5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X1008000000000000ULL;
	opp_discs = (discs_opponent & 0X0008040000000000ULL) | 0X0FF7F80000000000ULL;
	r = (opp_discs + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G4();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_WHITE_E2();
				default:
					p.flip_WHITE_F3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000020202ULL;
	opp_discs = (discs_opponent & 0X0000000002020200ULL) | 0X00000001FDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000200000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G4();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_G6();
				default:
					p.flip_WHITE_G5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202000000000000ULL;
	opp_discs = (discs_opponent & 0X0002020000000000ULL) | 0X01FDFC0000000000ULL;
	r = (opp_discs + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000200000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G4();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_G2();
				default:
					p.flip_WHITE_G3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H4(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X000000FC00000000ULL;
	r = (discs_opponent + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000100000000ULL;
		p = *pattern; //copy
		p.set_WHITE_H4();

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_E4();
				case 0X0000000800000000ULL:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_G4();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000040810ULL;
	opp_discs = (discs_opponent & 0X0000000002040800ULL) | 0X00000000FDFBF000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000100000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H4();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_G5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0804000000000000ULL;
	opp_discs = (discs_opponent & 0X0004020000000000ULL) | 0X07FBFC0000000000ULL;
	r = (opp_discs + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H4();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_WHITE_F2();
				default:
					p.flip_WHITE_G3();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000010101ULL;
	opp_discs = (discs_opponent & 0X0000000001010100ULL) | 0X00000000FEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000100000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H4();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_H7();
				case 55:
					p.flip_WHITE_H6();
				default:
					p.flip_WHITE_H5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101000000000000ULL;
	opp_discs = (discs_opponent & 0X0001010000000000ULL) | 0X00FEFE0000000000ULL;
	r = (opp_discs + 0X0000010000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000100000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H4();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_H2();
				default:
					p.flip_WHITE_H3();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X000000003F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000080000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000080000000ULL;
		p = *pattern; //copy
		p.set_WHITE_A5();

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_D5();
				case 35:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_B5();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0810200000000000ULL;
	opp_discs = (discs_opponent & 0X0010204000000000ULL) | 0X07EFDF8000000000ULL;
	r = (opp_discs + 0X0000004000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A5();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_B4();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000002010ULL;
	opp_discs = (discs_opponent & 0X0000000000402000ULL) | 0X000000007FBFC000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000080000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A5();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_WHITE_C7();
				default:
					p.flip_WHITE_B6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080800000000000ULL;
	opp_discs = (discs_opponent & 0X0080808000000000ULL) | 0X7F7F7F0000000000ULL;
	r = (opp_discs + 0X0000008000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A5();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_A2();
				case 0X0080000000000000ULL:
					p.flip_WHITE_A3();
				default:
					p.flip_WHITE_A4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000008080ULL;
	opp_discs = (discs_opponent & 0X0000000000808000ULL) | 0X000000007F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000080000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000080000000ULL;
			p = *pattern; //copy
			p.set_WHITE_A5();
		}

		switch(_cntlzll(my_discs)) {
				case 56:
					p.flip_WHITE_A7();
				default:
					p.flip_WHITE_A6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X000000001F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000040000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000040000000ULL;
		p = *pattern; //copy
		p.set_WHITE_B5();

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_E5();
				case 36:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_C5();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0408100000000000ULL;
	opp_discs = (discs_opponent & 0X0008102000000000ULL) | 0X03F7EFC000000000ULL;
	r = (opp_discs + 0X0000002000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B5();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_C4();
		}
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000001008ULL;
	opp_discs = (discs_opponent & 0X0000000000201000ULL) | 0X000000003FDFE000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000040000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B5();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_WHITE_D7();
				default:
					p.flip_WHITE_C6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040400000000000ULL;
	opp_discs = (discs_opponent & 0X0040404000000000ULL) | 0X3FBFBF8000000000ULL;
	r = (opp_discs + 0X0000004000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B5();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_B3();
				default:
					p.flip_WHITE_B4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000004040ULL;
	opp_discs = (discs_opponent & 0X0000000000404000ULL) | 0X000000003FBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000040000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000040000000ULL;
			p = *pattern; //copy
			p.set_WHITE_B5();
		}

		switch(_cntlzll(my_discs)) {
				case 57:
					p.flip_WHITE_B7();
				default:
					p.flip_WHITE_B6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	my_discs = discs_player & 0X0000000000000804ULL;
	opp_discs = (discs_opponent & 0X0000000000100800ULL) | 0X000000001FEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000020000000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000020000000ULL;
		p = *pattern; //copy
		p.set_WHITE_C5();

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_E7();
				default:
					p.flip_WHITE_D6();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000002020ULL;
	opp_discs = (discs_opponent & 0X0000000000202000ULL) | 0X000000001FDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000020000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_C7();
				default:
					p.flip_WHITE_C6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000020000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		switch(_cntlzll(my_discs)) {
				case 39:
					p.flip_WHITE_G5();
				case 38:
					p.flip_WHITE_F5();
				case 37:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_D5();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0204080000000000ULL;
	opp_discs = (discs_opponent & 0X0004081000000000ULL) | 0X01FBF7E000000000ULL;
	r = (opp_discs + 0X0000001000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_D4();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020200000000000ULL;
	opp_discs = (discs_opponent & 0X0020202000000000ULL) | 0X1FDFDFC000000000ULL;
	r = (opp_discs + 0X0000002000000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_C3();
				default:
					p.flip_WHITE_C4();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		p.flip_WHITE_B4();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000000008000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		p.flip_WHITE_B6();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000020000000ULL;
			p = *pattern; //copy
			p.set_WHITE_C5();
		}

		p.flip_WHITE_B5();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000000000100ULL) != 0)) {

		legal = true;
		move.square = 0X0000000004000000ULL;
		p = *pattern; //copy
		p.set_WHITE_F5();

		p.flip_WHITE_G6();
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000404ULL;
	opp_discs = (discs_opponent & 0X0000000000040400ULL) | 0X0000000003FBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000004000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		switch(_cntlzll(my_discs)) {
				case 61:
					p.flip_WHITE_F7();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		p.flip_WHITE_G5();
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		p.flip_WHITE_G4();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404040000000000ULL;
	opp_discs = (discs_opponent & 0X0004040400000000ULL) | 0X03FBFBF800000000ULL;
	r = (opp_discs + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_F4();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X4020100000000000ULL;
	opp_discs = (discs_opponent & 0X0020100800000000ULL) | 0X3FDFEFF000000000ULL;
	r = (opp_discs + 0X0000000800000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_D3();
				default:
					p.flip_WHITE_E4();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000001020ULL;
	opp_discs = (discs_opponent & 0X0000000000081000ULL) | 0X0000000003F7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000004000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		switch(_cntlzll(my_discs)) {
				case 58:
					p.flip_WHITE_D7();
				default:
					p.flip_WHITE_E6();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000F0000000ULL;
	r = (discs_opponent + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000004000000ULL;
			p = *pattern; //copy
			p.set_WHITE_F5();
		}

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_WHITE_B5();
				case 0X0000000040000000ULL:
					p.flip_WHITE_C5();
				case 0X0000000020000000ULL:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_E5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X00000000F8000000ULL;
	r = (discs_opponent + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000002000000ULL;
		p = *pattern; //copy
		p.set_WHITE_G5();

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_WHITE_B5();
				case 0X0000000040000000ULL:
					p.flip_WHITE_C5();
				case 0X0000000020000000ULL:
					p.flip_WHITE_D5();
				case 0X0000000010000000ULL:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_F5();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000000810ULL;
	opp_discs = (discs_opponent & 0X0000000000040800ULL) | 0X0000000001FBF000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000002000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G5();
		}

		switch(_cntlzll(my_discs)) {
				case 59:
					p.flip_WHITE_E7();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X2010080000000000ULL;
	opp_discs = (discs_opponent & 0X0010080400000000ULL) | 0X1FEFF7F800000000ULL;
	r = (opp_discs + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G5();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_E3();
				default:
					p.flip_WHITE_F4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000202ULL;
	opp_discs = (discs_opponent & 0X0000000000020200ULL) | 0X0000000001FDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000002000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G5();
		}

		switch(_cntlzll(my_discs)) {
				case 62:
					p.flip_WHITE_G7();
				default:
					p.flip_WHITE_G6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020000000000ULL;
	opp_discs = (discs_opponent & 0X0002020200000000ULL) | 0X01FDFDFC00000000ULL;
	r = (opp_discs + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000002000000ULL;
			p = *pattern; //copy
			p.set_WHITE_G5();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_G3();
				default:
					p.flip_WHITE_G4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H5(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X00000000FC000000ULL;
	r = (discs_opponent + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000001000000ULL;
		p = *pattern; //copy
		p.set_WHITE_H5();

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_WHITE_B5();
				case 0X0000000040000000ULL:
					p.flip_WHITE_C5();
				case 0X0000000020000000ULL:
					p.flip_WHITE_D5();
				case 0X0000000010000000ULL:
					p.flip_WHITE_E5();
				case 0X0000000008000000ULL:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_G5();
		}
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000000408ULL;
	opp_discs = (discs_opponent & 0X0000000000020400ULL) | 0X0000000000FDF800ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000001000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H5();
		}

		switch(_cntlzll(my_discs)) {
				case 60:
					p.flip_WHITE_F7();
				default:
					p.flip_WHITE_G6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X1008040000000000ULL;
	opp_discs = (discs_opponent & 0X0008040200000000ULL) | 0X0FF7FBFC00000000ULL;
	r = (opp_discs + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H5();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_F3();
				default:
					p.flip_WHITE_G4();
		}
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000101ULL;
	opp_discs = (discs_opponent & 0X0000000000010100ULL) | 0X0000000000FEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000001000000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H5();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_H7();
				default:
					p.flip_WHITE_H6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010000000000ULL;
	opp_discs = (discs_opponent & 0X0001010100000000ULL) | 0X00FEFEFE00000000ULL;
	r = (opp_discs + 0X0000000100000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000001000000ULL;
			p = *pattern; //copy
			p.set_WHITE_H5();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_H2();
				case 0X0001000000000000ULL:
					p.flip_WHITE_H3();
				default:
					p.flip_WHITE_H4();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00000000003F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000800000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000800000ULL;
		p = *pattern; //copy
		p.set_WHITE_A6();

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_D6();
				case 43:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_B6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0408102000000000ULL;
	opp_discs = (discs_opponent & 0X0008102040000000ULL) | 0X03F7EFDF80000000ULL;
	r = (opp_discs + 0X0000000040000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_WHITE_A6();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_B5();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_WHITE_A6();
		}

		p.flip_WHITE_B7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808000000000ULL;
	opp_discs = (discs_opponent & 0X0080808080000000ULL) | 0X7F7F7F7F00000000ULL;
	r = (opp_discs + 0X0000000080000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_WHITE_A6();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_A2();
				case 0X0080000000000000ULL:
					p.flip_WHITE_A3();
				case 0X0000800000000000ULL:
					p.flip_WHITE_A4();
				default:
					p.flip_WHITE_A5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000008000ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000800000ULL;
			p = *pattern; //copy
			p.set_WHITE_A6();
		}

		p.flip_WHITE_A7();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _E */
	my_discs = discs_player & 0X00000000001F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000400000ULL;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000400000ULL;
		p = *pattern; //copy
		p.set_WHITE_B6();

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_E6();
				case 44:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_C6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0204081000000000ULL;
	opp_discs = (discs_opponent & 0X0004081020000000ULL) | 0X01FBF7EFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_WHITE_B6();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_C5();
		}
	}

	/* direction SE */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_WHITE_B6();
		}

		p.flip_WHITE_C7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404000000000ULL;
	opp_discs = (discs_opponent & 0X0040404040000000ULL) | 0X3FBFBFBF80000000ULL;
	r = (opp_discs + 0X0000000040000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_WHITE_B6();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_B4();
				default:
					p.flip_WHITE_B5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000040ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000400000ULL;
			p = *pattern; //copy
			p.set_WHITE_B6();
		}

		p.flip_WHITE_B7();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000200000ULL;
		p = *pattern; //copy
		p.set_WHITE_C6();

		p.flip_WHITE_D7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		p.flip_WHITE_C7();
	}

	/* direction _E */
	my_discs = discs_player & 0X00000000000F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000200000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F6();
				case 45:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_D6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0102040800000000ULL;
	opp_discs = (discs_opponent & 0X0002040810000000ULL) | 0X00FDFBF7E0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_F3();
				case 0X0000040000000000ULL:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_D5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020202000000000ULL;
	opp_discs = (discs_opponent & 0X0020202020000000ULL) | 0X1FDFDFDFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_C5();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		p.flip_WHITE_B5();
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		p.flip_WHITE_B7();
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000200000ULL;
			p = *pattern; //copy
			p.set_WHITE_C6();
		}

		p.flip_WHITE_B6();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_D6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000100000ULL;
		p = *pattern; //copy
		p.set_WHITE_D6();

		p.flip_WHITE_E7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		p.flip_WHITE_D7();
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000070000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000100000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G6();
				case 46:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_E6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0001020400000000ULL;
	opp_discs = (discs_opponent & 0X0000020408000000ULL) | 0X0000FDFBF0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		switch(r) {
				case 0X0001000000000000ULL:
					p.flip_WHITE_G3();
				case 0X0000020000000000ULL:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_E5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X1010101000000000ULL;
	opp_discs = (discs_opponent & 0X0010101010000000ULL) | 0X0FEFEFEFE0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_D5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804000000000ULL;
	opp_discs = (discs_opponent & 0X0000004020000000ULL) | 0X00007FBFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B4();
				default:
					p.flip_WHITE_C5();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000040ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		p.flip_WHITE_C7();
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000C00000ULL;
	r = (discs_opponent + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000100000ULL;
			p = *pattern; //copy
			p.set_WHITE_D6();
		}

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_WHITE_B6();
				default:
					p.flip_WHITE_C6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_E6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000002ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000080000ULL;
		p = *pattern; //copy
		p.set_WHITE_E6();

		p.flip_WHITE_F7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		p.flip_WHITE_E7();
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000030000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000080000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		switch(_cntlzll(my_discs)) {
				case 47:
					p.flip_WHITE_G6();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010200000000ULL;
	opp_discs = (discs_opponent & 0X0000000204000000ULL) | 0X000000FDF8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		switch(r) {
				case 0X0000010000000000ULL:
					p.flip_WHITE_G4();
				default:
					p.flip_WHITE_F5();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0808080800000000ULL;
	opp_discs = (discs_opponent & 0X0008080808000000ULL) | 0X07F7F7F7F0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_E5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0080402000000000ULL;
	opp_discs = (discs_opponent & 0X0000402010000000ULL) | 0X007FBFDFE0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C4();
				default:
					p.flip_WHITE_D5();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		p.flip_WHITE_D7();
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000E00000ULL;
	r = (discs_opponent + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000080000ULL;
			p = *pattern; //copy
			p.set_WHITE_E6();
		}

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_WHITE_B6();
				case 0X0000000000400000ULL:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_D6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction SE */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {

		legal = true;
		move.square = 0X0000000000040000ULL;
		p = *pattern; //copy
		p.set_WHITE_F6();

		p.flip_WHITE_G7();
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		p.flip_WHITE_F7();
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		p.flip_WHITE_G6();
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		p.flip_WHITE_G5();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404040400000000ULL;
	opp_discs = (discs_opponent & 0X0004040404000000ULL) | 0X03FBFBFBF8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_F3();
				case 0X0000040000000000ULL:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_F5();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X8040201000000000ULL;
	opp_discs = (discs_opponent & 0X0040201008000000ULL) | 0X7FBFDFEFF0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_D4();
				default:
					p.flip_WHITE_E5();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		p.flip_WHITE_E7();
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000F00000ULL;
	r = (discs_opponent + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000040000ULL;
			p = *pattern; //copy
			p.set_WHITE_F6();
		}

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_WHITE_B6();
				case 0X0000000000400000ULL:
					p.flip_WHITE_C6();
				case 0X0000000000200000ULL:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_E6();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000000000F80000ULL;
	r = (discs_opponent + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000020000ULL;
		p = *pattern; //copy
		p.set_WHITE_G6();

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_WHITE_B6();
				case 0X0000000000400000ULL:
					p.flip_WHITE_C6();
				case 0X0000000000200000ULL:
					p.flip_WHITE_D6();
				case 0X0000000000100000ULL:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_WHITE_G6();
		}

		p.flip_WHITE_F7();
	}

	/* direction NW */
	my_discs = discs_player & 0X4020100800000000ULL;
	opp_discs = (discs_opponent & 0X0020100804000000ULL) | 0X3FDFEFF7F8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_WHITE_G6();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_E4();
				default:
					p.flip_WHITE_F5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000002ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_WHITE_G6();
		}

		p.flip_WHITE_G7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020200000000ULL;
	opp_discs = (discs_opponent & 0X0002020202000000ULL) | 0X01FDFDFDFC000000ULL;
	r = (opp_discs + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000020000ULL;
			p = *pattern; //copy
			p.set_WHITE_G6();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_G3();
				case 0X0000020000000000ULL:
					p.flip_WHITE_G4();
				default:
					p.flip_WHITE_G5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H6(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction _W */
	my_discs = discs_player & 0X0000000000FC0000ULL;
	r = (discs_opponent + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000010000ULL;
		p = *pattern; //copy
		p.set_WHITE_H6();

		switch(r) {
				case 0X0000000000800000ULL:
					p.flip_WHITE_B6();
				case 0X0000000000400000ULL:
					p.flip_WHITE_C6();
				case 0X0000000000200000ULL:
					p.flip_WHITE_D6();
				case 0X0000000000100000ULL:
					p.flip_WHITE_E6();
				case 0X0000000000080000ULL:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_G6();
		}
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_WHITE_H6();
		}

		p.flip_WHITE_G7();
	}

	/* direction NW */
	my_discs = discs_player & 0X2010080400000000ULL;
	opp_discs = (discs_opponent & 0X0010080402000000ULL) | 0X1FEFF7FBFC000000ULL;
	r = (opp_discs + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_WHITE_H6();
		}

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_F4();
				default:
					p.flip_WHITE_G5();
		}
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000100ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_WHITE_H6();
		}

		p.flip_WHITE_H7();
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010100000000ULL;
	opp_discs = (discs_opponent & 0X0001010101000000ULL) | 0X00FEFEFEFE000000ULL;
	r = (opp_discs + 0X0000000001000000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000010000ULL;
			p = *pattern; //copy
			p.set_WHITE_H6();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_H2();
				case 0X0001000000000000ULL:
					p.flip_WHITE_H3();
				case 0X0000010000000000ULL:
					p.flip_WHITE_H4();
				default:
					p.flip_WHITE_H5();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0204081020000000ULL;
	opp_discs = (discs_opponent & 0X0004081020400000ULL) | 0X01FBF7EFDF800000ULL;
	r = (opp_discs + 0X0000000000400000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000008000ULL;
		p = *pattern; //copy
		p.set_WHITE_A7();

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_B6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808080000000ULL;
	opp_discs = (discs_opponent & 0X0080808080800000ULL) | 0X7F7F7F7F7F000000ULL;
	r = (opp_discs + 0X0000000000800000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000008000ULL;
			p = *pattern; //copy
			p.set_WHITE_A7();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_A2();
				case 0X0080000000000000ULL:
					p.flip_WHITE_A3();
				case 0X0000800000000000ULL:
					p.flip_WHITE_A4();
				case 0X0000008000000000ULL:
					p.flip_WHITE_A5();
				default:
					p.flip_WHITE_A6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000003F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000008000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000008000ULL;
			p = *pattern; //copy
			p.set_WHITE_A7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_D7();
				case 51:
					p.flip_WHITE_C7();
				default:
					p.flip_WHITE_B7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0102040810000000ULL;
	opp_discs = (discs_opponent & 0X0002040810200000ULL) | 0X00FDFBF7EFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000004000ULL;
		p = *pattern; //copy
		p.set_WHITE_B7();

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_F3();
				case 0X0000040000000000ULL:
					p.flip_WHITE_E4();
				case 0X0000000800000000ULL:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_C6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404040000000ULL;
	opp_discs = (discs_opponent & 0X0040404040400000ULL) | 0X3FBFBFBFBF800000ULL;
	r = (opp_discs + 0X0000000000400000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000004000ULL;
			p = *pattern; //copy
			p.set_WHITE_B7();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_B5();
				default:
					p.flip_WHITE_B6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000001F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000004000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000004000ULL;
			p = *pattern; //copy
			p.set_WHITE_B7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_E7();
				case 52:
					p.flip_WHITE_D7();
				default:
					p.flip_WHITE_C7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X2020202020000000ULL;
	opp_discs = (discs_opponent & 0X0020202020200000ULL) | 0X1FDFDFDFDFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000002000ULL;
		p = *pattern; //copy
		p.set_WHITE_C7();

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_C6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0001020408000000ULL;
	opp_discs = (discs_opponent & 0X0000020408100000ULL) | 0X0000FDFBF7E00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_WHITE_C7();
		}

		switch(r) {
				case 0X0001000000000000ULL:
					p.flip_WHITE_G3();
				case 0X0000020000000000ULL:
					p.flip_WHITE_F4();
				case 0X0000000400000000ULL:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_D6();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_WHITE_C7();
		}

		p.flip_WHITE_B6();
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000002000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_WHITE_C7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F7();
				case 53:
					p.flip_WHITE_E7();
				default:
					p.flip_WHITE_D7();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000008000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000002000ULL;
			p = *pattern; //copy
			p.set_WHITE_C7();
		}

		p.flip_WHITE_B7();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_D7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X1010101010000000ULL;
	opp_discs = (discs_opponent & 0X0010101010100000ULL) | 0X0FEFEFEFEFE00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000001000ULL;
		p = *pattern; //copy
		p.set_WHITE_D7();

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_D6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010204000000ULL;
	opp_discs = (discs_opponent & 0X0000000204080000ULL) | 0X000000FDFBF00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_WHITE_D7();
		}

		switch(r) {
				case 0X0000010000000000ULL:
					p.flip_WHITE_G4();
				case 0X0000000200000000ULL:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_E6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000008040000000ULL;
	opp_discs = (discs_opponent & 0X0000000040200000ULL) | 0X0000007FBFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_WHITE_D7();
		}

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_WHITE_B5();
				default:
					p.flip_WHITE_C6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000700ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000001000ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_WHITE_D7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G7();
				case 54:
					p.flip_WHITE_F7();
				default:
					p.flip_WHITE_E7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000C000ULL;
	r = (discs_opponent + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000001000ULL;
			p = *pattern; //copy
			p.set_WHITE_D7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_WHITE_B7();
				default:
					p.flip_WHITE_C7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_E7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0808080808000000ULL;
	opp_discs = (discs_opponent & 0X0008080808080000ULL) | 0X07F7F7F7F7F00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000800ULL;
		p = *pattern; //copy
		p.set_WHITE_E7();

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_E4();
				case 0X0000000800000000ULL:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_E6();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000102000000ULL;
	opp_discs = (discs_opponent & 0X0000000002040000ULL) | 0X00000000FDF80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_WHITE_E7();
		}

		switch(r) {
				case 0X0000000100000000ULL:
					p.flip_WHITE_G5();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804020000000ULL;
	opp_discs = (discs_opponent & 0X0000004020100000ULL) | 0X00007FBFDFE00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_WHITE_E7();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_C5();
				default:
					p.flip_WHITE_D6();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000300ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000800ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_WHITE_E7();
		}

		switch(_cntlzll(my_discs)) {
				case 55:
					p.flip_WHITE_G7();
				default:
					p.flip_WHITE_F7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000E000ULL;
	r = (discs_opponent + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000800ULL;
			p = *pattern; //copy
			p.set_WHITE_E7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_WHITE_B7();
				case 0X0000000000004000ULL:
					p.flip_WHITE_C7();
				default:
					p.flip_WHITE_D7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0404040404000000ULL;
	opp_discs = (discs_opponent & 0X0004040404040000ULL) | 0X03FBFBFBFBF80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000400ULL;
		p = *pattern; //copy
		p.set_WHITE_F7();

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_F3();
				case 0X0000040000000000ULL:
					p.flip_WHITE_F4();
				case 0X0000000400000000ULL:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_WHITE_F7();
		}

		p.flip_WHITE_G6();
	}

	/* direction NW */
	my_discs = discs_player & 0X0080402010000000ULL;
	opp_discs = (discs_opponent & 0X0000402010080000ULL) | 0X007FBFDFEFF00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_WHITE_F7();
		}

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_D5();
				default:
					p.flip_WHITE_E6();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000100ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_WHITE_F7();
		}

		p.flip_WHITE_G7();
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000F000ULL;
	r = (discs_opponent + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000400ULL;
			p = *pattern; //copy
			p.set_WHITE_F7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_WHITE_B7();
				case 0X0000000000004000ULL:
					p.flip_WHITE_C7();
				case 0X0000000000002000ULL:
					p.flip_WHITE_D7();
				default:
					p.flip_WHITE_E7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X8040201008000000ULL;
	opp_discs = (discs_opponent & 0X0040201008040000ULL) | 0X7FBFDFEFF7F80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000200ULL;
		p = *pattern; //copy
		p.set_WHITE_G7();

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_E5();
				default:
					p.flip_WHITE_F6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020202000000ULL;
	opp_discs = (discs_opponent & 0X0002020202020000ULL) | 0X01FDFDFDFDFC0000ULL;
	r = (opp_discs + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000200ULL;
			p = *pattern; //copy
			p.set_WHITE_G7();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_G3();
				case 0X0000020000000000ULL:
					p.flip_WHITE_G4();
				case 0X0000000200000000ULL:
					p.flip_WHITE_G5();
				default:
					p.flip_WHITE_G6();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000F800ULL;
	r = (discs_opponent + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000200ULL;
			p = *pattern; //copy
			p.set_WHITE_G7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_WHITE_B7();
				case 0X0000000000004000ULL:
					p.flip_WHITE_C7();
				case 0X0000000000002000ULL:
					p.flip_WHITE_D7();
				case 0X0000000000001000ULL:
					p.flip_WHITE_E7();
				default:
					p.flip_WHITE_F7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H7(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X4020100804000000ULL;
	opp_discs = (discs_opponent & 0X0020100804020000ULL) | 0X3FDFEFF7FBFC0000ULL;
	r = (opp_discs + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000100ULL;
		p = *pattern; //copy
		p.set_WHITE_H7();

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_E4();
				case 0X0000000800000000ULL:
					p.flip_WHITE_F5();
				default:
					p.flip_WHITE_G6();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010101000000ULL;
	opp_discs = (discs_opponent & 0X0001010101010000ULL) | 0X00FEFEFEFEFE0000ULL;
	r = (opp_discs + 0X0000000000010000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000100ULL;
			p = *pattern; //copy
			p.set_WHITE_H7();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_H2();
				case 0X0001000000000000ULL:
					p.flip_WHITE_H3();
				case 0X0000010000000000ULL:
					p.flip_WHITE_H4();
				case 0X0000000100000000ULL:
					p.flip_WHITE_H5();
				default:
					p.flip_WHITE_H6();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000FC00ULL;
	r = (discs_opponent + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000100ULL;
			p = *pattern; //copy
			p.set_WHITE_H7();
		}

		switch(r) {
				case 0X0000000000008000ULL:
					p.flip_WHITE_B7();
				case 0X0000000000004000ULL:
					p.flip_WHITE_C7();
				case 0X0000000000002000ULL:
					p.flip_WHITE_D7();
				case 0X0000000000001000ULL:
					p.flip_WHITE_E7();
				case 0X0000000000000800ULL:
					p.flip_WHITE_F7();
				default:
					p.flip_WHITE_G7();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_A8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0102040810200000ULL;
	opp_discs = (discs_opponent & 0X0002040810204000ULL) | 0X00FDFBF7EFDF8000ULL;
	r = (opp_discs + 0X0000000000004000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000080ULL;
		p = *pattern; //copy
		p.set_WHITE_A8();

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_F3();
				case 0X0000040000000000ULL:
					p.flip_WHITE_E4();
				case 0X0000000800000000ULL:
					p.flip_WHITE_D5();
				case 0X0000000010000000ULL:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_B7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808080800000ULL;
	opp_discs = (discs_opponent & 0X0080808080808000ULL) | 0X7F7F7F7F7F7F0000ULL;
	r = (opp_discs + 0X0000000000008000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000080ULL;
			p = *pattern; //copy
			p.set_WHITE_A8();
		}

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_A2();
				case 0X0080000000000000ULL:
					p.flip_WHITE_A3();
				case 0X0000800000000000ULL:
					p.flip_WHITE_A4();
				case 0X0000008000000000ULL:
					p.flip_WHITE_A5();
				case 0X0000000080000000ULL:
					p.flip_WHITE_A6();
				default:
					p.flip_WHITE_A7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000003FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000080ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000080ULL;
			p = *pattern; //copy
			p.set_WHITE_A8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G8();
				case 62:
					p.flip_WHITE_F8();
				case 61:
					p.flip_WHITE_E8();
				case 60:
					p.flip_WHITE_D8();
				case 59:
					p.flip_WHITE_C8();
				default:
					p.flip_WHITE_B8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_B8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NE */
	my_discs = discs_player & 0X0001020408100000ULL;
	opp_discs = (discs_opponent & 0X0000020408102000ULL) | 0X0000FDFBF7EFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000040ULL;
		p = *pattern; //copy
		p.set_WHITE_B8();

		switch(r) {
				case 0X0001000000000000ULL:
					p.flip_WHITE_G3();
				case 0X0000020000000000ULL:
					p.flip_WHITE_F4();
				case 0X0000000400000000ULL:
					p.flip_WHITE_E5();
				case 0X0000000008000000ULL:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_C7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404040400000ULL;
	opp_discs = (discs_opponent & 0X0040404040404000ULL) | 0X3FBFBFBFBFBF8000ULL;
	r = (opp_discs + 0X0000000000004000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000040ULL;
			p = *pattern; //copy
			p.set_WHITE_B8();
		}

		switch(r) {
				case 0X4000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_B5();
				case 0X0000000040000000ULL:
					p.flip_WHITE_B6();
				default:
					p.flip_WHITE_B7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000001FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000040ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000040ULL;
			p = *pattern; //copy
			p.set_WHITE_B8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G8();
				case 62:
					p.flip_WHITE_F8();
				case 61:
					p.flip_WHITE_E8();
				case 60:
					p.flip_WHITE_D8();
				default:
					p.flip_WHITE_C8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_C8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X2020202020200000ULL;
	opp_discs = (discs_opponent & 0X0020202020202000ULL) | 0X1FDFDFDFDFDFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000020ULL;
		p = *pattern; //copy
		p.set_WHITE_C8();

		switch(r) {
				case 0X2000000000000000ULL:
					p.flip_WHITE_C2();
				case 0X0020000000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_C5();
				case 0X0000000020000000ULL:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_C7();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010204080000ULL;
	opp_discs = (discs_opponent & 0X0000000204081000ULL) | 0X000000FDFBF7E000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_WHITE_C8();
		}

		switch(r) {
				case 0X0000010000000000ULL:
					p.flip_WHITE_G4();
				case 0X0000000200000000ULL:
					p.flip_WHITE_F5();
				case 0X0000000004000000ULL:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_D7();
		}
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_WHITE_C8();
		}

		p.flip_WHITE_B7();
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000000FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000020ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_WHITE_C8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G8();
				case 62:
					p.flip_WHITE_F8();
				case 61:
					p.flip_WHITE_E8();
				default:
					p.flip_WHITE_D8();
		}
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000000040ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000020ULL;
			p = *pattern; //copy
			p.set_WHITE_C8();
		}

		p.flip_WHITE_B8();
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_D8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X1010101010100000ULL;
	opp_discs = (discs_opponent & 0X0010101010101000ULL) | 0X0FEFEFEFEFEFE000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000010ULL;
		p = *pattern; //copy
		p.set_WHITE_D8();

		switch(r) {
				case 0X1000000000000000ULL:
					p.flip_WHITE_D2();
				case 0X0010000000000000ULL:
					p.flip_WHITE_D3();
				case 0X0000100000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_D5();
				case 0X0000000010000000ULL:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_D7();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000102040000ULL;
	opp_discs = (discs_opponent & 0X0000000002040800ULL) | 0X00000000FDFBF000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_WHITE_D8();
		}

		switch(r) {
				case 0X0000000100000000ULL:
					p.flip_WHITE_G5();
				case 0X0000000002000000ULL:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_E7();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000000080400000ULL;
	opp_discs = (discs_opponent & 0X0000000000402000ULL) | 0X000000007FBFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_WHITE_D8();
		}

		switch(r) {
				case 0X0000000080000000ULL:
					p.flip_WHITE_B6();
				default:
					p.flip_WHITE_C7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000007ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000010ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_WHITE_D8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G8();
				case 62:
					p.flip_WHITE_F8();
				default:
					p.flip_WHITE_E8();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000C0ULL;
	r = (discs_opponent + 0X0000000000000020ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000010ULL;
			p = *pattern; //copy
			p.set_WHITE_D8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_WHITE_B8();
				default:
					p.flip_WHITE_C8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_E8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0808080808080000ULL;
	opp_discs = (discs_opponent & 0X0008080808080800ULL) | 0X07F7F7F7F7F7F000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000008ULL;
		p = *pattern; //copy
		p.set_WHITE_E8();

		switch(r) {
				case 0X0800000000000000ULL:
					p.flip_WHITE_E2();
				case 0X0008000000000000ULL:
					p.flip_WHITE_E3();
				case 0X0000080000000000ULL:
					p.flip_WHITE_E4();
				case 0X0000000800000000ULL:
					p.flip_WHITE_E5();
				case 0X0000000008000000ULL:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_E7();
		}
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000001020000ULL;
	opp_discs = (discs_opponent & 0X0000000000020400ULL) | 0X0000000000FDF800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_WHITE_E8();
		}

		switch(r) {
				case 0X0000000001000000ULL:
					p.flip_WHITE_G6();
				default:
					p.flip_WHITE_F7();
		}
	}

	/* direction NW */
	my_discs = discs_player & 0X0000008040200000ULL;
	opp_discs = (discs_opponent & 0X0000000040201000ULL) | 0X0000007FBFDFE000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_WHITE_E8();
		}

		switch(r) {
				case 0X0000008000000000ULL:
					p.flip_WHITE_B5();
				case 0X0000000040000000ULL:
					p.flip_WHITE_C6();
				default:
					p.flip_WHITE_D7();
		}
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000003ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000008ULL;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_WHITE_E8();
		}

		switch(_cntlzll(my_discs)) {
				case 63:
					p.flip_WHITE_G8();
				default:
					p.flip_WHITE_F8();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000E0ULL;
	r = (discs_opponent + 0X0000000000000010ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000008ULL;
			p = *pattern; //copy
			p.set_WHITE_E8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_WHITE_B8();
				case 0X0000000000000040ULL:
					p.flip_WHITE_C8();
				default:
					p.flip_WHITE_D8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_F8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction N_ */
	my_discs = discs_player & 0X0404040404040000ULL;
	opp_discs = (discs_opponent & 0X0004040404040400ULL) | 0X03FBFBFBFBFBF800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000004ULL;
		p = *pattern; //copy
		p.set_WHITE_F8();

		switch(r) {
				case 0X0400000000000000ULL:
					p.flip_WHITE_F2();
				case 0X0004000000000000ULL:
					p.flip_WHITE_F3();
				case 0X0000040000000000ULL:
					p.flip_WHITE_F4();
				case 0X0000000400000000ULL:
					p.flip_WHITE_F5();
				case 0X0000000004000000ULL:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_F7();
		}
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_WHITE_F8();
		}

		p.flip_WHITE_G7();
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804020100000ULL;
	opp_discs = (discs_opponent & 0X0000004020100800ULL) | 0X00007FBFDFEFF000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_WHITE_F8();
		}

		switch(r) {
				case 0X0000800000000000ULL:
					p.flip_WHITE_B4();
				case 0X0000004000000000ULL:
					p.flip_WHITE_C5();
				case 0X0000000020000000ULL:
					p.flip_WHITE_D6();
				default:
					p.flip_WHITE_E7();
		}
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000000002ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_WHITE_F8();
		}

		p.flip_WHITE_G8();
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000F0ULL;
	r = (discs_opponent + 0X0000000000000008ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000004ULL;
			p = *pattern; //copy
			p.set_WHITE_F8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_WHITE_B8();
				case 0X0000000000000040ULL:
					p.flip_WHITE_C8();
				case 0X0000000000000020ULL:
					p.flip_WHITE_D8();
				default:
					p.flip_WHITE_E8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_G8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X0080402010080000ULL;
	opp_discs = (discs_opponent & 0X0000402010080400ULL) | 0X007FBFDFEFF7F800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000002ULL;
		p = *pattern; //copy
		p.set_WHITE_G8();

		switch(r) {
				case 0X0080000000000000ULL:
					p.flip_WHITE_B3();
				case 0X0000400000000000ULL:
					p.flip_WHITE_C4();
				case 0X0000002000000000ULL:
					p.flip_WHITE_D5();
				case 0X0000000010000000ULL:
					p.flip_WHITE_E6();
				default:
					p.flip_WHITE_F7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020202020000ULL;
	opp_discs = (discs_opponent & 0X0002020202020200ULL) | 0X01FDFDFDFDFDFC00ULL;
	r = (opp_discs + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000002ULL;
			p = *pattern; //copy
			p.set_WHITE_G8();
		}

		switch(r) {
				case 0X0200000000000000ULL:
					p.flip_WHITE_G2();
				case 0X0002000000000000ULL:
					p.flip_WHITE_G3();
				case 0X0000020000000000ULL:
					p.flip_WHITE_G4();
				case 0X0000000200000000ULL:
					p.flip_WHITE_G5();
				case 0X0000000002000000ULL:
					p.flip_WHITE_G6();
				default:
					p.flip_WHITE_G7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000F8ULL;
	r = (discs_opponent + 0X0000000000000004ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000002ULL;
			p = *pattern; //copy
			p.set_WHITE_G8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_WHITE_B8();
				case 0X0000000000000040ULL:
					p.flip_WHITE_C8();
				case 0X0000000000000020ULL:
					p.flip_WHITE_D8();
				case 0X0000000000000010ULL:
					p.flip_WHITE_E8();
				default:
					p.flip_WHITE_F8();
		}
	}

	return legal;

}

bool RXBBPatterns::generate_patterns_WHITE_H8(RXMove& move) const {
	
	unsigned long long my_discs, opp_discs, r;
	
	const unsigned long long discs_player = board.discs[WHITE];
	const unsigned long long discs_opponent = board.discs[BLACK];
	
	RXPattern& p = *(move.pattern);
	
	
	bool legal = false;

	/* direction NW */
	my_discs = discs_player & 0X8040201008040000ULL;
	opp_discs = (discs_opponent & 0X0040201008040200ULL) | 0X7FBFDFEFF7FBFC00ULL;
	r = (opp_discs + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {

		legal = true;
		move.square = 0X0000000000000001ULL;
		p = *pattern; //copy
		p.set_WHITE_H8();

		switch(r) {
				case 0X8000000000000000ULL:
					p.flip_WHITE_B2();
				case 0X0040000000000000ULL:
					p.flip_WHITE_C3();
				case 0X0000200000000000ULL:
					p.flip_WHITE_D4();
				case 0X0000001000000000ULL:
					p.flip_WHITE_E5();
				case 0X0000000008000000ULL:
					p.flip_WHITE_F6();
				default:
					p.flip_WHITE_G7();
		}
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010101010000ULL;
	opp_discs = (discs_opponent & 0X0001010101010100ULL) | 0X00FEFEFEFEFEFE00ULL;
	r = (opp_discs + 0X0000000000000100ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000001ULL;
			p = *pattern; //copy
			p.set_WHITE_H8();
		}

		switch(r) {
				case 0X0100000000000000ULL:
					p.flip_WHITE_H2();
				case 0X0001000000000000ULL:
					p.flip_WHITE_H3();
				case 0X0000010000000000ULL:
					p.flip_WHITE_H4();
				case 0X0000000100000000ULL:
					p.flip_WHITE_H5();
				case 0X0000000001000000ULL:
					p.flip_WHITE_H6();
				default:
					p.flip_WHITE_H7();
		}
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000FCULL;
	r = (discs_opponent + 0X0000000000000002ULL) & my_discs;
	if(r != 0) {

		if(!legal) {
			legal = true;
			move.square = 0X0000000000000001ULL;
			p = *pattern; //copy
			p.set_WHITE_H8();
		}

		switch(r) {
				case 0X0000000000000080ULL:
					p.flip_WHITE_B8();
				case 0X0000000000000040ULL:
					p.flip_WHITE_C8();
				case 0X0000000000000020ULL:
					p.flip_WHITE_D8();
				case 0X0000000000000010ULL:
					p.flip_WHITE_E8();
				case 0X0000000000000008ULL:
					p.flip_WHITE_F8();
				default:
					p.flip_WHITE_G8();
		}
	}

	return legal;

}


void RXBBPatterns::init_generate_patterns() {

	generate_patterns[A1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A1;
	generate_patterns[A2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A2;
	generate_patterns[A3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A3;
	generate_patterns[A4][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A4;
	generate_patterns[A5][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A5;
	generate_patterns[A6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A6;
	generate_patterns[A7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A7;
	generate_patterns[A8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_A8;

	generate_patterns[B1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B1;
	generate_patterns[B2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B2;
	generate_patterns[B3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B3;
	generate_patterns[B4][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B4;
	generate_patterns[B5][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B5;
	generate_patterns[B6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B6;
	generate_patterns[B7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B7;
	generate_patterns[B8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_B8;
	
	generate_patterns[C1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C1;
	generate_patterns[C2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C2;
	generate_patterns[C3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C3;
	generate_patterns[C4][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C4;
	generate_patterns[C5][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C5;
	generate_patterns[C6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C6;
	generate_patterns[C7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C7;
	generate_patterns[C8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_C8;
	
	generate_patterns[D1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_D1;
	generate_patterns[D2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_D2;
	generate_patterns[D3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_D3;
	generate_patterns[D6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_D6;
	generate_patterns[D7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_D7;
	generate_patterns[D8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_D8;

	generate_patterns[E1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_E1;
	generate_patterns[E2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_E2;
	generate_patterns[E3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_E3;
	generate_patterns[E6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_E6;
	generate_patterns[E7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_E7;
	generate_patterns[E8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_E8;

	generate_patterns[F1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F1;
	generate_patterns[F2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F2;
	generate_patterns[F3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F3;
	generate_patterns[F4][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F4;
	generate_patterns[F5][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F5;
	generate_patterns[F6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F6;
	generate_patterns[F7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F7;
	generate_patterns[F8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_F8;

	generate_patterns[G1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G1;
	generate_patterns[G2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G2;
	generate_patterns[G3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G3;
	generate_patterns[G4][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G4;
	generate_patterns[G5][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G5;
	generate_patterns[G6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G6;
	generate_patterns[G7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G7;
	generate_patterns[G8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_G8;

	generate_patterns[H1][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H1;
	generate_patterns[H2][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H2;
	generate_patterns[H3][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H3;
	generate_patterns[H4][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H4;
	generate_patterns[H5][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H5;
	generate_patterns[H6][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H6;
	generate_patterns[H7][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H7;
	generate_patterns[H8][BLACK] = &RXBBPatterns::generate_patterns_BLACK_H8;

	generate_patterns[A1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A1;
	generate_patterns[A2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A2;
	generate_patterns[A3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A3;
	generate_patterns[A4][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A4;
	generate_patterns[A5][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A5;
	generate_patterns[A6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A6;
	generate_patterns[A7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A7;
	generate_patterns[A8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_A8;

	generate_patterns[B1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B1;
	generate_patterns[B2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B2;
	generate_patterns[B3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B3;
	generate_patterns[B4][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B4;
	generate_patterns[B5][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B5;
	generate_patterns[B6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B6;
	generate_patterns[B7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B7;
	generate_patterns[B8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_B8;
	
	generate_patterns[C1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C1;
	generate_patterns[C2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C2;
	generate_patterns[C3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C3;
	generate_patterns[C4][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C4;
	generate_patterns[C5][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C5;
	generate_patterns[C6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C6;
	generate_patterns[C7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C7;
	generate_patterns[C8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_C8;
	
	generate_patterns[D1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_D1;
	generate_patterns[D2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_D2;
	generate_patterns[D3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_D3;
	generate_patterns[D6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_D6;
	generate_patterns[D7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_D7;
	generate_patterns[D8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_D8;

	generate_patterns[E1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_E1;
	generate_patterns[E2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_E2;
	generate_patterns[E3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_E3;
	generate_patterns[E6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_E6;
	generate_patterns[E7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_E7;
	generate_patterns[E8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_E8;

	generate_patterns[F1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F1;
	generate_patterns[F2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F2;
	generate_patterns[F3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F3;
	generate_patterns[F4][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F4;
	generate_patterns[F5][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F5;
	generate_patterns[F6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F6;
	generate_patterns[F7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F7;
	generate_patterns[F8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_F8;

	generate_patterns[G1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G1;
	generate_patterns[G2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G2;
	generate_patterns[G3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G3;
	generate_patterns[G4][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G4;
	generate_patterns[G5][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G5;
	generate_patterns[G6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G6;
	generate_patterns[G7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G7;
	generate_patterns[G8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_G8;

	generate_patterns[H1][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H1;
	generate_patterns[H2][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H2;
	generate_patterns[H3][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H3;
	generate_patterns[H4][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H4;
	generate_patterns[H5][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H5;
	generate_patterns[H6][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H6;
	generate_patterns[H7][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H7;
	generate_patterns[H8][WHITE] = &RXBBPatterns::generate_patterns_WHITE_H8;

}

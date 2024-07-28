
/*
 *  RXBitBoard.cpp
 *  Roxane
 *
 *  Created by Bruno Causse on 27/06/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#include "RXBitBoard.h"
#include "RXTools.h"

bool RXBitBoard::generate_move_A1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XC79BFEF60AF9617CULL, 0X0429197C2FC669EEULL};
	static const unsigned long long HASH_SE[] = { 0, 0X41739819832B7B0BULL, 0X557FEB282D28CDD0ULL, 0X81026BA6A77A15CCULL, 0X4F7359C01D5C0470ULL, 0X160117C5132DCB5AULL, 0XDE2AB12F804E65DFULL};
	static const unsigned long long HASH_S_[] = { 0, 0X234987C9503B7392ULL, 0X3F0E8B0E7A50E41AULL, 0X3AE9FA38588407C3ULL, 0X4E545FAAF56CA2A8ULL, 0X658E2770F9D40FF5ULL, 0XD319D9CEB4587A51ULL};
	static const unsigned long long HASH__E[] = { 0, 0X6A95BB3492AA8F4CULL, 0X3A81F9BA42E1F4EAULL, 0XFEF2C9A5353D6FD9ULL, 0X1132836D542F70D6ULL, 0X1ED2A3DEEF90EBE8ULL, 0X4CFCD3C5F257A739ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000201008040201ULL;
	opp_discs = (discs_opponent & 0X0040201008040200ULL) | 0X7FBFDFEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X8000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 9;
		move.flipped |= (0X8000000000000000ULL - (0X0080000000000000ULL>>s)) & 0X0040201008040200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000808080808080ULL;
	opp_discs = (discs_opponent & 0X0080808080808000ULL) | 0X7F7F7F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X8000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 8;
		move.flipped |= (0X8000000000000000ULL - (0X0100000000000000ULL>>s)) & 0X0080808080808000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X3F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X8000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 1;
		move.flipped |= 0X8000000000000000ULL - (0X8000000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X8000000000000000ULL;
	move.position = A1;
	
	return true;

}

bool RXBitBoard::generate_move_B1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X008F6EF4453495A8ULL, 0X6A1AD5C0D79E1AE4ULL};
	static const unsigned long long HASH_SE[] = { 0, 0X1A6099F17BA4C4A4ULL, 0XA68D1A018194A9A5ULL, 0XFE81DA6061B26CE5ULL, 0XAEDAFCDBD3E19A29ULL, 0XB8623EEED9A87475ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X41739819832B7B0BULL, 0X9CA187F3972B4108ULL, 0XD88D019E8CAAF6B8ULL, 0X76610F85249C2CA9ULL, 0XD13E9FF5EAAA4AE3ULL, 0XA139F0DA5FE46562ULL};
	static const unsigned long long HASH__E[] = { 0, 0X5014428ED04B7BA6ULL, 0X94677291A797E095ULL, 0X7BA73859C685FF9AULL, 0X744718EA7D3A64A4ULL, 0X266968F160FD2875ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000100804020100ULL;
	opp_discs = (discs_opponent & 0X0020100804020000ULL) | 0X3FDFEFF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X4000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 10;
		move.flipped |= (0X4000000000000000ULL - (0X0040000000000000ULL>>s)) & 0X0020100804020000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000404040404040ULL;
	opp_discs = (discs_opponent & 0X0040404040404000ULL) | 0X3FBFBFBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X4000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 9;
		move.flipped |= (0X4000000000000000ULL - (0X0080000000000000ULL>>s)) & 0X0040404040404000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X1F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X4000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 2;
		move.flipped |= 0X4000000000000000ULL - (0X4000000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X4000000000000000ULL;
	move.position = B1;
	
	return true;

}

bool RXBitBoard::generate_move_C1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X6DE130CFBD5E4B03ULL, 0X3DF572416D1530A5ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X1A6099F17BA4C4A4ULL, 0X0E6CEAC0D5A7727FULL, 0X00220C073DD78D33ULL, 0XFEBBB60D753B3D73ULL, 0XDF5A762C121018ECULL, 0XC346FE5F2A5BA3F9ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XD8C65D867F1FC5ACULL, 0X74DFDD0D1F30CEC4ULL, 0XBB45AD7527DF373FULL, 0XB6FD9514587068C2ULL};
	static const unsigned long long HASH__E[] = { 0, 0XC473301F77DC9B33ULL, 0X2BB37AD716CE843CULL, 0X24535A64AD711F02ULL, 0X767D2A7FB0B653D3ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000202020202020ULL;
	opp_discs = (discs_opponent & 0X0020202020202000ULL) | 0X1FDFDFDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X2000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 10;
		move.flipped |= (0X2000000000000000ULL - (0X0040000000000000ULL>>s)) & 0X0020202020202000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000080402010000ULL;
	opp_discs = (discs_opponent & 0X0010080402000000ULL) | 0X1FEFF7FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X2000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 11;
		move.flipped |= (0X2000000000000000ULL - (0X0020000000000000ULL>>s)) & 0X0010080402000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {
		move.flipped |= 0X0040000000000000ULL;
		move.hash_code ^= 0X41739819832B7B0BULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X0F00000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X2000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 3;
		move.flipped |= 0X2000000000000000ULL - (0X2000000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	if(((discs_opponent & 0X4000000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {
		move.flipped |= 0X4000000000000000ULL;
		move.hash_code ^= 0X6A95BB3492AA8F4CULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X2000000000000000ULL;
	move.position = C1;
	
	return true;

}

bool RXBitBoard::generate_move_D1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X5D1A65EE28CACBF8ULL, 0X996955F15F1650CBULL};
	static const unsigned long long HASH_S_[] = { 0, 0XD8C65D867F1FC5ACULL, 0X642BDE76852FA8ADULL, 0XB0565EF80F7D70B1ULL, 0X68D453435CCF4598ULL, 0XB04409E393BA617BULL, 0X20CFCA9A5C33B47FULL};
	static const unsigned long long HASH_SE[] = { 0, 0X744ED952B2CF378BULL, 0X09D91F739521CEDAULL, 0X47FBF1529EC36B0EULL};
	static const unsigned long long HASH_SW[] = { 0, 0X1A6099F17BA4C4A4ULL, 0XC7B2861B6FA4FEA7ULL};
	static const unsigned long long HASH__E[] = { 0, 0XEFC04AC861121F0FULL, 0XE0206A7BDAAD8431ULL, 0XB20E1A60C76AC8E0ULL};
	static const unsigned long long HASH__W[] = { 0, 0X5014428ED04B7BA6ULL, 0X3A81F9BA42E1F4EAULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000101010101010ULL;
	opp_discs = (discs_opponent & 0X0010101010101000ULL) | 0X0FEFEFEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 11;
		move.flipped |= (0X1000000000000000ULL - (0X0020000000000000ULL>>s)) & 0X0010101010101000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000040201000000ULL;
	opp_discs = (discs_opponent & 0X0008040200000000ULL) | 0X0FF7FBFC00000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 12;
		move.flipped |= (0X1000000000000000ULL - (0X0010000000000000ULL>>s)) & 0X0008040200000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000408000000000ULL;
	opp_discs = (discs_opponent & 0X0020400000000000ULL) | 0X0FDF800000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X1000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 3;
		move.flipped |= (0X1000000000000000ULL - (0X2000000000000000ULL>>s)) & 0X0020400000000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0700000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X1000000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 4;
		move.flipped |= 0X1000000000000000ULL - (0X1000000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0XC000000000000000ULL;
	r = (discs_opponent + 0X2000000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0XE000000000000000ULL;
		
		s = 2 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X1000000000000000ULL;
	move.position = D1;
	
	return true;

}

bool RXBitBoard::generate_move_E1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XAE6327AFFB44559EULL, 0X41A36D679A564A91ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X744ED952B2CF378BULL, 0XD85759D9D2E03CE3ULL, 0X805B99B832C6F9A3ULL, 0X4E2AABDE88E0E81FULL, 0XBFB35360FBBBAB93ULL, 0X905D51D77FFD11B3ULL};
	static const unsigned long long HASH_SE[] = { 0, 0X80612B4ABCCBF81CULL, 0X2226112D4C157315ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XD8C65D867F1FC5ACULL, 0XCCCA2EB7D11C7377ULL, 0X88E6A8DACA9DC4C7ULL};
	static const unsigned long long HASH__E[] = { 0, 0X0FE020B3BBBF9B3EULL, 0X5DCE50A8A678D7EFULL};
	static const unsigned long long HASH__W[] = { 0, 0XC473301F77DC9B33ULL, 0X94677291A797E095ULL, 0XFEF2C9A5353D6FD9ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000080808080808ULL;
	opp_discs = (discs_opponent & 0X0008080808080800ULL) | 0X07F7F7F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 12;
		move.flipped |= (0X0800000000000000ULL - (0X0010000000000000ULL>>s)) & 0X0008080808080800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000020100000000ULL;
	opp_discs = (discs_opponent & 0X0004020000000000ULL) | 0X07FBFC0000000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 13;
		move.flipped |= (0X0800000000000000ULL - (0X0008000000000000ULL>>s)) & 0X0004020000000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000204080000000ULL;
	opp_discs = (discs_opponent & 0X0010204000000000ULL) | 0X07EFDF8000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0800000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 4;
		move.flipped |= (0X0800000000000000ULL - (0X1000000000000000ULL>>s)) & 0X0010204000000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0300000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0800000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 5;
		move.flipped |= 0X0800000000000000ULL - (0X0800000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0XE000000000000000ULL;
	r = (discs_opponent + 0X1000000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0XF000000000000000ULL;
		
		s = 3 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0800000000000000ULL;
	move.position = E1;
	
	return true;

}

bool RXBitBoard::generate_move_F1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X03CCD1127F12F62DULL, 0X0C2CF1A1C4AD6D13ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X80612B4ABCCBF81CULL, 0XFDF6ED6B9B25014DULL, 0X326C9D13A3CAF8B6ULL, 0X6237BBA811990E7AULL, 0X3B45F5AD1FE8C150ULL, 0X630404288D3022A8ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X744ED952B2CF378BULL, 0XC8A35AA248FF5A8AULL, 0XC6EDBC65A08FA5C6ULL, 0X6801B27E08B97FD7ULL};
	static const unsigned long long HASH__W[] = { 0, 0XEFC04AC861121F0FULL, 0X2BB37AD716CE843CULL, 0X7BA73859C685FF9AULL, 0X1132836D542F70D6ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000040404040404ULL;
	opp_discs = (discs_opponent & 0X0004040404040400ULL) | 0X03FBFBFBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0400000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 13;
		move.flipped |= (0X0400000000000000ULL - (0X0008000000000000ULL>>s)) & 0X0004040404040400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {
		move.flipped |= 0X0002000000000000ULL;
		move.hash_code ^= 0X3A79E438A1B1438DULL;
	}

	/* direction SW */
	my_discs = discs_player & 0X0000102040800000ULL;
	opp_discs = (discs_opponent & 0X0008102040000000ULL) | 0X03F7EFDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0400000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 5;
		move.flipped |= (0X0400000000000000ULL - (0X0800000000000000ULL>>s)) & 0X0008102040000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0200000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {
		move.flipped |= 0X0200000000000000ULL;
		move.hash_code ^= 0X522E701B1DC74CD1ULL;
	}

	/* direction _W */
	my_discs = discs_player & 0XF000000000000000ULL;
	r = (discs_opponent + 0X0800000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0XF800000000000000ULL;
		
		s = 4 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0400000000000000ULL;
	move.position = F1;
	
	return true;

}

bool RXBitBoard::generate_move_G1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X9F8AA3178F2B1394ULL, 0XCDA4D30C92EC5F45ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X80612B4ABCCBF81CULL, 0X2C78ABC1DCE4F374ULL, 0XF8052B4F56B62B68ULL, 0X069C91451E5A9B28ULL, 0XA1C30135D06CFD62ULL};
	static const unsigned long long HASH__W[] = { 0, 0X0FE020B3BBBF9B3EULL, 0XE0206A7BDAAD8431ULL, 0X24535A64AD711F02ULL, 0X744718EA7D3A64A4ULL, 0X1ED2A3DEEF90EBE8ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X3A79E438A1B1438DULL, 0X983EDE5F516FC884ULL, 0XD61C307E5A8D6D50ULL, 0XDBA4081F252232ADULL, 0XCD1CCA2A2F6BDCF1ULL, 0X05376CC0BC087274ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SW */
	my_discs = discs_player & 0X0000081020408000ULL;
	opp_discs = (discs_opponent & 0X0004081020400000ULL) | 0X01FBF7EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0200000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 6;
		move.flipped |= (0X0200000000000000ULL - (0X0400000000000000ULL>>s)) & 0X0004081020400000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0XF800000000000000ULL;
	r = (discs_opponent + 0X0400000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0XFC00000000000000ULL;
		
		s = 5 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000020202020202ULL;
	opp_discs = (discs_opponent & 0X0002020202020200ULL) | 0X01FDFDFDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0200000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 14;
		move.flipped |= (0X0200000000000000ULL - (0X0004000000000000ULL>>s)) & 0X0002020202020200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0200000000000000ULL;
	move.position = G1;
	
	return true;

}

bool RXBitBoard::generate_move_H1(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XBA0543A47E6FF2A9ULL, 0XA96D02C2645A0456ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X3A79E438A1B1438DULL, 0X47EE2219865FBADCULL, 0X1FE2E27866797F9CULL, 0XC760EFC335CB4AB5ULL, 0XE6812FE252E06F2AULL, 0X968640CDE7AE40ABULL};
	static const unsigned long long HASH__W[] = { 0, 0X522E701B1DC74CD1ULL, 0X5DCE50A8A678D7EFULL, 0XB20E1A60C76AC8E0ULL, 0X767D2A7FB0B653D3ULL, 0X266968F160FD2875ULL, 0X4CFCD3C5F257A739ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X674E786602C3A2D5ULL, 0X790208DBCBA6BFFFULL, 0X1A221F3DC929414FULL, 0XBD7B71C823853507ULL, 0X78EA37001B656326ULL, 0X481C17F2DF6E9F42ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SW */
	my_discs = discs_player & 0X0000040810204080ULL;
	opp_discs = (discs_opponent & 0X0002040810204000ULL) | 0X00FDFBF7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0100000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 7;
		move.flipped |= (0X0100000000000000ULL - (0X0200000000000000ULL>>s)) & 0X0002040810204000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0XFC00000000000000ULL;
	r = (discs_opponent + 0X0200000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0XFE00000000000000ULL;
		
		s = 6 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000010101010101ULL;
	opp_discs = (discs_opponent & 0X0001010101010100ULL) | 0X00FEFEFEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0100000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 15;
		move.flipped |= (0X0100000000000000ULL - (0X0002000000000000ULL>>s)) & 0X0001010101010100ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0100000000000000ULL;
	move.position = H1;
	
	return true;

}

bool RXBitBoard::generate_move_A2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X60DE7E0E3A76FDF0ULL, 0X4397F9C76A4D8E62ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XDDD21FEA14003A03ULL, 0XD39CF92DFC70C54FULL, 0X0B1EF496AFC2F066ULL, 0XFA870C28DC99B3EAULL, 0XA2C6FDAD4E415012ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X1C470CC72A6B9788ULL, 0X19A07DF108BF7451ULL, 0X6D1DD863A557D13AULL, 0X46C7A0B9A9EF7C67ULL, 0XF0505E07E46309C3ULL};
	static const unsigned long long HASH__E[] = { 0, 0X41739819832B7B0BULL, 0X5B1301E8F88FBFAFULL, 0X83D55C6E87907A03ULL, 0XF79B853C355F4D88ULL, 0X77FAAE768994B594ULL, 0X4D834A4E2825F619ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000002010080402ULL;
	opp_discs = (discs_opponent & 0X0000402010080400ULL) | 0X007FBFDFEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0080000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 17;
		move.flipped |= (0X0080000000000000ULL - (0X0000800000000000ULL>>s)) & 0X0000402010080400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000008080808080ULL;
	opp_discs = (discs_opponent & 0X0000808080808000ULL) | 0X007F7F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0080000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 16;
		move.flipped |= (0X0080000000000000ULL - (0X0001000000000000ULL>>s)) & 0X0000808080808000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X003F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0080000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 9;
		move.flipped |= 0X0080000000000000ULL - (0X0080000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0080000000000000ULL;
	move.position = A2;
	
	return true;

}

bool RXBitBoard::generate_move_B2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X668131FA5C735273ULL, 0X27F2A9E3DF582978ULL};
	static const unsigned long long HASH_SE[] = { 0, 0X140C7331AE03B6DBULL, 0XC071F3BF24516EC7ULL, 0X0E00C1D99E777F7BULL, 0X57728FDC9006B051ULL, 0X9F59293603651ED4ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XDDD21FEA14003A03ULL, 0X99FE99870F818DB3ULL, 0X3712979CA7B757A2ULL, 0X904D07EC698131E8ULL, 0XE04A68C3DCCF1E69ULL};
	static const unsigned long long HASH__E[] = { 0, 0X1A6099F17BA4C4A4ULL, 0XC2A6C47704BB0108ULL, 0XB6E81D25B6743683ULL, 0X3689366F0ABFCE9FULL, 0X0CF0D257AB0E8D12ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000001008040201ULL;
	opp_discs = (discs_opponent & 0X0000201008040200ULL) | 0X003FDFEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0040000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 18;
		move.flipped |= (0X0040000000000000ULL - (0X0000400000000000ULL>>s)) & 0X0000201008040200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000004040404040ULL;
	opp_discs = (discs_opponent & 0X0000404040404000ULL) | 0X003FBFBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0040000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 17;
		move.flipped |= (0X0040000000000000ULL - (0X0000800000000000ULL>>s)) & 0X0000404040404000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X001F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0040000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 10;
		move.flipped |= 0X0040000000000000ULL - (0X0040000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0040000000000000ULL;
	move.position = B2;
	
	return true;

}

bool RXBitBoard::generate_move_C2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X96F29C5A9B6FD15EULL, 0X8C9205ABE0CB15FAULL};
	static const unsigned long long HASH_S_[] = { 0, 0X140C7331AE03B6DBULL, 0X1A4295F646734997ULL, 0XE4DB2FFC0E9FF9D7ULL, 0XC53AEFDD69B4DC48ULL, 0XD92667AE51FF675DULL};
	static const unsigned long long HASH_SE[] = { 0, 0XBCED83F0FA306D01ULL, 0XE4E143911A16A841ULL, 0XB4BA652AA8455E8DULL, 0XA202A71FA20CB0D1ULL};
	static const unsigned long long HASH__E[] = { 0, 0XD8C65D867F1FC5ACULL, 0XAC8884D4CDD0F227ULL, 0X2CE9AF9E711B0A3BULL, 0X16904BA6D0AA49B6ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000002020202020ULL;
	opp_discs = (discs_opponent & 0X0000202020202000ULL) | 0X001FDFDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0020000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 18;
		move.flipped |= (0X0020000000000000ULL - (0X0000400000000000ULL>>s)) & 0X0000202020202000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000804020100ULL;
	opp_discs = (discs_opponent & 0X0000100804020000ULL) | 0X001FEFF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0020000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 19;
		move.flipped |= (0X0020000000000000ULL - (0X0000200000000000ULL>>s)) & 0X0000100804020000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {
		move.flipped |= 0X0000400000000000ULL;
		move.hash_code ^= 0XDDD21FEA14003A03ULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X000F000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0020000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 11;
		move.flipped |= 0X0020000000000000ULL - (0X0020000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X0080000000000000ULL) != 0)) {
		move.flipped |= 0X0040000000000000ULL;
		move.hash_code ^= 0X41739819832B7B0BULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0020000000000000ULL;
	move.position = C2;
	
	return true;

}

bool RXBitBoard::generate_move_D2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X619F1FAEC1E82DE0ULL, 0XB9594228BEF7E84CULL};
	static const unsigned long long HASH_S_[] = { 0, 0XBCED83F0FA306D01ULL, 0X6890037E7062B51DULL, 0XB0120EC523D08034ULL, 0X68825465ECA5A4D7ULL, 0XF809971C232C71D3ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XAC19808B602F0B68ULL, 0X6383F0F358C0F293ULL, 0X6E3BC892276FAD6EULL};
	static const unsigned long long HASH_SW[] = { 0, 0X140C7331AE03B6DBULL, 0X5020F55CB582016BULL};
	static const unsigned long long HASH__E[] = { 0, 0X744ED952B2CF378BULL, 0XF42FF2180E04CF97ULL, 0XCE561620AFB58C1AULL};
	static const unsigned long long HASH__W[] = { 0, 0X1A6099F17BA4C4A4ULL, 0X5B1301E8F88FBFAFULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000001010101010ULL;
	opp_discs = (discs_opponent & 0X0000101010101000ULL) | 0X000FEFEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 19;
		move.flipped |= (0X0010000000000000ULL - (0X0000200000000000ULL>>s)) & 0X0000101010101000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000402010000ULL;
	opp_discs = (discs_opponent & 0X0000080402000000ULL) | 0X000FF7FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 20;
		move.flipped |= (0X0010000000000000ULL - (0X0000100000000000ULL>>s)) & 0X0000080402000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000004080000000ULL;
	opp_discs = (discs_opponent & 0X0000204000000000ULL) | 0X000FDF8000000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0010000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 11;
		move.flipped |= (0X0010000000000000ULL - (0X0020000000000000ULL>>s)) & 0X0000204000000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0007000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0010000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 12;
		move.flipped |= 0X0010000000000000ULL - (0X0010000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00C0000000000000ULL;
	r = (discs_opponent + 0X0020000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00E0000000000000ULL;
		
		s = 10 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0010000000000000ULL;
	move.position = D2;
	
	return true;

}

bool RXBitBoard::generate_move_E2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X0A1AA93994AA5A9EULL, 0X7E54706B26656D15ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XAC19808B602F0B68ULL, 0XF41540EA8009CE28ULL, 0X3A64728C3A2FDF94ULL, 0XCBFD8A3249749C18ULL, 0XE4138885CD322638ULL};
	static const unsigned long long HASH_SE[] = { 0, 0X7D97C62127EEF951ULL, 0X33B528002C0C5C85ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XBCED83F0FA306D01ULL, 0XB2A365371240924DULL, 0X1C4F6B2CBA76485CULL};
	static const unsigned long long HASH__E[] = { 0, 0X80612B4ABCCBF81CULL, 0XBA18CF721D7ABB91ULL};
	static const unsigned long long HASH__W[] = { 0, 0XD8C65D867F1FC5ACULL, 0XC2A6C47704BB0108ULL, 0X83D55C6E87907A03ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000000808080808ULL;
	opp_discs = (discs_opponent & 0X0000080808080800ULL) | 0X0007F7F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 20;
		move.flipped |= (0X0008000000000000ULL - (0X0000100000000000ULL>>s)) & 0X0000080808080800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000201000000ULL;
	opp_discs = (discs_opponent & 0X0000040200000000ULL) | 0X0007FBFC00000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 21;
		move.flipped |= (0X0008000000000000ULL - (0X0000080000000000ULL>>s)) & 0X0000040200000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000002040800000ULL;
	opp_discs = (discs_opponent & 0X0000102040000000ULL) | 0X0007EFDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0008000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 12;
		move.flipped |= (0X0008000000000000ULL - (0X0010000000000000ULL>>s)) & 0X0000102040000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0003000000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0008000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 13;
		move.flipped |= 0X0008000000000000ULL - (0X0008000000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00E0000000000000ULL;
	r = (discs_opponent + 0X0010000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00F0000000000000ULL;
		
		s = 11 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0008000000000000ULL;
	move.position = E2;
	
	return true;

}

bool RXBitBoard::generate_move_F2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X0D521A9B644685DEULL, 0X8D3331D1D88D7DC2ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X7D97C62127EEF951ULL, 0XB20DB6591F0100AAULL, 0XE25690E2AD52F666ULL, 0XBB24DEE7A323394CULL, 0XE3652F6231FBDAB4ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XAC19808B602F0B68ULL, 0X78640005EA7DD374ULL, 0X86FDBA0FA2916334ULL, 0X21A22A7F6CA7057EULL};
	static const unsigned long long HASH__W[] = { 0, 0X744ED952B2CF378BULL, 0XAC8884D4CDD0F227ULL, 0XB6E81D25B6743683ULL, 0XF79B853C355F4D88ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction S */
	my_discs = discs_player & 0X0000000404040404ULL;
	opp_discs = (discs_opponent & 0X0000040404040400ULL) | 0X0003FBFBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0004000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 21;
		move.flipped |= (0X0004000000000000ULL - (0X0000080000000000ULL>>s)) & 0X0000040404040400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction SE */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {
		move.flipped |= 0X0000020000000000ULL;
		move.hash_code ^= 0XA2473A67F0DE8B09ULL;
	}

	/* direction SW */
	my_discs = discs_player & 0X0000001020408000ULL;
	opp_discs = (discs_opponent & 0X0000081020400000ULL) | 0X0003F7EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0004000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 13;
		move.flipped |= (0X0004000000000000ULL - (0X0008000000000000ULL>>s)) & 0X0000081020400000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0001000000000000ULL) != 0)) {
		move.flipped |= 0X0002000000000000ULL;
		move.hash_code ^= 0X3A79E438A1B1438DULL;
	}

	/* direction _W */
	my_discs = discs_player & 0X00F0000000000000ULL;
	r = (discs_opponent + 0X0008000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00F8000000000000ULL;
		
		s = 12 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0004000000000000ULL;
	move.position = F2;
	
	return true;

}

bool RXBitBoard::generate_move_G2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X73580BBFB1F518E3ULL, 0X4921EF8710445B6EULL};
	static const unsigned long long HASH_SW[] = { 0, 0X7D97C62127EEF951ULL, 0X259B0640C7C83C11ULL, 0XFD190BFB947A0938ULL, 0XDCF8CBDAF3512CA7ULL, 0XACFFA4F5461F0326ULL};
	static const unsigned long long HASH__W[] = { 0, 0X80612B4ABCCBF81CULL, 0XF42FF2180E04CF97ULL, 0X2CE9AF9E711B0A3BULL, 0X3689366F0ABFCE9FULL, 0X77FAAE768994B594ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XA2473A67F0DE8B09ULL, 0XEC65D446FB3C2EDDULL, 0XE1DDEC2784937120ULL, 0XF7652E128EDA9F7CULL, 0X3F4E88F81DB931F9ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SW */
	my_discs = discs_player & 0X0000000810204080ULL;
	opp_discs = (discs_opponent & 0X0000040810204000ULL) | 0X0001FBF7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0002000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 14;
		move.flipped |= (0X0002000000000000ULL - (0X0004000000000000ULL>>s)) & 0X0000040810204000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00F8000000000000ULL;
	r = (discs_opponent + 0X0004000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00FC000000000000ULL;
		
		s = 13 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000202020202ULL;
	opp_discs = (discs_opponent & 0X0000020202020200ULL) | 0X0001FDFDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0002000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 22;
		move.flipped |= (0X0002000000000000ULL - (0X0000040000000000ULL>>s)) & 0X0000020202020200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0002000000000000ULL;
	move.position = G2;
	
	return true;

}

bool RXBitBoard::generate_move_H2(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XB8844A364A8FD77AULL, 0XDFCA3250484C75AFULL};
	static const unsigned long long HASH_SW[] = { 0, 0XA2473A67F0DE8B09ULL, 0X6DDD4A1FC83172F2ULL, 0XA3AC78797217634EULL, 0X7B3C22D9BD6247ADULL, 0X6720AAAA8529FCB8ULL};
	static const unsigned long long HASH__W[] = { 0, 0X3A79E438A1B1438DULL, 0XBA18CF721D7ABB91ULL, 0XCE561620AFB58C1AULL, 0X16904BA6D0AA49B6ULL, 0X0CF0D257AB0E8D12ULL, 0X4D834A4E2825F619ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X1E4C70BDC9651D2AULL, 0X7D6C675BCBEAE39AULL, 0XDA3509AE214697D2ULL, 0X1FA44F6619A6C1F3ULL, 0X2F526F94DDAD3D97ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SW */
	my_discs = discs_player & 0X0000000408102040ULL;
	opp_discs = (discs_opponent & 0X0000020408102000ULL) | 0X0000FDFBF7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0001000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 15;
		move.flipped |= (0X0001000000000000ULL - (0X0002000000000000ULL>>s)) & 0X0000020408102000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00FC000000000000ULL;
	r = (discs_opponent + 0X0002000000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00FE000000000000ULL;
		
		s = 14 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000101010101ULL;
	opp_discs = (discs_opponent & 0X0000010101010100ULL) | 0X0000FEFEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0001000000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 23;
		move.flipped |= (0X0001000000000000ULL - (0X0000020000000000ULL>>s)) & 0X0000010101010100ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0001000000000000ULL;
	move.position = H2;
	
	return true;

}

bool RXBitBoard::generate_move_A3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X457499DA8421ACB2ULL, 0X5933951DAE4A3B3AULL};
	static const unsigned long long HASH__E[] = { 0, 0XDDD21FEA14003A03ULL, 0XC9DE6CDBBA038CD8ULL, 0X7533EF2B4033E1D9ULL, 0XD92A6FA0201CEAB1ULL, 0XA4BDA98107F213E0ULL, 0X06FA93E6F72C98E9ULL};
	static const unsigned long long HASH_SE[] = { 0, 0X442C866D1B81B7B0ULL, 0XBAB53C67536D07F0ULL, 0X622566C79C182313ULL, 0X4DCB6470185E9933ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X05E7713622D4E3D9ULL, 0X715AD4A48F3C46B2ULL, 0X5A80AC7E8384EBEFULL, 0XEC1752C0CE089E4BULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X00003F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000800000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 17;
		move.flipped |= 0X0000800000000000ULL - (0X0000800000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {
		move.flipped |= 0X0040000000000000ULL;
		move.hash_code ^= 0X41739819832B7B0BULL;
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000020100804ULL;
	opp_discs = (discs_opponent & 0X0000004020100800ULL) | 0X00007FBFDFEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000800000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 25;
		move.flipped |= (0X0000800000000000ULL - (0X0000008000000000ULL>>s)) & 0X0000004020100800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction N_ */
	if(((discs_opponent & 0X0080000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {
		move.flipped |= 0X0080000000000000ULL;
		move.hash_code ^= 0X234987C9503B7392ULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000080808080ULL;
	opp_discs = (discs_opponent & 0X0000008080808000ULL) | 0X00007F7F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000800000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 24;
		move.flipped |= (0X0000800000000000ULL - (0X0000010000000000ULL>>s)) & 0X0000008080808000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000800000000000ULL;
	move.position = A3;
	
	return true;

}

bool RXBitBoard::generate_move_B3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X90B88D84F01528F6ULL, 0X4D6A926EE41512F5ULL};
	static const unsigned long long HASH__E[] = { 0, 0X140C7331AE03B6DBULL, 0XA8E1F0C15433DBDAULL, 0X04F8704A341CD0B2ULL, 0X796FB66B13F229E3ULL, 0XDB288C0CE32CA2EAULL};
	static const unsigned long long HASH_SE[] = { 0, 0X0E4EE6C7E870FF4CULL, 0XD6CCEB7CBBC2CA65ULL, 0X275513C2C89989E9ULL, 0X7F14E2475A416A11ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X442C866D1B81B7B0ULL, 0XEAC08876B3B76DA1ULL, 0X4D9F18067D810BEBULL, 0X3D987729C8CF246AULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X00001F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000400000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 18;
		move.flipped |= 0X0000400000000000ULL - (0X0000400000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {
		move.flipped |= 0X0020000000000000ULL;
		move.hash_code ^= 0X1A6099F17BA4C4A4ULL;
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000010080402ULL;
	opp_discs = (discs_opponent & 0X0000002010080400ULL) | 0X00003FDFEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000400000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 26;
		move.flipped |= (0X0000400000000000ULL - (0X0000004000000000ULL>>s)) & 0X0000002010080400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction N_ */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X4000000000000000ULL) != 0)) {
		move.flipped |= 0X0040000000000000ULL;
		move.hash_code ^= 0X41739819832B7B0BULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000040404040ULL;
	opp_discs = (discs_opponent & 0X0000004040404000ULL) | 0X00003FBFBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000400000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 25;
		move.flipped |= (0X0000400000000000ULL - (0X0000008000000000ULL>>s)) & 0X0000004040404000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000400000000000ULL;
	move.position = B3;
	
	return true;

}

bool RXBitBoard::generate_move_C3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X024BD24533582E8BULL, 0X1647A1749D5B9850ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XD47D808E8A52D81CULL, 0X1A0CB2E83074C9A0ULL, 0X437EFCED3E05068AULL, 0X8B555A07AD66A80FULL};
	static const unsigned long long HASH_S_[] = { 0, 0X0E4EE6C7E870FF4CULL, 0XF0D75CCDA09C4F0CULL, 0XD1369CECC7B76A93ULL, 0XCD2A149FFFFCD186ULL};
	static const unsigned long long HASH__E[] = { 0, 0XBCED83F0FA306D01ULL, 0X10F4037B9A1F6669ULL, 0X6D63C55ABDF19F38ULL, 0XCF24FF3D4D2F1431ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000000008040201ULL;
	opp_discs = (discs_opponent & 0X0000001008040200ULL) | 0X00001FEFF7FBFC00ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000200000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 27;
		move.flipped |= (0X0000200000000000ULL - (0X0000002000000000ULL>>s)) & 0X0000001008040200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000020202020ULL;
	opp_discs = (discs_opponent & 0X0000002020202000ULL) | 0X00001FDFDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000200000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 26;
		move.flipped |= (0X0000200000000000ULL - (0X0000004000000000ULL>>s)) & 0X0000002020202000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X00000F0000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000200000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 19;
		move.flipped |= 0X0000200000000000ULL - (0X0000200000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {
		move.flipped |= 0X0010000000000000ULL;
		move.hash_code ^= 0XD8C65D867F1FC5ACULL;
	}

	/* direction N_ */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {
		move.flipped |= 0X0020000000000000ULL;
		move.hash_code ^= 0X1A6099F17BA4C4A4ULL;
	}

	/* direction NW */
	if(((discs_opponent & 0X0040000000000000ULL) != 0)  && ((discs_player & 0X8000000000000000ULL) != 0)) {
		move.flipped |= 0X0040000000000000ULL;
		move.hash_code ^= 0X41739819832B7B0BULL;
	}

	/* direction SW */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {
		move.flipped |= 0X0000004000000000ULL;
		move.hash_code ^= 0X442C866D1B81B7B0ULL;
	}

	/* direction _W */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {
		move.flipped |= 0X0000400000000000ULL;
		move.hash_code ^= 0XDDD21FEA14003A03ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000200000000000ULL;
	move.position = C3;
	
	return true;

}

bool RXBitBoard::generate_move_D3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X76CC6FE07CF98A2CULL, 0XCA21EC1086C9E72DULL};
	static const unsigned long long HASH_SE[] = { 0, 0X580CC061E026C540ULL, 0X0857E6DA5275338CULL, 0X1EEF24EF583CDDD0ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XD47D808E8A52D81CULL, 0X0CFF8D35D9E0ED35ULL, 0XD46FD7951695C9D6ULL, 0X44E414ECD91C1CD2ULL};
	static const unsigned long long HASH__E[] = { 0, 0XAC19808B602F0B68ULL, 0XD18E46AA47C1F239ULL, 0X73C97CCDB71F7930ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X0E4EE6C7E870FF4CULL, 0XA0A2E8DC4046255DULL};
	static const unsigned long long HASH__W[] = { 0, 0X140C7331AE03B6DBULL, 0XC9DE6CDBBA038CD8ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000000004020100ULL;
	opp_discs = (discs_opponent & 0X0000000804020000ULL) | 0X00000FF7FBFC0000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 28;
		move.flipped |= (0X0000100000000000ULL - (0X0000001000000000ULL>>s)) & 0X0000000804020000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000010101010ULL;
	opp_discs = (discs_opponent & 0X0000001010101000ULL) | 0X00000FEFEFEFE000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 27;
		move.flipped |= (0X0000100000000000ULL - (0X0000002000000000ULL>>s)) & 0X0000001010101000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000070000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000100000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 20;
		move.flipped |= 0X0000100000000000ULL - (0X0000100000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {
		move.flipped |= 0X0008000000000000ULL;
		move.hash_code ^= 0X744ED952B2CF378BULL;
	}

	/* direction N_ */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {
		move.flipped |= 0X0010000000000000ULL;
		move.hash_code ^= 0XD8C65D867F1FC5ACULL;
	}

	/* direction NW */
	if(((discs_opponent & 0X0020000000000000ULL) != 0)  && ((discs_player & 0X4000000000000000ULL) != 0)) {
		move.flipped |= 0X0020000000000000ULL;
		move.hash_code ^= 0X1A6099F17BA4C4A4ULL;
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000040800000ULL;
	opp_discs = (discs_opponent & 0X0000002040000000ULL) | 0X00000FDF80000000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000100000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 19;
		move.flipped |= (0X0000100000000000ULL - (0X0000200000000000ULL>>s)) & 0X0000002040000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X0000C00000000000ULL;
	r = (discs_opponent + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000E00000000000ULL;
		
		s = 18 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000100000000000ULL;
	move.position = D3;
	
	return true;

}

bool RXBitBoard::generate_move_E3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XCD6BD259CC4531BBULL, 0X617252D2AC6A3AD3ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XCF9A707838EFF9FBULL, 0XC22248194740A606ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X580CC061E026C540ULL, 0X967DF2075A00D4FCULL, 0X67E40AB9295B9770ULL, 0X480A080EAD1D2D50ULL};
	static const unsigned long long HASH__E[] = { 0, 0X7D97C62127EEF951ULL, 0XDFD0FC46D7307258ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XD47D808E8A52D81CULL, 0X2AE43A84C2BE685CULL, 0X8DBBAAF40C880E16ULL};
	static const unsigned long long HASH__W[] = { 0, 0XBCED83F0FA306D01ULL, 0XA8E1F0C15433DBDAULL, 0X7533EF2B4033E1D9ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000000002010000ULL;
	opp_discs = (discs_opponent & 0X0000000402000000ULL) | 0X000007FBFC000000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 29;
		move.flipped |= (0X0000080000000000ULL - (0X0000000800000000ULL>>s)) & 0X0000000402000000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000008080808ULL;
	opp_discs = (discs_opponent & 0X0000000808080800ULL) | 0X000007F7F7F7F000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 28;
		move.flipped |= (0X0000080000000000ULL - (0X0000001000000000ULL>>s)) & 0X0000000808080800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000030000000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000080000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 21;
		move.flipped |= 0X0000080000000000ULL - (0X0000080000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0200000000000000ULL) != 0)) {
		move.flipped |= 0X0004000000000000ULL;
		move.hash_code ^= 0X80612B4ABCCBF81CULL;
	}

	/* direction N_ */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {
		move.flipped |= 0X0008000000000000ULL;
		move.hash_code ^= 0X744ED952B2CF378BULL;
	}

	/* direction NW */
	if(((discs_opponent & 0X0010000000000000ULL) != 0)  && ((discs_player & 0X2000000000000000ULL) != 0)) {
		move.flipped |= 0X0010000000000000ULL;
		move.hash_code ^= 0XD8C65D867F1FC5ACULL;
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000020408000ULL;
	opp_discs = (discs_opponent & 0X0000001020400000ULL) | 0X000007EFDF800000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000080000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 20;
		move.flipped |= (0X0000080000000000ULL - (0X0000100000000000ULL>>s)) & 0X0000001020400000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X0000E00000000000ULL;
	r = (discs_opponent + 0X0000100000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000F00000000000ULL;
		
		s = 19 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000080000000000ULL;
	move.position = E3;
	
	return true;

}

bool RXBitBoard::generate_move_F3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X3B588BDB6258EA64ULL, 0X46CF4DFA45B61335ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XCF9A707838EFF9FBULL, 0X9FC156C38ABC0F37ULL, 0XC6B318C684CDC01DULL, 0X9EF2E943161523E5ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X580CC061E026C540ULL, 0X808ECDDAB394F069ULL, 0XA16F0DFBD4BFD5F6ULL, 0XD16862D461F1FA77ULL};
	static const unsigned long long HASH__W[] = { 0, 0XAC19808B602F0B68ULL, 0X10F4037B9A1F6669ULL, 0X04F8704A341CD0B2ULL, 0XD92A6FA0201CEAB1ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {
		move.flipped |= 0X0000000200000000ULL;
		move.hash_code ^= 0X4E22EE210BE2A5D4ULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000004040404ULL;
	opp_discs = (discs_opponent & 0X0000000404040400ULL) | 0X000003FBFBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000040000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 29;
		move.flipped |= (0X0000040000000000ULL - (0X0000000800000000ULL>>s)) & 0X0000000404040400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {
		move.flipped |= 0X0000020000000000ULL;
		move.hash_code ^= 0XA2473A67F0DE8B09ULL;
	}

	/* direction NE */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {
		move.flipped |= 0X0002000000000000ULL;
		move.hash_code ^= 0X3A79E438A1B1438DULL;
	}

	/* direction N_ */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {
		move.flipped |= 0X0004000000000000ULL;
		move.hash_code ^= 0X80612B4ABCCBF81CULL;
	}

	/* direction NW */
	if(((discs_opponent & 0X0008000000000000ULL) != 0)  && ((discs_player & 0X1000000000000000ULL) != 0)) {
		move.flipped |= 0X0008000000000000ULL;
		move.hash_code ^= 0X744ED952B2CF378BULL;
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000010204080ULL;
	opp_discs = (discs_opponent & 0X0000000810204000ULL) | 0X000003F7EFDF8000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000040000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 21;
		move.flipped |= (0X0000040000000000ULL - (0X0000080000000000ULL>>s)) & 0X0000000810204000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X0000F00000000000ULL;
	r = (discs_opponent + 0X0000080000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000F80000000000ULL;
		
		s = 20 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000040000000000ULL;
	move.position = F3;
	
	return true;

}

bool RXBitBoard::generate_move_G3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X4302A6DC441AD82FULL, 0XE1459CBBB4C45326ULL};
	static const unsigned long long HASH__W[] = { 0, 0X7D97C62127EEF951ULL, 0XD18E46AA47C1F239ULL, 0X6D63C55ABDF19F38ULL, 0X796FB66B13F229E3ULL, 0XA4BDA98107F213E0ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XCF9A707838EFF9FBULL, 0X01EB421E82C9E847ULL, 0XD97B18BE4DBCCCA4ULL, 0XC56790CD75F777B1ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X4E22EE210BE2A5D4ULL, 0X439AD640744DFA29ULL, 0X552214757E041475ULL, 0X9D09B29FED67BAF0ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X0000F80000000000ULL;
	r = (discs_opponent + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000FC0000000000ULL;
		
		s = 21 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000008102040ULL;
	opp_discs = (discs_opponent & 0X0000000408102000ULL) | 0X000001FBF7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000020000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 22;
		move.flipped |= (0X0000020000000000ULL - (0X0000040000000000ULL>>s)) & 0X0000000408102000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0004000000000000ULL) != 0)  && ((discs_player & 0X0800000000000000ULL) != 0)) {
		move.flipped |= 0X0004000000000000ULL;
		move.hash_code ^= 0X80612B4ABCCBF81CULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000002020202ULL;
	opp_discs = (discs_opponent & 0X0000000202020200ULL) | 0X000001FDFDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000020000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 30;
		move.flipped |= (0X0000020000000000ULL - (0X0000000400000000ULL>>s)) & 0X0000000202020200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction N_ */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0200000000000000ULL) != 0)) {
		move.flipped |= 0X0002000000000000ULL;
		move.hash_code ^= 0X3A79E438A1B1438DULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000020000000000ULL;
	move.position = G3;
	
	return true;

}

bool RXBitBoard::generate_move_H3(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XB73929FE1D7104E6ULL, 0XA9755943D41419CCULL};
	static const unsigned long long HASH__W[] = { 0, 0XA2473A67F0DE8B09ULL, 0XDFD0FC46D7307258ULL, 0X73C97CCDB71F7930ULL, 0XCF24FF3D4D2F1431ULL, 0XDB288C0CE32CA2EAULL, 0X06FA93E6F72C98E9ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X4E22EE210BE2A5D4ULL, 0X1E79C89AB9B15318ULL, 0XEFE03024CAEA1094ULL, 0X7F6BF35D0563C590ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X632017E6028FFEB0ULL, 0XC4797913E8238AF8ULL, 0X01E83FDBD0C3DCD9ULL, 0X311E1F2914C820BDULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X0000FC0000000000ULL;
	r = (discs_opponent + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000FE0000000000ULL;
		
		s = 22 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000004081020ULL;
	opp_discs = (discs_opponent & 0X0000000204081000ULL) | 0X000000FDFBF7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000010000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 23;
		move.flipped |= (0X0000010000000000ULL - (0X0000020000000000ULL>>s)) & 0X0000000204081000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0002000000000000ULL) != 0)  && ((discs_player & 0X0400000000000000ULL) != 0)) {
		move.flipped |= 0X0002000000000000ULL;
		move.hash_code ^= 0X3A79E438A1B1438DULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000001010101ULL;
	opp_discs = (discs_opponent & 0X0000000101010100ULL) | 0X000000FEFEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000010000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 31;
		move.flipped |= (0X0000010000000000ULL - (0X0000000200000000ULL>>s)) & 0X0000000101010100ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction N_ */
	if(((discs_opponent & 0X0001000000000000ULL) != 0)  && ((discs_player & 0X0100000000000000ULL) != 0)) {
		move.flipped |= 0X0001000000000000ULL;
		move.hash_code ^= 0X674E786602C3A2D5ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000010000000000ULL;
	move.position = H3;
	
	return true;

}

bool RXBitBoard::generate_move_A4(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X43F10D75AF82EBDAULL, 0X46167C438D560803ULL};
	static const unsigned long long HASH__E[] = { 0, 0X442C866D1B81B7B0ULL, 0X4A6260AAF3F148FCULL, 0X9E1FE02479A390E0ULL, 0XC6132045998555A0ULL, 0X0989503DA16AAC5BULL, 0X47ABBE1CAA88098FULL};
	static const unsigned long long HASH_NE[] = { 0, 0XDDD21FEA14003A03ULL, 0XC7B2861B6FA4FEA7ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XAEEC0E1BA836DA11ULL, 0X8F0DCE3ACF1DFF8EULL, 0X1F860D4300942A8AULL};
	static const unsigned long long HASH_N_[] = { 0, 0X1C470CC72A6B9788ULL, 0X3F0E8B0E7A50E41AULL};
	static const unsigned long long HASH_S_[] = { 0, 0X74BDA592ADE8A56BULL, 0X5F67DD48A1500836ULL, 0XE9F023F6ECDC7D92ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X0000003F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000008000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 25;
		move.flipped |= 0X0000008000000000ULL - (0X0000008000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X1020000000000000ULL;
	opp_discs = (discs_opponent & 0X0020400000000000ULL) | 0X0FDF800000000000ULL;
	r = (opp_discs + 0X0000400000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020400000000000ULL;
		
		s = (24 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000201008ULL;
	opp_discs = (discs_opponent & 0X0000000040201000ULL) | 0X0000007FBFDFE000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000008000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 33;
		move.flipped |= (0X0000008000000000ULL - (0X0000000080000000ULL>>s)) & 0X0000000040201000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080000000000000ULL;
	opp_discs = (discs_opponent & 0X0080800000000000ULL) | 0X7F7F000000000000ULL;
	r = (opp_discs + 0X0000800000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0080800000000000ULL;
		
		s = (16 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000808080ULL;
	opp_discs = (discs_opponent & 0X0000000080808000ULL) | 0X0000007F7F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000008000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 32;
		move.flipped |= (0X0000008000000000ULL - (0X0000000100000000ULL>>s)) & 0X0000000080808000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000008000000000ULL;
	move.position = A4;
	
	return true;

}

bool RXBitBoard::generate_move_B4(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X7F57A1BC6CC0C6A5ULL, 0X3B7B27D177417115ULL};
	static const unsigned long long HASH__E[] = { 0, 0X0E4EE6C7E870FF4CULL, 0XDA33664962222750ULL, 0X823FA6288204E210ULL, 0X4DA5D650BAEB1BEBULL, 0X03873871B109BE3FULL};
	static const unsigned long long HASH_NE[] = { 0, 0X140C7331AE03B6DBULL, 0XCCCA2EB7D11C7377ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XFE99BA0A48ECB040ULL, 0X2609E0AA879994A3ULL, 0X09E7E21D03DF2E83ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XDDD21FEA14003A03ULL, 0X9CA187F3972B4108ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XAEEC0E1BA836DA11ULL, 0X09B39E6B6600BC5BULL, 0X79B4F144D34E93DAULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X0000001F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000004000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 26;
		move.flipped |= 0X0000004000000000ULL - (0X0000004000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0810000000000000ULL;
	opp_discs = (discs_opponent & 0X0010200000000000ULL) | 0X07EFC00000000000ULL;
	r = (opp_discs + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010200000000000ULL;
		
		s = (25 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000100804ULL;
	opp_discs = (discs_opponent & 0X0000000020100800ULL) | 0X0000003FDFEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000004000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 34;
		move.flipped |= (0X0000004000000000ULL - (0X0000000040000000ULL>>s)) & 0X0000000020100800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040000000000000ULL;
	opp_discs = (discs_opponent & 0X0040400000000000ULL) | 0X3FBF800000000000ULL;
	r = (opp_discs + 0X0000400000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040400000000000ULL;
		
		s = (17 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000404040ULL;
	opp_discs = (discs_opponent & 0X0000000040404000ULL) | 0X0000003FBFBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000004000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 33;
		move.flipped |= (0X0000004000000000ULL - (0X0000000080000000ULL>>s)) & 0X0000000040404000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000004000000000ULL;
	move.position = B4;
	
	return true;

}

bool RXBitBoard::generate_move_C4(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XFA4AAF1082BF8F7FULL, 0XF40449D76ACF7033ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XD8820DBB53B23529ULL, 0X291BF50520E976A5ULL, 0X715A0480B231955DULL};
	static const unsigned long long HASH_S_[] = { 0, 0XFE99BA0A48ECB040ULL, 0XDF787A2B2FC795DFULL, 0XC364F258178C2ECAULL};
	static const unsigned long long HASH__E[] = { 0, 0XD47D808E8A52D81CULL, 0X8C7140EF6A741D5CULL, 0X43EB3097529BE4A7ULL, 0X0DC9DEB659794173ULL};
	static const unsigned long long HASH_NE[] = { 0, 0XBCED83F0FA306D01ULL, 0XC8A35AA248FF5A8AULL};
	static const unsigned long long HASH_N_[] = { 0, 0X140C7331AE03B6DBULL, 0X0E6CEAC0D5A7727FULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000000000080402ULL;
	opp_discs = (discs_opponent & 0X0000000010080400ULL) | 0X0000001FEFF7F800ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000002000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 35;
		move.flipped |= (0X0000002000000000ULL - (0X0000000020000000ULL>>s)) & 0X0000000010080400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000202020ULL;
	opp_discs = (discs_opponent & 0X0000000020202000ULL) | 0X0000001FDFDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000002000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 34;
		move.flipped |= (0X0000002000000000ULL - (0X0000000040000000ULL>>s)) & 0X0000000020202000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000F00000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000002000000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 27;
		move.flipped |= 0X0000002000000000ULL - (0X0000002000000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0408000000000000ULL;
	opp_discs = (discs_opponent & 0X0008100000000000ULL) | 0X03F7E00000000000ULL;
	r = (opp_discs + 0X0000100000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008100000000000ULL;
		
		s = (26 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020000000000000ULL;
	opp_discs = (discs_opponent & 0X0020200000000000ULL) | 0X1FDFC00000000000ULL;
	r = (opp_discs + 0X0000200000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020200000000000ULL;
		
		s = (18 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0000400000000000ULL) != 0)  && ((discs_player & 0X0080000000000000ULL) != 0)) {
		move.flipped |= 0X0000400000000000ULL;
		move.hash_code ^= 0XDDD21FEA14003A03ULL;
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {
		move.flipped |= 0X0000000040000000ULL;
		move.hash_code ^= 0XAEEC0E1BA836DA11ULL;
	}

	/* direction _W */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {
		move.flipped |= 0X0000004000000000ULL;
		move.hash_code ^= 0X442C866D1B81B7B0ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000002000000000ULL;
	move.position = C4;
	
	return true;

}

bool RXBitBoard::generate_move_F4(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XAD14C7E539D51489ULL, 0X628EB79D013AED72ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X505B26BBB253F6CCULL, 0X092968BEBC2239E6ULL, 0X5168993B2EFADA1EULL};
	static const unsigned long long HASH_N_[] = { 0, 0X7D97C62127EEF951ULL, 0XFDF6ED6B9B25014DULL};
	static const unsigned long long HASH_NW[] = { 0, 0XAC19808B602F0B68ULL, 0X74DFDD0D1F30CEC4ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XCE713266BA2611BCULL, 0X16E168C67553355FULL, 0X0AFDE0B54D188E4AULL};
	static const unsigned long long HASH__W[] = { 0, 0X580CC061E026C540ULL, 0X8C7140EF6A741D5CULL, 0X823FA6288204E210ULL, 0XC6132045998555A0ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {
		move.flipped |= 0X0000000002000000ULL;
		move.hash_code ^= 0XDB838617FAF5FFDULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000040404ULL;
	opp_discs = (discs_opponent & 0X0000000004040400ULL) | 0X00000003FBFBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000400000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 37;
		move.flipped |= (0X0000000400000000ULL - (0X0000000008000000ULL>>s)) & 0X0000000004040400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {
		move.flipped |= 0X0000000200000000ULL;
		move.hash_code ^= 0X4E22EE210BE2A5D4ULL;
	}

	/* direction NE */
	if(((discs_opponent & 0X0000020000000000ULL) != 0)  && ((discs_player & 0X0001000000000000ULL) != 0)) {
		move.flipped |= 0X0000020000000000ULL;
		move.hash_code ^= 0XA2473A67F0DE8B09ULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404000000000000ULL;
	opp_discs = (discs_opponent & 0X0004040000000000ULL) | 0X03FBF80000000000ULL;
	r = (opp_discs + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004040000000000ULL;
		
		s = (21 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X2010000000000000ULL;
	opp_discs = (discs_opponent & 0X0010080000000000ULL) | 0X1FEFF00000000000ULL;
	r = (opp_discs + 0X0000080000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010080000000000ULL;
		
		s = (20 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000102040ULL;
	opp_discs = (discs_opponent & 0X0000000008102000ULL) | 0X00000003F7EFC000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000400000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 29;
		move.flipped |= (0X0000000400000000ULL - (0X0000000800000000ULL>>s)) & 0X0000000008102000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X000000F000000000ULL;
	r = (discs_opponent + 0X0000000800000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000F800000000ULL;
		
		s = 28 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000400000000ULL;
	move.position = F4;
	
	return true;

}

bool RXBitBoard::generate_move_G4(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XBBD04C6669A079B3ULL, 0XF5F2A2476242DC67ULL};
	static const unsigned long long HASH__W[] = { 0, 0XCF9A707838EFF9FBULL, 0X9796B019D8C93CBBULL, 0X43EB3097529BE4A7ULL, 0X4DA5D650BAEB1BEBULL, 0X0989503DA16AAC5BULL};
	static const unsigned long long HASH_SW[] = { 0, 0X505B26BBB253F6CCULL, 0XA1C2DE05C108B540ULL, 0X31491D7C0E816044ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X7D97C62127EEF951ULL, 0X09D91F739521CEDAULL};
	static const unsigned long long HASH_S_[] = { 0, 0X0DB838617FAF5FFDULL, 0X1B00FA5475E6B1A1ULL, 0XD32B5CBEE6851F24ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XA2473A67F0DE8B09ULL, 0X983EDE5F516FC884ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X000000F800000000ULL;
	r = (discs_opponent + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000FC00000000ULL;
		
		s = 29 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000081020ULL;
	opp_discs = (discs_opponent & 0X0000000004081000ULL) | 0X00000001FBF7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000200000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 30;
		move.flipped |= (0X0000000200000000ULL - (0X0000000400000000ULL>>s)) & 0X0000000004081000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X1008000000000000ULL;
	opp_discs = (discs_opponent & 0X0008040000000000ULL) | 0X0FF7F80000000000ULL;
	r = (opp_discs + 0X0000040000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008040000000000ULL;
		
		s = (21 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000020202ULL;
	opp_discs = (discs_opponent & 0X0000000002020200ULL) | 0X00000001FDFDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000200000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 38;
		move.flipped |= (0X0000000200000000ULL - (0X0000000004000000ULL>>s)) & 0X0000000002020200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202000000000000ULL;
	opp_discs = (discs_opponent & 0X0002020000000000ULL) | 0X01FDFC0000000000ULL;
	r = (opp_discs + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002020000000000ULL;
		
		s = (22 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000200000000ULL;
	move.position = G4;
	
	return true;

}

bool RXBitBoard::generate_move_H4(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X3337CBDC99AA5E0AULL, 0X5017DC3A9B25A0BAULL};
	static const unsigned long long HASH__W[] = { 0, 0X4E22EE210BE2A5D4ULL, 0X81B89E59330D5C2FULL, 0XD9B45E38D32B996FULL, 0X0DC9DEB659794173ULL, 0X03873871B109BE3FULL, 0X47ABBE1CAA88098FULL};
	static const unsigned long long HASH_SW[] = { 0, 0X0DB838617FAF5FFDULL, 0X54CA766471DE90D7ULL, 0X7B2474D3F5982AF7ULL};
	static const unsigned long long HASH_NW[] = { 0, 0XA2473A67F0DE8B09ULL, 0X2226112D4C157315ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XA7596EF5EAAC7448ULL, 0X62C8283DD24C2269ULL, 0X523E08CF1647DE0DULL};
	static const unsigned long long HASH_N_[] = { 0, 0X1E4C70BDC9651D2AULL, 0X790208DBCBA6BFFFULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X000000FC00000000ULL;
	r = (discs_opponent + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000FE00000000ULL;
		
		s = 30 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000040810ULL;
	opp_discs = (discs_opponent & 0X0000000002040800ULL) | 0X00000000FDFBF000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000100000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 31;
		move.flipped |= (0X0000000100000000ULL - (0X0000000200000000ULL>>s)) & 0X0000000002040800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0804000000000000ULL;
	opp_discs = (discs_opponent & 0X0004020000000000ULL) | 0X07FBFC0000000000ULL;
	r = (opp_discs + 0X0000020000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004020000000000ULL;
		
		s = (22 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000010101ULL;
	opp_discs = (discs_opponent & 0X0000000001010100ULL) | 0X00000000FEFEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000100000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 39;
		move.flipped |= (0X0000000100000000ULL - (0X0000000002000000ULL>>s)) & 0X0000000001010100ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101000000000000ULL;
	opp_discs = (discs_opponent & 0X0001010000000000ULL) | 0X00FEFE0000000000ULL;
	r = (opp_discs + 0X0000010000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0001010000000000ULL;
		
		s = (23 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000100000000ULL;
	move.position = H4;
	
	return true;

}

bool RXBitBoard::generate_move_A5(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X2701859A5F3AF238ULL, 0X53BC2008F2D25753ULL};
	static const unsigned long long HASH__E[] = { 0, 0XAEEC0E1BA836DA11ULL, 0X5075B411E0DA6A51ULL, 0X88F7B9AAB3685F78ULL, 0X46868BCC094E4EC4ULL, 0X16DDAD77BB1DB808ULL, 0X1B659516C4B2E7F5ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X442C866D1B81B7B0ULL, 0X5020F55CB582016BULL, 0X88E6A8DACA9DC4C7ULL};
	static const unsigned long long HASH_SE[] = { 0, 0XA75F9070CE36664AULL, 0XBB431803F67DDD5FULL};
	static const unsigned long long HASH_N_[] = { 0, 0X05E7713622D4E3D9ULL, 0X19A07DF108BF7451ULL, 0X3AE9FA38588407C3ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X2BDA78DA0CB8AD5DULL, 0X9D4D86644134D8F9ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X000000003F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000080000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 33;
		move.flipped |= 0X0000000080000000ULL - (0X0000000080000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0810200000000000ULL;
	opp_discs = (discs_opponent & 0X0010204000000000ULL) | 0X07EFDF8000000000ULL;
	r = (opp_discs + 0X0000004000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010204000000000ULL;
		
		s = (32 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000002010ULL;
	opp_discs = (discs_opponent & 0X0000000000402000ULL) | 0X000000007FBFC000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000080000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 41;
		move.flipped |= (0X0000000080000000ULL - (0X0000000000800000ULL>>s)) & 0X0000000000402000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080800000000000ULL;
	opp_discs = (discs_opponent & 0X0080808000000000ULL) | 0X7F7F7F0000000000ULL;
	r = (opp_discs + 0X0000008000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0080808000000000ULL;
		
		s = (24 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000008080ULL;
	opp_discs = (discs_opponent & 0X0000000000808000ULL) | 0X000000007F7F0000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000080000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 40;
		move.flipped |= (0X0000000080000000ULL - (0X0000000001000000ULL>>s)) & 0X0000000000808000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000080000000ULL;
	move.position = A5;
	
	return true;

}

bool RXBitBoard::generate_move_B5(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XB04308D12EEC231FULL, 0X1EAF06CA86DAF90EULL};
	static const unsigned long long HASH__E[] = { 0, 0XFE99BA0A48ECB040ULL, 0X261BB7B11B5E8569ULL, 0XE86A85D7A17894D5ULL, 0XB831A36C132B6219ULL, 0XB5899B0D6C843DE4ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X0E4EE6C7E870FF4CULL, 0XB2A365371240924DULL, 0XC6EDBC65A08FA5C6ULL};
	static const unsigned long long HASH_SE[] = { 0, 0X21E1C021672B259FULL, 0XB16A0358A8A2F09BULL};
	static const unsigned long long HASH_N_[] = { 0, 0X442C866D1B81B7B0ULL, 0X99FE99870F818DB3ULL, 0XD88D019E8CAAF6B8ULL};
	static const unsigned long long HASH_S_[] = { 0, 0XA75F9070CE36664AULL, 0XD758FF5F7B7849CBULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X000000001F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000040000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 34;
		move.flipped |= 0X0000000040000000ULL - (0X0000000040000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0408100000000000ULL;
	opp_discs = (discs_opponent & 0X0008102000000000ULL) | 0X03F7EFC000000000ULL;
	r = (opp_discs + 0X0000002000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008102000000000ULL;
		
		s = (33 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction SE */
	my_discs = discs_player & 0X0000000000001008ULL;
	opp_discs = (discs_opponent & 0X0000000000201000ULL) | 0X000000003FDFE000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000040000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 42;
		move.flipped |= (0X0000000040000000ULL - (0X0000000000400000ULL>>s)) & 0X0000000000201000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040400000000000ULL;
	opp_discs = (discs_opponent & 0X0040404000000000ULL) | 0X3FBFBF8000000000ULL;
	r = (opp_discs + 0X0000004000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040404000000000ULL;
		
		s = (25 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000004040ULL;
	opp_discs = (discs_opponent & 0X0000000000404000ULL) | 0X000000003FBF8000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000040000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 41;
		move.flipped |= (0X0000000040000000ULL - (0X0000000000800000ULL>>s)) & 0X0000000000404000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000040000000ULL;
	move.position = B5;
	
	return true;

}

bool RXBitBoard::generate_move_C5(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XC40E3C62E1FEA4BCULL, 0X3A978668A91214FCULL};
	static const unsigned long long HASH_SE[] = { 0, 0XD8905AA0CF7524E3ULL, 0XF77E58174B339EC3ULL};
	static const unsigned long long HASH_S_[] = { 0, 0X21E1C021672B259FULL, 0X3DFD48525F609E8AULL};
	static const unsigned long long HASH__E[] = { 0, 0XD8820DBB53B23529ULL, 0X16F33FDDE9942495ULL, 0X46A819665BC7D259ULL, 0X4B10210724688DA4ULL};
	static const unsigned long long HASH_NE[] = { 0, 0XD47D808E8A52D81CULL, 0X78640005EA7DD374ULL, 0XF8052B4F56B62B68ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X0E4EE6C7E870FF4CULL, 0X1A4295F646734997ULL, 0X00220C073DD78D33ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	my_discs = discs_player & 0X0000000000000804ULL;
	opp_discs = (discs_opponent & 0X0000000000100800ULL) | 0X000000001FEFF000ULL;
	r = ((my_discs<<9) + opp_discs) & 0X0000000020000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 43;
		move.flipped |= (0X0000000020000000ULL - (0X0000000000200000ULL>>s)) & 0X0000000000100800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SE[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000002020ULL;
	opp_discs = (discs_opponent & 0X0000000000202000ULL) | 0X000000001FDFC000ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000020000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 42;
		move.flipped |= (0X0000000020000000ULL - (0X0000000000400000ULL>>s)) & 0X0000000000202000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000F000000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000020000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 35;
		move.flipped |= 0X0000000020000000ULL - (0X0000000020000000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0204080000000000ULL;
	opp_discs = (discs_opponent & 0X0004081000000000ULL) | 0X01FBF7E000000000ULL;
	r = (opp_discs + 0X0000001000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004081000000000ULL;
		
		s = (34 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020200000000000ULL;
	opp_discs = (discs_opponent & 0X0020202000000000ULL) | 0X1FDFDFC000000000ULL;
	r = (opp_discs + 0X0000002000000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020202000000000ULL;
		
		s = (26 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0000004000000000ULL) != 0)  && ((discs_player & 0X0000800000000000ULL) != 0)) {
		move.flipped |= 0X0000004000000000ULL;
		move.hash_code ^= 0X442C866D1B81B7B0ULL;
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000000008000ULL) != 0)) {
		move.flipped |= 0X0000000000400000ULL;
		move.hash_code ^= 0XA75F9070CE36664AULL;
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {
		move.flipped |= 0X0000000040000000ULL;
		move.hash_code ^= 0XAEEC0E1BA836DA11ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000020000000ULL;
	move.position = C5;
	
	return true;

}

bool RXBitBoard::generate_move_F5(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XE9805D61927900E1ULL, 0XB9DB7BDA202AF62DULL};
	static const unsigned long long HASH_S_[] = { 0, 0X59724E050E71CF2AULL, 0X0133BF809CA92CD2ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XCF9A707838EFF9FBULL, 0XB20DB6591F0100AAULL, 0X326C9D13A3CAF8B6ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X580CC061E026C540ULL, 0XE4E143911A16A841ULL, 0XFE81DA6061B26CE5ULL};
	static const unsigned long long HASH_SW[] = { 0, 0XF199F8BE735B438CULL, 0X61123BC7BCD29688ULL};
	static const unsigned long long HASH__W[] = { 0, 0XCE713266BA2611BCULL, 0X16F33FDDE9942495ULL, 0XE86A85D7A17894D5ULL, 0X46868BCC094E4EC4ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000000000100ULL) != 0)) {
		move.flipped |= 0X0000000000020000ULL;
		move.hash_code ^= 0X16B8C2350A49EE5CULL;
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000404ULL;
	opp_discs = (discs_opponent & 0X0000000000040400ULL) | 0X0000000003FBF800ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000004000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 45;
		move.flipped |= (0X0000000004000000ULL - (0X0000000000080000ULL>>s)) & 0X0000000000040400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {
		move.flipped |= 0X0000000002000000ULL;
		move.hash_code ^= 0XDB838617FAF5FFDULL;
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000200000000ULL) != 0)  && ((discs_player & 0X0000010000000000ULL) != 0)) {
		move.flipped |= 0X0000000200000000ULL;
		move.hash_code ^= 0X4E22EE210BE2A5D4ULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404040000000000ULL;
	opp_discs = (discs_opponent & 0X0004040400000000ULL) | 0X03FBFBF800000000ULL;
	r = (opp_discs + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004040400000000ULL;
		
		s = (29 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X4020100000000000ULL;
	opp_discs = (discs_opponent & 0X0020100800000000ULL) | 0X3FDFEFF000000000ULL;
	r = (opp_discs + 0X0000000800000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020100800000000ULL;
		
		s = (28 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000001020ULL;
	opp_discs = (discs_opponent & 0X0000000000081000ULL) | 0X0000000003F7E000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000004000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 37;
		move.flipped |= (0X0000000004000000ULL - (0X0000000008000000ULL>>s)) & 0X0000000000081000ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000F0000000ULL;
	r = (discs_opponent + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000F8000000ULL;
		
		s = 36 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000004000000ULL;
	move.position = F5;
	
	return true;

}

bool RXBitBoard::generate_move_G5(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X0857FDCD16047C54ULL, 0X05EFC5AC69AB23A9ULL};
	static const unsigned long long HASH__W[] = { 0, 0X505B26BBB253F6CCULL, 0X9E2A14DD0875E770ULL, 0X46A819665BC7D259ULL, 0XB831A36C132B6219ULL, 0X16DDAD77BB1DB808ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X59724E050E71CF2AULL, 0X769C4CB28A37750AULL};
	static const unsigned long long HASH_NW[] = { 0, 0XCF9A707838EFF9FBULL, 0X6383F0F358C0F293ULL, 0XBB45AD7527DF373FULL};
	static const unsigned long long HASH_S_[] = { 0, 0X16B8C2350A49EE5CULL, 0XDE9364DF992A40D9ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X4E22EE210BE2A5D4ULL, 0XEC65D446FB3C2EDDULL, 0XD61C307E5A8D6D50ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X00000000F8000000ULL;
	r = (discs_opponent + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000FC000000ULL;
		
		s = 37 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000000810ULL;
	opp_discs = (discs_opponent & 0X0000000000040800ULL) | 0X0000000001FBF000ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000002000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 38;
		move.flipped |= (0X0000000002000000ULL - (0X0000000004000000ULL>>s)) & 0X0000000000040800ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X2010080000000000ULL;
	opp_discs = (discs_opponent & 0X0010080400000000ULL) | 0X1FEFF7F800000000ULL;
	r = (opp_discs + 0X0000000400000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010080400000000ULL;
		
		s = (29 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000202ULL;
	opp_discs = (discs_opponent & 0X0000000000020200ULL) | 0X0000000001FDFC00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000002000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 46;
		move.flipped |= (0X0000000002000000ULL - (0X0000000000040000ULL>>s)) & 0X0000000000020200ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020000000000ULL;
	opp_discs = (discs_opponent & 0X0002020200000000ULL) | 0X01FDFDFC00000000ULL;
	r = (opp_discs + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002020200000000ULL;
		
		s = (30 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000002000000ULL;
	move.position = G5;
	
	return true;

}

bool RXBitBoard::generate_move_H5(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X20578A4BAF901694ULL, 0X870EE4BE453C62DCULL};
	static const unsigned long long HASH__W[] = { 0, 0X0DB838617FAF5FFDULL, 0X5DE31EDACDFCA931ULL, 0X93922CBC77DAB88DULL, 0X4B10210724688DA4ULL, 0XB5899B0D6C843DE4ULL, 0X1B659516C4B2E7F5ULL};
	static const unsigned long long HASH_SW[] = { 0, 0X16B8C2350A49EE5CULL, 0X4EF933B098910DA4ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X4E22EE210BE2A5D4ULL, 0X33B528002C0C5C85ULL, 0X47FBF1529EC36B0EULL};
	static const unsigned long long HASH_S_[] = { 0, 0XC59146C838E05621ULL, 0XF567663AFCEBAA45ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X632017E6028FFEB0ULL, 0X7D6C675BCBEAE39AULL, 0X1A221F3DC929414FULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X00000000FC000000ULL;
	r = (discs_opponent + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000FE000000ULL;
		
		s = 38 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	my_discs = discs_player & 0X0000000000000408ULL;
	opp_discs = (discs_opponent & 0X0000000000020400ULL) | 0X0000000000FDF800ULL;
	r = ((my_discs<<7) + opp_discs) & 0X0000000001000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 39;
		move.flipped |= (0X0000000001000000ULL - (0X0000000002000000ULL>>s)) & 0X0000000000020400ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_SW[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X1008040000000000ULL;
	opp_discs = (discs_opponent & 0X0008040200000000ULL) | 0X0FF7FBFC00000000ULL;
	r = (opp_discs + 0X0000000200000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008040200000000ULL;
		
		s = (30 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction S */
	my_discs = discs_player & 0X0000000000000101ULL;
	opp_discs = (discs_opponent & 0X0000000000010100ULL) | 0X0000000000FEFE00ULL;
	r = ((my_discs<<8) + opp_discs) & 0X0000000001000000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 47;
		move.flipped |= (0X0000000001000000ULL - (0X0000000000020000ULL>>s)) & 0X0000000000010100ULL;
		
		s >>= 3;
		move.hash_code ^= HASH_S_[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010000000000ULL;
	opp_discs = (discs_opponent & 0X0001010100000000ULL) | 0X00FEFEFE00000000ULL;
	r = (opp_discs + 0X0000000100000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0001010100000000ULL;
		
		s = (31 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000001000000ULL;
	move.position = H5;
	
	return true;

}

bool RXBitBoard::generate_move_A6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X91FAB6AA406CD6A5ULL, 0XBA20CE704CD47BF8ULL};
	static const unsigned long long HASH__E[] = { 0, 0XA75F9070CE36664AULL, 0X86BE5051A91D43D5ULL, 0X5E2E0AF166686736ULL, 0XAFB7F24F153324BAULL, 0XF6C5BC4A1B42EB90ULL, 0XE07D7E7F110B05CCULL};
	static const unsigned long long HASH_NE[] = { 0, 0XAEEC0E1BA836DA11ULL, 0XA0A2E8DC4046255DULL, 0X1C4F6B2CBA76485CULL, 0X6801B27E08B97FD7ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X74BDA592ADE8A56BULL, 0X715AD4A48F3C46B2ULL, 0X6D1DD863A557D13AULL, 0X4E545FAAF56CA2A8ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X00000000003F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000800000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 41;
		move.flipped |= 0X0000000000800000ULL - (0X0000000000800000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0408102000000000ULL;
	opp_discs = (discs_opponent & 0X0008102040000000ULL) | 0X03F7EFDF80000000ULL;
	r = (opp_discs + 0X0000000040000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008102040000000ULL;
		
		s = (40 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction SE */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {
		move.flipped |= 0X0000000000004000ULL;
		move.hash_code ^= 0X70076F2FB54E2F81ULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808000000000ULL;
	opp_discs = (discs_opponent & 0X0080808080000000ULL) | 0X7F7F7F7F00000000ULL;
	r = (opp_discs + 0X0000000080000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0080808080000000ULL;
		
		s = (32 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000008000ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {
		move.flipped |= 0X0000000000008000ULL;
		move.hash_code ^= 0XB697FEBE4D8C75A4ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000800000ULL;
	move.position = A6;
	
	return true;

}

bool RXBitBoard::generate_move_B6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XF8F082FDDBDC088FULL, 0X5FAF128D15EA6EC5ULL};
	static const unsigned long long HASH__E[] = { 0, 0X21E1C021672B259FULL, 0XF9719A81A85E017CULL, 0X08E8623FDB0542F0ULL, 0X519A2C3AD5748DDAULL, 0X4722EE0FDF3D6386ULL};
	static const unsigned long long HASH_NE[] = { 0, 0XFE99BA0A48ECB040ULL, 0X2AE43A84C2BE685CULL, 0X86FDBA0FA2916334ULL, 0X069C91451E5A9B28ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XAEEC0E1BA836DA11ULL, 0XEAC08876B3B76DA1ULL, 0X3712979CA7B757A2ULL, 0X76610F85249C2CA9ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _E */
	my_discs = discs_player & 0X00000000001F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000400000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 42;
		move.flipped |= 0X0000000000400000ULL - (0X0000000000400000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0204081000000000ULL;
	opp_discs = (discs_opponent & 0X0004081020000000ULL) | 0X01FBF7EFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004081020000000ULL;
		
		s = (41 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction SE */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {
		move.flipped |= 0X0000000000002000ULL;
		move.hash_code ^= 0X1C1C8873384BBB15ULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404000000000ULL;
	opp_discs = (discs_opponent & 0X0040404040000000ULL) | 0X3FBFBFBF80000000ULL;
	r = (opp_discs + 0X0000000040000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040404040000000ULL;
		
		s = (33 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000040ULL) != 0)) {
		move.flipped |= 0X0000000000004000ULL;
		move.hash_code ^= 0X70076F2FB54E2F81ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000400000ULL;
	move.position = B6;
	
	return true;

}

bool RXBitBoard::generate_move_C6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XF70DDB51ECA37304ULL, 0XD6EC1B708B88569BULL};
	static const unsigned long long HASH__E[] = { 0, 0XD8905AA0CF7524E3ULL, 0X2909A21EBC2E676FULL, 0X707BEC1BB25FA845ULL, 0X66C32E2EB8164619ULL};
	static const unsigned long long HASH_NE[] = { 0, 0XD8820DBB53B23529ULL, 0X808ECDDAB394F069ULL, 0XFD190BFB947A0938ULL, 0XC760EFC335CB4AB5ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XFE99BA0A48ECB040ULL, 0XF0D75CCDA09C4F0CULL, 0XE4DB2FFC0E9FF9D7ULL, 0XFEBBB60D753B3D73ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {
		move.flipped |= 0X0000000000001000ULL;
		move.hash_code ^= 0X908BC379CF89D504ULL;
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {
		move.flipped |= 0X0000000000002000ULL;
		move.hash_code ^= 0X1C1C8873384BBB15ULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X00000000000F0000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000200000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 43;
		move.flipped |= 0X0000000000200000ULL - (0X0000000000200000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0102040800000000ULL;
	opp_discs = (discs_opponent & 0X0002040810000000ULL) | 0X00FDFBF7E0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002040810000000ULL;
		
		s = (42 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X2020202000000000ULL;
	opp_discs = (discs_opponent & 0X0020202020000000ULL) | 0X1FDFDFDFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020202020000000ULL;
		
		s = (34 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000040000000ULL) != 0)  && ((discs_player & 0X0000008000000000ULL) != 0)) {
		move.flipped |= 0X0000000040000000ULL;
		move.hash_code ^= 0XAEEC0E1BA836DA11ULL;
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {
		move.flipped |= 0X0000000000004000ULL;
		move.hash_code ^= 0X70076F2FB54E2F81ULL;
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {
		move.flipped |= 0X0000000000400000ULL;
		move.hash_code ^= 0XA75F9070CE36664AULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000200000ULL;
	move.position = C6;
	
	return true;

}

bool RXBitBoard::generate_move_D6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X0B23D602B5E730EAULL, 0XD3B38CA27A921409ULL};
	static const unsigned long long HASH__E[] = { 0, 0XF199F8BE735B438CULL, 0XA8EBB6BB7D2A8CA6ULL, 0XBE53748E776362FAULL};
	static const unsigned long long HASH_NE[] = { 0, 0XCE713266BA2611BCULL, 0X01EB421E82C9E847ULL, 0XA3AC78797217634EULL};
	static const unsigned long long HASH_N_[] = { 0, 0XD8820DBB53B23529ULL, 0X0CFF8D35D9E0ED35ULL, 0XB0120EC523D08034ULL, 0X68D453435CCF4598ULL};
	static const unsigned long long HASH_NW[] = { 0, 0XFE99BA0A48ECB040ULL, 0XBAB53C67536D07F0ULL};
	static const unsigned long long HASH__W[] = { 0, 0X21E1C021672B259FULL, 0X86BE5051A91D43D5ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {
		move.flipped |= 0X0000000000000800ULL;
		move.hash_code ^= 0X2FEE02B78446BA20ULL;
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {
		move.flipped |= 0X0000000000001000ULL;
		move.hash_code ^= 0X908BC379CF89D504ULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000070000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000100000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 44;
		move.flipped |= 0X0000000000100000ULL - (0X0000000000100000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0001020400000000ULL;
	opp_discs = (discs_opponent & 0X0000020408000000ULL) | 0X0000FDFBF0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000020408000000ULL;
		
		s = (43 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X1010101000000000ULL;
	opp_discs = (discs_opponent & 0X0010101010000000ULL) | 0X0FEFEFEFE0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010101010000000ULL;
		
		s = (35 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804000000000ULL;
	opp_discs = (discs_opponent & 0X0000004020000000ULL) | 0X00007FBFC0000000ULL;
	r = (opp_discs + 0X0000000020000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000004020000000ULL;
		
		s = (34 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000002000ULL) != 0)  && ((discs_player & 0X0000000000000040ULL) != 0)) {
		move.flipped |= 0X0000000000002000ULL;
		move.hash_code ^= 0X1C1C8873384BBB15ULL;
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000C00000ULL;
	r = (discs_opponent + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000E00000ULL;
		
		s = 42 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000100000ULL;
	move.position = D6;
	
	return true;

}

bool RXBitBoard::generate_move_E6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XE141127AFF5D9D88ULL, 0X10D8EAC48C06DE04ULL};
	static const unsigned long long HASH__E[] = { 0, 0X59724E050E71CF2AULL, 0X4FCA8C3004382176ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X505B26BBB253F6CCULL, 0X1E79C89AB9B15318ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XCE713266BA2611BCULL, 0X967DF2075A00D4FCULL, 0X3A64728C3A2FDF94ULL, 0X4E2AABDE88E0E81FULL};
	static const unsigned long long HASH_NW[] = { 0, 0XD8820DBB53B23529ULL, 0XD6CCEB7CBBC2CA65ULL, 0X0B1EF496AFC2F066ULL};
	static const unsigned long long HASH__W[] = { 0, 0XD8905AA0CF7524E3ULL, 0XF9719A81A85E017CULL, 0X5E2E0AF166686736ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000002ULL) != 0)) {
		move.flipped |= 0X0000000000000400ULL;
		move.hash_code ^= 0X5841F18592D8E3F8ULL;
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {
		move.flipped |= 0X0000000000000800ULL;
		move.hash_code ^= 0X2FEE02B78446BA20ULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000030000ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000080000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 45;
		move.flipped |= 0X0000000000080000ULL - (0X0000000000080000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010200000000ULL;
	opp_discs = (discs_opponent & 0X0000000204000000ULL) | 0X000000FDF8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000204000000ULL;
		
		s = (44 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0808080800000000ULL;
	opp_discs = (discs_opponent & 0X0008080808000000ULL) | 0X07F7F7F7F0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008080808000000ULL;
		
		s = (36 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0080402000000000ULL;
	opp_discs = (discs_opponent & 0X0000402010000000ULL) | 0X007FBFDFE0000000ULL;
	r = (opp_discs + 0X0000000010000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000402010000000ULL;
		
		s = (35 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000001000ULL) != 0)  && ((discs_player & 0X0000000000000020ULL) != 0)) {
		move.flipped |= 0X0000000000001000ULL;
		move.hash_code ^= 0X908BC379CF89D504ULL;
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000E00000ULL;
	r = (discs_opponent + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000F00000ULL;
		
		s = 43 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000080000ULL;
	move.position = E6;
	
	return true;

}

bool RXBitBoard::generate_move_F6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X06AB4E930C3C3B4CULL, 0X5FD90096024DF466ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X505B26BBB253F6CCULL, 0X9FC156C38ABC0F37ULL, 0XE25690E2AD52F666ULL, 0X6237BBA811990E7AULL};
	static const unsigned long long HASH_NW[] = { 0, 0XCE713266BA2611BCULL, 0X1A0CB2E83074C9A0ULL, 0X0E00C1D99E777F7BULL, 0X4F7359C01D5C0470ULL};
	static const unsigned long long HASH__W[] = { 0, 0XF199F8BE735B438CULL, 0X2909A21EBC2E676FULL, 0X08E8623FDB0542F0ULL, 0XAFB7F24F153324BAULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction SE */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {
		move.flipped |= 0X0000000000000200ULL;
		move.hash_code ^= 0XC82BA6EA9363AE85ULL;
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {
		move.flipped |= 0X0000000000000400ULL;
		move.hash_code ^= 0X5841F18592D8E3F8ULL;
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {
		move.flipped |= 0X0000000000020000ULL;
		move.hash_code ^= 0X16B8C2350A49EE5CULL;
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000002000000ULL) != 0)  && ((discs_player & 0X0000000100000000ULL) != 0)) {
		move.flipped |= 0X0000000002000000ULL;
		move.hash_code ^= 0XDB838617FAF5FFDULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X0404040400000000ULL;
	opp_discs = (discs_opponent & 0X0004040404000000ULL) | 0X03FBFBFBF8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004040404000000ULL;
		
		s = (37 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X8040201000000000ULL;
	opp_discs = (discs_opponent & 0X0040201008000000ULL) | 0X7FBFDFEFF0000000ULL;
	r = (opp_discs + 0X0000000008000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040201008000000ULL;
		
		s = (36 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000800ULL) != 0)  && ((discs_player & 0X0000000000000010ULL) != 0)) {
		move.flipped |= 0X0000000000000800ULL;
		move.hash_code ^= 0X2FEE02B78446BA20ULL;
	}

	/* direction _W */
	my_discs = discs_player & 0X0000000000F00000ULL;
	r = (discs_opponent + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000F80000ULL;
		
		s = 44 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000040000ULL;
	move.position = F6;
	
	return true;

}

bool RXBitBoard::generate_move_G6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X2F58A940D4150E0AULL, 0X39E06B75DE5CE056ULL};
	static const unsigned long long HASH__W[] = { 0, 0X59724E050E71CF2AULL, 0XA8EBB6BB7D2A8CA6ULL, 0X707BEC1BB25FA845ULL, 0X519A2C3AD5748DDAULL, 0XF6C5BC4A1B42EB90ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X505B26BBB253F6CCULL, 0X0857E6DA5275338CULL, 0XB4BA652AA8455E8DULL, 0XAEDAFCDBD3E19A29ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X0DB838617FAF5FFDULL, 0X439AD640744DFA29ULL, 0XE1DDEC2784937120ULL, 0XDBA4081F252232ADULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X0000000000F80000ULL;
	r = (discs_opponent + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000FC0000ULL;
		
		s = 45 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000400ULL) != 0)  && ((discs_player & 0X0000000000000008ULL) != 0)) {
		move.flipped |= 0X0000000000000400ULL;
		move.hash_code ^= 0X5841F18592D8E3F8ULL;
	}

	/* direction NW */
	my_discs = discs_player & 0X4020100800000000ULL;
	opp_discs = (discs_opponent & 0X0020100804000000ULL) | 0X3FDFEFF7F8000000ULL;
	r = (opp_discs + 0X0000000004000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020100804000000ULL;
		
		s = (37 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000002ULL) != 0)) {
		move.flipped |= 0X0000000000000200ULL;
		move.hash_code ^= 0XC82BA6EA9363AE85ULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020200000000ULL;
	opp_discs = (discs_opponent & 0X0002020202000000ULL) | 0X01FDFDFDFC000000ULL;
	r = (opp_discs + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002020202000000ULL;
		
		s = (38 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000020000ULL;
	move.position = G6;
	
	return true;

}

bool RXBitBoard::generate_move_H6(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XF4FD8BED713AE0E8ULL, 0X316CCD2549DAB6C9ULL};
	static const unsigned long long HASH__W[] = { 0, 0X16B8C2350A49EE5CULL, 0X4FCA8C3004382176ULL, 0XBE53748E776362FAULL, 0X66C32E2EB8164619ULL, 0X4722EE0FDF3D6386ULL, 0XE07D7E7F110B05CCULL};
	static const unsigned long long HASH_NW[] = { 0, 0X0DB838617FAF5FFDULL, 0XC22248194740A606ULL, 0X6E3BC892276FAD6EULL, 0XB6FD9514587068C2ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XA7596EF5EAAC7448ULL, 0XC4797913E8238AF8ULL, 0XDA3509AE214697D2ULL, 0XBD7B71C823853507ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction _W */
	my_discs = discs_player & 0X0000000000FC0000ULL;
	r = (discs_opponent + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000FE0000ULL;
		
		s = 46 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	/* direction SW */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000004ULL) != 0)) {
		move.flipped |= 0X0000000000000200ULL;
		move.hash_code ^= 0XC82BA6EA9363AE85ULL;
	}

	/* direction NW */
	my_discs = discs_player & 0X2010080400000000ULL;
	opp_discs = (discs_opponent & 0X0010080402000000ULL) | 0X1FEFF7FBFC000000ULL;
	r = (opp_discs + 0X0000000002000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010080402000000ULL;
		
		s = (38 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction S */
	if(((discs_opponent & 0X0000000000000100ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {
		move.flipped |= 0X0000000000000100ULL;
		move.hash_code ^= 0X30F620F2C40BFC64ULL;
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010100000000ULL;
	opp_discs = (discs_opponent & 0X0001010101000000ULL) | 0X00FEFEFEFE000000ULL;
	r = (opp_discs + 0X0000000001000000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0001010101000000ULL;
		
		s = (39 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000010000ULL;
	move.position = H6;
	
	return true;

}

bool RXBitBoard::generate_move_A7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XBDD43971341B3DD5ULL, 0X0B43C7CF79974871ULL};
	static const unsigned long long HASH_NE[] = { 0, 0XA75F9070CE36664AULL, 0X59C62A7A86DAD60AULL, 0X8DBBAAF40C880E16ULL, 0X21A22A7F6CA7057EULL, 0XA1C30135D06CFD62ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X2BDA78DA0CB8AD5DULL, 0X5F67DD48A1500836ULL, 0X5A80AC7E8384EBEFULL, 0X46C7A0B9A9EF7C67ULL, 0X658E2770F9D40FF5ULL};
	static const unsigned long long HASH__E[] = { 0, 0X70076F2FB54E2F81ULL, 0X6C1BE75C8D059494ULL, 0XFC902425428C4190ULL, 0XD37E2692C6CAFBB0ULL, 0X8B3FD71754121848ULL, 0X431471FDC771B6CDULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NE */
	my_discs = discs_player & 0X0204081020000000ULL;
	opp_discs = (discs_opponent & 0X0004081020400000ULL) | 0X01FBF7EFDF800000ULL;
	r = (opp_discs + 0X0000000000400000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004081020400000ULL;
		
		s = (48 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808080000000ULL;
	opp_discs = (discs_opponent & 0X0080808080800000ULL) | 0X7F7F7F7F7F000000ULL;
	r = (opp_discs + 0X0000000000800000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0080808080800000ULL;
		
		s = (40 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000003F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000008000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 49;
		move.flipped |= 0X0000000000008000ULL - (0X0000000000008000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000008000ULL;
	move.position = A7;
	
	return true;

}

bool RXBitBoard::generate_move_B7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X1A7A170899D82293ULL, 0X6A7D78272C960D12ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X21E1C021672B259FULL, 0XF963CD9A349910B6ULL, 0XA16F0DFBD4BFD5F6ULL, 0XDCF8CBDAF3512CA7ULL, 0XE6812FE252E06F2AULL};
	static const unsigned long long HASH_N_[] = { 0, 0XA75F9070CE36664AULL, 0X09B39E6B6600BC5BULL, 0X4D9F18067D810BEBULL, 0X904D07EC698131E8ULL, 0XD13E9FF5EAAA4AE3ULL};
	static const unsigned long long HASH__E[] = { 0, 0X1C1C8873384BBB15ULL, 0X8C974B0AF7C26E11ULL, 0XA37949BD7384D431ULL, 0XFB38B838E15C37C9ULL, 0X33131ED2723F994CULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NE */
	my_discs = discs_player & 0X0102040810000000ULL;
	opp_discs = (discs_opponent & 0X0002040810200000ULL) | 0X00FDFBF7EFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002040810200000ULL;
		
		s = (49 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404040000000ULL;
	opp_discs = (discs_opponent & 0X0040404040400000ULL) | 0X3FBFBFBFBF800000ULL;
	r = (opp_discs + 0X0000000000400000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040404040400000ULL;
		
		s = (41 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000001F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000004000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 50;
		move.flipped |= 0X0000000000004000ULL - (0X0000000000004000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000004000ULL;
	move.position = B7;
	
	return true;

}

bool RXBitBoard::generate_move_C7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X06995AE685421F11ULL, 0X1A85D295BD09A404ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X21E1C021672B259FULL, 0XDF787A2B2FC795DFULL, 0XD1369CECC7B76A93ULL, 0XC53AEFDD69B4DC48ULL, 0XDF5A762C121018ECULL};
	static const unsigned long long HASH_NE[] = { 0, 0XD8905AA0CF7524E3ULL, 0X16E168C67553355FULL, 0XD97B18BE4DBCCCA4ULL, 0X7B3C22D9BD6247ADULL};
	static const unsigned long long HASH__E[] = { 0, 0X908BC379CF89D504ULL, 0XBF65C1CE4BCF6F24ULL, 0XE724304BD9178CDCULL, 0X2F0F96A14A742259ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X2020202020000000ULL;
	opp_discs = (discs_opponent & 0X0020202020200000ULL) | 0X1FDFDFDFDFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020202020200000ULL;
		
		s = (42 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0001020408000000ULL;
	opp_discs = (discs_opponent & 0X0000020408100000ULL) | 0X0000FDFBF7E00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000020408100000ULL;
		
		s = (50 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000000400000ULL) != 0)  && ((discs_player & 0X0000000080000000ULL) != 0)) {
		move.flipped |= 0X0000000000400000ULL;
		move.hash_code ^= 0XA75F9070CE36664AULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000F00ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000002000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 51;
		move.flipped |= 0X0000000000002000ULL - (0X0000000000002000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000008000ULL) != 0)) {
		move.flipped |= 0X0000000000004000ULL;
		move.hash_code ^= 0X70076F2FB54E2F81ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000002000ULL;
	move.position = C7;
	
	return true;

}

bool RXBitBoard::generate_move_D7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XEBBC7CB71EB476C1ULL, 0X7B37BFCED13DA3C5ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XD8905AA0CF7524E3ULL, 0X0012571B9CC711CAULL, 0XD46FD7951695C9D6ULL, 0X68825465ECA5A4D7ULL, 0XB04409E393BA617BULL};
	static const unsigned long long HASH_NE[] = { 0, 0XF199F8BE735B438CULL, 0XA1C2DE05C108B540ULL, 0XEFE03024CAEA1094ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X21E1C021672B259FULL, 0X8F0DCE3ACF1DFF8EULL};
	static const unsigned long long HASH__E[] = { 0, 0X2FEE02B78446BA20ULL, 0X77AFF332169E59D8ULL, 0XBF8455D885FDF75DULL};
	static const unsigned long long HASH__W[] = { 0, 0X1C1C8873384BBB15ULL, 0X6C1BE75C8D059494ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X1010101010000000ULL;
	opp_discs = (discs_opponent & 0X0010101010100000ULL) | 0X0FEFEFEFEFE00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010101010100000ULL;
		
		s = (43 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010204000000ULL;
	opp_discs = (discs_opponent & 0X0000000204080000ULL) | 0X000000FDFBF00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000204080000ULL;
		
		s = (51 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0000008040000000ULL;
	opp_discs = (discs_opponent & 0X0000000040200000ULL) | 0X0000007FBFC00000ULL;
	r = (opp_discs + 0X0000000000200000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000040200000ULL;
		
		s = (42 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000700ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000001000ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 52;
		move.flipped |= 0X0000000000001000ULL - (0X0000000000001000ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000C000ULL;
	r = (discs_opponent + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000000000E000ULL;
		
		s = 50 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000001000ULL;
	move.position = D7;
	
	return true;

}

bool RXBitBoard::generate_move_E7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X8B9289F7BDFA0A8AULL, 0XA47C8B4039BCB0AAULL};
	static const unsigned long long HASH_N_[] = { 0, 0XF199F8BE735B438CULL, 0X3FE8CAD8C97D5230ULL, 0X67E40AB9295B9770ULL, 0XCBFD8A3249749C18ULL, 0XBFB35360FBBBAB93ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X59724E050E71CF2AULL, 0X54CA766471DE90D7ULL};
	static const unsigned long long HASH_NW[] = { 0, 0XD8905AA0CF7524E3ULL, 0X2609E0AA879994A3ULL, 0X622566C79C182313ULL};
	static const unsigned long long HASH__E[] = { 0, 0X5841F18592D8E3F8ULL, 0X906A576F01BB4D7DULL};
	static const unsigned long long HASH__W[] = { 0, 0X908BC379CF89D504ULL, 0X8C974B0AF7C26E11ULL, 0XFC902425428C4190ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X0808080808000000ULL;
	opp_discs = (discs_opponent & 0X0008080808080000ULL) | 0X07F7F7F7F7F00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008080808080000ULL;
		
		s = (44 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000102000000ULL;
	opp_discs = (discs_opponent & 0X0000000002040000ULL) | 0X00000000FDF80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000002040000ULL;
		
		s = (52 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804020000000ULL;
	opp_discs = (discs_opponent & 0X0000004020100000ULL) | 0X00007FBFDFE00000ULL;
	r = (opp_discs + 0X0000000000100000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000004020100000ULL;
		
		s = (43 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000300ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000800ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 53;
		move.flipped |= 0X0000000000000800ULL - (0X0000000000000800ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000E000ULL;
	r = (discs_opponent + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000000000F000ULL;
		
		s = 51 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000800ULL;
	move.position = E7;
	
	return true;

}

bool RXBitBoard::generate_move_F7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X0DBAAFDBEE9F073CULL, 0X55FB5E5E7C47E4C4ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X59724E050E71CF2AULL, 0X092968BEBC2239E6ULL, 0XC6B318C684CDC01DULL, 0XBB24DEE7A323394CULL, 0X3B45F5AD1FE8C150ULL};
	static const unsigned long long HASH_NW[] = { 0, 0XF199F8BE735B438CULL, 0X291BF50520E976A5ULL, 0X275513C2C89989E9ULL, 0XFA870C28DC99B3EAULL};
	static const unsigned long long HASH__W[] = { 0, 0X2FEE02B78446BA20ULL, 0XBF65C1CE4BCF6F24ULL, 0XA37949BD7384D431ULL, 0XD37E2692C6CAFBB0ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X0404040404000000ULL;
	opp_discs = (discs_opponent & 0X0004040404040000ULL) | 0X03FBFBFBFBF80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004040404040000ULL;
		
		s = (45 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000000020000ULL) != 0)  && ((discs_player & 0X0000000001000000ULL) != 0)) {
		move.flipped |= 0X0000000000020000ULL;
		move.hash_code ^= 0X16B8C2350A49EE5CULL;
	}

	/* direction NW */
	my_discs = discs_player & 0X0080402010000000ULL;
	opp_discs = (discs_opponent & 0X0000402010080000ULL) | 0X007FBFDFEFF00000ULL;
	r = (opp_discs + 0X0000000000080000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000402010080000ULL;
		
		s = (44 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000000100ULL) != 0)) {
		move.flipped |= 0X0000000000000200ULL;
		move.hash_code ^= 0XC82BA6EA9363AE85ULL;
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000F000ULL;
	r = (discs_opponent + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000000000F800ULL;
		
		s = 52 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000400ULL;
	move.position = F7;
	
	return true;

}

bool RXBitBoard::generate_move_G7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XF484677142134734ULL, 0X3CAFC19BD170E9B1ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X59724E050E71CF2AULL, 0X97037C63B457DE96ULL, 0X437EFCED3E05068AULL, 0X57728FDC9006B051ULL, 0X160117C5132DCB5AULL};
	static const unsigned long long HASH_N_[] = { 0, 0X16B8C2350A49EE5CULL, 0X1B00FA5475E6B1A1ULL, 0X552214757E041475ULL, 0XF7652E128EDA9F7CULL, 0XCD1CCA2A2F6BDCF1ULL};
	static const unsigned long long HASH__W[] = { 0, 0X5841F18592D8E3F8ULL, 0X77AFF332169E59D8ULL, 0XE724304BD9178CDCULL, 0XFB38B838E15C37C9ULL, 0X8B3FD71754121848ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NW */
	my_discs = discs_player & 0X8040201008000000ULL;
	opp_discs = (discs_opponent & 0X0040201008040000ULL) | 0X7FBFDFEFF7F80000ULL;
	r = (opp_discs + 0X0000000000040000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040201008040000ULL;
		
		s = (45 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020202000000ULL;
	opp_discs = (discs_opponent & 0X0002020202020000ULL) | 0X01FDFDFDFDFC0000ULL;
	r = (opp_discs + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002020202020000ULL;
		
		s = (46 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000F800ULL;
	r = (discs_opponent + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000000000FC00ULL;
		
		s = 53 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000200ULL;
	move.position = G7;
	
	return true;

}

bool RXBitBoard::generate_move_H7(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X96F1CBC65D7D8FD0ULL, 0XA607EB34997673B4ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X16B8C2350A49EE5CULL, 0X46E3E48EB81A1890ULL, 0X1EEF24EF583CDDD0ULL, 0XA202A71FA20CB0D1ULL, 0XB8623EEED9A87475ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XC59146C838E05621ULL, 0X62C8283DD24C2269ULL, 0X01E83FDBD0C3DCD9ULL, 0X1FA44F6619A6C1F3ULL, 0X78EA37001B656326ULL};
	static const unsigned long long HASH__W[] = { 0, 0XC82BA6EA9363AE85ULL, 0X906A576F01BB4D7DULL, 0XBF8455D885FDF75DULL, 0X2F0F96A14A742259ULL, 0X33131ED2723F994CULL, 0X431471FDC771B6CDULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NW */
	my_discs = discs_player & 0X4020100804000000ULL;
	opp_discs = (discs_opponent & 0X0020100804020000ULL) | 0X3FDFEFF7FBFC0000ULL;
	r = (opp_discs + 0X0000000000020000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020100804020000ULL;
		
		s = (46 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010101000000ULL;
	opp_discs = (discs_opponent & 0X0001010101010000ULL) | 0X00FEFEFEFEFE0000ULL;
	r = (opp_discs + 0X0000000000010000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0001010101010000ULL;
		
		s = (47 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X000000000000FC00ULL;
	r = (discs_opponent + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X000000000000FE00ULL;
		
		s = 54 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000100ULL;
	move.position = H7;
	
	return true;

}

bool RXBitBoard::generate_move_A8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X2C89DA6AD9CF1CE1ULL, 0X4BEB70B395691171ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X70076F2FB54E2F81ULL, 0X51E6AF0ED2650A1EULL, 0X8964A2B581D73F37ULL, 0XD16862D461F1FA77ULL, 0XACFFA4F5461F0326ULL, 0X968640CDE7AE40ABULL};
	static const unsigned long long HASH_N_[] = { 0, 0XB697FEBE4D8C75A4ULL, 0X9D4D86644134D8F9ULL, 0XE9F023F6ECDC7D92ULL, 0XEC1752C0CE089E4BULL, 0XF0505E07E46309C3ULL, 0XD319D9CEB4587A51ULL};
	static const unsigned long long HASH__E[] = { 0, 0XBE68B59195DC4968ULL, 0XAB24D8CF20EAFC73ULL, 0X003DE6FD4B72E428ULL, 0X73C816674AA4BF95ULL, 0XFDD92493789353CFULL, 0XE03C83281CE16F5EULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NE */
	my_discs = discs_player & 0X0102040810200000ULL;
	opp_discs = (discs_opponent & 0X0002040810204000ULL) | 0X00FDFBF7EFDF8000ULL;
	r = (opp_discs + 0X0000000000004000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002040810204000ULL;
		
		s = (56 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X8080808080800000ULL;
	opp_discs = (discs_opponent & 0X0080808080808000ULL) | 0X7F7F7F7F7F7F0000ULL;
	r = (opp_discs + 0X0000000000008000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0080808080808000ULL;
		
		s = (48 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000003FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000080ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 57;
		move.flipped |= 0X0000000000000080ULL - (0X0000000000000080ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000080ULL;
	move.position = A8;
	
	return true;

}

bool RXBitBoard::generate_move_B8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X339D774EDFF65CDCULL, 0X8DF5C2DF4A2A15B4ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X1C1C8873384BBB15ULL, 0XC48CD2D3F73E9FF6ULL, 0X0AFDE0B54D188E4AULL, 0XC56790CD75F777B1ULL, 0X6720AAAA8529FCB8ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X70076F2FB54E2F81ULL, 0XD758FF5F7B7849CBULL, 0X79B4F144D34E93DAULL, 0X3D987729C8CF246AULL, 0XE04A68C3DCCF1E69ULL, 0XA139F0DA5FE46562ULL};
	static const unsigned long long HASH__E[] = { 0, 0X154C6D5EB536B51BULL, 0XBE55536CDEAEAD40ULL, 0XCDA0A3F6DF78F6FDULL, 0X43B19102ED4F1AA7ULL, 0X5E5436B9893D2636ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NE */
	my_discs = discs_player & 0X0001020408100000ULL;
	opp_discs = (discs_opponent & 0X0000020408102000ULL) | 0X0000FDFBF7EFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000020408102000ULL;
		
		s = (57 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X4040404040400000ULL;
	opp_discs = (discs_opponent & 0X0040404040404000ULL) | 0X3FBFBFBFBFBF8000ULL;
	r = (opp_discs + 0X0000000000004000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040404040404000ULL;
		
		s = (49 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000001FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000040ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 58;
		move.flipped |= 0X0000000000000040ULL - (0X0000000000000040ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000040ULL;
	move.position = B8;
	
	return true;

}

bool RXBitBoard::generate_move_C8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XEE4FFAA05000D7A3ULL, 0XFB0397FEE53662B8ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X1C1C8873384BBB15ULL, 0X3DFD48525F609E8AULL, 0XC364F258178C2ECAULL, 0XCD2A149FFFFCD186ULL, 0XD92667AE51FF675DULL, 0XC346FE5F2A5BA3F9ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X908BC379CF89D504ULL, 0X61123BC7BCD29688ULL, 0X31491D7C0E816044ULL, 0X7F6BF35D0563C590ULL};
	static const unsigned long long HASH__E[] = { 0, 0XAB193E326B98185BULL, 0XD8ECCEA86A4E43E6ULL, 0X56FDFC5C5879AFBCULL, 0X4B185BE73C0B932DULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X2020202020200000ULL;
	opp_discs = (discs_opponent & 0X0020202020202000ULL) | 0X1FDFDFDFDFDFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0020202020202000ULL;
		
		s = (50 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0000010204080000ULL;
	opp_discs = (discs_opponent & 0X0000000204081000ULL) | 0X000000FDFBF7E000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000204081000ULL;
		
		s = (58 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction NW */
	if(((discs_opponent & 0X0000000000004000ULL) != 0)  && ((discs_player & 0X0000000000800000ULL) != 0)) {
		move.flipped |= 0X0000000000004000ULL;
		move.hash_code ^= 0X70076F2FB54E2F81ULL;
	}

	/* direction _E */
	my_discs = discs_player & 0X000000000000000FULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000020ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 59;
		move.flipped |= 0X0000000000000020ULL - (0X0000000000000020ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	if(((discs_opponent & 0X0000000000000040ULL) != 0)  && ((discs_player & 0X0000000000000080ULL) != 0)) {
		move.flipped |= 0X0000000000000040ULL;
		move.hash_code ^= 0XBE68B59195DC4968ULL;
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000020ULL;
	move.position = C8;
	
	return true;

}

bool RXBitBoard::generate_move_D8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X076CEBC185343BB6ULL, 0XAC75D5F3EEAC23EDULL};
	static const unsigned long long HASH_N_[] = { 0, 0X908BC379CF89D504ULL, 0X481B99D900FCF1E7ULL, 0X90999462534EC4CEULL, 0X44E414ECD91C1CD2ULL, 0XF809971C232C71D3ULL, 0X20CFCA9A5C33B47FULL};
	static const unsigned long long HASH_NE[] = { 0, 0X2FEE02B78446BA20ULL, 0X769C4CB28A37750AULL, 0X7B2474D3F5982AF7ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X1C1C8873384BBB15ULL, 0XBB431803F67DDD5FULL};
	static const unsigned long long HASH__E[] = { 0, 0X73F5F09A01D65BBDULL, 0XFDE4C26E33E1B7E7ULL, 0XE00165D557938B76ULL};
	static const unsigned long long HASH__W[] = { 0, 0X154C6D5EB536B51BULL, 0XAB24D8CF20EAFC73ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X1010101010100000ULL;
	opp_discs = (discs_opponent & 0X0010101010101000ULL) | 0X0FEFEFEFEFEFE000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0010101010101000ULL;
		
		s = (51 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000102040000ULL;
	opp_discs = (discs_opponent & 0X0000000002040800ULL) | 0X00000000FDFBF000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000002040800ULL;
		
		s = (59 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0000000080400000ULL;
	opp_discs = (discs_opponent & 0X0000000000402000ULL) | 0X000000007FBFC000ULL;
	r = (opp_discs + 0X0000000000002000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000402000ULL;
		
		s = (50 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000007ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000010ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 60;
		move.flipped |= 0X0000000000000010ULL - (0X0000000000000010ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000C0ULL;
	r = (discs_opponent + 0X0000000000000020ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000000000E0ULL;
		
		s = 58 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000010ULL;
	move.position = D8;
	
	return true;

}

bool RXBitBoard::generate_move_E8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XF899D4E5A6A89530ULL, 0X8B6C247FA77ECE8DULL};
	static const unsigned long long HASH_N_[] = { 0, 0X2FEE02B78446BA20ULL, 0XDE77FA09F71DF9ACULL, 0X1006C86F4D3BE810ULL, 0X480A080EAD1D2D50ULL, 0XE4138885CD322638ULL, 0X905D51D77FFD11B3ULL};
	static const unsigned long long HASH_NE[] = { 0, 0X5841F18592D8E3F8ULL, 0X4EF933B098910DA4ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X908BC379CF89D504ULL, 0XB16A0358A8A2F09BULL, 0X1F860D4300942A8AULL};
	static const unsigned long long HASH__E[] = { 0, 0X8E1132F43237EC5AULL, 0X93F4954F5645D0CBULL};
	static const unsigned long long HASH__W[] = { 0, 0XAB193E326B98185BULL, 0XBE55536CDEAEAD40ULL, 0X003DE6FD4B72E428ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X0808080808080000ULL;
	opp_discs = (discs_opponent & 0X0008080808080800ULL) | 0X07F7F7F7F7F7F000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0008080808080800ULL;
		
		s = (52 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	my_discs = discs_player & 0X0000000001020000ULL;
	opp_discs = (discs_opponent & 0X0000000000020400ULL) | 0X0000000000FDF800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000000020400ULL;
		
		s = (60 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NE[s];
	}

	/* direction NW */
	my_discs = discs_player & 0X0000008040200000ULL;
	opp_discs = (discs_opponent & 0X0000000040201000ULL) | 0X0000007FBFDFE000ULL;
	r = (opp_discs + 0X0000000000001000ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000000040201000ULL;
		
		s = (51 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction _E */
	my_discs = discs_player & 0X0000000000000003ULL;
	r = ((my_discs<<1) + discs_opponent) & 0X0000000000000008ULL;
	if(r != 0) {
		s = _cntlzll(my_discs) - 61;
		move.flipped |= 0X0000000000000008ULL - (0X0000000000000008ULL>>s);
		
		move.hash_code ^= HASH__E[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000E0ULL;
	r = (discs_opponent + 0X0000000000000010ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000000000F0ULL;
		
		s = 59 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000008ULL;
	move.position = E8;
	
	return true;

}

bool RXBitBoard::generate_move_F8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XF71AA37EC76E7E58ULL, 0X790B918AF5599202ULL};
	static const unsigned long long HASH_N_[] = { 0, 0X5841F18592D8E3F8ULL, 0X0133BF809CA92CD2ULL, 0X5168993B2EFADA1EULL, 0X9EF2E943161523E5ULL, 0XE3652F6231FBDAB4ULL, 0X630404288D3022A8ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X2FEE02B78446BA20ULL, 0XF77E58174B339EC3ULL, 0X09E7E21D03DF2E83ULL, 0X4DCB6470185E9933ULL};
	static const unsigned long long HASH__W[] = { 0, 0X73F5F09A01D65BBDULL, 0XD8ECCEA86A4E43E6ULL, 0XCDA0A3F6DF78F6FDULL, 0X73C816674AA4BF95ULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction N_ */
	my_discs = discs_player & 0X0404040404040000ULL;
	opp_discs = (discs_opponent & 0X0004040404040400ULL) | 0X03FBFBFBFBFBF800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0004040404040400ULL;
		
		s = (53 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction NE */
	if(((discs_opponent & 0X0000000000000200ULL) != 0)  && ((discs_player & 0X0000000000010000ULL) != 0)) {
		move.flipped |= 0X0000000000000200ULL;
		move.hash_code ^= 0XC82BA6EA9363AE85ULL;
	}

	/* direction NW */
	my_discs = discs_player & 0X0000804020100000ULL;
	opp_discs = (discs_opponent & 0X0000004020100800ULL) | 0X00007FBFDFEFF000ULL;
	r = (opp_discs + 0X0000000000000800ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000004020100800ULL;
		
		s = (52 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction _E */
	if(((discs_opponent & 0X0000000000000002ULL) != 0)  && ((discs_player & 0X0000000000000001ULL) != 0)) {
		move.flipped |= 0X0000000000000002ULL;
		move.hash_code ^= 0X1DE5A7BB64723C91ULL;
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000F0ULL;
	r = (discs_opponent + 0X0000000000000008ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000000000F8ULL;
		
		s = 60 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000004ULL;
	move.position = F8;
	
	return true;

}

bool RXBitBoard::generate_move_G8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0XB0CD851861F3B7B6ULL, 0XAD2822A305818B27ULL};
	static const unsigned long long HASH_NW[] = { 0, 0X5841F18592D8E3F8ULL, 0XA9D8093BE183A074ULL, 0X715A0480B231955DULL, 0X7F14E2475A416A11ULL, 0XA2C6FDAD4E415012ULL};
	static const unsigned long long HASH_N_[] = { 0, 0XC82BA6EA9363AE85ULL, 0XDE9364DF992A40D9ULL, 0XD32B5CBEE6851F24ULL, 0X9D09B29FED67BAF0ULL, 0X3F4E88F81DB931F9ULL, 0X05376CC0BC087274ULL};
	static const unsigned long long HASH__W[] = { 0, 0X8E1132F43237EC5AULL, 0XFDE4C26E33E1B7E7ULL, 0X56FDFC5C5879AFBCULL, 0X43B19102ED4F1AA7ULL, 0XFDD92493789353CFULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NW */
	my_discs = discs_player & 0X0080402010080000ULL;
	opp_discs = (discs_opponent & 0X0000402010080400ULL) | 0X007FBFDFEFF7F800ULL;
	r = (opp_discs + 0X0000000000000400ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0000402010080400ULL;
		
		s = (53 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0202020202020000ULL;
	opp_discs = (discs_opponent & 0X0002020202020200ULL) | 0X01FDFDFDFDFDFC00ULL;
	r = (opp_discs + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0002020202020200ULL;
		
		s = (54 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000F8ULL;
	r = (discs_opponent + 0X0000000000000004ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000000000FCULL;
		
		s = 61 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000002ULL;
	move.position = G8;
	
	return true;

}

bool RXBitBoard::generate_move_H8(RXMove& move) const {
	
	static const unsigned long long HASH[]    = {    0X5F4871C661CF2338ULL, 0X33FEA1852435F281ULL};
	static const unsigned long long HASH_NW[] = { 0, 0XC82BA6EA9363AE85ULL, 0X9159E8EF9D1261AFULL, 0X5F28DA8927347013ULL, 0X8B555A07AD66A80FULL, 0X9F59293603651ED4ULL, 0XDE2AB12F804E65DFULL};
	static const unsigned long long HASH_N_[] = { 0, 0X30F620F2C40BFC64ULL, 0XF567663AFCEBAA45ULL, 0X523E08CF1647DE0DULL, 0X311E1F2914C820BDULL, 0X2F526F94DDAD3D97ULL, 0X481C17F2DF6E9F42ULL};
	static const unsigned long long HASH__W[] = { 0, 0X1DE5A7BB64723C91ULL, 0X93F4954F5645D0CBULL, 0XE00165D557938B76ULL, 0X4B185BE73C0B932DULL, 0X5E5436B9893D2636ULL, 0XE03C83281CE16F5EULL};

	move.flipped = 0ULL;
	move.hash_code = HASH[player];

	const unsigned long long discs_player = discs[player];
	const unsigned long long discs_opponent = discs[player^1];

	unsigned long long my_discs, opp_discs, r, s;



	/* direction NW */
	my_discs = discs_player & 0X8040201008040000ULL;
	opp_discs = (discs_opponent & 0X0040201008040200ULL) | 0X7FBFDFEFF7FBFC00ULL;
	r = (opp_discs + 0X0000000000000200ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0040201008040200ULL;
		
		s = (54 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_NW[s];
	}

	/* direction N_ */
	my_discs = discs_player & 0X0101010101010000ULL;
	opp_discs = (discs_opponent & 0X0001010101010100ULL) | 0X00FEFEFEFEFEFE00ULL;
	r = (opp_discs + 0X0000000000000100ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X0001010101010100ULL;
		
		s = (55 - _cntlzll(r)) >> 3;
		move.hash_code ^= HASH_N_[s];
	}

	/* direction _W */
	my_discs = discs_player & 0X00000000000000FCULL;
	r = (discs_opponent + 0X0000000000000002ULL) & my_discs;
	if(r != 0) {
		move.flipped |= (r-1) & 0X00000000000000FEULL;
		
		s = 62 - _cntlzll(r);
		move.hash_code ^= HASH__W[s];
	}

	if(move.flipped == 0)
		return false;
	
	move.square = 0X0000000000000001ULL;
	move.position = H8;
	
	return true;

}



void RXBitBoard::init_generate_move() {

	generate_move[A1] = &RXBitBoard::generate_move_A1;
	generate_move[A2] = &RXBitBoard::generate_move_A2;
	generate_move[A3] = &RXBitBoard::generate_move_A3;
	generate_move[A4] = &RXBitBoard::generate_move_A4;
	generate_move[A5] = &RXBitBoard::generate_move_A5;
	generate_move[A6] = &RXBitBoard::generate_move_A6;
	generate_move[A7] = &RXBitBoard::generate_move_A7;
	generate_move[A8] = &RXBitBoard::generate_move_A8;

	generate_move[B1] = &RXBitBoard::generate_move_B1;
	generate_move[B2] = &RXBitBoard::generate_move_B2;
	generate_move[B3] = &RXBitBoard::generate_move_B3;
	generate_move[B4] = &RXBitBoard::generate_move_B4;
	generate_move[B5] = &RXBitBoard::generate_move_B5;
	generate_move[B6] = &RXBitBoard::generate_move_B6;
	generate_move[B7] = &RXBitBoard::generate_move_B7;
	generate_move[B8] = &RXBitBoard::generate_move_B8;
	
	generate_move[C1] = &RXBitBoard::generate_move_C1;
	generate_move[C2] = &RXBitBoard::generate_move_C2;
	generate_move[C3] = &RXBitBoard::generate_move_C3;
	generate_move[C4] = &RXBitBoard::generate_move_C4;
	generate_move[C5] = &RXBitBoard::generate_move_C5;
	generate_move[C6] = &RXBitBoard::generate_move_C6;
	generate_move[C7] = &RXBitBoard::generate_move_C7;
	generate_move[C8] = &RXBitBoard::generate_move_C8;
	
	generate_move[D1] = &RXBitBoard::generate_move_D1;
	generate_move[D2] = &RXBitBoard::generate_move_D2;
	generate_move[D3] = &RXBitBoard::generate_move_D3;
	generate_move[D6] = &RXBitBoard::generate_move_D6;
	generate_move[D7] = &RXBitBoard::generate_move_D7;
	generate_move[D8] = &RXBitBoard::generate_move_D8;

	generate_move[E1] = &RXBitBoard::generate_move_E1;
	generate_move[E2] = &RXBitBoard::generate_move_E2;
	generate_move[E3] = &RXBitBoard::generate_move_E3;
	generate_move[E6] = &RXBitBoard::generate_move_E6;
	generate_move[E7] = &RXBitBoard::generate_move_E7;
	generate_move[E8] = &RXBitBoard::generate_move_E8;

	generate_move[F1] = &RXBitBoard::generate_move_F1;
	generate_move[F2] = &RXBitBoard::generate_move_F2;
	generate_move[F3] = &RXBitBoard::generate_move_F3;
	generate_move[F4] = &RXBitBoard::generate_move_F4;
	generate_move[F5] = &RXBitBoard::generate_move_F5;
	generate_move[F6] = &RXBitBoard::generate_move_F6;
	generate_move[F7] = &RXBitBoard::generate_move_F7;
	generate_move[F8] = &RXBitBoard::generate_move_F8;

	generate_move[G1] = &RXBitBoard::generate_move_G1;
	generate_move[G2] = &RXBitBoard::generate_move_G2;
	generate_move[G3] = &RXBitBoard::generate_move_G3;
	generate_move[G4] = &RXBitBoard::generate_move_G4;
	generate_move[G5] = &RXBitBoard::generate_move_G5;
	generate_move[G6] = &RXBitBoard::generate_move_G6;
	generate_move[G7] = &RXBitBoard::generate_move_G7;
	generate_move[G8] = &RXBitBoard::generate_move_G8;

	generate_move[H1] = &RXBitBoard::generate_move_H1;
	generate_move[H2] = &RXBitBoard::generate_move_H2;
	generate_move[H3] = &RXBitBoard::generate_move_H3;
	generate_move[H4] = &RXBitBoard::generate_move_H4;
	generate_move[H5] = &RXBitBoard::generate_move_H5;
	generate_move[H6] = &RXBitBoard::generate_move_H6;
	generate_move[H7] = &RXBitBoard::generate_move_H7;
	generate_move[H8] = &RXBitBoard::generate_move_H8;

}

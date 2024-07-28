/*
 *  RXSearch.cpp
 *  Roxane
 *
 *  Created by BrunoCausse on 07/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "RXSearch.h"

void RXBestMove::to_COsMoveListItem(COsMoveListItem& mli) {
	
	if (position == PASS) {
		mli.mv.fPass = true;
		mli.mv.row = -1;
		mli.mv.col = -1;
		
	} else {
		mli.mv.fPass = false;
		mli.mv.row = 7 - static_cast<int>(floor(position/8));
		mli.mv.col = 7 - position%8;
	}
	
	mli.dEval = (double)score/VALUE_DISC;
	mli.tElapsed = tElapsed;
	
}

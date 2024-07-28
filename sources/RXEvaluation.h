/*
 *  RXEvaluation.h
 *  Roxane
 *
 *  Created by Bruno Causse on 06/08/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#ifndef RXEVALUATION_H
#define RXEVALUATION_H

#include <iostream>

#include "RXConstantes.h"

class RXEvaluation {
	
	static const unsigned int START = 16;
	static const unsigned int END = 57;

	friend class RXBBPatterns;

	public :
	
	static short* DIAG_5[61];

	static short* DIAG_6[61];
	
	static short* DIAG_7[61];

	static short* DIAG_8[61];
	
	static short* HV_4[61];

	static short* HV_3[61];

	static short* HV_2[61];
	
	static short* EDGE_6_4[61];

	static short* CORNER_2x5[61];
	
	static short* CORNER_11[61];
	
	static short* EDGE_2XC[61];
	
	//public :
	
	static void load();
	
	~RXEvaluation() {
		
//		const unsigned int START = 16;
//		const unsigned int END = 57;

		for(unsigned int iStage = START; iStage<END; iStage++) {
			
			DIAG_5[iStage] -= 121;
			delete[]	DIAG_5[iStage];
			DIAG_6[iStage] -= 364;
			delete[]	DIAG_6[iStage];
			DIAG_7[iStage] -= 1093;
			delete[]	DIAG_7[iStage];
			DIAG_8[iStage] -= 3280;
			delete[]	DIAG_8[iStage];
			
			HV_4[iStage] -= 3280;
			delete[]	HV_4[iStage];
			HV_3[iStage] -= 3280;
			delete[]	HV_3[iStage];
			HV_2[iStage] -= 3280;
			delete[]	HV_2[iStage];
			
			EDGE_6_4[iStage] -= 29524;
			delete[]	EDGE_6_4[iStage];
			CORNER_2x5[iStage] -= 29524;
			delete[]	CORNER_2x5[iStage];
			CORNER_11[iStage] -= 88573;
			delete[]	CORNER_11[iStage];
			EDGE_2XC[iStage] -= 265720;
			delete[]	EDGE_2XC[iStage];
		}
		
	};


		
};




#endif

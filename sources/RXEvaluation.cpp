/*
 *  RXEvaluation.cpp
 *  Roxane
 *
 *  Created by Bruno Causse on 06/08/05.
 *  Copyleft 2005-2024 personnel.
 *
 */

#include <fstream>
#include <cmath>

#include "RXEvaluation.hpp"


short* RXEvaluation::DIAG_5[61];

short* RXEvaluation::DIAG_6[61];

short* RXEvaluation::DIAG_7[61];

short* RXEvaluation::DIAG_8[61];

short* RXEvaluation::HV_4[61];

short* RXEvaluation::HV_3[61];

short* RXEvaluation::HV_2[61];

short* RXEvaluation::EDGE_6_4[61];

short* RXEvaluation::CORNER_2x5[61];

short* RXEvaluation::CORNER_11[61];

short* RXEvaluation::EDGE_2XC[61];



void RXEvaluation::load() {

//	const unsigned int START = 16;
//	const unsigned int END = 57;

	// creation des tables
	
	std::ifstream from("/Users/caussebruno/Documents/othello/MPRoxane[2024-07-21]/build/Coefficientsi386.data", std::ios::binary); //Edmond
	if(from) {
		//chargement des donnees & decalage des tables
		for(unsigned int iStage = START; iStage<END; iStage++) {

			DIAG_5[iStage] = new short[243];
			from.read(reinterpret_cast<char*> (DIAG_5[iStage]), sizeof(short)*243);
			DIAG_5[iStage] += 121;
			
			DIAG_6[iStage] = new short[729];
			from.read(reinterpret_cast<char*> (DIAG_6[iStage]), sizeof(short)*729);
			DIAG_6[iStage] += 364;

			DIAG_7[iStage] = new short[2187];
			from.read(reinterpret_cast<char*> (DIAG_7[iStage]), sizeof(short)*2187);
			DIAG_7[iStage] += 1093;

			DIAG_8[iStage] = new short[6561];
			from.read(reinterpret_cast<char*> (DIAG_8[iStage]), sizeof(short)*6561);
			DIAG_8[iStage] += 3280;

			HV_4[iStage] = new short[6561];
			from.read(reinterpret_cast<char*> (HV_4[iStage]), sizeof(short)*6561);
			HV_4[iStage] += 3280;

			HV_3[iStage] = new short[6561];
			from.read(reinterpret_cast<char*> (HV_3[iStage]), sizeof(short)*6561);
			HV_3[iStage] += 3280;

			HV_2[iStage] = new short[6561];
			from.read(reinterpret_cast<char*> (HV_2[iStage]), sizeof(short)*6561);
			HV_2[iStage] += 3280;

			EDGE_6_4[iStage] = new short[59049];
			from.read(reinterpret_cast<char*> (EDGE_6_4[iStage]), sizeof(short)*59049);
			EDGE_6_4[iStage] += 29524;

			CORNER_2x5[iStage] = new short[59049];
			from.read(reinterpret_cast<char*> (CORNER_2x5[iStage]), sizeof(short)*59049);
			CORNER_2x5[iStage] += 29524;

			CORNER_11[iStage] = new short[177147];
			from.read(reinterpret_cast<char*> (CORNER_11[iStage]), sizeof(short)*177147);
			CORNER_11[iStage] += 88573;

			EDGE_2XC[iStage] = new short[531441];
			from.read(reinterpret_cast<char*> (EDGE_2XC[iStage]), sizeof(short)*531441);
			EDGE_2XC[iStage] += 265720;
			
		}
	}
	from.close();

	
	// recopie des extremites
	
	//du stage 0 au START
	for(unsigned int iStage = 0; iStage<START; iStage++) {

		DIAG_5[iStage] = DIAG_5[START];
		DIAG_6[iStage] = DIAG_6[START];
		DIAG_7[iStage] = DIAG_7[START];
		DIAG_8[iStage] = DIAG_8[START];
		HV_4[iStage] = HV_4[START];
		HV_3[iStage] = HV_3[START];
		HV_2[iStage] = HV_2[START];
		EDGE_6_4[iStage] = EDGE_6_4[START];
		CORNER_2x5[iStage] = CORNER_2x5[START];
		CORNER_11[iStage] = CORNER_11[START];
		EDGE_2XC[iStage] = EDGE_2XC[START];
		
	}
	
	//du Stage END au 61
	for(unsigned int iStage = END; iStage<61; iStage++) {

		DIAG_5[iStage] = DIAG_5[END-1];
		DIAG_6[iStage] = DIAG_6[END-1];
		DIAG_7[iStage] = DIAG_7[END-1];
		DIAG_8[iStage] = DIAG_8[END-1];
		HV_4[iStage] = HV_4[END-1];
		HV_3[iStage] = HV_3[END-1];
		HV_2[iStage] = HV_2[END-1];
		EDGE_6_4[iStage] = EDGE_6_4[END-1];
		CORNER_2x5[iStage] = CORNER_2x5[END-1];
		CORNER_11[iStage] = CORNER_11[END-1];
		EDGE_2XC[iStage] = EDGE_2XC[END-1];
		
	}

}




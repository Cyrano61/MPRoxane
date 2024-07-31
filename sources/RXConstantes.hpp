/*
 *  RXConstantes.hpp
 *  learn_01
 *
 *  Created by Bruno Causse on 11/05/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#ifndef RXCONSTANTES_HPP
#define RXCONSTANTES_HPP

#include <limits>

/*! constants for colors */
enum {
	BLACK = 0,
	WHITE,
	UNDEF
};

/*! constants for square coordinates */
enum {

	H8 = 0, G8, F8, E8, D8, C8, B8, A8,
	H7, G7, F7, E7, D7, C7, B7, A7,
	H6, G6, F6, E6, D6, C6, B6, A6,
	H5, G5, F5, E5, D5, C5, B5, A5,
	H4, G4, F4, E4, D4, C4, B4, A4,
	H3, G3, F3, E3, D3, C3, B3, A3,
	H2, G2, F2, E2, D2, C2, B2, A2,
	H1, G1, F1, E1, D1, C1, B1, A1,
	
	PASS = 127,
	NOMOVE = 255
};

/*! flipping directions */
enum {
	NW = 0, N, NE,  E, SE, S , SW,  W
};




/*! maximal score */
const short UNDEF_SCORE = -std::numeric_limits<short>::max();
const short INTERRUPT_SEARCH = 32000;
const short MAX_SCORE = 22222; //must diff %VALUE_DISC == 0 (222,22 discs)
const int VALUE_DISC = 100;
const unsigned int SHARED = 0;

#endif

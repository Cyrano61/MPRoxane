/*
 *  RXSquareList.hpp
 *  learn_01
 *
 *  Created by Bruno Causse on 11/05/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */


#ifndef RXSQUARELIST_HPP
#define RXSQUARELIST_HPP

#include "RXConstantes.hpp"

class RXSquareList {

	friend class RXBitBoard;
	friend class RXEngine;
	friend class RXHashTable;
	
	int position;
	RXSquareList *previous;
	RXSquareList *next;

	RXSquareList(): position(NOMOVE), previous(NULL), next(NULL) {};			

};

#endif


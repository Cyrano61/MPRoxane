/*
 *  RXSquareList.h
 *  learn_01
 *
 *  Created by Bruno Causse on 11/05/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */


#ifndef RXSQUARELIST_H
#define RXSQUARELIST_H

#include "RXConstantes.h"

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


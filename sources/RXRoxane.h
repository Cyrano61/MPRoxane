/*
 *  RXRoxane.h
 *  BitBoard
 *
 *  Created by Bruno Causse on 01/09/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#ifndef RXROXANE_H
#define RXROXANE_H

#include <string>
#include<atomic>

#include "OsObjects.h"
#include "ODKStream.h"

#include "RXConstantes.h"
#include "RXBBPatterns.h"
#include "RXHashTable.h"
#include "RXEngine.h"
#include "RXHelper.h"
#include "RXSearch.h"

extern "C"
void* init_process(void* pt);

class CODKStream;
class CassioProtocol;

class RXRoxane: public Runnable {

	RXHashTable* hTable;
	RXHashTable* main_PV;
	RXHashTable* expected_PV;

	RXEngine* engine[2]; //BLACK and WHITE
	RXSearch search;

	pthread_t process[1];
	
	pthread_mutex_t mutex;
	
	//volatile bool resume_flag;
    std::atomic_bool resume_flag;
    
	//interface GGS server
	CODKStream* GGSClient;
	COsPosition game[2];
	string idg;

	unsigned long long hash_opening[60];
	char move_opening[60];

		
	

public :

	RXRoxane(unsigned int size_hashtable = 20, int max_thread = 1);	
	~RXRoxane();
	
	
	void resume();

	virtual void run();

	
	//privateProtocol
	void get_move(const std::string& file_name);


	//wthorProtocol
	void check_allWTHOR();
	void check_WTHOR(const std::string& file_name, const std::string& file_error);
	
	
	//GGSProtocol
	void connectGGS(CODKStream* client);
	void imposed_opening(const std::string& line);

	void get_move(const std::string& _idg, COsGame* game);

	void sendMsg(std::string msg);
	
	

};


#endif


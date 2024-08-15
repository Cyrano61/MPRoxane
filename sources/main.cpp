/*
 *  main.cpp
 *  Roxane
 *
 *  Created by Bruno Causse on 10/08/05.
 *  Copyright 2005-2024 personnel. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <pthread.h>


#include "types.hpp"

#include "ODKStream.hpp"
#include "RXRoxane.hpp"
#include "RXBBPatterns.hpp"

#include "RXEngine.hpp"
#include "RXTools.hpp"


/*******************************************************************/
/*           version Fast Solver             */
/*                                           */
/*   split at EG_PVS_root    fforum-40-59    */
/*   selectivity 84% et 100% fforum-40-59    */
/*******************************************************************/


int main (int argc, char * const argv[]) {
    	
	std::string login, password, file_name, mode, imposed_opening = "";
	unsigned int nBitsTable = 20;
	unsigned int nThreads = 1;
	
	for(int i = 1; i<argc; i++) {
		
		std::string arg(argv[i]);
		if(arg == "-login" && i+1<argc) {
			login = argv[++i];
		} else if(arg == "-passw" && i+1<argc) {
			password =  argv[++i];
		} else if(arg == "-fixeline" && i+1<argc) {
			imposed_opening = argv[++i];
		}  else if(arg == "-h" && i+1<argc) {
			std::istringstream iss(argv[++i]);
			iss >> nBitsTable;
		} else if(arg == "-t" && i+1<argc) {
			std::istringstream iss(argv[++i]);
			iss >> nThreads;
		} else if(arg == "-mode" && i+1<argc) {
			mode =  argv[++i];
		} else if(file_name.empty()) {
			file_name = argv[i];
		}
	}

	std::cout << "Version Roxane 1.8.0" << std::endl;
	std::cout << "Number of threads: " << nThreads << std::endl;
	std::cout << "Size hashTable: " << nBitsTable << std::endl;
    std::cout << file_name << std::endl;
    
	
	RXRoxane roxane(nBitsTable, nThreads);
    
 
	
	//warm up
	if(!file_name.empty())
		roxane.get_move(file_name);
	
	if(imposed_opening != "")
		roxane.imposed_opening(imposed_opening);
	
	
//	if(mode == "wthor")
//		roxane.check_allWTHOR(); //try for robust endgame
	
	
	if(mode == "ggs" && !login.empty() && !password.empty()) {

        std::cout << "tentative conection" << std::endl;

		int err;
		CODKStream gs;
		
		roxane.connectGGS(&gs);
		gs.pComputer = &roxane;
		
		// Connect(server, port)
		if ((err = gs.Connect("www.skatgame.net",5000))) {
            std::cout << "erreur conection" << std::endl;

			cerr << gs.ErrText(err) << "\n";
			return err;
		}
		
		// Login(name, password)
		if ((err = gs.Login(login.c_str(), password.c_str()))) {
			cerr << gs.ErrText(err) << "\n";
			gs.Disconnect();
			return err;
		}
        
        std::cout << "lance le process" <<std::endl;
		
		gs.Process();			// receive, parse, and pass on messages
	}
	
	

	return 0;
}


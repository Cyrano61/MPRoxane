/*
 *  RXThreadHelper.h
 *  Roxane
 *
 *  Created by BrunoCausse on 10/09/08.
 *  Copyright 2008 personnel. All rights reserved.
 *
 */
#ifndef RXHELPER_H
#define RXHELPER_H

#include <pthread.h>

// Interface
class RXHelper {
	public :
	virtual void idle_loop() = 0;
};

// Interface
class Runnable {
	public :
	virtual void run() = 0;
};

#endif

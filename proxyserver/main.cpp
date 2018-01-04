/*
 * main.cpp
 *
 *  Created on: 2013-8-21
 *      Author: aaaa
 */

#include "stdio.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

#include "CServer.h"

//#include "memcheck.h"
//#include "memorydebug.h"

int main(int argc, char ** argv) {

	if (g_Server.Init())
		g_Server.Start(argc, argv);


	printf("ProxyServer is Exit\n");
	//DumpUnfreed();

	return 0;
}

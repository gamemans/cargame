//============================================================================
// Name        : robot.cpp
// Author      : ww
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
//#include "memcheck.h"
using namespace std;
#include "CNetApp.h"
#include "GetTime.h"

class bbb
{

};

class aaa
{
public:
	bbb b;
};

map<int, aaa *> p;
int main(int argc, char * argv[]) {


	//delete p1;
	usleep(1000);
	printf("%lu\n", RakNet::GetTime());


	//CNetApp app;
	g_NetApp.Init();
	g_NetApp.Run();

//	DumpUnfreed();
	return 0;
}

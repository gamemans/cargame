VPATH = ../src:../include:../common
all:game 

INC = -I../include
SDKINC = -I../raknetsdk64/include
SDKEXINC = -I../raknet64
#XML_INC = -I/usr/local/include/libxml2
XML_INC = -I/usr/include/libxml2
COMMON_INC = -I../common
DBUG = -g

LIB = -L ~/workspace/game/libs -lraknet64 -lraknetsdk64 -lxml2 -lrt
game: main.o CBase.o CServer.o CBaseGame.o CMJGame.o CBaseUser.o CMJUser.o CPlayer.o CBaselist.o CTimer.o
	g++ $(DBUG) $^ -o $@ -I../include $(LIB)

main.o: main.cpp 
	g++ $(DBUG) -c ../src/main.cpp $(INC) $(SDKINC) $(SDKEXINC) $(XML_INC) $(COMMON_INC) 

CBase.o: CBase.cpp CTimer.o
	g++ $(DBUG) -c ../src/CBase.cpp $(INC) $(SDKINC)
	
CServer.o: CServer.cpp
	g++ $(DBUG) -c ../src/CServer.cpp $(INC) $(SDKINC) $(SDKEXINC) $(XML_INC) $(COMMON_INC)

CBaseGame.o: CBaseGame.cpp
	g++ $(DBUG) -c ../src/CBaseGame.cpp $(INC) $(SDKINC) $(SDKEXINC) $(XML_INC) $(COMMON_INC)

CMJGame.o:CMJGame.cpp
	g++ $(DBUG) -c ../src/CMJGame.cpp $(INC) $(SDKINC) $(COMMON_INC)

CMJUser.o:CMJUser.cpp
	g++ $(DBUG) -c ../src/CMJUser.cpp $(INC) $(SDKINC)

CBaseUser.o:CBaseUser.cpp
	g++ $(DBUG) -c ../src/CBaseUser.cpp $(INC)

CPlayer.o:CPlayer.cpp
	g++ $(DBUG) -c ../src/CPlayer.cpp $(INC) $(SDKINC)

CBaselist.o:CBaselist.cpp
	g++ $(DBUG) -c ../src/CBaselist.cpp $(INC) $(SDKINC) $(XML_INC) $(SDKEXINC)

CTimer.o:CTimer.cpp
	g++ $(DBUG) -c ../src/CTimer.cpp $(INC)

clean:
	-rm game *.o

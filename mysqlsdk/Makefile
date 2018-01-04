HEAD_DIR = -I/usr/include/mysql
LIB_DIR = -L/usr/lib/mysql
LIB = -lmysqlclient
CC = g++
OBJ = CMysqlManager.cpp
all:$(OBJ)
	$(CC) $(OBJ) $(LIB) $(LIB_DIR) -fPIC -g -shared -o libmysqlsdk.so 

.PHONY: clean
clean:
	rm libmysqlsdk.so
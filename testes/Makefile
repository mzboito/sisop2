
CC=gcc
LIB_DIR=../lib
INC_DIR=../include
BIN_DIR=../bin
SRC_DIR=../src

all:
	gcc -c $(SRC_DIR)/t2fs.c -o $(LIB_DIR)/t2fs.o -Wall
	gcc -c $(SRC_DIR)/aux.c -o $(LIB_DIR)/aux.o -Wall
	gcc -c $(SRC_DIR)/utils.c -o $(LIB_DIR)/utils.o -Wall
	ar crs $(LIB_DIR)/libt2fs.a $(LIB_DIR)/utils.o $(LIB_DIR)/t2fs.o $(LIB_DIR)/aux.o $(LIB_DIR)/apidisk.o 
	gcc -o $(BIN_DIR)/structures_tester structures_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/createsAndDeletes_tester createsAndDeletes_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/openCloseFile_tester openCloseFile_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/seek_tester seek_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/readFile_tester readFile_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/openClosedir_tester openClosedir_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/getSetDirPath_tester getSetDirPath_tester.c -L$(LIB_DIR) -lt2fs -Wall
	gcc -o $(BIN_DIR)/writeFile_tester writeFile_tester.c -L$(LIB_DIR) -lt2fs -Wall
	
clean:
	rm $(BIN_DIR)/*_tester

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all:
	gcc -c $(SRC_DIR)/t2fs.c -o $(LIB_DIR)/t2fs.o -Wall
	gcc -c $(SRC_DIR)/aux.c -o $(LIB_DIR)/aux.o -Wall
	gcc -c $(SRC_DIR)/utils.c -o $(LIB_DIR)/utils.o -Wall
	ar crs $(LIB_DIR)/libt2fs.a $(LIB_DIR)/utils.o $(LIB_DIR)/t2fs.o $(LIB_DIR)/aux.o $(LIB_DIR)/apidisk.o

clean:
	rm -rf $(LIB_DIR)/*.a $(LIB_DIR)/t2fs.o $(LIB_DIR)/aux.o $(LIB_DIR)/utils.o

#
# Makefile ESQUELETO
#
# DEVE ter uma regra "all" para geração da biblioteca
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#
#

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all:
	gcc -c src/utils.c -o bin/utils.o -Wall
	gcc -c src/aux.c -o bin/aux.o -Wall
	gcc -c src/t2fs.c -o bin/t2fs.o -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/t2fs.o $(BIN_DIR)/aux.o $(BIN_DIR)/utils.o $ $(SRC_DIR)/*~ $(INC_DIR)/*~ *~

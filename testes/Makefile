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
LIB_DIR=../lib
INC_DIR=../include
BIN_DIR=../bin
SRC_DIR=../src

all:
	gcc -c structures_tester.c -o structures_tester.o
	gcc -o structures_tester $(BIN_DIR)/* structures_tester.o
	gcc -c createsAndDeletes_tester.c -o createsAndDeletes_tester.o
	gcc -o createsAndDeletes_tester $(BIN_DIR)/* createsAndDeletes_tester.o
	gcc -c openCloseFile_tester.c -o openCloseFile_tester.o
	gcc -o openCloseFile_tester $(BIN_DIR)/* openCloseFile_tester.o
	gcc -c seek_tester.c -o seek_tester.o
	gcc -o seek_tester $(BIN_DIR)/* seek_tester.o
	gcc -c readFile_tester.c -o readFile_tester.o
	gcc -o readFile_tester $(BIN_DIR)/* readFile_tester.o
	gcc -c openClosedir_tester.c -o openClosedir_tester.o
	gcc -o openClosedir_tester $(BIN_DIR)/* openClosedir_tester.o
	gcc -c getSetDirPath_tester.c -o getSetDirPath_tester.o
	gcc -o getSetDirPath_tester $(BIN_DIR)/* getSetDirPath_tester.o

clean:
	rm *_tester

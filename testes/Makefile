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
	gcc -c delete2_tester.c -o delete2_tester.o
	gcc -o delete2_tester $(BIN_DIR)/* delete2_tester.o
	gcc -c mkdir2_tester.c -o mkdir2_tester.o
	gcc -o mkdir2_tester $(BIN_DIR)/* mkdir2_tester.o
	gcc -c getcwd2_tester.c -o getcwd2_tester.o
	gcc -o getcwd2_tester $(BIN_DIR)/* getcwd2_tester.o

clean:
	rm *_tester

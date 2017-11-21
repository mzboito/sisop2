#pragma once
#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include "t2fs.h"
//#include "apidisk.h"

/*OUR CONTROL VARIABLES*/
extern SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
extern DWORD *FAT; //ponteiro para a FAT
extern struct t2fs_record *ROOT;
extern int partitionInfoInitialized;

#define ERROR_FAT 0xFFFFFFFE
#define EOF_FAT 0xFFFFFFFF
#define FREE_FAT 0x00000000

#define MAX_OPEN_FILES 10

int structures_init();
int readSuperBlock();
int initializeFAT();
int initializeRoot();
int read_cluster();
int write_cluster();
DWORD cluster2sector();
void debugStructures();

#endif

#pragma once
#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include "t2fs.h"
//#include "apidisk.h"

/*OUR CONTROL VARIABLES*/
extern SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
extern DWORD *FAT; //ponteiro para a FAT
extern int partitionInfoInitialized;

#define ERROR_FAT 0xFFFFFFFE
#define EOF_FAT 0xFFFFFFFF

#define MAX_OPEN_FILES 10


int readSuperBlock();
int initializeFAT();

#endif

#pragma once

/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include "t2fs.h"
#include "apidisk.h"

/*OUR CONTROL VARIABLES*/
SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
DWORD *FAT; //ponteiro para a FAT

#define ERROR_FAT 0xFFFFFFFE
#define EOF_FAT 0xFFFFFFFF

#define MAX_OPEN_FILES 10

int partitionInfoInitialized = -1;

int readSuperBlock();
int initializeFAT();

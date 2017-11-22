#pragma once
#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include "t2fs.h"

#define ERROR_FAT 0xFFFFFFFE
#define EOF_FAT 0xFFFFFFFF
#define FREE_FAT 0x00000000

#define MAX_OPEN_FILES 10

/*OUR CONTROL VARIABLES*/
extern SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
extern DWORD *FAT; //ponteiro para a FAT
extern struct t2fs_record *ROOT;
extern File_descriptor OPEN_FILES[MAX_OPEN_FILES];

extern int partitionInfoInitialized;
extern DWORD FATtotalSize;
extern int nOpenFiles;


int structures_init();
int readSuperBlock();
int initializeFAT();
int initializeRoot();
void initializeOpenFiles();
int read_cluster();
int write_cluster();
DWORD cluster2sector();
void debugStructures();
DWORD findFreeCluster();
int findFreeDirEntry(struct t2fs_record *dir);
void* getDirRecord(char *dirPath);
DWORD set_cluster(DWORD i);
DWORD free_cluster(DWORD i);
int getNewHandle();


#endif

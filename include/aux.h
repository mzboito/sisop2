#pragma once
#ifndef AUX_H
#define AUXF_H

/*** FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include "t2fs.h"

#define EOF_FAT 0xFFFFFFFF
#define ERROR_FAT 0xFFFFFFFE
#define FREE_FAT 0x00000000
#define MAX_OPEN_FILES 10

/*OUR CONTROL VARIABLES*/
extern SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
extern DWORD *FAT; //ponteiro para a FAT
extern RECORD *ROOT; //struct t2fs_record *ROOT;
extern RECORD *CURRENT_DIR; //struct t2fs_record CURRENT_DIR;
extern File_descriptor OPEN_FILES[MAX_OPEN_FILES];

extern int partitionInfoInitialized;
extern int nOpenFiles;
extern DWORD FATtotalSize;
extern DWORD DIRsize; //in number of entries
extern char * current_path;

DWORD cluster2sector();
void debugStructures();
int findFreeDirEntry(struct t2fs_record *dir);
RECORD* get_dir(char *dirPath);
int initializeFAT();
void initializeOPEN_FILES();
int initializeROOT();
int printf_directory(RECORD *dir, int count);
int read_cluster();
int readSuperBlock();
DWORD searchEntryPerName(RECORD* dir, char *name, BYTE type);
int structures_init();


/*
int write_cluster();
DWORD findFreeCluster();
DWORD set_cluster(DWORD i);
DWORD free_cluster(DWORD i);
*/
#endif

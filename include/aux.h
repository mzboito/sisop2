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

void addEntry2Dir(RECORD *dir, int position, RECORD entry);
DWORD cluster2sector();
void createNewDir(RECORD *new_dir, RECORD dir_entry, RECORD father_entry);
void debugStructures();
int findEntryInDirectory(RECORD *dir, char *entry_name, BYTE type);
DWORD findFreeCluster();
int findFreeDirEntry(struct t2fs_record *dir);
DWORD free_cluster(DWORD i);
RECORD* get_dir(char *dirPath);
int initializeFAT();
void initializeOPEN_FILES();
int initializeROOT();
int isNotEmpty(RECORD *dir);
int printf_directory(RECORD *dir, int count);
int printf_FAT(int count);
int printf_OPEN_FILES(int count);
int read_cluster();
int readSuperBlock();
DWORD searchEntryPerName(RECORD* dir, char *name, BYTE type);
DWORD set_cluster(DWORD i);
int structures_init();
void wipeFromDirectory(RECORD *dir, char *name, BYTE type);
int write_cluster();
int write_DIR(RECORD *dir);
int write_FAT();

#endif

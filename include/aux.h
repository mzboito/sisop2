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
extern Directory_descriptor OPEN_DIRS[MAX_OPEN_FILES];

extern int partitionInfoInitialized;
extern int nOpenFiles;
extern int nOpenDirs;
extern DWORD FATtotalSize;
extern DWORD DIRsize; //in number of entries
extern char *current_path;

void addEntry2Dir(RECORD *dir, int position, RECORD entry);
DWORD cluster2sector();
void createNewDir(RECORD *new_dir, RECORD dir_entry, RECORD father_entry);
void debugStructures();
int findEntryInDirectory(RECORD *dir, char *entry_name, BYTE type);
DWORD findFreeCluster();
int findFreeDirEntry(struct t2fs_record *dir);
int findPointerCluster(DWORD pointer);
DWORD free_cluster(DWORD i);
RECORD* get_dir(char *dirPath);
RECORD* get_opened_dir(DWORD cluster);
int getFileClusters(DWORD first_cluster, DWORD *list);
DWORD getPointerPositionInCluster(DWORD pointer);
int initializeFAT();
void initializeOPEN_LISTS();
int initializeROOT();
int isAnOpenDir(DWORD cluster);
int isNotEmpty(RECORD *dir);
int printf_directory(RECORD *dir, int count);
int printf_FAT(int count);
int printf_OPEN_DIRS(int count);
int printf_OPEN_FILES(int count);
int read_cluster(DWORD data_cluster, BYTE *buffer);
int read_clusters(FILE2 handle, char *buffer, int size);
int readSuperBlock();
DWORD searchEntryPerName(RECORD* dir, char *name, BYTE type);
DWORD set_cluster(DWORD i);
int size2clusterNumber(int size);
int shrink(int handle);
int structures_init();
int updateDirectoryonDisk(int handle);
void wipeFromDirectory(RECORD *dir, char *name, BYTE type);
int write_cluster(DWORD data_cluster, BYTE *buffer);
int write_clusters(FILE2 handle, char *buffer, int size);
int write_DIR(RECORD *dir);
int write_FAT();

#endif

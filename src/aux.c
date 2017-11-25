#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/apidisk.h"
#include "../include/aux.h"
#include "../include/utils.h"

SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
DWORD *FAT; //lista da FAT
RECORD *ROOT;
RECORD *CURRENT_DIR;
File_descriptor OPEN_FILES[MAX_OPEN_FILES];

int partitionInfoInitialized = -1;
int nOpenFiles;
DWORD FATtotalSize;
DWORD DIRsize; //in number of entries
char * current_path;

void addEntry2Dir(RECORD *dir, int position, RECORD entry){
	dir[position].TypeVal = entry.TypeVal;
	strcpy(dir[position].name, entry.name);
	dir[position].bytesFileSize = entry.bytesFileSize;
	dir[position].firstCluster = entry.firstCluster;
}

DWORD cluster2sector(DWORD data_cluster){
	DWORD initialDataSector = partitionInfo->DataSectorStart;
	DWORD displacement = partitionInfo->SectorsPerCluster * data_cluster;
	DWORD firstSector = initialDataSector + displacement;
	return firstSector;
}

void createNewDir(RECORD *new_dir, RECORD dir_entry, RECORD father_entry){
	strcpy(dir_entry.name,".\0"); //instead of the dir name, we use the .
	strcpy(father_entry.name,"..\0"); //father is ..
	addEntry2Dir(new_dir, 0, dir_entry);
	addEntry2Dir(new_dir, 1, father_entry);
	//printf("\n\nNEW DIR\n\n");
	//printf_directory(new_dir, 4);
	//printf("father entry %s\n", father_entry.name);
	//write on the disk
	//return 0;
}

void debugStructures(){
	structures_init();
  printf("Return superBlock_init: %d\n", readSuperBlock());
  if(readSuperBlock() == 0){
    printf("\n\n Now printing the retrieved information from superblock\n\n");
    printf("id: %s\n", partitionInfo->id);
    printf("version: %d\n", partitionInfo->version);
    printf("Superblock size: %d\n", partitionInfo->SuperBlockSize);
    printf("Disk size: %d\n", partitionInfo->DiskSize);
    printf("Number of sectors: %d\n", partitionInfo->NofSectors);
    printf("Sectors per cluster: %d\n", partitionInfo->SectorsPerCluster);
    printf("Fat sector start: %d\n", partitionInfo->pFATSectorStart);
    printf("Root directory start: %d\n", partitionInfo->RootDirCluster);
    printf("Data sector start: %d\n", partitionInfo->DataSectorStart);
    printf("\n\nReturn initializeFAT: %d\n", initializeFAT());
    if(initializeFAT() == 0){
      printf("\n\n Now printing the retrieved information from FAT\n\n");
      printf("FAT length: %d\n", FATtotalSize);
			int i = 0;
			while(i < FATtotalSize){
						printf("%dth FAT sector: %08x\n", i, FAT[i]);
						i++;
			}
			printf("FREE_FAT %08x\n", FREE_FAT);
			printf("ERROR_FAT %08x\n", ERROR_FAT);
			printf("EOF_FAT %08x\n", EOF_FAT);
    }
		if(initializeROOT() == 0){
			int i = 0;
			while(i <= 20){
				printf("name %s\n", ROOT[i].name);
				printf("file size %08x\n", ROOT[i].bytesFileSize);
				printf("first cluster %08x\n", ROOT[i].firstCluster);
				printf("type %04x\n", ROOT[i].TypeVal);
				if(ROOT[i].TypeVal == TYPEVAL_REGULAR)
					printf("        VALID\n");
				i++;
			}
			printf("\ncurrent dir: %s\n\n", CURRENT_DIR->name);
		}

  }
}

DWORD findFreeCluster(){//encontrar cluster livre
	if(structures_init() != 0){
		return -1; //problem initializing
	}
  DWORD i = 0;
  while(i < FATtotalSize){
		if (FAT[i] == FREE_FAT){ //found a free cluster
		   return i;
		}
		i++;
  }
  return ERROR_FAT;
}

int findFreeDirEntry(RECORD *dir){ //get first free position on directory
	int i = 0;
	//all directories use only one CLUSTER each
	while(i < DIRsize){ //iterates until it finds a free entry in the directory
		if(dir[i].TypeVal == TYPEVAL_INVALIDO){
			return i;
		}
		i++;
	}
	return -1;
}

DWORD free_cluster(DWORD i){ //liberar um cluster ocupado na FAT
	if (FAT[i] == ERROR_FAT){ //cannot free an error entry
		return ERROR_FAT; //return -1
	}
	if(FAT[i] == FREE_FAT){ //cannot free a free fat
		return ERROR_FAT; //return -1
	}
	if(FAT[i] != EOF_FAT){
		//if it is not the last file cluster and we free it, we will destroy the file clusters list
		DWORD this = i;
		DWORD next = i;
		while(FAT[this]!= EOF_FAT){ //while is not the next one
				next = FAT[this];
				FAT[this] = FREE_FAT; //wipe this one
				this = next;
		}
		FAT[this] = FREE_FAT;
		return FREE_FAT; //return 0
	}
	FAT[i] = FREE_FAT; //if only one cluster, then just free it
	return FREE_FAT; //return 0
}

RECORD* get_dir(char *dirPath){
	if(structures_init() != 0){
		return NULL;
	}
	int first_time = 1;
	int len = strlen(dirPath);
	char first_dir_name[MAX_FILE_NAME_SIZE];
	char remain[len];
	RECORD *current_local = ROOT;
	printf("dir path %s\n", remain);
	while(strlen(remain)>0){
		int j = deleteFirstDirEntryStr(remain, first_dir_name);
		remain = remain + j;
		printf("first %s, rest %s\n", first_dir_name, remain);
		if(strcmp(first_dir_name, "/\0") == 0){ //if it is the root
			printf("forever here\n");
			current_local = ROOT;
		}else{
			DWORD cluster = searchEntryPerName(current_local, first_dir_name, TYPEVAL_DIRETORIO);
			printf("cluster %d\n", cluster);
			if(cluster == EOF_FAT){
				return NULL; //it is not in current directory
			}
			if(first_time == 0){ //if it is not the first time
					free(current_local);
			}
			/*if(cluster == ROOT[0].firstCluster){ //keep pointer consistency
				current_local = ROOT;
				first_time = 1; //cannot free root
			}*/else{
				RECORD *r = (RECORD *)malloc(SECTOR_SIZE * partitionInfo->SectorsPerCluster);
				read_cluster(cluster, r); //read the new directory
				current_local = r;
			}
		}
	}
	return current_local;
}

int initializeFAT(){
  if(partitionInfoInitialized < 0){
    return -1;
  }
	DWORD initial = partitionInfo->pFATSectorStart;
	DWORD final = partitionInfo->DataSectorStart;
  FATtotalSize = final - initial;
	FAT = (DWORD *)malloc(SECTOR_SIZE * FATtotalSize); // sector size = 256 bytes; FAT entry = 4 bytes
	int entriesPerSector = SECTOR_SIZE/sizeof(DWORD);
	DWORD *initialPoint = FAT;
	while(initial < final){
			if(read_sector(initial, (unsigned char *) FAT) != 0){
				return -1;
			}
			initial = initial + 1;
			FAT = FAT + entriesPerSector;
	}
	FAT = initialPoint;
  return 0;
}

void initializeOPEN_FILES(){
	int i = 0;
	while(i < MAX_OPEN_FILES){
		OPEN_FILES[i].fileHandle = -1;
		i++;
	}
}

int initializeROOT(){
	if(partitionInfoInitialized < 0){
    return -1;
  }
	ROOT = (RECORD *)malloc(SECTOR_SIZE * partitionInfo->SectorsPerCluster);
	if(read_cluster(partitionInfo->RootDirCluster, (char *) ROOT) != 0){
		return -1;
	}
	CURRENT_DIR = &ROOT[0];
	current_path = (char *)malloc(sizeof(char)*300);
	strcpy(current_path, "/\0");
	DIRsize = (SECTOR_SIZE * partitionInfo->SectorsPerCluster) / sizeof(RECORD);
	return 0;
}

int isNotEmpty(RECORD *dir){
	int i = 2; //does not count . and ..
	while(i < DIRsize){
		if(dir[i].TypeVal != TYPEVAL_INVALIDO){ //there is an entry
			return 1;
		}
		i++;
	}
	return 0;
}

int printf_directory(RECORD *dir, int count){
	if(count > DIRsize){
		return -1;
	}
	int i = 0;
	while(i < count){
		printf("name %s\n", dir[i].name);
		printf("file size %08x\n", dir[i].bytesFileSize);
		printf("first cluster %08x\n", dir[i].firstCluster);
		printf("type %04x\n", dir[i].TypeVal);
		i++;
	}
	return 0;
}

int printf_FAT(int count){
	if(count > FATtotalSize){
		return -1;
	}
	int i = 0;
	while(i < count){
		printf("%dth FAT sector: %08x\n", i, FAT[i]);
		i++;
	}
	printf("FREE_FAT %08x\n", FREE_FAT);
	printf("ERROR_FAT %08x\n", ERROR_FAT);
	printf("EOF_FAT %08x\n", EOF_FAT);
	return 0;
}

int printf_OPEN_FILES(int count){
	if((count > MAX_OPEN_FILES)||(count > nOpenFiles)){
		printf("%d, %d\n", count, nOpenFiles);
		return -1;
	}
	int i = 0;
	while(i < count){
		printf("current pointer: %d\n", OPEN_FILES[i].currentPointer);
		printf("handle: %d\n", OPEN_FILES[i].fileHandle);
		printf("name in the record: %s\n", OPEN_FILES[i].record->name);
		printf("dir size: %08x\n", OPEN_FILES[i].dir_record->bytesFileSize);
		i++;
	}
	return 0;
}

int read_cluster(DWORD data_cluster, BYTE *buffer){ //this function iterates to read a whole cluster, instead of only a sector
	DWORD firstSector = cluster2sector(data_cluster);
	DWORD lastSector = firstSector + partitionInfo->SectorsPerCluster;
	while(firstSector < lastSector){
		if(read_sector(firstSector, buffer) != 0){
			return -1; //error reading
		}
		buffer = buffer + SECTOR_SIZE;//iterar o buffer
		firstSector = firstSector + 1; //go to the next sector
	}
	return 0;
}

int readSuperBlock(){ //this function reads the superblock to get the info we need for all the rest!
  partitionInfo = (SUPERBLOCO *) malloc(SECTOR_SIZE);//we need to malloc space for partitionInfo
  int flag = read_sector(0,(unsigned char *)partitionInfo); //we know it is in the first sector of our disk
  if(flag != 0){ //if there was something wrong with the reading
    return -1;
    }
  return 0;
}

DWORD searchEntryPerName(RECORD* dir, char *name, BYTE type){ //searches for a name in the directory and return the cluster
	int i = 0;
	while(i < DIRsize){
		if(strcmp(dir[i].name, name) == 0){
			if(dir[i].TypeVal == type){
				return dir[i].firstCluster;
			}
		}
		i++;
	}
	return EOF_FAT; //nao achou
}

DWORD set_cluster(DWORD i){ //TODO WRITE IN THE DISK
	//marcar um cluster como ocupado na FAT
	if(FAT[i] != FREE_FAT){
		return ERROR_FAT;
	}
	FAT[i] = EOF_FAT;
  return FREE_FAT;
}

int structures_init(){ //this function tests if the superblock and fat were already initialized
	if(partitionInfoInitialized < 0){ //if it was not yet read
		if(readSuperBlock() != 0){ //if tries to read and fails
			return -1; //problem reading the superblock
		}
		partitionInfoInitialized = 0;
		if(initializeFAT() != 0){
			return -1; //problem creating the FAT
		}
		if(initializeROOT() != 0){
			return -1;
		}
		nOpenFiles = 0; //no open files at mounting time
		initializeOPEN_FILES();
		return 0;
	}
	return 0;
}

void wipeFromDirectory(RECORD *dir, char *name, BYTE type){
	int i = 0;
	while(i < DIRsize){
		if(strcmp(dir[i].name, name) == 0){
			if(dir[i].TypeVal == type){
				int first_free = findFreeDirEntry(dir);
				if(first_free == -1){ //dir is full
						first_free = DIRsize;
				}
				addEntry2Dir(dir, i, dir[first_free-1]); //put the last entry in the new space
				dir[first_free-1].TypeVal = TYPEVAL_INVALIDO;
			}
		}
		i++;
	}
}

int write_cluster(DWORD data_cluster, BYTE *buffer){
	//this function iterates to write a whole cluster, instead of only a sector
	DWORD firstSector = cluster2sector(data_cluster);
	DWORD lastSector = firstSector + partitionInfo->SectorsPerCluster;
	while(firstSector < lastSector){
		if(write_sector(firstSector, buffer) != 0){ //write a sector
			return -1; //stops if error writing
		}
		buffer = buffer + SECTOR_SIZE;//iterar o buffer
		firstSector = firstSector + 1; //go to the next sector
	}
	return 0;
}

int write_DIR(RECORD *dir){
	if(dir == NULL){
		return -1; //problem with the pointer
	}
	DWORD cluster = dir[0].firstCluster;
	if(cluster == FREE_FAT){
		return -1;
	}
	if(write_cluster(cluster, (BYTE *)dir) != 0){ //every dir uses only one cluster
		return -1;
	}
	return 0;
}

int write_FAT(){
	if(structures_init() != 0){
		return -1;
	}
	DWORD initial = partitionInfo->pFATSectorStart;
	DWORD final = partitionInfo->DataSectorStart;
	int entriesPerSector = SECTOR_SIZE/sizeof(DWORD);
	DWORD *initialPoint = FAT;
	while(initial < final){
			if(write_sector(initial, (unsigned char *) FAT) != 0){
				return -1;
			}
			initial = initial + 1;
			FAT = FAT + entriesPerSector;
	}
	FAT = initialPoint;
	return 0;
}

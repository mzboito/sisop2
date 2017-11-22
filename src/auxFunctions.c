
/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include <stdlib.h>
#include "stdio.h"
#include "../include/apidisk.h"
#include "../include/auxFunctions.h"

SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
DWORD *FAT; //lista da FAT
struct t2fs_record *ROOT; //lista do diretorio raiz
File_descriptor OPEN_FILES[MAX_OPEN_FILES];

DWORD FATtotalSize;
int partitionInfoInitialized = -1;
int nOpenFiles;

/*EXTRA FUNCTIONS*/
int structures_init(){ //this function tests if the superblock and fat were already initialized
	if(partitionInfoInitialized < 0){ //if it was not yet read
		if(readSuperBlock() != 0){ //if tries to read and fails
			return -1; //problem reading the superblock
		}
		partitionInfoInitialized = 0;
		nOpenFiles = 0; //no open files at mounting time
		//time to initialize the FAT
		if(initializeFAT() != 0){
			//printf("FAT PROBLEM\n");
			return -1; //problem creating the FAT
		}
		if(initializeRoot() != 0){
			return -1;
		}
		initializeOpenFiles();
		return 0;//initializeFAT(); //the superblock, FAT and ROOT are now ready
	}
	return 0; //no need to read it, it is already in memory
}

int readSuperBlock(){ //this function reads the superblock to get the info we need for all the rest!
  partitionInfo = (SUPERBLOCO *) malloc(SECTOR_SIZE);//we need to malloc space for partitionInfo
  //its size will be the size of a sector :) the SECTOR_SIZE is at t2fs.h
  int flag = read_sector(0,(char*)partitionInfo); //we know it is in the first sector of our disk
  if(flag != 0){ //if there was something wrong with the reading
    return -1; // :(
    }
  //at this point partitionInfo has information inside! :)
  return 0; //we are good to go
}

int isRelativePath (char *path) {// return 1 se absoluto, 0 se relativo
	if (*path == '/') {
	   return 0;
	}
	else return 1;
}

int initializeFAT(){
  if(partitionInfoInitialized < 0){
    return -1;
  }
	DWORD initial = partitionInfo->pFATSectorStart;
	DWORD final = partitionInfo->DataSectorStart;
  FATtotalSize = final - initial;
	FAT = (DWORD *)malloc(SECTOR_SIZE * FATtotalSize);
	// sector size = 256 bytes
	// FAT entry = 4 bytes
	int entriesPerSector = SECTOR_SIZE/sizeof(DWORD);
	DWORD *initialPoint = FAT;
	while(initial < final){
			read_sector(initial,(char*)FAT);
			initial = initial + 1;

			FAT = FAT + entriesPerSector;
	}
	FAT = initialPoint;
  return 0;
}

DWORD findFreeCluster(){//encontrar cluster livre
  DWORD i = 0;
  while(i < FATtotalSize){
		printf("Cluster value: %08x\n ", FAT[i]);
		if (FAT[i] == FREE_FAT){ //found a free cluster
		   printf("Find Free cluster value: %08x\n",FAT[i]);
		   return i;
		}
		i++;
  }
  return ERROR_FAT;
}

DWORD set_cluster(DWORD i){ //marcar um cluster como ocupado na FAT
	if(FAT[i] != FREE_FAT){
		return ERROR_FAT;
	}
	FAT[i] = EOF_FAT;
	printf("Set cluster value: %08x\n",FAT[i]);
  return FREE_FAT;
}

DWORD free_cluster(DWORD i){ //liberar um cluster ocupado na FAT
	if (FAT[i] == ERROR_FAT){ //cannot free an error entry
		return ERROR_FAT;
	}
	if(FAT[i] == FREE_FAT){ //cannot free a free fat
		return ERROR_FAT;
	}
	if(FAT[i] != EOF_FAT){
		//if it is not the last file cluster and we free it, we will destroy the file clusters list
		return ERROR_FAT;
	}
	FAT[i] = FREE_FAT;
	printf("Free cluster value: %08x\n",FAT[i]);
	return FREE_FAT; //return 0;
}

int initializeRoot(){
	if(partitionInfoInitialized < 0){
    return -1;
  }
	//the root directory uses only ONE cluster
	ROOT = (struct t2fs_record *)malloc(SECTOR_SIZE * partitionInfo->SectorsPerCluster);
	if(read_cluster(partitionInfo->RootDirCluster, (char *) ROOT) != 0){
		return -1;
	}
	return 0;
}

int read_cluster(DWORD data_cluster, BYTE *buffer){ //DWORD = unsigned int, BYTE = unsigned char
	//this function iterates to read a whole cluster, instead of only a sector
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

int write_cluster(DWORD data_cluster, BYTE *buffer){ //TODO test this function
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

DWORD cluster2sector(DWORD data_cluster){
	DWORD initialDataSector = partitionInfo->DataSectorStart;
	DWORD displacement = partitionInfo->SectorsPerCluster * data_cluster;
	DWORD firstSector = initialDataSector + displacement;
	return firstSector;
}

void initializeOpenFiles(){ //TODO test this function
	int i;
	while(i < MAX_OPEN_FILES){
		File_descriptor d;
		d.fileHandle = -1; //init every entry with -1 value (invalid handle value)
		OPEN_FILES[i] = d;
		i++;
	}
}

int getNewHandle(){ //TODO test this function
	int i;
	while(i < MAX_OPEN_FILES){
		if(OPEN_FILES[i].fileHandle == -1){ //found a free entry
			return i;
		}
		i++;
	}
	return -1; //didn't find, error
}

int findFreeDirEntry(struct t2fs_record *dir){ //TODO TO IMPLEMENT THIS
	//all directories use only one CLUSTER each
	int i = 0;
	//while(i < ) //iterates until it finds a free entry in the directory
}

void* getDirRecord(char *dirPath){ //TODO TO IMPLEMENT THIS
	if(structures_init() != 0){
		return NULL;
	}
	//TODO THE FUNCTION
	return NULL;
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
      //DWORD totalSize = partitionInfo->DataSectorStart - partitionInfo->pFATSectorStart;
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
		if(initializeRoot() == 0){
			int i = 0;
			while(i <= 6){
				printf("name %s\n", ROOT[i].name);
				printf("file size %08x\n", ROOT[i].bytesFileSize);
				printf("first cluster %08x\n", ROOT[i].firstCluster);
				if(ROOT[i].TypeVal == TYPEVAL_REGULAR)
					printf("valid\n");
				i++;
			}
		}

  }
}

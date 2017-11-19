
/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include <stdlib.h>
#include "stdio.h"
#include "../include/apidisk.h"
#include "../include/auxFunctions.h"

SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
DWORD *FAT; //ponteiro para a FAT
int partitionInfoInitialized = -1;

/*EXTRA FUNCTIONS*/
int structures_init(){ //this function tests if the superblock and fat were already initialized
	if(partitionInfoInitialized < 0){ //if it was not yet read
		if(readSuperBlock() != 0){ //if tries to read and fails
			return -1; //problem reading the superblock
		}
		partitionInfoInitialized = 0;
		//time to initialize the FAT
		if(initializeFAT() != 0){
			printf("FAT PROBLEM\n");
			return -1; //problem creating the FAT
		}
		return 0;//initializeFAT(); //the superblock and FAT are now ready
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

int initializeFAT(){
  //first we need the FAT total size
  if(partitionInfoInitialized < 0){
		printf("wtf\n");
    return -1;
  }

	DWORD initial = partitionInfo->pFATSectorStart;
	DWORD final = partitionInfo->DataSectorStart;
  DWORD totalSize = final - initial;

	FAT = (DWORD *)malloc(SECTOR_SIZE * totalSize);

	// sector size = 256 bytes
	// FAT entry = 4 bytes
	int entriesPerSector = SECTOR_SIZE/sizeof(DWORD);
	printf("entries per sector: %d\n", entriesPerSector);

	DWORD *initialPoint = FAT;
	while(initial < final){
			read_sector(initial,(char*)FAT);
			initial = initial + 1;

			FAT = FAT + entriesPerSector;//sizeof(DWORD);
	}
	FAT = initialPoint;
  return 0;
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
      DWORD totalSize = partitionInfo->DataSectorStart - partitionInfo->pFATSectorStart;
      printf("FAT length: %d\n", totalSize);
			int i = 0;
			while(i < 15){
						printf("What is inside the %dth FAT sector: %d\n", i, FAT[i]);
						i++;
			}
			printf("FREE_FAT %d\n", FREE_FAT);
			printf("ERROR_FAT %d\n", ERROR_FAT);
			printf("EOF_FAT %d\n", EOF_FAT);
    }
  }
}


/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include <stdlib.h>
#include "stdio.h"
#include "../include/apidisk.h"
#include "../include/auxFunctions.h"

SUPERBLOCO *partitionInfo; //ponteiro para o superbloco
DWORD *FAT; //lista da FAT
struct t2fs_record *ROOT; //lista do diretorio raiz
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
	//sectorsPerCluster = partitionInfo->SectorsPerCluster; //save the clusters size
  //at this point partitionInfo has information inside! :)
  return 0; //we are good to go
}

int initializeFAT(){
  if(partitionInfoInitialized < 0){
    return -1;
  }
	DWORD initial = partitionInfo->pFATSectorStart;
	DWORD final = partitionInfo->DataSectorStart;
  DWORD totalSize = final - initial;

	FAT = (DWORD *)malloc(SECTOR_SIZE * totalSize);

	// sector size = 256 bytes
	// FAT entry = 4 bytes
	int entriesPerSector = SECTOR_SIZE/sizeof(DWORD);
	//printf("entries per sector: %d\n", entriesPerSector);

	DWORD *initialPoint = FAT;
	while(initial < final){
			read_sector(initial,(char*)FAT);
			initial = initial + 1;

			FAT = FAT + entriesPerSector;//sizeof(DWORD);
	}
	FAT = initialPoint;
  return 0;
}

//encontrar cluster livre

DWORD findFreeCluster () {

  DWORD i = 0;
  int sector = 0;
  while (i < FATtotalSize) {

	
	printf("FAT sector %d %08x Cluster value: %08x\n ",sector,i, FAT[i]);
	
	if (FAT[i] == FREE_FAT) {
	   printf("Find Free cluster value: %08x\n",FAT[i]);
	 
	   return i;
	}
	i++;
	sector++;
  }
  return ERROR_FAT;

}

//marcar um cluster como ocupado na FAT

DWORD markCluster () {

  DWORD i = 0;
  while (i < FATtotalSize) {
	
	if ( FAT[i] != ERROR_FAT && FAT[i] != EOF_FAT && FAT[i] != FREE_FAT) {
	    
	    FAT[i] = EOF_FAT;
	  //  printf("Cluster: %08x\n",i);
	    printf("Mark Cluster value: %08x\n",FAT[i]);
	    return i;
	    
	}
	i++;
  }
  return ERROR_FAT;
	
}

//liberar um cluster ocupado na FAT

DWORD freeCluster () {

  DWORD i = 0;
  while (i < FATtotalSize) {
	
	if ( FAT[i] != ERROR_FAT && FAT[i] != FREE_FAT || FAT[i] == EOF_FAT ) {
	    
	    FAT[i] = FREE_FAT;
	    printf("Free Cluster value: %08x\n",FAT[i]);
	    return i;
	    
	}
	i++;
  }
  return ERROR_FAT;

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

int write_cluster(DWORD data_cluster, BYTE *buffer){
	//this function iterates to write a whole cluster, instead of only a sector
	return -1;
}

DWORD cluster2sector(DWORD data_cluster){
	DWORD initialDataSector = partitionInfo->DataSectorStart;
	DWORD displacement = partitionInfo->SectorsPerCluster * data_cluster;
	DWORD firstSector = initialDataSector + displacement;
	return firstSector;
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
			while(i < totalSize){
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

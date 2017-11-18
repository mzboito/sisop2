
/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include <stdlib.h>
#include "../include/apidisk.h"
#include "../include/auxFunctions.h"

int partitionInfoInitialized = -1;

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
    return -1;
  }
  DWORD totalSize = partitionInfo->DataSectorStart - partitionInfo->pFATSectorStart;
  printf("%d", totalSize);

  return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/apidisk.h"
#include "../include/aux.h"

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

int findFreeDirEntry(RECORD *dir){ //get first free position on directory
	int i = 0;
	//all directories use only one CLUSTER each
	while(i < DIRsize){ //iterates until it finds a free entry in the directory
		if(dir[i].firstCluster == FREE_FAT){
			return i;
		}
		i++;
	}
	return -1;
}

RECORD* get_dir(char *dirPath){
	if(structures_init() != 0){
		return NULL;
	}
	int first_time = 1;
	char *first_dir_name = (char *)malloc(sizeof(char)*MAX_FILE_NAME_SIZE);
	RECORD *current_local = ROOT;

	while(strlen(dirPath)>0){
		dirPath = dirPath + removeFirstDir(dirPath, first_dir_name);
		if(strcmp(first_dir_name, "/\0") == 0){ //if it is the root
			//printf("I hope\n");
			current_local = ROOT;
		}else{
			DWORD cluster = searchEntryPerName(current_local, first_dir_name, TYPEVAL_DIRETORIO);
			if(cluster == EOF_FAT){
				return NULL; //it is not in current directory
			}
			if(first_time == 0){ //if it is not the first time
					free(current_local);
			}
			RECORD *r = (RECORD *)malloc(SECTOR_SIZE * partitionInfo->SectorsPerCluster);
			read_cluster(cluster, r); //read the new directory
			current_local = r;
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
			read_sector(initial, (unsigned char *) FAT);
			initial = initial + 1;
			FAT = FAT + entriesPerSector;
	}
	FAT = initialPoint;
  return 0;
}

void initializeOPEN_FILES(){
	int i;
	while(i < MAX_OPEN_FILES){
		//File_descriptor *d = malloc(sizeof(File_descriptor));
		//d->fileHandle = -1; //init every entry with -1 value (invalid handle value)
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



/*
DWORD findFreeCluster(){//encontrar cluster livre
  DWORD i = 0;
  while(i < FATtotalSize){
		//printf("Cluster value: %08x\n ", FAT[i]);
		if (FAT[i] == FREE_FAT){ //found a free cluster
		   //printf("Find Free cluster value: %08x\n",FAT[i]);
		   return i;
		}
		i++;
  }
  return ERROR_FAT;
}

DWORD set_cluster(DWORD i){ //TODO WRITE IN THE DISK
	//marcar um cluster como ocupado na FAT
	if(FAT[i] != FREE_FAT){
		return ERROR_FAT;
	}
	FAT[i] = EOF_FAT;
	//printf("Set cluster value: %08x\n",FAT[i]);
  return FREE_FAT;
}

DWORD free_cluster(DWORD i){ //TODO WRITE IN THE DISK
	//liberar um cluster ocupado na FAT
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
	//printf("Free cluster value: %08x\n",FAT[i]);
	return FREE_FAT; //return 0;

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


int addEntry2Dir(struct t2fs_record *dir, int position, struct t2fs_record *entry){
	printf("before print\n");
	printf("%08x\n", ROOT[1].firstCluster);
	printf("%08x\n", dir[1].firstCluster);
	dir[position].firstCluster = entry->firstCluster;
	printf("%08x\n", dir[position].firstCluster);
	printf("%08x\n", ROOT[position].firstCluster);
}

*/

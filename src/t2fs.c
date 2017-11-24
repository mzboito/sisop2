#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/utils.h"
#include "../include/t2fs.h"

int identify2(char *name, int size){
	int length = 30;
	  if(size < length){
	      return -1;
	 }
	  char names[] = {'L','i','s','i','a','n','e',':','2','5','2','7','3','9','\n',
		          'M','a','r','c','e','l','y',':','2','2','8','4','5','4', '\0'};
	  int i = 0;
	  while(i < length){
	    *name = names[i];
	    name++;
	    i++;
	  }
	return 0;
}

FILE2 create2(char *filename){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if(nOpenFiles == MAX_OPEN_FILES){
		return -1; //we do not have space for another open file
	}
	printf("number of open files: %d\n", nOpenFiles);
	int length_path = strlen(filename);
	char * name = (char *)malloc(sizeof(char)*length_path);
	char * dir = (char *)malloc(sizeof(char)*length_path);
	RECORD *target_dir;
	int position;
	if(isRelativePath(filename) == 1){
		relative2absolute(filename,name,dir);
			//>>> transform in absolute path
	}else{
		printf("absolute path\n");
		printf("entrada: %s\n", filename);
		dismemberString(filename,name,dir);
		printf("%s,%s\n", name, dir);
		//?
		target_dir = get_dir(dir);
		if(target_dir == NULL){
			return -1; //problem finding the directory
		}
		if(searchEntryPerName(target_dir, name, TYPEVAL_REGULAR) != EOF_FAT){
			return -1; //it there is already a file in this directory with same name
		}
		position = findFreeDirEntry(target_dir); //search for a free entry
		printf("position: %d\n", position);
		if(position == -1){
			return -1; //full directory
		}
		//PROCURAR UMA ENTRADA DA FAT
		DWORD cluster = findFreeCluster();
		if(cluster == EOF_FAT){ //FULL FAT
				return -1;
		}
		printf("new cluster: %d\n", cluster);
		if(set_cluster(cluster) != 0){ //now the cluster is set as occupied
				return -1; //allocation problem
		}
		//COLOCAR NOVO REGISTRO NO DIRETORIO
		target_dir[position].TypeVal = TYPEVAL_REGULAR;
		strcpy(target_dir[position].name, name);
		target_dir[position].bytesFileSize = 0;
		target_dir[position].firstCluster = cluster;

	}//<< tirar aqui quando descomentar o outro
	/*
	addEntry2Dir(ROOT, position, new_record);
	printf("%d\n", ROOT[position].firstCluster);
	printf("%d\n", target_dir[0].TypeVal);

	target_dir[position].TypeVal = TYPEVAL_REGULAR;
	strcpy(target_dir[position].name, name);
	target_dir[position].bytesFileSize = 0;
	target_dir[position].firstCluster = cluster;

	printf("is it here?\n");*/

	//CRIAR O HANDLER DO ARQUIVO
	/*int handler = nOpenFiles;

	//ADICIONAR O ARQUIVO NA LISTA DE ARQUIVOS ABERTOS
	if(OPEN_FILES[handler].fileHandle != -1){ //if the position we have is not free
			free_cluster(cluster);
			return -1; //major logical error
	}
	strcpy(OPEN_FILES[handler].name, name);
	OPEN_FILES[handler].currentPointer = 0;
	OPEN_FILES[handler].fileHandle = nOpenFiles;
	OPEN_FILES[handler].record = &target_dir[position];
	OPEN_FILES[handler].dir_record = &target_dir[0];

	nOpenFiles++;
	return handler;
	}
	printf("position %d\n", position);*/
	return -1;
}

int delete2 (char *filename){
	return -1;
}
FILE2 open2 (char *filename){
	return -1;
}
int close2 (FILE2 handle){
	return -1;
}
int read2 (FILE2 handle, char *buffer, int size){
	return -1;
}
int write2 (FILE2 handle, char *buffer, int size){
	return -1;
}
int truncate2 (FILE2 handle){
	return -1;
}
int seek2 (FILE2 handle, unsigned int offset){
	return -1;
}
int mkdir2 (char *pathname){
	return -1;
}
int rmdir2 (char *pathname){
	return -1;
}
int chdir2 (char *pathname){
	return -1;
}
int getcwd2 (char *pathname,int size){
	return -1;
}
DIR2 opendir2 (char *pathname){
	return -1;
}
int readdir2 (DIR2 handle,DIRENT2 *dentry){
	return -1;
}
int closedir2 (DIR2 handle){
	return -1;
}

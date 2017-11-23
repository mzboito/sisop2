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
	//printf("number of open files: %d\n", nOpenFiles);

	int length_path = strlen(filename);
	char * name = (char *)malloc(sizeof(char)*length_path);
	char * dir = (char *)malloc(sizeof(char)*length_path);
	RECORD *target_dir;
	int position;
	if(isRelativePath(filename) == 1){
			//get target directory relative
	}else{
		dismemberString(filename,name,dir);
		//printf("%s,%s\n", name, dir);
		if(getDir(dir, target_dir) != 0){
			return -1; //problem finding the directory
		}
		//get target directory absolute
	}


	//ENCONTRAR O DIRETÓRIO
	/*
	int position;
	printf("is relative path return for entry %s: %d\n", filename, isRelativePath(filename));

	if(isRelativePath(filename) == 1){
		printf("is relative!\n");
	}
	else{
		//printf("\n\n%d\n", ROOT[10].firstCluster);
		}
		position = findFreeDirEntry(target_dir);
		printf("\n\nTHIS ONE IS OK\n%d\n", ROOT[position].firstCluster);
		printf("position: %d\n", position);
		if(position == -1){
			return -1; //full directory
		}
		printf("\n\nTHIS ONE CRASHES\n");
		printf("%d\n", target_dir[position].firstCluster);*/


	//testar se já existe alguém no diretório pedido com o mesmo nome -> se sim, erro
	// isUnique(name, path_for_directory) (or something like this)

	//PROCURAR UMA ENTRADA DA FAT
	/*DWORD cluster = findFreeCluster();
	if(cluster == EOF_FAT){ //FULL FAT
			return -1;
	}
	printf("new cluster: %d\n", cluster);
	if(set_cluster(cluster) != 0){ //now the cluster is set as occupied
			return -1; //allocation problem
	}*/

	//CRIAR UMA ESTRUTURA PARA O NOVO REGISTRO
	/*struct t2fs_record *new_record = malloc(sizeof(struct t2fs_record));
	new_record->TypeVal = TYPEVAL_REGULAR;
	strcpy(new_record->name, name); //copies the name for the STRUCTURE
	new_record->bytesFileSize = 0; //a file starts empty
	new_record->firstCluster = cluster;
	*/
	//printf("\n\n%d\n", ROOT[position].firstCluster);
	//COLAR NOVO REGISTRO NO DIRETORIO
	//target_dir[position] = new_record;

	//target_dir[position] = malloc(sizeof(struct t2fs_record));
	/*printf("before\n");
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

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
	char name[length_path];
	char dir[length_path];
	RECORD *target_dir;
	int position;
	getPointersFromPath(filename, name, dir);
	//printf("create pointers %s %s %s\n", filename, name, dir);
	target_dir = get_dir(dir);
	if(target_dir == NULL){
		return -1; //problem finding the directory
	}
	if(searchEntryPerName(target_dir, name, TYPEVAL_REGULAR) != EOF_FAT){

		return -1; //it there is already a file in this directory with same name
	}
	position = findFreeDirEntry(target_dir); //search for a free entry
	//printf("position: %d\n", position);
	if(position == -1){

		return -1; //full directory
	}
	//PROCURAR UMA ENTRADA DA FAT
	DWORD cluster = findFreeCluster();
	if(cluster == EOF_FAT){ //FULL FAT

		return -1;
	}
	//printf("new cluster: %d\n", cluster);
	if(set_cluster(cluster) != 0){ //now the cluster is set as occupied

		return -1; //allocation problem
	}
	//CRIAR NOVO REGISTRO
	RECORD entry;
	entry.TypeVal = TYPEVAL_REGULAR;
	strcpy(entry.name, name);
	entry.bytesFileSize = 0;
	entry.firstCluster = cluster;
	//COLOCAR NOVO REGISTRO NO DIRETORIO
	addEntry2Dir(target_dir, position, entry);
	//CRIAR O HANDLE DO ARQUIVO
	int handle = nOpenFiles;
	if(handle < 0){
		free_cluster(cluster);
		return -1; //nOpenFiles init problem
	}
	//ADICIONAR O ARQUIVO NA LISTA DE ARQUIVOS ABERTOS
	if(OPEN_FILES[handle].fileHandle != -1){ //if the position we have is not free
		free_cluster(cluster); //fix fat

		return -1; //major logical error
	}
	strcpy(OPEN_FILES[handle].name, name);
	OPEN_FILES[handle].currentPointer = 0;
	OPEN_FILES[handle].fileHandle = handle;
	OPEN_FILES[handle].record = &target_dir[position];
	OPEN_FILES[handle].dir_record = &target_dir[0];
	//incrementa para o proximo handle
	nOpenFiles++;
	//ESCREVER NO DISCO
	if((write_FAT()!=0)||(write_DIR(target_dir) !=0)){
		free_cluster(cluster);
		target_dir[position].TypeVal = TYPEVAL_INVALIDO;
		return -1;
	}
	return handle;
}

int delete2 (char *filename){
	if(structures_init()!= 0){
		return -1;
	}
	int length_path = strlen(filename);
	char name[length_path];
	char dir[length_path];
	RECORD *target_dir;
	getPointersFromPath(filename, name, dir);
	target_dir = get_dir(dir);
	if(target_dir == NULL){
		//printf("nao achou diretorio\n");
		return -1; //problem finding the directory
	}
	int init_cluster = searchEntryPerName(target_dir, name, TYPEVAL_REGULAR);
	if(init_cluster != EOF_FAT){ //found the name
		//printf("found the name\n");
		free_cluster(init_cluster);
		wipeFromDirectory(target_dir, name, TYPEVAL_REGULAR);
		write_FAT();
		write_DIR(target_dir);
		return 0;
	}else{

		return -1; //the file does not exists
	}
}

FILE2 open2 (char *filename){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if(nOpenFiles == MAX_OPEN_FILES){
		return -1; //we do not have space for another open file
	}
	int length_path = strlen(filename);
	char name[length_path];
	char dir[length_path];
	RECORD *target_dir;
	int position;
	getPointersFromPath(filename, name, dir);
	//printf("create pointers %s %s %s\n", filename, name, dir);
	target_dir = get_dir(dir);
	if(target_dir == NULL){
		//printf("MAS MEU DEUS FILHO\n");
		return -1; //problem finding the directory
	}
	position = findEntryInDirectory(target_dir, name, TYPEVAL_REGULAR);
	if(position == -1){ //did not found the entry in the directory =(
			//printf("oieeee\n");
			return -1; //problem
	}
	int handle = nOpenFiles;
	if(OPEN_FILES[handle].fileHandle != -1){ //if the position we have is not free
		return -1; //major logical error
	}
	//init for the new open file
	strcpy(OPEN_FILES[handle].name, name);
	OPEN_FILES[handle].currentPointer = 0;
	OPEN_FILES[handle].fileHandle = handle;
	OPEN_FILES[handle].record = &target_dir[position];
	OPEN_FILES[handle].dir_record = &target_dir[0];
	nOpenFiles++;
	return handle;
}

int close2 (FILE2 handle){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if((handle < 0)||(handle > nOpenFiles-1)){
		return -1; //invalid handle
	}
	if(OPEN_FILES[handle].fileHandle == -1){ //if the position we have is free
		return -1; //file is not there??
	}
	OPEN_FILES[handle].fileHandle = -1;
	nOpenFiles--;
	return 0;
}

int read2 (FILE2 handle, char *buffer, int size){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if((handle < 0)||(handle > nOpenFiles-1)){
		return -1; //invalid handle
	}
	if(OPEN_FILES[handle].fileHandle == -1){ //if the position we have is not free
		return -1; //file is not there??
	}
	if(size < 0){
		return -1;
	}
	if(read_clusters(handle, buffer, size) == -1){
		return -1; //problem reading
	}
	int amount = strlen(buffer);
	//update_handle(handle, amount);
	//update current pointer
	OPEN_FILES[handle].currentPointer = OPEN_FILES[handle].currentPointer + amount;
	return amount; //NUMBER OF BYTES
}

int write2 (FILE2 handle, char *buffer, int size){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if((handle < 0)||(handle > nOpenFiles-1)){
		return -1; //invalid handle
	}
	if(OPEN_FILES[handle].fileHandle == -1){ //if the position we have is not free
		return -1; //file is not there??
	}
	if(size < 0){
		return -1;
	}


	/*
	if(read_clusters(handle, buffer, size) == -1){
		return -1; //problem reading
	}
	int amount = strlen(buffer);
	//update_handle(handle, amount);
	//update current pointer
	OPEN_FILES[handle].currentPointer = OPEN_FILES[handle].currentPointer + amount;
	return amount;*/
	return -1;
}

//truncate2 place

int seek2 (FILE2 handle, unsigned int offset){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if((handle < 0)||(handle > nOpenFiles-1)){
		return -1; //invalid handle
	}
	if(OPEN_FILES[handle].fileHandle == -1){ //if the position we have is not free
		return -1; //file is not there??
	}
	if(offset == -1){
		OPEN_FILES[handle].currentPointer = OPEN_FILES[handle].record->bytesFileSize + sizeof(BYTE);
		//printf("%08x\n", OPEN_FILES[handle].record->bytesFileSize + sizeof(BYTE));
	}else{
		if(offset <= OPEN_FILES[handle].record->bytesFileSize){
			OPEN_FILES[handle].currentPointer = offset;
		}else{
			return -1;
		}
	}
	return 0;
}

int mkdir2 (char *pathname){
	if(structures_init()!= 0){
		return -1; //problem init structures
	}
	int length_path = strlen(pathname);
	char name[length_path];
	char dir[length_path];
	RECORD *target_dir;
	int position;
	getPointersFromPath(pathname, name, dir);
	target_dir = get_dir(dir);
	if(target_dir == NULL){
		return -1; //problem finding the directory
	}
	if(searchEntryPerName(target_dir, name, TYPEVAL_DIRETORIO) != EOF_FAT){
		return -1; //it there is already a file in this directory with same name
	}
	position = findFreeDirEntry(target_dir); //search for a free entry
	if(position == -1){
		return -1; //full directory
	}
	//PROCURAR UMA ENTRADA DA FAT
	DWORD cluster = findFreeCluster();
	if(cluster == EOF_FAT){ //FULL FAT
		return -1;
	}
	if(set_cluster(cluster) != 0){ //now the cluster is set as occupied
		return -1; //allocation problem
	}
	//CRIAR NOVO REGISTRO
	RECORD entry;
	entry.TypeVal = TYPEVAL_DIRETORIO;
	strcpy(entry.name, name);
	entry.bytesFileSize = SECTOR_SIZE * partitionInfo->SectorsPerCluster; //sizeof(one cluster)
	entry.firstCluster = cluster;
	addEntry2Dir(target_dir, position, entry); //adds in the father directory
	RECORD *new_dir = (RECORD *)malloc(SECTOR_SIZE * partitionInfo->SectorsPerCluster);
	//CAUTION MAYBE HERE CREATE NEW ENTRY FOR FATHER
	createNewDir(new_dir, entry, target_dir[0]);
	if(write_DIR(new_dir) != 0){
		free_cluster(cluster);
		target_dir[position].TypeVal = TYPEVAL_INVALIDO;

		return -1;
	}
	if((write_FAT()!=0)||(write_DIR(target_dir) !=0)){
		free_cluster(cluster);
		target_dir[position].TypeVal = TYPEVAL_INVALIDO;

		return -1;
	}
	//escreve no cluster o novo diretorio
	//escreve a fat
	//escreve diretorio pai no disco
	return 0;
}

int rmdir2 (char *pathname){
	if(structures_init()!= 0){
		return -1;
	}
	int length_path = strlen(pathname);
	char name[length_path];
	char dir[length_path];
	RECORD *target_dir;
	getPointersFromPath(pathname, name, dir);
	//printf("%s %s %s\n", pathname, name, dir);
	target_dir = get_dir(dir);
	if(target_dir == NULL){
		return -1; //problem finding the directory
	}
	int init_cluster = searchEntryPerName(target_dir, name, TYPEVAL_DIRETORIO);
	if(init_cluster != EOF_FAT){ //found the name
		//printf("found the name\n");
		//ok so now let's open the directory we want to delete for a second
		//printf("pathname at this moment %s\n", pathname);
		RECORD *this_dir = get_dir(pathname);
		if(this_dir == NULL){ //reeeeeeeeeeeelly wrong
			//printf("cannot open it\n");
			//printf("the pathname %s\n", pathname);
			return -1; //problem finding the directory
		}
		//printf("before is not empty\n");
		if(isNotEmpty(this_dir) != 0){
			return -1;
		}
		free_cluster(init_cluster);
		wipeFromDirectory(target_dir, name, TYPEVAL_DIRETORIO);
		write_FAT();
		write_DIR(target_dir);
		return 0;
	}else{
		return -1; //the file does not exists
	}
}

int chdir2 (char *pathname){
	if(structures_init()!= 0){
		return -1;
	}
	RECORD *target_dir = get_dir(pathname);
	if(target_dir == NULL){ //not a directory
		//printf("NULL DIR\n");
		return -1;
	}
	//printf("current path before: %s\n", current_path);
	strcpy(current_path, pathname);
	//printf("current path after: %s\n", current_path);
	return 0;
}

int getcwd2 (char *pathname,int size){
	if(structures_init() != 0){
		return -1; //init problem
	}
	//printf("%d %s %d", size, current_path, strlen(current_path));
	//printf("strlen current %d\n", strlen(current_path));
	if(size < strlen(current_path)){
		return -1; //not large enough to contain the current path
	}
	//printf("current %s size %d\n", current_path, size);
	strncpy(pathname, current_path, size);
	return 0;
}

DIR2 opendir2 (char *pathname){
	if(structures_init() != 0){
		return -1;
	}
	if(nOpenDirs == MAX_OPEN_FILES){
		return -1; //we do not have space for another open file
	}
	int length_path = strlen(pathname);
	char name[length_path];
	char dir[length_path];
	getPointersFromPath(pathname, name, dir);

	RECORD *target_dir = get_dir(pathname);
	if(target_dir == NULL){
		//printf("NULL DIR RETURN\n");
		return -1;
	}
	int handle = nOpenDirs;
	if(OPEN_DIRS[handle].dirHandle != -1){ //if the position we have is not free
		return -1; //major logical error
	}
	strcpy(OPEN_DIRS[handle].name, name);
	OPEN_DIRS[handle].currentPointer = 0;
	OPEN_DIRS[handle].dirHandle = handle;
	OPEN_DIRS[handle].record = target_dir;
	nOpenDirs++;
	return handle;


	//init for the new open file

	/*Fun��o:	Abre um diret�rio existente no disco.
		O caminho desse diret�rio � aquele informado pelo par�metro "pathname".
		Se a opera��o foi realizada com sucesso, a fun��o:
			(a) deve retornar o identificador (handle) do diret�rio
			(b) deve posicionar o ponteiro de entradas (current entry) na primeira posi��o v�lida do diret�rio "pathname".
		O handle retornado ser� usado em chamadas posteriores do sistema de arquivo para fins de manipula��o do diret�rio.

	Entra:	pathname -> caminho do diret�rio a ser aberto

	Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o identificador do diret�rio (handle).
		Em caso de erro, ser� retornado um valor negativo.*/
	return -1;
}

int readdir2 (DIR2 handle,DIRENT2 *dentry){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -2; //if problem to initialize, then ERROR
	}
	if((handle < 0)||(handle > nOpenDirs-1)){
		return -2; //invalid handle
	}
	if(OPEN_DIRS[handle].dirHandle == -1){ //if the position we have is not free
		return -2; //file is not there??
	}
	if(OPEN_DIRS[handle].currentPointer == DIRsize){ //end of the directory
		return -END_OF_DIR;
	}
	RECORD *dir = OPEN_DIRS[handle].record;
	DWORD pointer = OPEN_DIRS[handle].currentPointer;
	if(dir[pointer].TypeVal == TYPEVAL_INVALIDO){
		return -END_OF_DIR; //end of valid entries
	}
	strcpy(dentry->name, dir[pointer].name);
	dentry->fileType = dir[pointer].TypeVal;
	dentry->fileSize = dir[pointer].bytesFileSize;
	OPEN_DIRS[handle].currentPointer++;
	return 0;
}

int closedir2 (DIR2 handle){
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if((handle < 0)||(handle > nOpenDirs-1)){
		return -1; //invalid handle
	}
	if(OPEN_DIRS[handle].dirHandle == -1){ //if the position we have is free
		return -1; //file is not there??
	}
	OPEN_DIRS[handle].dirHandle = -1;
	nOpenDirs--;
	return 0;
}

//TODO IMPLEMENT EVERYTHING BELLOW THIS COMMENT
int truncate2 (FILE2 handle){
	return -1;
}

#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"
/*includes extras*/
#include "../include/auxFunctions.h"
#include "string.h"


/*OUR CONTROL STRUCTURES*/

//File_descriptor *TDAA; //Tabela de descritores de arquivos abertos
//TAAP //TAbela de descritores de arquivos por processo
//int numberOpenFiles = 10;

/*HEADERS FOR EXTRA FUNCTIONS*/

/*START IMPLEMENTATION*/
int identify2(char *name, int size){
	int length = 30;
	  if(size < length){
	      return -1;
	 }
	  char names[] = {'L','i','s','i','a','n','e',':','2','5','2','7','3','9','\n',
		          'M','a','r','c','e','l','y',':','2','2','8','4','5','4'};
	  int i = 0;
	  while(i < length){
	    *name = names[i];
	    name++;
	    i++;
	  }
	return 0;
}

FILE2 create2 (char *filename) {
	if(structures_init()!= 0){ //first we need to test if the superblock was initialized
		return -1; //if problem to initialize, then ERROR
	}
	if(nOpenFiles == MAX_OPEN_FILES){
		return -1; //we do not have space for another open file
	}

	//desmembrar o nome para descobrir nome, tipo de path, path


	//VARIÁVEIS PROVISORIAS PARA PODER ESCREVER TODO O RESTO
	char *dir_path; //provisory, this will be the return of the function that gets the path from string
	char *name;

	//testar se já existe alguém no diretório pedido com o mesmo nome -> se sim, erro
	// isUnique(name, path_for_directory) (or something like this)

	//ENCONTRAR O DIRETÓRIO
	//cria uma entrada no diretorio -> se não tem espaço mais pra entradas, erro
	struct t2fs_record *actual_dir = (struct t2fs_record *)getDirRecord(dir_path);
	if(actual_dir == NULL){
		return -1; //problem finding the directory
	}
	int position = findFreeDirEntry(actual_dir);
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


	//TODO TRANSFORMAR EM PONTEIRO PQ ESSA MEMÓRIA VAI SUMIR
	//CRIAR UMA ESTRUTURA PARA O NOVO REGISTRO
	struct t2fs_record new_record;
	new_record.TypeVal = TYPEVAL_REGULAR;
	strcpy(new_record.name, name); //copies the name for the STRUCTURE
	new_record.bytesFileSize = 0; //a file starts empty
	new_record.firstCluster = cluster;

	//COLAR NOVO REGISTRO NO DIRETORIO

	//TODO TRANSFORMAR EM PONTEIRO PQ ESSA MEMÓRIA VAI SUMIR
	actual_dir[position] = new_record; // <<<<<<<<<< THIS MAY NOT WORK

	//CRIAR O HANDLER DO ARQUIVO
	int handler = nOpenFiles;

	//TODO TRANSFORMAR EM PONTEIRO PQ ESSA MEMÓRIA VAI SUMIR
	//ADICIONAR O ARQUIVO NA LISTA DE ARQUIVOS ABERTOS
	if(OPEN_FILES[handler].fileHandle != -1){ //if the position we have is not free
			return -1; //major logical error
	}
	strcpy(OPEN_FILES[handler].name, name);
	OPEN_FILES[handler].currentPointer = 0;
	OPEN_FILES[handler].fileHandle = nOpenFiles;
	OPEN_FILES[handler].record = &new_record;
	//OPEN_FILES[handler].dir_record = &dir_record;
	nOpenFiles++;
	return handler;
}



int delete2 (char *filename);
FILE2 open2 (char *filename);
int close2 (FILE2 handle);
int read2 (FILE2 handle, char *buffer, int size);
int write2 (FILE2 handle, char *buffer, int size);
int truncate2 (FILE2 handle);
int seek2 (FILE2 handle, unsigned int offset);
int mkdir2 (char *pathname);
int rmdir2 (char *pathname);
int chdir2 (char *pathname);
int getcwd2 (char *pathname,int size);
DIR2 opendir2 (char *pathname);
int readdir2 (DIR2 handle,DIRENT2 *dentry);
int closedir2 (DIR2 handle);

#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"
/*includes extras*/
#include "auxFunctions.h"
#include "string.h"


/*SETUP*/

#define MAX_OPEN_FILES 10

/*OUR CONTROL STRUCTURES*/
SUPERBLOCO partitionInfo;

//File_descriptor *TDAA; //Tabela de descritores de arquivos abertos

//TAAP //TAbela de descritores de arquivos por processo

//int numberOpenFiles = 0;
bool partitionInfoInitialized = false;

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
	//what we need to create a file?

	//we need space for its name
	char name = malloc(sizeof(char)*MAX_FILE_NAME_SIZE);
	strcopy(name, filename);
	printf("string: %s,  original: %s\n", name, filename);


	/*File_descriptor *fileDescr = malloc(sizeof(File_descriptor));
	fileDescr->currentPointer = 0; //?
	fileDescr->fileHandle = createFileHandle();
	fileDescr->name = filename;
	t2fs_record registroDir = malloc(sizeof(t2fs_record));
	registroDir->TypeVal = 0x01;
	registroDir->name = filename;
	registroDir->bytesFileSize = 0; //?
	registroDir->firstCluster = 0; //?

	DIRENT2 entradaDir = malloc(sizeof(DIRENT2));
	entradaDir->name = filename;
	entradaDir->bytesFileSize = 0; //?


	fileDescr->registroDiretorio = registroDir; //?
	fileDescr->entradaDiretorio = entradaDir; //?*/
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

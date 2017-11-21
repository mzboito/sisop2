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


	//testar se já existe alguém no diretório pedido com o mesmo nome -> se sim, erro

	//catar um cluster da fat -> se full fat, erro

	//alocar cluster da fat

	//cria uma entrada no diretorio -> se não tem espaço mais pra entradas, erro

	//fazer uma estrutura de arquivo aberto com current pointer e colocá-lo em zero

	//retornar o handler criado


	/*Fun��o: Criar um novo arquivo.
		O nome desse novo arquivo � aquele informado pelo par�metro "filename".
		O contador de posi��o do arquivo (current pointer) deve ser colocado na posi��o zero.
		Caso j� exista um arquivo ou diret�rio com o mesmo nome, a fun��o dever� retornar um erro de cria��o.
		A fun��o deve retornar o identificador (handle) do arquivo.
		Esse handle ser� usado em chamadas posteriores do sistema de arquivo para fins de manipula��o do arquivo criado.

	Entra:	filename -> path absoluto para o arquivo a ser criado. Todo o "path" deve existir.

	Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o handle do arquivo (n�mero positivo).
		Em caso de erro, deve ser retornado um valor negativo.*/

	//we need space for its name
	/*char name = malloc(sizeof(char)*MAX_FILE_NAME_SIZE);
	strcopy(name, filename);
	printf("string: %s,  original: %s\n", name, filename);*/


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

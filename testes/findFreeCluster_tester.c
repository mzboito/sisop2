#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"
/*includes extras*/
#include "../include/auxFunctions.h"
#include "string.h"

int main() {


  printf("Imprimindo valores das estruturas.\n");

 // TESTE PARA DIR_PATH

 char names[] = {'A','r','q','/', 'M','a','r','\0'};
 
  int fimDirPath = fimPath(names);
  char *dir_path;
  dir_path = malloc (sizeof (char) * (fimDirPath + 2));
  int i = 0;
  dirPath(names,dir_path);
   while (i != fimDirPath + 1) {
	
	printf("%c\n ", *dir_path);
	dir_path++;
	i++;
	}

printf("\n\n\n\n");

 // TESTE PARA FILE_PATH

	int inicioPath = inicioNome(names);
	int tam = lengthChar (names);
	int dif = tam - inicioPath + 1;
	char *file_path;
	file_path = malloc (sizeof (char) * (dif));
	filePath(names,file_path);
	int j = inicioPath;

	 while (j != tam + 1) {
	
	printf("%c\n ", *file_path);
	file_path++;
	j++;
	}

printf("inicio nome %d\n\n", inicioPath);
printf("inicio nome %d", tam);

/*
  if (structures_init() == 0) {
	printf("\n\n");
	printf("Find free cluster return: %08x\n", findFreeCluster());
	printf("\n\n");
	printf("Mark cluster ocupado: %08x\n", set_cluster(4));
	printf("\n\n");
	printf("Free cluster: %08x\n", free_cluster(3));
printf("\n\n");
printf("\n\n");
printf("Is Relative: ", isRelativePath (names));
printf("\n\n");
printf("\n\n");
printf("Return file length: %d ",lengthChar (names)); 
printf("\n\n");
printf("Inicio nome: %d ",inicioNome (names)); 
printf("\n\n");
printf("\n\n");
printf("Fim path: %d ",fimPath (names)); 

  }*/
  return 0;
}

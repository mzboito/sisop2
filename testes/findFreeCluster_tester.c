#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/aux.h"


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

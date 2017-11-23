#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

main(){
  char *fullpath = "/utils/coisa/estranha.jpg\0";
  char *fullpath2 = "/assimdaerro/ou/nao/sera/que/nao.txt\0";
	int inicioPath = getFileNameStart(fullpath);
  int inicioPath2 = getFileNameStart(fullpath2);
	int tam = strlen(fullpath);
  int tam2 = strlen(fullpath2);
	int dif = tam - inicioPath + 1; //tamanho do nome na string
	int dif2 = tam2 - inicioPath2 + 1; //tamanho do nome na string
	char *nameFromPath = malloc (sizeof(char) * (dif));
  char *dir = malloc (sizeof(char) * tam);
  char *nameFromPath2 = malloc (sizeof(char) * (dif2));
  char *dir2 = malloc (sizeof(char) * tam2);
	dismemberString(fullpath,nameFromPath, dir);
  dismemberString(fullpath2, nameFromPath2, dir2);
  printf("%s\n", fullpath);
  printf("%s\n", nameFromPath);
  printf("%s\n", dir);
  printf("\n%s\n", fullpath2);
  printf("%s\n", nameFromPath2);
  printf("%s\n", dir2);
  return 0;
}

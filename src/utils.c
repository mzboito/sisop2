#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/t2fs.h"
#include "../include/utils.h"

void dismemberString(char *fullpath, char *name, char *dirpath){
	int inicioName = getFileNameStart(fullpath);
  int fimDir = inicioName; //aponta para a última letra do nome do dir
	int len = strlen(fullpath) -1; //tamanho do fullpath vai de 0 até len
	strncpy(name, &fullpath[inicioName], len);
  strncpy(dirpath, &fullpath[0],fimDir);
}

int getFileNameStart(char *fullpath){ //get name start for ABSOLUTE PATH
	int len = strlen(fullpath) -1; //tamanho do fullpath vai de 0 até len
	int lenFixo = len;
	int i = 0;
	while (len != -1) {
		i++;
		if (fullpath[len] == '/') {
			return (lenFixo - i + 2);
		}
		len--;
	}
	return (lenFixo - i + 2);
}

int isRelativePath(char *path){// return 1 se absoluto, 0 se relativo
	if (*path == '/') {
	   return 0;
	}
	else return 1;
}

int removeFirstDir(char *dir_path, char *first_dir){ //retorna um valor para somar ao ponteiro do dir_path
  int len = strlen(dir_path);
  int i = 0;
  while(i < len){
    if(dir_path[i] == '/'){ //found the end of the dir string
      i++; //tamanho do que vai ser copiado
      strncpy(first_dir, dir_path, i);
      if(i > 1){ //if it is not root dir
        first_dir[i-1] = '\0'; //remove last char
      }else{
        first_dir[i] = '\0';
      }
      return i;
    }
    i++;
  }
  return -1; //nao achou
}
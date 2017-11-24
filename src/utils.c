#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/t2fs.h"
#include "../include/utils.h"

void dismemberString(char *fullpath, char *name, char *dirpath){
	int inicioName = getFileNameStart(fullpath);
  int fimDir = inicioName; //aponta para a última letra do nome do dir
	int len = strlen(fullpath); //tamanho do fullpath vai de 0 até len
  strncpy(name, &fullpath[inicioName], len);
  name[len] = '\0';
  strncpy(dirpath, &fullpath[0],fimDir);
  dirpath[fimDir] = '\0';
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

int relative2absolute(char *fullpath, char *name, char *dir_path){
  if(fullpath[0] == '/'){
    return -1; //ABSOLUTE PATH <O>
  }
  else{
    if(strstr(fullpath,"../\0")){ //path começa com dois pontos
      //printf("dois pontos!\n");
    }else{
      if(strstr(fullpath,"./\0")){ //path começa com um ponto
        //printf("um ponto!\n");
      }else{ //path não começa com ponto

        //strcpy(name, fullpath);
        //strcpy(dir_path, current_path);
        return 0;
      }
    }
  }
}

int removeFirstDir(char *dir_path, char *first_dir){ //retorna um valor para somar ao ponteiro do dir_path
  int len = strlen(dir_path);
  int i = 0;
  while(i < len){
    if(dir_path[i] == '/'){ //found the end of the dir string
      i++; //tamanho do que vai ser copiado
      strncpy(first_dir, dir_path, i);
      if(i > 1){ //if it is not root dir
        first_dir[i-1] = '\0'; //remove last char (/)
      }else{ //if it is the root dir
        first_dir[1] = '\0';
      }
      return i;
    }
    i++;
  }
  return -1; //nao achou
}

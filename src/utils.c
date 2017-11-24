#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/aux.h"
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

void eraseLastDirString(char *string, char *new_string){
  int i = strlen(string);
  if(i == 1){ //root
    strncpy(new_string, string, i);
  }
  i--; //does not count the final / e.g.: /dir1/dir2/ -> /dir1/
  while(i > 0){
    i--;
    if(string[i] == '/'){
      break;
    }
  }
  strncpy(new_string, string, i+1);
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
      fullpath = fullpath + 3;
      char *from_relative = (char *)malloc(sizeof(char)*300);
      char *new_current = (char *)malloc(sizeof(char)*300);
      dismemberString(fullpath, name, from_relative);
      eraseLastDirString(current_path, new_current);
      dir_path[0] = '\0'; //to wipe the trash
      strcat(dir_path,new_current);
      strcat(dir_path,from_relative);
    }else{
      if(strstr(fullpath,"./\0")){ //path começa com um ponto
        fullpath = fullpath + 2;
        char *from_relative = (char *)malloc(sizeof(char)*300);
        dismemberString(fullpath, name, from_relative);
        dir_path[0] = '\0'; //to wipe the trash
        strcat(dir_path,current_path);
        strcat(dir_path,from_relative);
      }else{ //path não começa com ponto
        if(strstr(fullpath,"/\0")){ //if there are directories inside
          char *from_relative = (char *)malloc(sizeof(char)*300);
          dismemberString(fullpath, name, from_relative);
          dir_path[0] = '\0'; //to wipe the trash
          strcat(dir_path,current_path);
          strcat(dir_path,from_relative);
        }else{ //only the name in the fullpath
          strcpy(name, fullpath);
          strcpy(dir_path, current_path);
        }
      }
    }
    return 0;
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


/*
int achaBarras (char *fullpath) {

	int len = strlen(current_path);
	int barras = 0;

	while (len != -1) {

		len--;
		if (fullpath[len] == '/') {
		    barras++;
		}
		if (barras == 2) {
			//novo caminho começa em 0, termina em len, que ja é a barra
			return len;

		}
	}
	return len;
}
*/

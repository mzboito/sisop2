#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int deleteFirstDirEntryStr(char *dir_path, char *first_dir){ //retorna um valor para somar ao ponteiro do dir_path
  //printf("Starting delete first\n");
  int len = strlen(dir_path);
  char dir_string[len+2];
  strcpy(dir_string, dir_path);
  if(dir_path[len-1] != '/'){
    dir_string[len] = '/';
    dir_string[len+1] = '\0';
    len = len + 1;
  }
  int i = 0;
  while(i < len){
    if(dir_string[i] == '/'){ //found the end of the dir string
      i++; //tamanho do que vai ser copiado
      strncpy(first_dir, dir_string, i);
      //printf("first_dir %s , dir_string %s\n", first_dir, dir_string);
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

void dismemberString(char *fullpath, char *name, char *dirpath){
	int inicioName = getFileNameStart(fullpath);
  //printf("dismemberString: fullpath %s inicio name %d\n", fullpath, inicioName);
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

int getFileNameStart(char *fullpath){ //get name start
	int len = strlen(fullpath); //tamanho do fullpath vai de 0 até len
	int i = len;
  while(i >= 0){
    if(fullpath[i] == '/'){ //if found a bar
      //printf("found bar at i = %d\n", i);
      return i+1; //returns the start of the name
    }
    i--;
  }
  return 0; //if does not find a bar, the whole path is the name
  /*  int lenFixo = len;
  	while (len != -1) {
  		i++;
  		if (fullpath[len] == '/') {
  			return (lenFixo - i + 2);
  		}
  		len--;
  	}
  	return (lenFixo - i + 2);*/
}

void getPointersFromPath(char *filename, char *name, char *dir){
	if(isRelativePath(filename) == 1){
      //printf("aqui, relativo\n");
			int length_path = strlen(filename) + 5;
			char relative[length_path];
			dismemberString(filename,name,relative);
      //printf("%s %s %s \n", filename, name, relative);
      //printf("%s\n", dir);
			dir[0] = '\0';
			strcat(dir, current_path); //get path until that point
			strcat(dir, relative);
	}else{
    //printf("abs\n");
		dismemberString(filename,name,dir);
	}
}

int isRelativePath(char *path){// return 1 se absoluto, 0 se relativo
	if (*path == '/') {
	   return 0;
	}
	else return 1;
}

/*int relative2absolute(char *fullpath, char *name, char *dir_path){
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
}*/

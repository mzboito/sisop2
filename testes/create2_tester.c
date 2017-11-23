#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main() {
  printf("return init structures %d\n", structures_init());
  //debugStructures();
  //printf("return first free directory entry %d\n", findFreeDirEntry(ROOT));
  char *dir_path = "/coiso/coisa/coiso/treco/\0";
  char *first_path = (char *)malloc(sizeof(char)*MAX_FILE_NAME_SIZE);
  while(strlen(dir_path) > 0){
    dir_path = dir_path + removeFirstDir(dir_path, first_path);
    printf("first: %s remain: %s\n", first_path, dir_path);
  }
  RECORD *r;
  char *path = "/dir1/\0";
  getDir(path,r);
  //create2("/file.txt\0");

  return 0;
}

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
  r = get_dir(path);
  printf("\n\n");
  printf_directory(ROOT, 5);
  printf("\n\n");
  printf_directory(r, 5);
  printf("test error\n");
  char *path1 = "/lalalala/hue/achoquenao/\0";
  if(get_dir(path1) == NULL){
    printf("catching the error\n\n");
  }
  char *name1 = "file1.txt\0";
  char *name2 = "file5.txt\0";
  if(searchEntryPerName(r, name1, TYPEVAL_REGULAR) != EOF_FAT){
    printf("JA EXISTE %s em %s\n", name1, path);
  }else{
    printf("NAO EXISTE %s em %s\n", name1, path);
  }
  if(searchEntryPerName(ROOT, name2, TYPEVAL_REGULAR) != EOF_FAT){
    printf("JA EXISTE %s em %s\n", name2, "root");
  }else{
    printf("NAO EXISTE %s em %s\n", name2, "root");
  }
  printf("\n\ncurrent path: %s\n", current_path);

  relative2absolute("../file.txt",name1,name2);
  relative2absolute("./file.txt",name1,name2);
  relative2absolute("file.txt",name1,name2);
  create2("/file.txt\0");

  return 0;
}

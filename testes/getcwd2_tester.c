#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  int size = 10;
  char * buffer = (char *)malloc(sizeof(char)*size);
  printf("return %d\n", getcwd2(buffer,size));
  printf("buffer now has: %s\n", buffer);
  current_path = "/now/i/am/a/really/long/path/\0";
  printf("return %d\n", getcwd2(buffer,size));
  printf("open dir\n");
  opendir2("dir1\0");
  printf_OPEN_DIRS(10);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){

  char *file1 = "dir1/file1.txt\0"; //valid
  int handle = open2(file1);
  printf("RETURN OPEN2 FOR FILE (HANDLE) %s: %d\n", file1, handle);
  RECORD *r = get_dir("./dir1\0");
  printf_directory(r,10);
  seek2(handle, -1);
  r = get_dir("../dir1/../dir1/../dir1/./../dir1\0");
  printf_directory(r,10);
  seek2(handle, -1);
  
  return 0;
}

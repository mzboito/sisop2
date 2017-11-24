#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main() {
  /*structures_init();
  printf("FAT BEFORE\n\n");
  RECORD *r = get_dir("/dir1/");
  printf_FAT(20);
  printf("\n\nNOW THE DIRECTORY\n\n");
  printf_directory(r,10);
  char *path = "/dir1/file71.txt\0";
  int handle = create2(path);
  printf("handle %d\n", handle);
  printf("\n\nFAT AFTER\n\n");
  printf_FAT(20);
  printf_directory(r,10);
  printf("Open files registers:\n");
  printf_OPEN_FILES(handle+1);*/
  char *path = "./file2.txt\0";
  delete2(path);


  return 0;
}

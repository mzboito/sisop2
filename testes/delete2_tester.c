#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main() {
  structures_init();
  create2("/olhaeuaqui1.txt\0");
  printf("FAT BEFORE\n\n");
  printf_FAT(20);
  RECORD *r = get_dir("/");
  printf("\n\nNOW THE DIRECTORY\n\n");
  printf_directory(r,10);
  /*
  char *path = "/dir1/file71.txt\0";
  int handle = create2(path);
  printf("handle %d\n", handle);
  printf("\n\nFAT AFTER\n\n");
  printf_FAT(20);
  printf_directory(r,10);
  printf("Open files registers:\n");
  printf_OPEN_FILES(handle+1);*/
  char *path = "./file1.txt\0";
  int value = delete2(path);
  printf("return: %d\n", value);


  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main() {
  structures_init();
  RECORD *r = get_dir("/");
  int value;
  //THIS PART CREATES AND DELETES A FILE
  //printf("FAT BEFORE\n\n");
  //printf_directory(r,10);
  value = create2("/olhaeuaqui1.txt\0");
  printf("return: %d\n", value);
  printf_FAT(20);
  printf_directory(r,10);
  printf("\n\n");
  //printf_FAT(20);
  value = delete2("olhaeuaqui1.txt\0");
  printf("return: %d\n", value);
  printf_FAT(20);
  printf_directory(r,10);
  //printf_FAT(20);
  //NOW WITH WEIRD PATHS

  //printf("\n\nTHE DIRECTORY BEFORE\n\n");
  //printf_directory(r,10);
  //r = get_dir("../dir1/");
  //printf_directory(r,10);
  /*
  char *path = "./dir1/file71.txt\0";
  int handle = create2(path);
  r = get_dir("./dir1/");
  if(r == NULL){
    printf("\nerror to get new dir\n");
  }
  else{
    printf("handle %d\n", handle);
    printf("\n\nFAT AFTER\n\n");
    printf_FAT(20);
    printf_directory(r,10);
    printf("Open files registers:\n");
    printf_OPEN_FILES(handle+1);
    printf("\n\n");
    value = delete2("/dir1/../dir1/file71.txt\0");
    printf("return: %d\n", value);
    printf_FAT(20);
    printf_directory(r,10);
    r = get_dir("./dir1/");
    printf("refresh\n");
    printf_directory(r,10);
    //char *path = "/newdir2\0";

  }*/

  /*
  int value = mkdir2(path);
  printf("return: %d\n", value);
  value = 0;
  if(value == -1){
    printf("ERROR CREATING\n");
  }else{
    printf("\n\nTHE DIRECTORY AFTER\n\n");
    printf_directory(r,6);
    printf("now let's remove it\n");
    value = rmdir2(path);
    if(value == -1){
      printf("ERROR REMOVING IT\n");
      printf("return: %d\n", value);
    }else{
      printf("\n\nTHE DIRECTORY AFTER\n\n");
      printf_directory(r,6);

    }
  }

  */

  return 0;
}

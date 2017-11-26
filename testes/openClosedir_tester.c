/*
THIS FUNCTION TESTS OPENDIR2, CLOSEDIR2, DELETE2, CREATE2 AND READDIR2

IT WILL SHOW YOU THE DIRECTORY ENTRIES BEFORE AND AFTER CREATING A FILE, AS WELL AS THE HANDLE FOR THE OPENED DIRECTORY


THIS TEST MAY NOT SEE REALLY IMPORTANT,
BUT INTERNALLY THIS TEST IS ESSENTIAL, TO BE SURE THAT WE ARE KEEPING OUR POINTERS CONSISTENT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

void print_dir(int handle){
  DIRENT2 *info = (DIRENT2 *)malloc(sizeof(DIRENT2));
  int i = 0;
  int value = 0;
  printf("\nDIRECTORY PRINT:\n");
  while(i < DIRsize){
    value = readdir2(handle, info);
    if(value < 0){
      printf("END OF VALID ENTRIES\n");
      break;
    }
    printf("Name: %s\n", info->name);
    printf("File Type: %04x\n", info->fileType);
    printf("File Size: %08x\n", info->fileSize);
    i++;
  }
  printf("\n");
  OPEN_DIRS[handle].currentPointer = 0;
}

int main() {
  int value = opendir2("dir1\0");
  printf("RETURN OPENDIR2 (HANDLE): %d\n", value);
  if(value == -1){
    printf("PROBLEM OPENING THE DIRECTORY\n");
  }else{
  printf("PRINT OPEN DIRECTORIES VECTOR\n");
  printf_OPEN_DIRS(10);
  char *path = "./dir1/file71.txt\0";
  int handle = create2(path);
  printf("\nCREATING FILE %s\nRETURN CREATE2 (HANDLE): %d\n", path, handle);
  if(handle == -1){
    printf("PROBLEM CREATING FILE!\n");
  }else{
    RECORD *r = get_dir("./dir1/");
    if(r == NULL){
      printf("\nThis is a control error\nThe user should not be able to access this function\nANYWAY, something is wrong\n");
    }
    else{
      printf("PRINT DIRECTORY AFTER CREATING FILE\n");
      print_dir(value);
      printf("\n\nNOW I WILL DELETE THE FILE AND SEE THE CONTENT OF THE DIRECTORY\n");
      value = delete2("/dir1/../dir1/file71.txt\0");
      printf("RETURN DELETE2: %d\n", value);
      if(value == -1){
        printf("PROBLEM DELETING THE FILE!!\n");
      }else{
        print_dir(value);
        }
      }
    }
    printf("\nNOW LET'S SEE WHAT WILL HAPPEN IF WE CLOSE THE DIRECTORY!\n");
    printf("RETURN OF CLOSEDIR2: %d\n", closedir2(value));
    printf("NOW LET'S LOOK AT THE OPEN DIRECTORIES VECTOR\n");
    printf_OPEN_DIRS(10);
  }
  return 0;
}

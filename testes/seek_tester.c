/*
THIS FUNCTIONS TESTS SEEK2

FIRST IT OPENS A FILE AND PRINTS THE INFORMATION INSIDE THE OPEN FILE STRUCTURE

THEN IT SETS THE SEEK FOR 10 AND RE-PRINTS THE INFO

FINALLY IT SETS THE SEEK TO -1, AND CHECKS IF THE POINTER IS ONE AFTER THE FILE SIZE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  printf("FIRST SOME TESTING USING SEEK2\n");
  char *file1 = "dir1/file1.txt\0"; //valid
  int handle = open2(file1);
  printf("RETURN OPEN2 FOR FILE (HANDLE) %s: %d\n", file1, handle);
  if(handle == -1){
    printf("WE HAD A PROBLEM OPENING THE FILE!\n");
  }else{
    printf("STATUS OPEN FILE VECTOR\n");
    printf_OPEN_FILES(10);
    printf("NOW WE DO A SEEK2(HANDLE,10)\n");
    seek2(handle, 10);
    printf_OPEN_FILES(10);
    printf("TESTING SEEK -1\n");
    seek2(handle, -1);
    printf("The size of %s is %08x bytes, so this >%08x< should be %08x + 1\n",
      file1, OPEN_FILES[handle].record->bytesFileSize, OPEN_FILES[handle].currentPointer, OPEN_FILES[handle].record->bytesFileSize);
    if(OPEN_FILES[handle].currentPointer == (OPEN_FILES[handle].record->bytesFileSize + 1)){
      printf("AND IT IS!\n TEST COMPLETE! :)\n");
    }else{
      printf("BUT IT IS NOT!\n SOMETHING WENT WRONG! :(\n");
    }
  }
  return 0;
}

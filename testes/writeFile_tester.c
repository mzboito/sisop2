/*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  structures_init(); //just because I'm using the partitionInfo variable before the first call for the T2FS library
  //char *buffer = (char *)malloc(sizeof(char)*(SECTOR_SIZE*partitionInfo->SectorsPerCluster)*10);

  char *file = "file20.txt\0";
  printf("NOW I WILL OPEN %s\n", file);
  int handle = open2(file);
  if(handle == -1){
    printf("PROBLEM OPENING THE FILE :(\n DID YOU CHANGED THE .DAT FILE?\n");
  }else{
  char *buffer = "I was thinking about writing something really cute here :)\0";
  int size = strlen(buffer);
  int ret = write2(handle, buffer, size);
  printf("return: %s\n", buffer);
  seek2(handle, 0);
  char *buffer2 = (char *)malloc(sizeof(char)*size+20);
  ret = read2(handle, buffer2,size);
  printf("retorno da lida %s\n", buffer2);
  /*printf("\nNOW I WILL START THE READINGS\n\n");
  int position = 0;
  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION %08x\n", 30, position);
  int size = read2(handle, buffer, 30);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("NEW HANDLE POSITION: %08x\n", OPEN_FILES[handle].currentPointer);
  printf("content inside buffer:\n%s\n", buffer);
  */
  }
  /*printf("FIRST I AM ALLOCATING A REALLY LARGE BUFFER (10*CLUSTER SIZE)\n");

  position = (SECTOR_SIZE*partitionInfo->SectorsPerCluster+1);
  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION %08x\n", 430, position);
  seek2(handle, position);
  size = read2(handle, buffer, 430);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("NEW HANDLE POSITION: %08x\n", OPEN_FILES[handle].currentPointer);
  printf("content inside buffer:\n%s\n", buffer);

  position = 0;
  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION 0\n", 1025, position);
  seek2(handle, 0);
  size = read2(handle, buffer, 1025);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("NEW HANDLE POSITION: %08x\n", OPEN_FILES[handle].currentPointer);
  printf("content inside buffer:\n%s\n", buffer);

  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION %08x\n", OPEN_FILES[handle].record->bytesFileSize, position);
  seek2(handle, 0);
  size = read2(handle, buffer, OPEN_FILES[handle].record->bytesFileSize);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("NEW HANDLE POSITION: %08x\n", OPEN_FILES[handle].currentPointer);
  printf("content inside buffer:\n%s\n", buffer);

  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION 0\n", OPEN_FILES[handle].record->bytesFileSize*10);
  seek2(handle, 0);
  size = read2(handle, buffer, OPEN_FILES[handle].record->bytesFileSize*10);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("NEW HANDLE POSITION: %08x\n", OPEN_FILES[handle].currentPointer);
  printf("content inside buffer:\n%s\n", buffer);
  */
  //printf_directory(ROOT, 10);
  /*seek2(handle, -1);
  read2(handle, buffer, 1025);*/
  //}
  return 0;
}

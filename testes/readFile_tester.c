/*
THIS FUNCTION TESTS OPEN FILE, PRINTING THE BUFFER AFTER READING!
I'M USING /FILE2.TXT BECAUSE IT HAS MORE THAN ONE CLUSTER, TURNING THE EXAMPLE MORE INTERESTING, BECAUSE IT SHOWS THE
CASE IN WHICH WE START FROM THE MIDDLE OF A CLUSTER AND CONTINUE IN THE NEXT ONE

YOU CAN TEST OTHER FILES FROM THE HD CHANGIN THE CHAR *FILE CONTENT =)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  structures_init(); //just because I'm using the partitionInfo variable before the first call for the T2FS library
  printf("FIRST I AM ALLOCATING A REALLY LARGE BUFFER (10*CLUSTER SIZE)\n");
  char *buffer = (char *)malloc(sizeof(char)*(SECTOR_SIZE*partitionInfo->SectorsPerCluster)*10);
  char *file = "file2.txt\0";
  printf("NOW I WILL OPEN %s\n", file);
  int handle = open2(file);
  if(handle == -1){
    printf("PROBLEM OPENING THE FILE :(\n DID YOU CHANGED THE .DAT FILE?\n");
  }else{
  printf("\nNOW I WILL START THE READINGS\n\n");
  int position = 0;
  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION %08x\n", 30, position);
  int size = read2(handle, buffer, 30);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("content inside buffer:\n%s\n", buffer);

  position = (SECTOR_SIZE*partitionInfo->SectorsPerCluster+1);
  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION %08x\n", 430, position);
  seek2(handle, position);
  size = read2(handle, buffer, 430);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("content inside buffer:\n%s\n", buffer);

  position = 0;
  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION 0\n", 1025, position);
  seek2(handle, 0);
  size = read2(handle, buffer, 1025);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("content inside buffer:\n%s\n", buffer);

  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION %08x\n", OPEN_FILES[handle].record->bytesFileSize, position);
  seek2(handle, 0);
  size = read2(handle, buffer, OPEN_FILES[handle].record->bytesFileSize);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("content inside buffer:\n%s\n", buffer);

  printf(".\n\nASKING TO READ %08x BYTES FROM POSITION 0\n", OPEN_FILES[handle].record->bytesFileSize*10);
  seek2(handle, 0);
  size = read2(handle, buffer, OPEN_FILES[handle].record->bytesFileSize*10);
  printf("NUMBER OF BYTES READ: %08x\n", size);
  printf("content inside buffer:\n%s\n", buffer);
  //printf_directory(ROOT, 10);
  /*seek2(handle, -1);
  read2(handle, buffer, 1025);*/
  }
  return 0;
}

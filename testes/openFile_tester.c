#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  char *file1 = "file1.txt\0"; //valid
  char *file2 = "file3.txt\0"; //invalid
  char *file3 = "dir1/file2.txt\0"; //valid
  int value = open2(file1);
  printf("RETURN OPEN2 FOR FILE %s: %d\n", file1, value);
  value = open2(file2);
  printf("RETURN OPEN2 FOR FILE %s: %d\n", file2, value);
  value = open2(file3);
  printf("RETURN OPEN2 FOR FILE %s: %d\n", file3, value);
  printf("NOW LET'S SEE THE OPEN FILES!\n(Printing 10 entries)\n");
  printf_OPEN_FILES(10);
  return 0;
}

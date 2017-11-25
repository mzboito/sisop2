/*
THIS TESTER EVALUATES THE OPEN2 AND CLOSE2 FUNCTIONS, AS WELL AS VERIFIES THE OPEN FILES STRUCTURE

FLOW:
Just read the prints, they will guide you through the execution path :)
*/

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
  printf("NOW LET'S SEE THE OPEN FILES!\n(Printing 5 entries)\n");
  printf_OPEN_FILES(10);
  printf("NOW I WILL ADD MORE 8 ENTRIES TO USE ALL ENTRIES\n");
  int i = 0;
  while(i< 8){
    open2(file1);
    i++;
  }
  printf("NOW LET'S PRINT THE OPEN FILES STRUCTURE\n");
  printf_OPEN_FILES(10);
  printf("NOW LET'S OPEN ONE MORE FILE, TO GET AN ERROR!\n");
  value = open2(file3);
  printf("RETURN OPEN2 FOR FILE %s: %d\n", file3, value);
  if(value == 0){
    printf("SOMETHING IS WRONG =(( \n");
  }else{
    printf("NOW I WILL DELETE THE HANDLE 3 AND 7!\n");
    int handle = 3;
    value = close2(handle);
    printf("RETURN CLOSE2 FOR HANDLE %d: %d\n", handle, value);
    handle = 7;
    value = close2(handle);
    printf("RETURN CLOSE2 FOR HANDLE %d: %d\n", handle, value);
    printf("NOW LET'S PRINT THE OPEN FILES STRUCTURE\n");
    printf_OPEN_FILES(10);
    printf("Seek the >> to see positions that are not allocated :) \n You should see two! \n");
    printf("LASTLY, LET'S TRY TO CLOSE HANDLE %d AGAIN TO GET AN ERROR!\n", handle);
    value = close2(handle);
    printf("RETURN CLOSE2 FOR HANDLE %d: %d\n", handle, value);
    if(value == -1){
      printf("\n\nTEST COMPLETE!\n\n");
    }
  }

  return 0;
}

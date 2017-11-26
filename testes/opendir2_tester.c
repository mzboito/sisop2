/*
THIS FUNCTION TESTS OPENDIR2, DELETE2 AND CREATE2

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
      printf_directory(r,7);
      printf("\n\nNOW I WILL DELETE THE FILE AND SEE THE CONTENT OF THE DIRECTORY\n");
      value = delete2("/dir1/../dir1/file71.txt\0");
      printf("RETURN DELETE2: %d\n", value);
      if(value == -1){
        printf("PROBLEM DELETING THE FILE!!\n");
      }else{
        printf_directory(r,7);
        printf("\nNOTE THAT THE FILES IS STILL >THERE< BUT ITS TYPEVAL NOW IS %04x (TYPEVAL_INVALIDO), SO THE ENTRY IS FREE!\n",TYPEVAL_INVALIDO);
        }
      }
    }
  }
  return 0;
}

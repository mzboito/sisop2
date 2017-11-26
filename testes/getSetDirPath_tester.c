/*
  THIS FUNCTION TESTS GETCWD2 AND CHDIR2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  int size = 10;
  int value;
  printf("CREATING A BUFFER OF SIZE %d\n", size);
  char * buffer = (char *)malloc(sizeof(char)*size);
  value = getcwd2(buffer,size);
  printf("Return getcwd2 %d\n", value);
  if(value == 0){
    printf("Buffer now has: %s\n", buffer);
    printf("Now we change the current directory using chdir2\n");
    buffer = "/dir1/\0";
    printf("The path we want to set: %s\n", buffer);
    value = chdir2(buffer);
    printf("Return chdir2 %d\n", value);
    if(value == 0){
        size = 25;
        printf("Now we try to retrieve what we set\n");
        printf("CREATING A BUFFER OF SIZE %d\n", size);
        char *buffer1 = (char *)malloc(sizeof(char)*size);
        value = getcwd2(buffer1,size);
        printf("Return getcwd2 %d\n", value);
        if(value == 0){
          printf("Buffer now has: %s\n", buffer1);
          printf("Now we try getcwd2 with an invalid buffer (too small):\n");
          size = 3;
          char *buffer2 = (char *)malloc(sizeof(char)*size);
          value = getcwd2(buffer2,size);
          printf("return %d\n", value);
          if(value < 0){
            printf("TEST COMPLETE :)\n");
          }
        }else{
          printf("Problem trying to retrieve the current directory\n");
        }
      }else{
        printf("Problem trying to set the current directory\n");
      }
    }else{
      printf("Problem trying to retrieve the current directory\n");
    }
  return 0;
}

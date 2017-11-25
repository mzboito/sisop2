/*
This program tests these functions: create2, delete2, mkdir2 and rmdir2.

FLOW:
-> Creates directory new_dir inside the directory dir1

-> Creates file new_file.txt inside the directory new_dir

-> Tries to delete new_dir and fails because it is not empty

-> Deletes new_file.txt

-> Sucessfully deletes new_dir

PS: It does all these operations while testing relative and absolute paths
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/t2fs.h"

int main(){
  char *fileName = "../dir1/./new_dir/../new_dir/new_file.txt\0";
  char *newDirectory = "dir1/new_dir\0";
  printf("DIRECTORY NAME FOR MKDIR2: %s\n", newDirectory);
  int value = mkdir2(newDirectory);
  printf("RETURN MKDIR2: %d\n", value);
  if(value == -1){
    printf("Something went wrong creating the directory...\n");
  }else{
    printf("FILE NAME FOR CREATE2: %s\n", fileName);
    value = create2(fileName);
    printf("RETURN CREATE2: %d\n", value);
    if(value == -1){
      printf("Something went wrong creating the file...\n");
    }else{
      newDirectory = "/dir1/../dir1/new_dir\0";
      printf("DIRECTORY NAME FOR RMDIR2: %s\n", newDirectory);
      value = rmdir2(newDirectory);
      printf("RETURN RMDIR2: %d\n", value);
      if(value == -1){
        printf("IT FAILED TO DELETE BECAUSE THE DIRECTORY IS NOT EMPTY!\n");
        fileName = "/dir1/new_dir/new_file.txt\0";
        printf("FILE NAME FOR DELETE2: %s\n", fileName);
        value = delete2(fileName);
        printf("RETURN DELETE2: %d\n", value);
        if(value == -1){
          printf("Something went wrong deleting the file...\n");
        }else{
          printf("FINALLY, WE DELETE THE DIRECTORY\n");
          newDirectory = "dir1/new_dir\0";
          printf("DIRECTORY NAME FOR RMDIR2: %s\n", newDirectory);
          value = rmdir2(newDirectory);
          printf("RETURN RMDIR2: %d\n", value);
          if(value == 0){
            printf("EVERYTHING IS PERFECT! :)\n\n");
          }else{
            printf("Something went wrong deleting the directory...\n");
          }
        }
      }else{
        printf("For some reason it deleted the directory with the file inside...\n");
      }
    }
  }

  return 0;
}

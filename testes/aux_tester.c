#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"


int main() {
  if(structures_init() != 0){
    printf("ERROR INIT\n");
    debugStructures();
  }else{
    int i =0;
    while(i < MAX_OPEN_FILES){
      printf("%d\n", OPEN_FILES[i].fileHandle);
      i++;
    }
  }

  return 0;
}

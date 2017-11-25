/*
THIS FUNCTION INITIALIZES THE S.A. AND PRINTS THE STRUCTURES (SUPERBLOCK, FAT AND OPEN_FILES STRUCTURE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main() {
  printf("Imprimindo valores das estruturas.\n");
  debugStructures();
  return 0;
}

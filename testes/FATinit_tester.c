#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"
/*includes extras*/
#include "../include/auxFunctions.h"
#include "string.h"

int main() {
  printf("ok, I work\n");
  printf("Block init: %d\n", superBlock_init());
  printf("Return superblock: %d\n", readSuperBlock());
  printf("Return FAT: %d\n",initializeFAT());
  return 0;
}

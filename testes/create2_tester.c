#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"
/*includes extras*/
#include "../include/auxFunctions.h"
#include "string.h"

int main() {
  printf("return init structures %d\n", structures_init());
  printf("return first free directory entry %d\n", findFreeDirEntry(ROOT));

  return 0;
}

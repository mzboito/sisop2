#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"
/*includes extras*/
#include "../include/auxFunctions.h"
#include "string.h"

int main() {
  printf("Imprimindo valores das estruturas.\n");
  
 
  if (structures_init() == 0) {
	printf("\n\n");
	printf("Find free cluster return: %08x\n", findFreeCluster());
	printf("\n\n");
	printf("Mark cluster ocupado: %08x\n", markCluster());
	printf("\n\n");
	printf("Free cluster: %08x\n", freeCluster());

  }
  return 0;
}

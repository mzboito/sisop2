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
  char names[] = {'.','i','s','i','a','n','e',':','2','5','2','7','3','9','\n',
		          'M','a','r','c','e','l','y',':','2','2','8','4','5','4'};
 
  if (structures_init() == 0) {
	printf("\n\n");
	printf("Find free cluster return: %08x\n", findFreeCluster());
	printf("\n\n");
	printf("Mark cluster ocupado: %08x\n", set_cluster(4));
	printf("\n\n");
	printf("Free cluster: %08x\n", free_cluster(3));
printf("\n\n");
printf("\n\n");
printf("Is Relative: ", isRelativePath (names));


  }
  return 0;
}

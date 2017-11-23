#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  structures_init();
  printf_FAT(30);
  DWORD cluster = findFreeCluster();
  set_cluster(cluster);
  return 0;
}

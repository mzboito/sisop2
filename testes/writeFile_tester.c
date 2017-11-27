/*

ESSE É UM TESTE DA FUNÇÃO WRITE2, TRUNCATE2 E READ2, QUE TAMBÉM UTILIZA CREATE2, DELETE2 E SEEK2

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aux.h"
#include "../include/t2fs.h"
#include "../include/utils.h"

int main(){
  char *file = "file_bonito.txt\0";
  printf("STARTING BY OPENING THE FILE %s\n", file);
  int handle = create2(file);
  if(handle == -1){
    printf("PROBLEM OPENING THE FILE :(\n DID YOU CHANGED THE .DAT FILE?\n");
    //delete2(file);
    return 0;
  }else{
    printf("NEW HANDLE IS: %d\n", handle);
    char *buffer = "I was thinking about writing something here>>>\0";
    int size = strlen(buffer);
    printf("NOW I WILL TRY TO WRITE %s INSIDE THE FILE!\n", buffer);
    printf("ITS SIZE IS %08x\n", size);
    //printf("SEEK FOR THE")
    //seek2(handle, -1);
    int ret = write2(handle, buffer, size);
    printf("WRITE RETURN: %08x BYTES\n", ret);
    //seek2(handle, -1);
    printf("NOW LET'S READ IT!\n");
    seek2(handle,0);
    char *buffer2 = (char *)malloc(sizeof(char)*size);
    printf("I AM ASKING TO READ %08x BYTES FROM FILE\n", size);
    ret = read2(handle, buffer2,size);
    printf("READ RETURN: %08x\n", ret);
    printf("INSIDE OUR BUFFER WE HAVE: %s\n", buffer2);
    seek2(handle, -1);
    printf("THIS IS FUN! LET'S KEEP WRITING!\n");
    char *buffer3 = "<<I love writing in files!\0";
    int size2 = strlen(buffer3);
    printf("NOW I WILL WRITE %s INSIDE THE FILE!\n", buffer3);
    printf("ITS SIZE IS %08x\n", size2);
    ret = write2(handle, buffer3, size2);
    printf("WRITE RETURN: %08x\n", ret);
    printf("LET'S SEE THE RESULT WITH READ:\n");
    seek2(handle,0);
    char *buffer4 = (char *)malloc(size2 + size);
    ret = read2(handle, buffer4, size2+size);
    printf("READ RETURN: %08x\n", ret);
    buffer4[size2+size] = '\0';
    printf("INSIDE OUR BUFFER WE HAVE: %s\n", buffer4);
    printf("\nNOW LET'S GO CRAZY! I WILL WRITE IN THE MIDDLE!!!\n");
    seek2(handle, size-2);
    char *buffer5 = "\\o/";
    int size3 = strlen(buffer5);
    printf("NOW I WILL WRITE %s INSIDE THE FILE!\n", buffer5);
    printf("ITS SIZE IS %08x\n", size3);
    ret = write2(handle, buffer5, size3);
    printf("WRITE RETURN: %08x\n", ret);
    printf("LET'S SEE THE RESULT WITH READ:\n");
    seek2(handle,0);
    char *buffer6 = (char *)malloc(size2 + size+size3);
    int size4 = size2 + size;
    ret = read2(handle, buffer6, size4);
    printf("READ RETURN: %08x\n", ret);
    buffer6[size4] = '\0';
    //printf("BUFFER SIZE %08x\n", size4);
    printf("INSIDE OUR BUFFER WE HAVE: %s\n", buffer6);
    size = size + 1;
    seek2(handle,size);
    printf("NOW I WILL TRUNCATE THE FILE, CUTTING EVERYTHING AFTER MY \\o/ GUY\n");
    ret = truncate2(handle);
    seek2(handle,0);
    char *buffer7 = (char *)malloc(sizeof(char)*size);
    //printf("I AM ASKING TO READ %08x BYTES FROM FILE\n", size);
    ret = read2(handle, buffer7,size);
    printf("READ RETURN: %08x\n", ret);
    printf("INSIDE OUR BUFFER WE HAVE: %s\n", buffer7);
    delete2(file);
    if(ret != -1){
      printf("SUCCESS!\n TEST COMPLETE!\n");
    }
  }
  return 0;
}

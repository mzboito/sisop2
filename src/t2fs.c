

#include "stdio.h"
#include "stdlib.h"
#include "ucontext.h"
#include "../include/t2fs.h"
#include "../include/apidisk.h"

int identify2 (char *name, int size){

	int length = 30;
	  if(size < length){
	      return -1;
	 }
	  char names[] = {'L','i','s','i','a','n','e',':','2','5','2','7','3','9','\n',
		          'M','a','r','c','e','l','y',':','2','2','8','4','5','4'};
	  int i = 0;
	  while(i < length){
	    *name = names[i];
	    name++;
	    i++;
	  }
	return 0;
}


FILE2 create2 (char *filename);

int delete2 (char *filename);

FILE2 open2 (char *filename);

int close2 (FILE2 handle);

int read2 (FILE2 handle, char *buffer, int size);

int write2 (FILE2 handle, char *buffer, int size);

int truncate2 (FILE2 handle);

int seek2 (FILE2 handle, unsigned int offset);

int mkdir2 (char *pathname);

int rmdir2 (char *pathname);

int chdir2 (char *pathname);

int getcwd2 (char *pathname,int size);

DIR2 opendir2 (char *pathname);

int readdir2 (DIR2 handle,DIRENT2 *dentry);

int closedir2 (DIR2 handle);


/*** ARQUIVO DE FUNCOES AUXILIARES PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
#include "t2fs.h"
#include "apidisk.h"

/*OUR CONTROL VARIABLES*/
SUPERBLOCO *partitionInfo; //ponteiro para o superbloco


int readSuperBlock();

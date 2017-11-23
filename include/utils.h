#pragma once
#ifndef AUX_H
#define AUXF_H

/*** FUNCOES DE MANIPULACAO PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
void dismemberString(char *fullpath, char *name, char *dirpath);
int getFileNameStart(char *fullpath);
int isRelativePath(char *path);
int removeFirstDir(char *dir_path, char *first_dir);

#endif

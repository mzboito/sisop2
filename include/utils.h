#pragma once
#ifndef AUX_H
#define AUXF_H

/*** FUNCOES DE MANIPULACAO PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
void dismemberString(char *fullpath, char *name, char *dirpath);
void eraseLastDirString(char *string, char *new_string);
int getFileNameStart(char *fullpath);
int isRelativePath(char *path);
//int relative2absolute(char *fullpath, char *name, char *dir_path);
int removeFirstDir(char *dir_path, char *first_dir);

#endif

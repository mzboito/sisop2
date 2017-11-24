#pragma once
#ifndef AUX_H
#define AUXF_H

/*** FUNCOES DE MANIPULACAO PARA A IMPLEMENTACAO DA BIBLITOECA T2FS ***/
void dismemberString(char *fullpath, char *name, char *dirpath);
void eraseLastDirString(char *string, char *new_string);
int getFileNameStart(char *fullpath);
void getPointersFromPath(char *filename, char *name, char *dir);
int isRelativePath(char *path);
int deleteFirstDirEntry(char *dir_path, char *first_dir);

#endif

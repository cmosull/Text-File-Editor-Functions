#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int menu();
void SearchReplace(char *arr[], int size, int linelen);
int SpellCheck(char *arr[], FILE *Dptr, int size, int linelen,int pdict, char *name);
int LineCounter(FILE *In);
void testArg(int argnum);
void testFile(FILE *In,FILE *Dict);
int MaxLength(FILE *In);

#endif

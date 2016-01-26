/*(1) student's name:     Alec Chen
(2) student ID:         301187669
(3) SFU user name:      cca169
(4) lecture section:    CMPT 300 D1 (Fall 2015)
(5) instructor's name:  Brian Booth
(6) TA's name:          Scott Kristjanson
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#pragma once

#define MAX_CHAR 256
#define NUM_CYPHER_WORD 6
#define MODULAR 4294434817
#define EXPONENT 1921821779



void removeExtraSymbol(char* line);
int getLineLength(char *line);
void removeTrailingNewLine(char* line);
void debugPrintLine(char* line, int);
char* getCurrentTime();




int decrypt( char *in, char *out);

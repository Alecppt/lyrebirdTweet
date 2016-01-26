/*(1) student's name:     Alec Chen
(2) student ID:         301187669
(3) SFU user name:      cca169
(4) lecture section:    CMPT 300 D1 (Fall 2015)
(5) instructor's name:  Brian Booth
(6) TA's name:          Scott Kristjanson
*/
#include "decrypt.h"
#define DEBUG 1

void debugPrintLine(char* line, int debug){
    if(debug == 1){
       printf("%s\n", line);
    }
}

int getLineLength(char *line){
    char *c;
    for(c = line; *c; ++c);
    return (c - line);
}
void removeExtraSymbol(char *line){
    int i, j;
    int lineLength = getLineLength(line);
    for (i = 0; i < lineLength; ++i){
        if ((i % 8) == 7){
            line[i] = '%';
        }
    }
    for(i = 0; i < lineLength; ++i){
        if(line[i] == '%'){
            for (j = i; j < lineLength -1; ++j){
                line[j] = line[j+1];
            }
            line[j] = '\0';
        }
    }
}

void removeTrailingNewLine(char* line){
    if (line[getLineLength(line)-1] == '\n'){
        line[getLineLength(line)-1] = '\0';
    }
}

int** create2DArrayOnHeap(int row, int col){
    int i;
    int **arr = (int**)malloc(sizeof(int*) * row );
    for (i = 0; i<row; ++i){
        arr[i] = (int*)malloc(sizeof(int) * col);
    }
    return arr;
}
void destroy2DArrayOnHeap(int** arr, int row){
   int i;
   for (i = 0; i < row; ++i){
    free(arr[i]);
   }
   free(arr);
}
unsigned long long int* createUlliArr(int numRow){
    unsigned long long int* ullIntArr;
    ullIntArr = (unsigned long long int*) malloc(sizeof(unsigned long long int) * numRow);
    return ullIntArr;
}

unsigned long long int getModExp(unsigned long long int base){
  unsigned long long int result = 1;
  unsigned long long int exp  = EXPONENT;
  while (exp>0){
    if(exp%2 == 1){
      result = result * base % MODULAR;
    }
    base = (base * base) % MODULAR;
    exp = exp / 2;
  }
  return result% MODULAR;
}

int charToBase41Int(char c){
    switch (c) {
    case ' ': return 0;
    case 'a': return 1;
    case 'b': return 2;
    case 'c': return 3;
    case 'd': return 4;
    case 'e': return 5;
    case 'f': return 6;
    case 'g': return 7;
    case 'h': return 8;
    case 'i': return 9;
    case 'j': return 10;
    case 'k': return 11;
    case 'l': return 12;
    case 'm': return 13;
    case 'n': return 14;
    case 'o': return 15;
    case 'p': return 16;
    case 'q': return 17;
    case 'r': return 18;
    case 's': return 19;
    case 't': return 20;
    case 'u': return 21;
    case 'v': return 22;
    case 'w': return 23;
    case 'x': return 24;
    case 'y': return 25;
    case 'z': return 26;
    case '#': return 27;
    case '.': return 28;
    case ',': return 29;
    case '\'': return 30;
    case '!': return 31;
    case '?': return 32;
    case '(': return 33;
    case ')': return 34;
    case '-': return 35;
    case ':': return 36;
    case '$': return 37;
    case '/': return 38;
    case '&': return 39;
    case '\\': return 40;
    default:
      fprintf(stderr, "%s\n", "invalid input char");
      exit(-1);

  }
}
char covertBaseIntBackToChar(int i){
    switch (i) {
    case 0: return ' ';
    case 1: return 'a';
    case 2: return 'b';
    case 3: return 'c';
    case 4: return 'd';
    case 5: return 'e';
    case 6: return 'f';
    case 7: return 'g';
    case 8: return 'h';
    case 9: return 'i';
    case 10: return 'j';
    case 11: return 'k';
    case 12: return 'l';
    case 13: return 'm';
    case 14: return 'n';
    case 15: return 'o';
    case 16: return 'p';
    case 17: return 'q';
    case 18: return 'r';
    case 19: return 's';
    case 20: return 't';
    case 21: return 'u';
    case 22: return 'v';
    case 23: return 'w';
    case 24: return 'x';
    case 25: return 'y';
    case 26: return 'z';
    case 27: return '#';
    case 28: return '.';
    case 29: return ',';
    case 30: return '\'';
    case 31: return '!';
    case 32: return '?';
    case 33: return '(';
    case 34: return ')';
    case 35: return '-';
    case 36: return ':';
    case 37: return '$';
    case 38: return '/';
    case 39: return '&';
    case 40: return '\\';
    default:
      fprintf(stderr, "%s\n", "invalid input char");
      exit(-1);
 }
}

char* getCurrentTime(){
  time_t nowTime;
  time (&nowTime);
  char* now =ctime(&nowTime);
  removeTrailingNewLine(now);
  return now;
}


int decrypt( char* inputFile, char* outputFile
    /*FILE *in, FILE *out*/
                                    ){
    FILE *in, *out;
    in =fopen(inputFile, "r");
    out =fopen(outputFile, "w+");
    char line[MAX_CHAR];
    int i  = 0, j = 0;
    if(in == NULL){
        /*printf("%s\"%s\"\n", "fail to open the file",inputFile);*/
        return 1;
    }
    while(fgets(line, sizeof(line), in)){
        /*step 1*/
        removeTrailingNewLine(line);
        removeExtraSymbol(line);
        /*end of step 1*/
        /*step 2*/
        int lineLength = getLineLength(line);
        int numIntArrNeeded = lineLength / NUM_CYPHER_WORD;
        int **base41_int_storage = create2DArrayOnHeap(numIntArrNeeded, NUM_CYPHER_WORD);
        /*filling 2d array by mapping each char to a int, 6 chars in int array*/
        for( i = 0; i < numIntArrNeeded; ++i){
            for(j = 0; j < NUM_CYPHER_WORD; ++j){
                base41_int_storage[i][j] = charToBase41Int(line[i*NUM_CYPHER_WORD + j]);
            }
        }
        unsigned long long int* cypherUllIntArr = createUlliArr(numIntArrNeeded);
        /*transform each arr of 6 integers into a base41 Integer*/
        for(i = 0; i < numIntArrNeeded; i++){
            cypherUllIntArr[i] = 0ull;

            for (j = 0; j< NUM_CYPHER_WORD; ++j){
                unsigned long long int base41Int =
                (unsigned long long int) (pow(41, (5 - j)) * base41_int_storage[i][j]);
                cypherUllIntArr[i] += base41Int;
            }

        }
        /*end of step 2*/

        /*step 3 map each cypher number onto a plain-text number*/
        for(i = 0; i < numIntArrNeeded; i ++){
            cypherUllIntArr[i] = getModExp(cypherUllIntArr[i]);
        }
        /*end of step 3*/

        /*step 4 reverse step 3 to get the decrypted text*/
        for(i = 0; i < numIntArrNeeded; i++){
            unsigned long long int key = cypherUllIntArr[i];
            for(j = NUM_CYPHER_WORD -1; j >=0; j--){
                base41_int_storage[i][j] = key %41;
                key = key / 41;
            }
        }
        for(i=0; i<numIntArrNeeded; ++i){
            for (j = 0; j < NUM_CYPHER_WORD; ++j){
                line[i*NUM_CYPHER_WORD + j] = covertBaseIntBackToChar(base41_int_storage[i][j]);
            }
        }
        /*end of step 4*/

        fputs(line, out);
        fputc('\n', out);
        free(cypherUllIntArr);
        destroy2DArrayOnHeap(base41_int_storage, numIntArrNeeded);
    }
    fclose(out);
    fclose(in);
    return 0;
}

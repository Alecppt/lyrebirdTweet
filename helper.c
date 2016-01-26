#include "helper.h"


int getLineLength(char *line){
    char *c;
    for(c = line; *c; ++c);
    return (c - line);
}

void removeTrailingNewLine(char* line){
    if (line[getLineLength(line)-1] == '\n'){
        line[getLineLength(line)-1] = '\0';
    }
}

char* getCurrentTime(){
  time_t nowTime;
  time (&nowTime);
  char* now =ctime(&nowTime);
  removeTrailingNewLine(now);
  return now;
}
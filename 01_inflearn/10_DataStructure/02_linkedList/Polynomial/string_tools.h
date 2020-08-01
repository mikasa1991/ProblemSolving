#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

#include <string.h>
#include <stdio.h>

//function declared
int read_line(FILE* fp, char* str, int limit);
void erase_blanks(char* expression);

#endif
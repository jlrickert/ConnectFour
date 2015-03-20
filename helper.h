#ifndef HELPER_H
#define HELPER_H

#define loop while(1)
typedef char* string;

// Clears lines n times. 0 for just the current line
void
clear_lines(unsigned int nLines);

// get input until a \n or EOF is encountered
int
get_str(char** buffer);

// get a number from the user and returns an Integer
int
get_int();

#endif

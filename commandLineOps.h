
#ifndef COMMANDLINEOPS_H
#define COMMANDLINEOPS_H

#include "shellOps.h"


bool readCL(char buffer[]);
int tokenize(char buffer[], CLInput *commandLine);
int tok(char buffer[], char arg[], int i, int *numOfArgs);
void clearCL(CLInput *commandLine);

#endif
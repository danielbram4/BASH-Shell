#include "commandLineOps.h"

bool readCL(char buffer[])
{
  int bytesRead = 0;
  int exitCond = false;
  int endOfString = false;
  int i = 0;
  int k = 0;
  char *delimit = buffer;
  bytesRead = read(0, buffer, BUFF_LEN);
  exitCond = checkExit(bytesRead, buffer);
  return exitCond;
}

int tokenize(char buffer[], CLInput *commandLine)
{
  int bytesRead = 0;
  int endOfString = false;
  int i = 0;
  char *delimit = buffer;
  int numOfArgs = 0;

  if (buffer[0] != '\n')
  {
    clearCL(commandLine);
    i = tok(buffer, commandLine->arg1, i, &numOfArgs);
    i = tok(buffer, commandLine->arg2, i, &numOfArgs);
    i = tok(buffer, commandLine->arg3, i, &numOfArgs);
    i = tok(buffer, commandLine->arg4, i, &numOfArgs);
    i = tok(buffer, commandLine->arg5, i, &numOfArgs);
  }
  return numOfArgs;
}

// tokenizes
int tok(char buffer[], char arg[], int i, int *numOfArgs)
{
  int bytesRead = 0;
  int endOfString = false;
  char *delimit = buffer;
  int k = 0;
  clearArg(arg);
  if (buffer[i] == '\n')
  {
    endOfString = true;
  }
  else
  {
    *numOfArgs = *numOfArgs + 1;
  }
  while (*delimit != ' ' && endOfString == false)
  {
    arg[k] = buffer[i];

    i++;
    k++;
    if (buffer[i] != '\n')
    {
      *delimit = buffer[i];
    }
    else
    {
      endOfString = true;
    }
  }

  if (endOfString == false)
  {
    i++;
    *delimit = buffer[i];
  }
  return i;
}

// clears the command line
void clearCL(CLInput *commandLine)
{
  int i = 0;
  for (i = 0; i < BUFF_LEN; i++)
  {
    commandLine->arg1[i] = 0;
    commandLine->arg2[i] = 0;
    commandLine->arg3[i] = 0;
  }
}
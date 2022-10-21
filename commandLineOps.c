#include "mysh.h"

char *newargv[6];
char *newargv2[6];
//Reads the buffer and Checks if "exit" command as been inputted. Returns boolean whether exit condition has been fullfilled or not.
bool readCL(char buffer[])
{
  int bytesRead = 0;
  int exitCond = false;
  bytesRead = read(0, buffer, BUFF_LEN);
  if(bytesRead == ERROR_NO){
    printReadError();
    exit(EXIT_FAILURE);
  }
  exitCond = checkExit(bytesRead, buffer);
  return exitCond;
}

//Checks if buffer is empty, if not, tokenizes buffer into max 5 tokens.
//Returns total number of tokens.
int tokenize(char buffer[], CLInput *commandLine)
{
  int i = 0;
  char *delimit = buffer;
  int numOfArgs = 0;

  if (buffer[0] != NEW_LINE_CHAR)
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

// Tokenizes buffer by using a delimiter to check for a space. All characters that occurred before
// the delimiter are stored in a character array called arg.
// End of the string has been reached when we come into contact with a newline character. 
// Returns the index position of the buffer one character after the last space occurred.
int tok(char buffer[], char arg[], int i, int *numOfArgs)
{
  int endOfString = false;
  char *delimit = buffer;
  int k = 0;
  clearArg(arg);
  if (buffer[i] == NEW_LINE_CHAR)
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
    if (buffer[i] != NEW_LINE_CHAR)
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
    commandLine->arg4[i] = 0;
    commandLine->arg4[i] = 0;
  }
}
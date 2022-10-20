#include "mysh.h"

void printCommandPrompt(){
  write(STDOUT_FILENO, "mysh$ ", PROMPT_LENGTH);
}

void printForkFailed(){
   write(STDOUT_FILENO, "fork failed\n", FORK_FAILED_LENGTH);
}

void printInvalidArgument(){
  write(STDOUT_FILENO, "Not Valid, Try again\n", NOT_VALID_COMMAND_LENGTH);
}

void printUsernamePrompt(){
  write(STDOUT_FILENO, "enter username: ", USERNAME_PROMPT_LENGTH);
}

void printPasswordPrompt(){
  write(STDOUT_FILENO, "enter password: ", PASSWORD_PROMPT_LENGTH);
}

void printSIGINT(){
  write(STDOUT_FILENO, " Process Interuppted!\n", PROCESSES_INT_LENGTH); 
}

// compares a string
int my_strcmp(char *s1, char *s2)
{
  int charCompareStatus = 0;
  while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
  {
    s1++;
    s2++;
  }
  // compare the mismatching character

charCompareStatus = (*s1 == *s2) ? 0 : (*s1 > *s2) ? 1
                                                     : -1;
  return charCompareStatus;
}
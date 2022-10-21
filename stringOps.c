// #include "mysh.h"
#include <stdlib.h>
#include <unistd.h>
#include "stringOps.h"

void printCommandPrompt()
{
  if (write(STDOUT_FILENO, "mysh$ ", PROMPT_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printForkFailed()
{
  if (write(STDOUT_FILENO, "fork failed\n", FORK_FAILED_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printInvalidArgument()
{
  if (write(STDOUT_FILENO, "Not Valid, Try again\n", NOT_VALID_COMMAND_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printUsernamePrompt()
{
  if (write(STDOUT_FILENO, "enter username: ", USERNAME_PROMPT_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printPasswordPrompt()
{
  if (write(STDOUT_FILENO, "enter password: ", PASSWORD_PROMPT_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printSIGINT()
{
  if (write(STDOUT_FILENO, " Process Interuppted!\n", PROCESSES_INT_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
  write(STDOUT_FILENO, " Process Interuppted!\n", PROCESSES_INT_LENGTH);
}

void printBackgroundFailed()
{
  if (write(STDOUT_FILENO, "Background operation failed\n", BACKGROUND_FAILED_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printWaitPidFailed()
{
  if (write(STDOUT_FILENO, "Wait PID Failed\n", WAIT_PID_FAILED_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printReadError()
{
  if (write(STDOUT_FILENO, "Failure to read input\n", READ_ERROR_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printFailedToOpen()
{
  if (write(STDOUT_FILENO, "Failed to open file\n", FAILED_TO_OPEN_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printRedirectionFailed()
{
  if (write(STDOUT_FILENO, "I/O redirection failed\n", REDIRECTION_FAILED_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printFailedToClose()
{
  if (write(STDOUT_FILENO, "Failed to close file\n", FAILED_TO_CLOSE_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printPipeFailed()
{
  if (write(STDOUT_FILENO, "Failed to open pipe\n", FAILED_PIPE_LENGTH) == ERROR_NO)
  {
    writeFailed();
  }
}

void printFailedToWrite()
{

  if (write(STDOUT_FILENO, "Failed to write\n", FAILED_TO_WRITE_LENGTH) == ERROR_NO)
  {
    exit(EXIT_FAILURE);
  };
}

// compares a string
int my_strcmp(char *s1, char *s2)
{
  int comp = 0;
  while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
  {
    s1++;
    s2++;
  }

  if (*s1 == *s2)
  {
    comp = 0;
  }
  else if (*s1 > *s2)
  {
    comp = 1;
  }
  else
  {
    comp = -1;
  }

  return comp;
}

void writeFailed()
{
  printFailedToWrite();
  exit(EXIT_FAILURE);
}
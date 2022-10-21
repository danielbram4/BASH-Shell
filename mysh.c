/*
  A basic BASH like shell program for the Linux Operating System.
  By Daniel Bahrami and Scott Charles
*/

#include "mysh.h"
#include "stdio.h"

char *newargv_mysh[6];
char *newargv_mysh2[6];

int main()
{
  CLInput commandLine = {};
  CLInput *cl = &commandLine;
  char buffer[BUFF_LEN] = {};
  char *const newenvp[] = {NULL};

  int bytesRead;
  int status;
  int pipefd[2];
  int numberOfArgs = 0;
  int comp;
  // int argumentNumber;

  bool isPipe = false;
  bool background = false;
  bool redirection = false;
  bool in = false;
  bool out = false;

  pid_t pid;
  pid_t pid2;

  signal(SIGINT, &handle_sigchld);
  login(buffer);
  printCommandPrompt();

  // Main loop for command prompt
  while (readCL(buffer) == false)
  {

    // initialize new prompt
    clearArgs(newargv_mysh, newargv_mysh2);
    background = false;

    // check command conditions
    numberOfArgs = tokenize(buffer, cl);
    background = isBackground(numberOfArgs, cl, newargv_mysh);
    isPipe = isPipeline(numberOfArgs, cl, newargv_mysh, newargv_mysh2);

    if (isPipe == false)
    {
      pid = fork();

      if (pid == ERROR_NO)
      {
        printForkFailed();
        exit(EXIT_FAILURE);
      }

      if (pid == 0)
      {
        checkRedirection(cl, &in, &out, numberOfArgs);

        // If input redirected
        if (in)
        {
          if (numberOfArgs == 3)
          {
            processRedirect(1, 2, commandLine.arg3, INPUT, newargv_mysh, newargv_mysh2);
          }
          else
          {
            processRedirect(2, 3, commandLine.arg4, INPUT, newargv_mysh, newargv_mysh2);
          }
        }
        // If output redirected
        if (out)
        {
          if (numberOfArgs == 3)
          {
            processRedirect(1, 2, commandLine.arg3, OUTPUT, newargv_mysh, newargv_mysh2);
          }
          else
          {
            processRedirect(2, 3, commandLine.arg4, OUTPUT, newargv_mysh, newargv_mysh2);
          }
        }
        // If process is sent to the background
        if (background == true)
        {
          if(setpgid(0, 0) ==  ERROR_NO) {
            printBackgroundFailed();
            exit(EXIT_FAILURE);
          }
        }

        if (execve(commandLine.arg1, newargv_mysh, newenvp) == ERROR_NO)
        {
          printInvalidArgument();
          exit(EXIT_FAILURE);
        }
      }
      else
      {
        // Parent Process
        if (background == false)
        {
          if(waitpid(pid, &status, 0) == ERROR_NO){
            printWaitPidFailed();
            exit(EXIT_FAILURE);
          }
        }
        else
        {
          if(waitpid(pid, &status, WNOHANG) == ERROR_NO){
            printWaitPidFailed();
            exit(EXIT_FAILURE);
          }
        }
      }
    }
    else
    {
      processPipe(newargv_mysh, newargv_mysh2);
    }
    printCommandPrompt();
  }
  return 0;
}



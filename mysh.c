/*
  Main File.
  By Daniel Bahrami and Scott Charles III
*/

#include "mysh.h"
#include "stdio.h"

int main()
{
  CLInput commandLine = {};
  CLInput *cl = &commandLine;
  char buffer[BUFF_LEN] = {};
  char *const newenvp[] = {NULL};

  int bytesRead;
  int status;
  int pipefd[2];
  int isCommand;
  int numberOfArgs = 0;
  int comp;
  // int argumentNumber;

  bool isPipe = false;
  bool exitFlag = false;
  bool background = false;
  bool redirection = false;
  bool in = false;
  bool out = false;

  pid_t pid;
  pid_t pid2;

  signal(SIGINT, &handle_sigchld);
  login(buffer);

  printCommandPrompt();

  exitFlag = readCL(buffer);

  // Main loop for command prompt
  while (exitFlag == false)
  {

    // initialize new prompt
    clearArgs(newargv, newargv2);
    background = false;

    // check command conditions
    numberOfArgs = tokenize(buffer, cl);
    background = isBackground(numberOfArgs, cl, newargv);
    isPipe = isPipeline(numberOfArgs, cl, newargv, newargv2);

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
            processRedirect(1, 2, commandLine.arg3, INPUT);
          }
          else
          {
            processRedirect(2, 3, commandLine.arg4, INPUT);
          }
        }
        // If output redirected
        if (out)
        {
          if (numberOfArgs == 3)
          {
            processRedirect(1, 2, commandLine.arg3, OUTPUT);
          }
          else
          {
            processRedirect(2, 3, commandLine.arg4, OUTPUT);
          }
        }
        // If process is sent to the background
        if (background == true)
        {
          setpgid(0, 1);
        }

        isCommand = execve(commandLine.arg1, newargv, newenvp);
        if (isCommand == -1)
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
          waitpid(pid, &status, 0);
        }
        else
        {
          waitpid(pid, &status, WNOHANG);
        }
      }
    }
    else
    {
      processPipe(newargv, newargv2);
    }
    printCommandPrompt();
    exitFlag = readCL(buffer);
  }
  return 0;
}



/*
  Main File.
  By Daniel Bahrami and Scott Charles III
*/

#include "mysh.h"




int bgPid;

//TO DO: do we need this??
// #include <sys/types.h>

int main()
{
  CLInput commandLine = {};
  CLInput *cl = &commandLine;
  char buffer[BUFF_LEN] = {};
  char *const newenvp[] = {NULL};
  char *newargv[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
  char *newargv2[6] = {NULL, NULL, NULL, NULL, NULL, NULL};

  int bytesRead;
  int status;
  int pipefd[2];
  int isCommand;
  int numberOfArgs = 0;
  int comp;
  int argumentNumber;
  int isPipe = 0;
  

  bool exitFlag = false;
  bool background = false;
  bool redirection = false;
  bool in = false;
  bool out = false;

  pid_t pid;
  pid_t pid2;

  signal(SIGCHLD, &handle_sigchld);

  login(buffer);

  write(1, "mysh$ ", 6);
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

      if (pid == -1)
      {
        write(1, "fork failed\n", 12);
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
            newargv[1] = NULL;
            newargv[2] = NULL;
            int fd0 = open(commandLine.arg3, O_RDONLY);
            dup2(fd0, 0);
            close(fd0);
          }
          else
          {
            newargv[2] = NULL;
            newargv[3] = NULL;
            int fd0 = open(commandLine.arg4, O_RDONLY);
            dup2(fd0, 0);
            close(fd0);
          }
        }
        // If output redirected
        if (out)
        {
          if (numberOfArgs == 4)
          {
            newargv[2] = NULL;
            newargv[3] = NULL;
            int fd1 = open(commandLine.arg4, O_WRONLY);
            dup2(fd1, 1);
            close(fd1);
          }
          else
          {
            newargv[1] = NULL;
            newargv[2] = NULL;
            int fd1 = open(commandLine.arg3, O_WRONLY);
            dup2(fd1, 1);
            close(fd1);
          }
        }
        // If process is sent to the background
        if (background == true)
        {
          setpgid(0, 1);

        bgPid = getgpid(getpid());
          passBgPid(bgPid);
        }

        isCommand = execve(commandLine.arg1, newargv, newenvp);
        if (isCommand == -1)
        {
          write(1, "Not Valid, Try again\n", 21);
          exit(1);
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
      // process pipe
      processPipe(newargv, newargv2);
    }

    write(1, "mysh$ ", 6);
    exitFlag = readCL(buffer);
  }
  return 0;
}

// #include <stdio.h>
#include "shellOps.h"
#include "mysh.h"



// Provides a log username and login prompt to authenticate the user
// char buffer[], command line input
// return void
void login(char buffer[])
{
  int compUser = 0;
  int compPass = 0;
  bool correctLogin = false;
  char user1[BUFF_LEN] = "dan\n";
  char pass1[BUFF_LEN] = "apple\n";
  // Prompt Username
  do
  {
    clearArg(buffer);
    write(1, "enter username: ", 16);
    read(0, buffer, BUFF_LEN);
    compUser = my_strcmp(buffer, user1);
  } while (compUser != 0);

  // Prompt Password
  do
  {
    clearArg(buffer);
    write(1, "enter password: ", 16);
    read(0, buffer, BUFF_LEN);
    compPass = my_strcmp(buffer, pass1);
  } while (compPass != 0);
}

// Checks if I/O redirection was requested and sets either the in or out boolean accoridingly
// CLInput *commandLine, command line object
// bool *in, dereferenced 'in' boolean
// bool *out, dereferenced 'out' boolean
// int numberOfArgs, the number of arguments in the commandline input
// returns void
void checkRedirection(CLInput *commandLine, bool *in, bool *out, int numberOfArgs)
{
  char inFlag[BUFF_LEN] = {"<"};
  char outFlag[BUFF_LEN] = {">"};
  int comp = 0;
  *in = false;
  *out = false;
  if (numberOfArgs == 3)
  {
    comp = my_strcmp(inFlag, commandLine->arg2);
    if (comp == 0)
    {
      // < process
      // isRedir = true;
      *in = true;
    }
    else if (my_strcmp(outFlag, commandLine->arg2) == 0)
    {
      // > process
      // isRedir = true;
      *out = true;
    }
    else
    {
      // isRedir = false;
    }
  }
  else if (numberOfArgs == 4)
  {
    comp = my_strcmp(inFlag, commandLine->arg3);
    if (comp == 0)
    {
      // < process
      // isRedir = true;
      *in = true;
    }
    else if (my_strcmp(outFlag, commandLine->arg3) == 0)
    {
      // > process
      // isRedir = true;
      *out = true;
    }
    else
    {
      // isRedir = false;
    }
  }
}

// Clears all arguments in argument buffers 1 and 2
// char *newargv[], buffer 1
// char *newargv2[], buffer 2
// returns void
void clearArgs(char *newargv[], char *newargv2[])
{
  newargv[0] = NULL;
  newargv[1] = NULL;
  newargv[2] = NULL;
  newargv[3] = NULL;
  newargv[4] = NULL;

  newargv2[0] = NULL;
  newargv2[1] = NULL;
  newargv2[2] = NULL;
  newargv2[3] = NULL;
  newargv2[4] = NULL;
}

// executes the pipe operation based on the two commands passed in buffers 1 and 2
// char *newargv[], buffer 1
// char *newargv2[], buffer 2
// returns void
void processPipe(char *newargv[], char *newargv2[])
{
  int pipefd[2];
  char *const envp[] = {NULL};
  int pid1, pid2;
  int child_status;
  int isCommand;

  char *const argv1[] = {newargv[0], newargv[1], NULL};
  char *const argv2[] = {newargv2[0], newargv2[1], NULL};

  pipe(pipefd);
  pid1 = fork();
  if (pid1 == 0)
  {
    close(pipefd[READ_END]);
    dup2(pipefd[WRITE_END], 1);
    isCommand = execve(argv1[0], argv1, envp);
    if (isCommand == -1)
    {
      write(1, "Not Valid, Try again\n", 21);
      exit(1);
    }
  }
  close(pipefd[WRITE_END]);
  pid2 = fork();

  if (pid2 == 0)
  {
    dup2(pipefd[READ_END], 0);
    isCommand = execve(argv2[0], argv2, envp);
    if (isCommand == -1)
    {
      write(1, "Not Valid, Try again\n", 21);
      exit(1);
    }
  }
  close(pipefd[READ_END]);
  waitpid(pid1, &child_status, 0);
  waitpid(pid2, &child_status, 0);
}

// checks if a pipe is requested, sets the argument buffers
// int numberOfArgs, number of set arguments in the command line object
// CLInput *commandLine, commandline object
// char *newargv[], buffer 1
// char *newargv2[], buffer 2
// returns true if pipeline is requested
bool isPipeline(int numberOfArgs, CLInput *commandLine, char *newargv[], char *newargv2[])
{
  bool isPipe = false;
  char pipelineFlag[BUFF_LEN] = {"|"};
  int comp = 0;

  if (numberOfArgs == 3)
  {
    comp = my_strcmp(pipelineFlag, commandLine->arg2);
    if (comp == 0)
    {
      clearArgs(newargv, newargv2);
      newargv[0] = commandLine->arg1;
      newargv2[0] = commandLine->arg3;
      isPipe = true;
    }
  }
  if (numberOfArgs == 4)
  {
    comp = my_strcmp(pipelineFlag, commandLine->arg2);
    if (comp == 0)
    {
      clearArgs(newargv, newargv2);
      newargv[0] = commandLine->arg1;
      newargv2[0] = commandLine->arg3;
      newargv2[1] = commandLine->arg4;
      isPipe = true;
    }
    else
    {
      comp = my_strcmp(pipelineFlag, commandLine->arg3);
      if (comp == 0)
      {
        clearArgs(newargv, newargv2);
        newargv[0] = commandLine->arg1;
        newargv[1] = commandLine->arg2;
        newargv2[0] = commandLine->arg4;
        isPipe = true;
      }
    }
  }
  if (numberOfArgs == 5)
  {
    comp = my_strcmp(pipelineFlag, commandLine->arg3);
    if (comp == 0)
    {
      clearArgs(newargv, newargv2);
      newargv[0] = commandLine->arg1;
      newargv[1] = commandLine->arg2;
      newargv2[0] = commandLine->arg4;
      newargv2[1] = commandLine->arg5;
      isPipe = true;
    }
  }
  return isPipe;
}

// checks if process is sent to the background and sets arguments
// int numberOfArgs, number of set arguments in the command line object
// CLInput *commandLine, commandline object
// char *newargv[], buffer 1
// returns true if '&' is last argument
bool isBackground(int numberOfArgs, CLInput *commandLine, char *newargv[])
{
  int argumentNumber;
  bool background = false;
  char backgroundFlag[BUFF_LEN] = {"&"};
  int comp = 0;
  if (numberOfArgs == 1)
  {
    newargv[0] = commandLine->arg1;
    newargv[1] = NULL;
  }
  else if (numberOfArgs == 2)
  {
    newargv[0] = commandLine->arg1;
    newargv[1] = commandLine->arg2;
    newargv[2] = NULL;
    comp = my_strcmp(backgroundFlag, commandLine->arg2);
    if (comp == 0)
    {
      background = true;
      argumentNumber = 2;
      newargv[1] = NULL;
    }
  }
  else if (numberOfArgs == 3)
  {
    newargv[0] = commandLine->arg1;
    newargv[1] = commandLine->arg2;
    newargv[2] = commandLine->arg3;
    comp = my_strcmp(backgroundFlag, commandLine->arg3);
    if (comp == 0)
    {
      background = true;
      argumentNumber = 3;
      newargv[2] = NULL;
    }
  }
  else if (numberOfArgs == 4)
  {
    newargv[0] = commandLine->arg1;
    newargv[1] = commandLine->arg2;
    newargv[2] = commandLine->arg3;
    newargv[3] = commandLine->arg4;
    comp = my_strcmp(backgroundFlag, commandLine->arg4);
    if (comp == 0)
    {
      background = true;
      argumentNumber = 4;
      newargv[3] = NULL;
    }
  }
  else
  {
    newargv[0] = commandLine->arg1;
    newargv[1] = commandLine->arg2;
    newargv[2] = commandLine->arg3;
    newargv[3] = commandLine->arg4;
    newargv[4] = commandLine->arg5;
    comp = my_strcmp(backgroundFlag, commandLine->arg5);
    if (comp == 0)
    {
      background = true;
      argumentNumber = 5;
      newargv[4] = NULL;
    }
  }

  return background;
}

// internal exit command, exits the shell
// int bytesRead, number of bytes read 
// char buffer[], command line input
// returns true if 'exit' is typed
bool checkExit(int bytesRead, char buffer[])
{
  int i = 0;
  int sameString = false;
  char exit[5] = "exit\n";
  while (exit[i] == buffer[i] && exit[i] != '\n')
    i++;
  if (i == 4)
  {
    sameString = true;
  }
  return sameString;
}

// clears a single argument array
// char arg[], clears the array
// returns void
void clearArg(char arg[])
{
  int i = 0;
  for (i = 0; i < BUFF_LEN; i++)
  {
    arg[i] = 0;
  }
}
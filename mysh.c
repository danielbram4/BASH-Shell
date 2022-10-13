/*
  Main File.
  By Daniel Bahrami and Scott Charles III
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_LEN 256

typedef int bool;
#define true 1
#define false 0

#define READ_END  0
#define WRITE_END 1

//Represents CommandLine as a structure
struct CLInput
{
  char arg1[BUFF_LEN];
  char arg2[BUFF_LEN];
  char arg3[BUFF_LEN];
  char arg4[BUFF_LEN];
  char arg5[BUFF_LEN];
};typedef struct CLInput CLInput;

//Function Prototypes
bool checkExit(int bytesRead, char buffer[]);
void clearCL(CLInput *commandLine);
bool readCL(char buffer[]);
int tokenize(char buffer[], CLInput *commandLine);
int tok(char buffer[], char arg[], int i, int *numOfArgs);
void clearArg(char arg[]);

int main()
{
  CLInput commandLine = {};
  CLInput *cl = &commandLine;
  
  char buffer[BUFF_LEN] = {};

  int bytesRead;
  bool exitFlag = false;
  pid_t pid;
  pid_t pid2;
  int status;
  int pipefd[2];
  int isCommand;
  int numberOfArgs = 0;

  char * const newenvp[] = { NULL };


  write(1, "mysh$ ", 6);
  exitFlag = readCL(buffer);

  char * newargv[] = { NULL, NULL, NULL, NULL};
  char * newargv2[] = {NULL,NULL,NULL};
  
  while(exitFlag == false)
    {
      //Process CL **TO DO**
      if(pipe(pipefd) == -1)
	{
	  write(1,"pipe failed\n",12);
	  exit(EXIT_FAILURE);
	}
      
      pid = fork();

      if(pid == -1)
	{
	  write(1,"fork failed\n",12);
	  exit(EXIT_FAILURE);
	}
      
      if(pid == 0)
	{
	  //In Child Process, reading message from pipe
	  close(pipefd[WRITE_END]); //Close end not being used
	  bytesRead = read(pipefd[READ_END], buffer, BUFF_LEN-1);
	  numberOfArgs = tokenize(buffer, cl);
	  close(pipefd[READ_END]);
	  
	  if(numberOfArgs == 1)
	    {
	      newargv[0] = commandLine.arg1;
	    }
	  else if (numberOfArgs == 2)
	    {
	      newargv[0] = commandLine.arg1;
	      newargv[1] = commandLine.arg2;
	    }
	  else
	    {
	      newargv[0] = commandLine.arg1;
              newargv[1] = commandLine.arg2;
	      newargv[2] = commandLine.arg3;
	      newargv[3] = commandLine.arg4;
	      newargv[4] = commandLine.arg5;
	    }
	  if(*commandLine.arg3 == '&')
	    {
	      setpgid(0,0);
	      execve(commandLine.arg1, newargv, newenvp);
	      if(isCommand == -1)
                {
                  write(1, "Not Valid, Try again\n", 21);
                  exit(1);
                }
	    }
	  else
	    {
	      isCommand = execve(commandLine.arg1, newargv, newenvp);
	      if(isCommand == -1)
		{
		  write(1, "Not Valid, Try again\n", 21);
		  exit(1);
		}
	    }
	  
	}
      else
	{
	  close(pipefd[READ_END]);
	  write(pipefd[WRITE_END], buffer, BUFF_LEN);
	  if(*commandLine.arg3 == '&')
	    {
	      waitpid(pid, &status, 0);
	    }
	  else
	    {
	      waitpid(pid, &status, WNOHANG);
	    }
	    //printf("WAITING");
	    //}
	  
	  //Reading CL
	  write(1, "mysh$ ", 6);
	  exitFlag = readCL(buffer);
    
	}
    }
  return 0;
}

//Reads CL and Stores it inside the buffer
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
  
  if(buffer[0] != '\n')
    {
      numOfArgs++;
      clearCL(commandLine);
      i = tok(buffer, commandLine->arg1, i, &numOfArgs);
      i = tok(buffer, commandLine->arg2, i, &numOfArgs);
      i = tok(buffer, commandLine->arg3, i, &numOfArgs);
      i = tok(buffer, commandLine->arg4, i, &numOfArgs);
      i = tok(buffer, commandLine->arg5, i, &numOfArgs);
      
      printf("\nfirst arg is: %s\n", commandLine->arg1);
      printf("\nSecond arg is: %s\n", commandLine->arg2);
      printf("\nThird arg is: %s\n", commandLine->arg3);
    }
  return numOfArgs;
}

int tok(char buffer[], char arg[], int i, int *numOfArgs)
{
  int bytesRead = 0;
  int endOfString = false;
  char *delimit = buffer;
  int k = 0;
  clearArg(arg);
  if(buffer[i] == '\n')
    endOfString = true;
  while(*delimit != ' ' && endOfString == false)
    {
      arg[k] = buffer[i];
      
      i++;
      k++;
      if(buffer[i] != '\n')
	{
	  *delimit = buffer[i];
	}
      else
	{
	  endOfString = true;
	}
    }
  
  if(endOfString == false)
    {
      *numOfArgs = *numOfArgs + 1;
      i++;
      *delimit = buffer[i];
    }
  return i;
}
bool checkExit(int bytesRead, char buffer[])

{
  int i = 0;
  int sameString = false;
  char exit[5] = "exit\n";
  while(exit[i] == buffer[i] && exit[i] != '\n')
    i++;
  if(i == 4)
    {
      sameString = true;
    }
  return sameString;
}

void clearCL(CLInput *commandLine)

{
  int i = 0;
  for(i = 0; i < BUFF_LEN; i++)
    {
      commandLine->arg1[i] = 0;
      commandLine->arg2[i] = 0;
      commandLine->arg3[i] = 0;
    }
}

void clearArg(char arg[])
{
  int i = 0;
  for(i = 0; i < BUFF_LEN; i++)
    {
      arg[i] = 0;
    }
}

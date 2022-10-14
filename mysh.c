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
  //char arg4[BUFF_LEN];
  //  char arg5[BUFF_LEN];
};typedef struct CLInput CLInput;

//Function Prototypes
bool checkExit(int bytesRead, char buffer[]);
void clearCL(CLInput *commandLine);
bool readCL(char buffer[]);
int tokenize(char buffer[], CLInput *commandLine);
int tok(char buffer[], char arg[], int i, int *numOfArgs);
void clearArg(char arg[]);
int my_strcmp(char *s1, char *s2);
bool isBackground(int numOfArgs, CLInput *commandLine, char * newargv[]);

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
  bool background = false;
  int comp;
  int argumentNumber;

  char * const newenvp[] = { NULL };


  write(1, "mysh$ ", 6);
  exitFlag = readCL(buffer);

  char * newargv[] = { NULL, NULL, NULL,NULL};
  
  while(exitFlag == false)
    {
      background = false;
      //Process CL **TO DO**
      if(pipe(pipefd) == -1)
	{
	  write(1,"pipe failed\n",12);
	  exit(EXIT_FAILURE);
	}
      

      numberOfArgs = tokenize(buffer,cl);
      printf("Number of args: %i\n", numberOfArgs);
      background = isBackground(numberOfArgs, cl, newargv);
      
      pid = fork();
      
      if(pid == -1)
	{
	  write(1,"fork failed\n",12);
	  exit(EXIT_FAILURE);
	}
      
      if(pid == 0)
	{
	  if(background == true)
	    {
	      setpgid(0,0);
	    }

	  execve(commandLine.arg1, newargv, newenvp);
	  if(isCommand == -1)
	    {
	      write(1, "Not Valid, Try again\n", 21);
	      exit(1);
	    }
	}
      else
	{
	  //Parent Process       
	  if(background == false)
	    {
	      waitpid(pid, &status, 0);
	    }
	  else
	    {
	      waitpid(pid, &status, WNOHANG);
	    }
	}
      write(1, "mysh$ ", 6);
      exitFlag = readCL(buffer);
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
      clearCL(commandLine);
      i = tok(buffer, commandLine->arg1, i, &numOfArgs);
      i = tok(buffer, commandLine->arg2, i, &numOfArgs);
      i = tok(buffer, commandLine->arg3, i, &numOfArgs);
      //i = tok(buffer, commandLine->arg4, i, &numOfArgs);
      //i = tok(buffer, commandLine->arg5, i, &numOfArgs);
      
      printf("\nfirst arg is: %s\n", commandLine->arg1);
      printf("\nSecond arg is: %s\n", commandLine->arg2);
      printf("\nThird arg is: %s\n", commandLine->arg3);
    }
  return numOfArgs;
}
bool isBackground(int numberOfArgs, CLInput *commandLine, char * newargv[])
{
  int argumentNumber;
  bool background = false;
  char backgroundFlag[BUFF_LEN] = {"&"};
  int comp = 0;
  if(numberOfArgs == 1)
    {
      newargv[0] = commandLine->arg1;
      newargv[1] = NULL;
    }
  else if (numberOfArgs == 2)
    {
      newargv[0] = commandLine->arg1;
      newargv[1] = commandLine->arg2;
      newargv[2] = NULL;
      comp = my_strcmp(backgroundFlag,commandLine->arg2);
      if(comp == 0)
	{
	  background = true;
	  argumentNumber = 2;
	  newargv[1] = NULL;
	}
    }
  else
    {
      newargv[0] = commandLine->arg1;
      newargv[1] = commandLine->arg2;
      newargv[2] = commandLine->arg3;
      comp = my_strcmp(backgroundFlag,commandLine->arg3);
      if(comp == 0)
	{
	  background = true;
	  argumentNumber = 3;
	  newargv[2] = NULL;
	}
      
      // newargv[3] = commandLine.arg4;
      //newargv[4] = commandLine.arg5;
    }
  return background;
}
int tok(char buffer[], char arg[], int i, int *numOfArgs)
{
  int bytesRead = 0;
  int endOfString = false;
  char *delimit = buffer;
  int k = 0;
  clearArg(arg);
  if(buffer[i] == '\n')
    {
      endOfString = true;
    }
  else
    {
      *numOfArgs = *numOfArgs + 1;
    }
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

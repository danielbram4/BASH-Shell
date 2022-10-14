/*
  Main File.
  By Daniel Bahrami and Scott Charles III
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_LEN 256

typedef int bool;
#define true 1
#define false 0

#define READ_END 0
#define WRITE_END 1

// Represents CommandLine as a structure
struct CLInput
{
  char arg1[BUFF_LEN];
  char arg2[BUFF_LEN];
  char arg3[BUFF_LEN];
<<<<<<< HEAD
  char arg4[BUFF_LEN];
  char arg5[BUFF_LEN];
};typedef struct CLInput CLInput;
=======
  char arg4[1];
};
typedef struct CLInput CLInput;
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006

// Function Prototypes
bool checkExit(int bytesRead, char buffer[]);
void clearCL(CLInput *commandLine);
bool readCL(char buffer[]);
int tokenize(char buffer[], CLInput *commandLine);
<<<<<<< HEAD
int tok(char buffer[], char arg[], int i, int *numOfArgs);
void clearArg(char arg[]);
int my_strcmp(char *s1, char *s2);
bool isBackground(int numOfArgs, CLInput *commandLine, char * newargv[]);
bool isPipeline(int numberOfArgs, CLInput *commandLine, char * argv1[], char * argv2[]);
void clearArgs(char * newargv[], char * newargv2[]);
void processPipe(char * argv1[], char * argv2[]);
bool isRedirection(CLInput *commandLine, bool *in, bool *out);
=======
int my_strcmp(char *s1, char *s2);
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006

int main()
{
  CLInput commandLine = {};
  CLInput *cl = &commandLine;

  char buffer[BUFF_LEN] = {};

  int bytesRead;
  bool exitFlag = false;
  bool background = false;
  pid_t pid;
  pid_t pid2;
  int status;
  int pipefd[2];
  int isCommand;
  int numberOfArgs = 0;
<<<<<<< HEAD
  bool background = false;
  int comp;
  int argumentNumber;
  int isPipe = 0;
  bool redirection = false;
  bool in = false;
  bool out = false;
=======
  char backgroundFlag[BUFF_LEN] = {"&"};
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006

  char *const newenvp[] = {NULL};

  write(1, "mysh$ ", 6);
  exitFlag = readCL(buffer);

<<<<<<< HEAD
  char * newargv[6] = { NULL, NULL, NULL,NULL, NULL,NULL};
  char * newargv2[6] = { NULL, NULL, NULL,NULL, NULL,NULL};
  
  while(exitFlag == false)
    {
      clearArgs(newargv, newargv2);
      background = false;

      numberOfArgs = tokenize(buffer,cl);
      printf("Number of args: %i\n", numberOfArgs);
      background = isBackground(numberOfArgs, cl, newargv);
      isPipe = isPipeline(numberOfArgs, cl, newargv, newargv2);
      printf("Is a Pipe %d\n", isPipe);

      if(isPipe == false)
	{
	  pid = fork();
	  
	  if(pid == -1)
	    {
	      write(1,"fork failed\n",12);
	      exit(EXIT_FAILURE);
	    }

	  
	  if(pid == 0)
	    {
	      redirection =  isRedirection(cl, &in, &out);
	      if(in)
		{
		  newargv[1] = NULL;
		  newargv[2] = NULL;
		  int fd0 = open(commandLine.arg3, O_RDONLY);
		  dup2(fd0,0);
		  close(fd0);
		}
	      if(out)
		{
		  newargv[1] = NULL;
                  newargv[2] = NULL;
		  int fd1 = open(commandLine.arg3 ,O_WRONLY);
		  dup2(fd1, 1);
		  close(fd1);
		}
	      
	      if(background == true)
		{
		  setpgid(0,0);
		}
	      
	      isCommand = execve(commandLine.arg1, newargv, newenvp);
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
	}
      else
	{
	  //process pipe
	  printf("Processed Pipe!\n");
	  processPipe(newargv, newargv2);
	  //	  printf("Processed Pipe!\n");
	}
      
      write(1, "mysh$ ", 6);
=======
  char *newargv[] = {NULL, NULL, NULL, NULL};

  while (exitFlag == false)
  {
    // Process CL **TO DO**
    if (pipe(pipefd) == -1)
    {
      write(1, "pipe failed\n", 12);
      exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
      write(1, "fork failed\n", 12);
      exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {

      
      // if (background == true)
      // {
      //   setpgid(0, 1);
      // }
      
      // In Child Process, reading message from pipe
      close(pipefd[WRITE_END]); // Close end not being used
      bytesRead = read(pipefd[READ_END], buffer, BUFF_LEN - 1);
      numberOfArgs = tokenize(buffer, cl);
      close(pipefd[READ_END]);
      if (numberOfArgs == 1)
      {
        newargv[0] = commandLine.arg1;
      }
      else if (numberOfArgs == 2)
      {
        newargv[0] = commandLine.arg1;

        int comp = my_strcmp(backgroundFlag, commandLine.arg2);
        if (comp == 0)
        {
          background = true;
        }
        else
        {
          newargv[1] = commandLine.arg2;
        }
      }
      else
      {
        newargv[0] = commandLine.arg1;
        newargv[1] = commandLine.arg2;

        int comp = my_strcmp(backgroundFlag, commandLine.arg3);
        if (comp == 0)
        {
          background = true;
        }
        else
        {
          newargv[2] = commandLine.arg3;
        }
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
      close(pipefd[READ_END]);
      write(pipefd[WRITE_END], buffer, BUFF_LEN);

      waitpid(pid, &status, 0);

      // Reading CL
      write(1, "mysh$ ", 0);
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006
      exitFlag = readCL(buffer);
    }
  }
  return 0;
}
<<<<<<< HEAD
bool isRedirection(CLInput *commandLine, bool *in, bool *out)
{
  char inFlag[BUFF_LEN] = {"<"};
  char outFlag[BUFF_LEN] = {">"};
  int comp = 0;
  bool isRedir;
  *in = false;
  *out = false;
  comp = my_strcmp(inFlag,commandLine->arg2);
  if(comp == 0)
    {
      // < process
      isRedir = true;
      *in = true;
    }
  else if (my_strcmp(outFlag,commandLine->arg2) == 0)
    {
      // > process
      isRedir = true;
      *out = true;
    }
  else
    {
      isRedir = false;
    }
}
//Reads CL and Stores it inside the buffer
void clearArgs(char * newargv[], char * newargv2[])
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
=======

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

// Reads CL and Stores it inside the buffer
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006
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
<<<<<<< HEAD
=======
// tokenizes 3 arguments from command line
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006
int tokenize(char buffer[], CLInput *commandLine)
{
  int bytesRead = 0;
  int endOfString = false;
  int i = 0;
  char *delimit = buffer;
  int numOfArgs = 0;

  if (buffer[0] != '\n')
  {
    numOfArgs++;
    clearCL(commandLine);
    while (*delimit != ' ' && endOfString == false)
    {
      commandLine->arg1[i] = buffer[i];

      i++;
      if (buffer[i] != '\n')
      {
        *delimit = buffer[i];
      }
      else
      {
        endOfString = true;
      }
    }

    // printf("\nfirst arg is: %s\n", commandLine->arg1); // testing
    if (endOfString == false)
    {
<<<<<<< HEAD
      clearCL(commandLine);
      i = tok(buffer, commandLine->arg1, i, &numOfArgs);
      i = tok(buffer, commandLine->arg2, i, &numOfArgs);
      i = tok(buffer, commandLine->arg3, i, &numOfArgs);
      i = tok(buffer, commandLine->arg4, i, &numOfArgs);
      i = tok(buffer, commandLine->arg5, i, &numOfArgs);
      
      printf("\nfirst arg is: %s\n", commandLine->arg1);
      printf("\nSecond arg is: %s\n", commandLine->arg2);
      printf("\nThird arg is: %s\n", commandLine->arg3);
      printf("\nFourth arg is: %s\n", commandLine->arg4);
      printf("\nFifth arg is: %s\n", commandLine->arg5);

=======
      numOfArgs++;
      *delimit = buffer[++i];
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006
    }
    while (*delimit != ' ' && endOfString == false)
    {
      commandLine->arg2[f] = buffer[i];
      i++;
      f++;
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
      numOfArgs++;
    while (endOfString == false)
    {
      i++;
      if (buffer[i] == '\n')
      {
        endOfString = true;
      }
      else
      {
        commandLine->arg3[k] = buffer[i];
        k++;
      }
    }

    // printf("\nsecond arg is: %s\n", commandLine->arg2);
    // printf("\nthird arg is: %s\n", commandLine->arg3);
  }
  return numOfArgs;
}
void processPipe(char * newargv[], char * newargv2[])
{
  int pipefd[2];
  char * const envp[] = {NULL};
  int pid1, pid2;
  int child_status;
  int isCommand;

  char * const argv1[] = {newargv[0], newargv[1], NULL };
  char * const argv2[] = {newargv2[0], newargv2[1], NULL };

  pipe(pipefd);
  pid1 = fork();
  if(pid1 == 0)
    {
      close(pipefd[READ_END]);
      dup2(pipefd[WRITE_END], 1);
      isCommand = execve(argv1[0], argv1, envp);
      if(isCommand == -1)
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
      isCommand = execve(argv2[0],argv2,envp);
      if(isCommand == -1)
	{
	  write(1, "Not Valid, Try again\n", 21);
	  exit(1);
	}
    }
  close(pipefd[READ_END]);
  waitpid(pid1, &child_status, 0);
  waitpid(pid2, &child_status, 0);
}
bool isPipeline(int numberOfArgs, CLInput *commandLine, char * newargv[], char * newargv2[])
{
  bool isPipe = false;
  char pipelineFlag[BUFF_LEN] = {"|"};
  int comp = 0;

  if(numberOfArgs == 3)
    {
      comp = my_strcmp(pipelineFlag,commandLine->arg2);
      if(comp == 0)
	{
	  clearArgs(newargv, newargv2);
	  newargv[0] = commandLine->arg1;
	  /*newargv[1] = NULL;
	  newargv[2] = NULL;
	  newargv[3] = NULL;
	  newargv[4] = NULL;
	  newargv[5] = NULL;*/
	  newargv2[0] = commandLine->arg3;
	  isPipe = true;
	  //*commandLine->arg2 = NULL;
	}
    }
  if(numberOfArgs == 4)
    {
      comp = my_strcmp(pipelineFlag,commandLine->arg2);
      if(comp == 0)
        {
	  clearArgs(newargv, newargv2);
          newargv[0] = commandLine->arg1;
          newargv2[0] = commandLine->arg3;
	  newargv2[1] = commandLine->arg4;
          isPipe = true;
	  //	  *commandLine->arg2 = NULL;
        }
      else
	{
	  comp = my_strcmp(pipelineFlag,commandLine->arg3);
	  if(comp == 0)
	    {
	      clearArgs(newargv, newargv2);
	      newargv[0] = commandLine->arg1;
	      newargv[1] = commandLine->arg2;
	      newargv2[0] = commandLine->arg4;
	      isPipe = true;
	      // *commandLine->arg3 = NULL;
	    }
	}
    }
  if(numberOfArgs == 5)
    {
      comp = my_strcmp(pipelineFlag,commandLine->arg3);
      if(comp == 0)
        {
	  clearArgs(newargv, newargv2);
          newargv[0] = commandLine->arg1;
	  newargv[1] = commandLine->arg2;
          newargv2[0] = commandLine->arg4;
	  newargv2[1] = commandLine->arg5;
          isPipe = true;
	  //	  *commandLine->arg3 = NULL;
        }
    }
  /*
  if(isPipe == true)
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
  */
  return isPipe;
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
  while (exit[i] == buffer[i] && exit[i] != '\n')
    i++;
  if (i == 4)
  {
    sameString = true;
  }
  return sameString;
}

void clearCL(CLInput *commandLine)

{
  int i = 0;
<<<<<<< HEAD
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
=======
  for (i = 0; i < BUFF_LEN; i++)
  {
    commandLine->arg1[i] = 0;
    commandLine->arg2[i] = 0;
    commandLine->arg3[i] = 0;
  }
}
>>>>>>> 2f40ff151f8064e70fb59895d18910679ae45006

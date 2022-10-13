/*
  Main File.
  By Daniel Bahrami and Scott Charles III

  Testing for push
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_LEN 256

typedef int bool;
#define true 1
#define false 0

#define READ_END  0
#define WRITE_END 1

bool readCL();
void clearCL();
bool checkExit(int bytesRead);
char buffer[BUFF_LEN] = {};

//Represents the Command Line as a structure
struct CLInput
{
  char arg1[BUFF_LEN];
  char arg2[BUFF_LEN];

};typedef struct CLInput CLInput;

CLInput commandLine = {};

int main()
{
  int bytesRead;
  bool exit = false;
  pid_t pid;
  int status;

  char * const newenvp[] = { NULL };

  write(1, "mysh$ ", 6);
  exit = readCL();

  char * const newargv[] = { commandLine.arg1 , commandLine.arg2,NULL };
  
  while(exit == false)
    {
      //Process CL **TO DO**
      
      pid = fork();
      if(pid == 0)
	{
	  //printf("Hello from child");
	  execve(commandLine.arg1, newargv, newenvp);
	}
      else
	{
	  waitpid(pid, &status, 0);
	  //Reading CL
	  write(1, "mysh$ ", 6);
	  exit = readCL();
	}
    }
  return 0;
}
bool readCL()
{
  int bytesRead = 0;
  int exitCond = false;
  int endOfString = false;
  int i = 0;
  int k = 0;
  char *delimit = buffer;
  
  bytesRead = read(0, buffer, BUFF_LEN);
  exitCond = checkExit(bytesRead);
  /*Tokenizes two arguments*/
  if(exitCond == false)
    {
      clearCL();
      while(*delimit != ' ' && endOfString == false)
	{
	  commandLine.arg1[i] = buffer[i];
	  i++;
	  if(buffer[i] != '\n')
	    {
	      *delimit = buffer[i];
	    }
	  else
	    {
	      endOfString = true;
	    }
	}
       printf("\nfirst arg is: %s\n", commandLine.arg1);
       while(endOfString == false)
	 {
	   i++;
	   if(buffer[i] == '\n')
	     {
	       endOfString = true;
	     }
	   else
	     {
	       commandLine.arg2[k] = buffer[i];
	       k++;
	     }
	 }
      
      printf("\nsecond arg is: %s\n", commandLine.arg2);
    }
  return exitCond;
}
bool checkExit(int bytesRead)
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

void clearCL()
{
  int i = 0;
  for(i = 0; i < BUFF_LEN; i++)
    {
      commandLine.arg1[i] = 0;
      commandLine.arg2[i] = 0;
    }
}

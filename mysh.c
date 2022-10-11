/*
  Main File.
  By Daniel Bahrami and Scott Charles III
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFF_LEN 256
typedef int bool;
#define true 1
#define false 0

bool readCL();
bool checkExit(int bytesRead);
char buffer[BUFF_LEN] = {};

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
  write(1, "mysh$ ", 6);
  exit = readCL();

  while(exit == false)
    {
      //Process CL **TO DO**
      
      //Reading CL
      write(1, "mysh$ ", 6);
      exit = readCL();

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
      memset(commandLine.arg1, 0 , sizeof commandLine.arg1);
      memset(commandLine.arg2, 0 , sizeof commandLine.arg2);
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
	   commandLine.arg2[k] = buffer[i];
	   k++;
	   if(buffer[i] == '\n')
	     {
	       endOfString = true;
	     }
	 }
      
      printf("\nsecond arg is: %s\n\n", commandLine.arg2);
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

/*
  Main File.
  By Daniel Bahrami and Scott Charles III
*/
#include <stdio.h>
#include <unistd.h>
#define BUFF_LEN 256
typedef int bool;
#define true 1
#define false 0

bool readCL();
bool checkExit(int bytesRead);
char buffer[BUFF_LEN] = {};


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
  char *delimit = buffer;
  char arg1[BUFF_LEN] = {};
  char arg2[BUFF_LEN] = {};
  
  bytesRead = read(0, buffer, BUFF_LEN);
  exitCond = checkExit(bytesRead);
  /*Tokenizes first argument*/
  if(exitCond == false)
    {
      while(*delimit != ' ' && endOfString == false)
	{
	  arg1[i] = buffer[i];
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
      printf("first arg is: %s\n", arg1);
      /*Tokenize 2nd Argument*/
    }
  //For testing
  
  //printf("first arg is: %s\n", arg1);
  //printf("second arg is: %s\n", arg2);
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

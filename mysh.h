#ifndef MYSH_H
#define MYSH_H
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
  char arg4[BUFF_LEN];
  char arg5[BUFF_LEN];
};
typedef struct CLInput CLInput;

// Function Prototypes
bool checkExit(int bytesRead, char buffer[]);
void clearCL(CLInput *commandLine);
bool readCL(char buffer[]);
int tokenize(char buffer[], CLInput *commandLine);
int tok(char buffer[], char arg[], int i, int *numOfArgs);
void clearArg(char arg[]);
int my_strcmp(char *s1, char *s2);
bool isBackground(int numOfArgs, CLInput *commandLine, char *newargv[]);
bool isPipeline(int numberOfArgs, CLInput *commandLine, char *argv1[], char *argv2[]);
void clearArgs(char *newargv[], char *newargv2[]);
void processPipe(char *argv1[], char *argv2[]);
bool isRedirection(CLInput *commandLine, bool *in, bool *out, int numberOfArgs);
void login(char buffer[]);

#endif

#ifndef SHELLOPS_H
#define SHELLOPS_H

typedef int bool;
#define true 1
#define false 0

#define READ_END 0
#define WRITE_END 1
#define BUFF_LEN 256
#define EQUAL 0
#define USERNAME "dan\n"
#define PASSWORD "apple\n"

void login(char buffer[]);
void checkRedirection(CLInput *commandLine, bool *in, bool *out, int numberOfArgs);
void clearArgs(char *newargv[], char *newargv2[]);
void processPipe(char *argv1[], char *argv2[]);
bool isPipeline(int numberOfArgs, CLInput *commandLine, char *argv1[], char *argv2[]);
bool isBackground(int numOfArgs, CLInput *commandLine, char *newargv[]);
bool checkExit(int bytesRead, char buffer[]);
void clearArg(char arg[]);
void processRedirect(int null1, int null2, char argument[], int direction, char *newargv[], char *newargv2[]);

#endif
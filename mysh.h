#ifndef MYSH_H
#define MYSH_H
#define BUFF_LEN 256

struct CLInput
{
  char arg1[BUFF_LEN];
  char arg2[BUFF_LEN];
  char arg3[BUFF_LEN];
  char arg4[BUFF_LEN];
  char arg5[BUFF_LEN];
};
typedef struct CLInput CLInput;

typedef int bool;
#define true 1
#define false 0

#include "shellOps.h"
#include "commandLineOps.h"
#include "stringOps.h"
#include "signalhandlers.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERROR_NO -1
#define INPUT 0
#define OUTPUT 1

#endif

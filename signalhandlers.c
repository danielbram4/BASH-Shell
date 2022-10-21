#include "mysh.h"

//notifies user when process is complete
void handle_sigchld(int sig)
{
    printSIGINT();    
}
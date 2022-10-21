#include "signalhandlers.h"
#include "stringOps.h"

//notifies user when process is complete
void handle_sigchld(int sig)
{
    printSIGINT();    
}
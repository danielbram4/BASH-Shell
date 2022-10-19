#include "signalhandlers.h"
#include "mysh.h"


//notifies user when process is complete
void handle_sigchld(int sig)
{
    write(1, "\nProcess Interuppted!\n", 23);       
}
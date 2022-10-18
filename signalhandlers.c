#include "signalhandlers.h"
#include "mysh.h"



//notifies user when process is complete
void handle_sigchld(int sig)
{

    if(getgpid(bgPid) == 1){
        write(1, "Process Complete!\n", 19);
    }
  
}
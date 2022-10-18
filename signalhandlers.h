#ifndef SIGNALHANDLERS_H
#define SIGNALHANDLERS_H

void handle_sigchld(int sig);
void passBgPid(int pid);

#endif
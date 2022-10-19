#ifndef SIGNALHANDLERS_H
#define SIGNALHANDLERS_H

void handle_sigchld(int sig);
void passPid(int pid);

#endif
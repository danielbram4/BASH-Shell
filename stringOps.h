#ifndef STRINGOPS_H
#define STRINGOPS_H

#define PROMPT_LENGTH 6
#define FORK_FAILED_LENGTH 12
#define NOT_VALID_COMMAND_LENGTH 21
#define USERNAME_PROMPT_LENGTH 16
#define PASSWORD_PROMPT_LENGTH 16
#define PROCESSES_INT_LENGTH 22
#define BACKGROUND_FAILED_LENGTH 28
#define WAIT_PID_FAILED_LENGTH 16
#define READ_ERROR_LENGTH 22
#define FAILED_TO_OPEN_LENGTH 20
#define EQUAL 0
#define REDIRECTION_FAILED_LENGTH 23
#define FAILED_TO_CLOSE_LENGTH 21
#define FAILED_PIPE_LENGTH 20
#define FAILED_TO_WRITE_LENGTH 16

#define USERNAME "dan\n"
#define PASSWORD "apple\n"
#define EXIT_COMMAND "exit\n"
#define NEW_LINE_CHAR '\n'
#define AMPERSAND '&'
#define INPUT_CHAR "<"
#define OUTPUT_CHAR ">"
#define PIPE_CHAR '|'

int my_strcmp(char *s1, char *s2);
void printCommandPrompt();
void printForkFailed();
void printInvalidArgument();
void printUsernamePrompt();
void printPasswordPrompt();
void printSIGINT();
void printBackgroundFailed();
void printWaitPidFailed();
void printReadError();
void printFailedToOpen();
void printFailedToClose();
void printRedirectionFailed();
void printPipeFailed();
void writeFailed();

#endif
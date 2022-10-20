#ifndef STRINGOPS_H
#define STRINGOPS_H

#define PROMPT_LENGTH 6
#define FORK_FAILED_LENGTH 12
#define NOT_VALID_COMMAND_LENGTH 21
#define USERNAME_PROMPT_LENGTH 16
#define PASSWORD_PROMPT_LENGTH 16
#define PROCESSES_INT_LENGTH 22
#define EQUAL 0

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

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LIMIT 200

#define COMMAND_LNGTH  10

#define MAX_NO_OF_PATHS  100

#define MAX_LEN 1024

#define STRING_LEN  512

#define DIR_SEPARATOR   "/"

#define EXIT_CMD 1

#define ECHO_CMD 2

#define TYPE_CMD 3

#define PWD_CMD  4

#define CD_CMD   5

#define FAILURE -1

#define SUCCESS 0

int getCommandType(char *command);

void workingOfExit(char command[]);

void workingOfEcho(char *command);

void workingOfType(char *command, int count);

int getFilePath(char envVar[], char cmdToBeSearch[], char *returnFilePath);

void executeCommand(char command[]);

void workingOfPwd();

void workingOfCD(char command[]);

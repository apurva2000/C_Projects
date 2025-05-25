#include <headerFile.h>

int getCommandType(char command[])
{
    if(strcmp(command, "exit") == 0)
    {
        return EXIT_CMD;
    }
    if(strcmp(command, "echo") == 0)
    {
        return ECHO_CMD;
    }
    if(strcmp(command, "type") == 0)
    {
        return TYPE_CMD;
    }
    if(strcmp(command, "pwd") == 0)
    {
        return PWD_CMD;
    }
    if(strcmp(command, "cd") == 0)
    {
        return CD_CMD;
    }
    return FAILURE;
}

void workingOfExit(char command[])
{
    if(strcmp(command, "exit 0") == 0)
    {
        exit(0);
    }
    else
    {
        printf("Incorrect Usage.\n");
    }
}

void workingOfEcho(char *command)
{
    char *cmdstr;
    int i = 0;
    cmdstr = strtok(command, " ");
    while(cmdstr != NULL)
    {
        if(i > 0)
        {
            for(int j=0; j<strlen(cmdstr); j++)
            {
                if(cmdstr[j] != '"')
                {
                    printf("%c", cmdstr[j]);
                }
            }
            printf(" ");
        }
        cmdstr = strtok(NULL, " ");
        i++;
    }
    printf("\n");
}

void workingOfType(char *command, int count)
{
    char *cmdstr;
    char *cmdToSrch;
    int returnType;
    char filepath[MAX_LEN];
    int fileFoundFlag = 0;
    const char envVar[] = "PATH";

    if(count > 1)
    {
        printf("Too many arguments.\n");
        return;
    }

    cmdstr = strtok(command, " ");
    if(cmdstr == NULL)
    {
        printf("Empty command.\n");
        return;
    }

    cmdToSrch = strtok(NULL, " ");
    if(cmdToSrch == NULL)
    {
        printf("Enter command after type");
        return;
    }

    returnType = getCommandType(cmdToSrch);
    if(returnType == FAILURE)
    {
        fileFoundFlag = getFilePath((char *)envVar, cmdToSrch, filepath);

        if(fileFoundFlag == 0)
        {
            printf("%s is in %s\n", cmdToSrch, filepath);
        }
        else
        {
            printf("%s: not found\n", cmdToSrch);
        }
    }
    else
    {
        printf("%s is a shell builtin\n", cmdToSrch);
        return;
    }
}

int getFilePath(char envVar[], char cmdToBeSearch[], char *returnFilePath)
{
    char *pathVar = NULL;
    char pathArr[MAX_NO_OF_PATHS][STRING_LEN];
    char filepath[MAX_LEN];
    char tempPath[MAX_LEN];
    int pathCount = 0;
    int icounter = 0;
    int fileFoundFlag = 0;

    strncpy(tempPath, getenv(envVar), MAX_LEN);
    pathVar = strtok(tempPath, ":");
    while(pathVar != NULL && pathCount < MAX_NO_OF_PATHS)
    {
        strcpy(pathArr[pathCount], pathVar);
        pathCount++;
        pathVar = strtok(NULL, ":");
    }
    for(icounter=0; icounter<pathCount; icounter++)
    {
        snprintf(filepath,
                 MAX_LEN,
                 "%s%s%s",
                 pathArr[icounter],
                 DIR_SEPARATOR,
                 cmdToBeSearch);

        if(access(filepath, F_OK) == 0)
        {
            fileFoundFlag = 1;
            break;
        }
    }
    if(fileFoundFlag == 1)
    {
        strncpy(returnFilePath, filepath, MAX_LEN);
        return SUCCESS;
    }

    return FAILURE;
}

void executeCommand(char command[])
{
    char *cmdstr;
    char filepath[MAX_LEN];
    const char *envVar = "PATH";
    int fileFoundFlag = 0;
    char commandCopy[MAX_LEN];
    char firstToken[STRING_LEN];

    strncpy(commandCopy, command, MAX_LEN);

    cmdstr = strtok(commandCopy, " ");
    if(cmdstr == NULL)
    {
        printf("Empty command.\n");
        return;
    }

    strncpy(firstToken, cmdstr, STRING_LEN);
    firstToken[STRING_LEN - 1] = '\0';

    fileFoundFlag = getFilePath((char *)envVar, firstToken, filepath);
    if(fileFoundFlag == SUCCESS)
    {
        system(command);
    }
    else
    {
        printf("%s: not found\n", cmdstr);
    }
}

void workingOfPwd()
{
    char pwd[MAX_LEN];

    if(getcwd(pwd, MAX_LEN) != NULL)
    {
        printf("%s\n", pwd);
        return;
    }

    printf("Unable to get present working directory.");
}

void workingOfCD(char command[])
{
    char commandCopy[MAX_LEN];
    char *dirpath;
    char *cmdstr;

    strncpy(commandCopy, command, MAX_LEN);

    cmdstr = strtok(commandCopy, " ");
    if(cmdstr == NULL)
    {
        printf("Empty command.\n");
        return;
    }

    dirpath = strtok(NULL, " ");
    if(dirpath == NULL)
    {
        printf("Enter path");
        return;
    }

    if(chdir(dirpath) == FAILURE)
    {
        printf("%s: %s: No such file or directory\n", cmdstr, dirpath);
    }

}

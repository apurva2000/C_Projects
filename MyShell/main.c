#include <headerFile.h>

int main()
{
    char str[MAX_LIMIT];
    char *command;
    char tempCmd[COMMAND_LNGTH];
    int cmdtype;
    int count = 0;
    while(1)
    {
        printf("$ ");
        fgets(str, MAX_LIMIT, stdin);
        str[strcspn(str, "\n")] = 0;

        if(strlen(str) == 0)
        {
            continue;
        }

        char *origStr = (char *)malloc(sizeof(str) * sizeof(char));
        if(strlen(str) < MAX_LEN)
        {
            strcpy(origStr, str);
        }
        else
        {
            printf("Input Command size is greater than or equal to %d", MAX_LEN);
            return 0;
        }

        command = strtok(str, " ");
        cmdtype = getCommandType(command);
        strcpy(tempCmd, command);
        while(command != NULL)
        {
            command = strtok(NULL, " ");
            count++;
        }
        //printf("command = %s, cmdtype = %d\n", command, cmdtype);
        switch(cmdtype)
        {
            case EXIT_CMD:
                workingOfExit(origStr);
                break;

            case ECHO_CMD:
                workingOfEcho(origStr);
                break;

            case TYPE_CMD:
                workingOfType(origStr, count-1);
                break;

            case PWD_CMD:
                workingOfPwd();
                break;

            case CD_CMD:
                workingOfCD(origStr);
                break;

            default:
                //printf("%s\n", origStr);
                executeCommand(origStr);
                //printf("%s: command not found\n", tempCmd);
        }
        count = 0;
        free(origStr);
    }
    return 0;
}

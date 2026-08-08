#ifndef _SHELL_COMMANDS_H
#define _SHELL_COMMANDS_H

#include "shell.h"
#include <sys/cdefs.h>W
#include <stdio.h>

int hello(char *command)
{
    printf("Hello World\r\n");
}

typedef int (*fptr)(char*);

typedef struct {
    char command_name[COMMAND_NAME_LENGHTH_MAX];
    fptr function;
} command_item_t;


command_item_t command_list[] = {
    {
    .command_name ="hello",
    .function = hello
    },
    {
        .command_name ="END",
        .function = 0x0}
};


#endif
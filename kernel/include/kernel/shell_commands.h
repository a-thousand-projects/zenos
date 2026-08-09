#ifndef _SHELL_COMMANDS_H
#define _SHELL_COMMANDS_H

#include "command.h"
#include "shell.h"
#include "shell_commands.h"
#include <sys/cdefs.h>
#include <stdio.h>
#include <kernel/error_codes.h>

///// Includes for command dunctions
#include <kernel/commands.h>


int hello(char *command)
{
    printf("Hello World\r\n");
    return ERR_OK;
}




command_item_t command_list[] = {
    {
        .command_name ="hello",
        .function = hello
    },
    {
        .command_name = "version",
        .function = cmd_version
    },
    {
        .command_name = "clear",
        .function = cmd_tty_clear
    },
    {
        .command_name ="END",
        .function = 0x0}
};


#endif
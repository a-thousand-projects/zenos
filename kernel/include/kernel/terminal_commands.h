#ifndef _TERMINAL_COMMANDS_H
#define _TERMINAL_COMMANDS_H

#include "terminal.h"
#include <sys/cdefs.h>
command_item_t command_list[] = {
    {
    .command_name ="hello",
    .function = 0x0
    },
    {
        .command_name ="END",
        .function = 0x0}
};


#endif
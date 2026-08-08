#include "kernel/shell.h"
#include "kernel/shell.h"
#include "kernel/cbuffer.h"
#include "kernel/keyboard_driver.h"
#include "kernel/eventqueue.h"
#include "kernel/shell_commands.h"
#include "stdio.h"
#include "string.h"

circular_buffer_t shell_buffer={.init_status= 0};
static char running = 0;

/***********************************************************************************/
/*                          PRIVATE PROTOTYPES                                     */
/***********************************************************************************/
command_item_t *find_command(char * command_string);



void shell_init()
{
    cbuffer_initialize(&shell_buffer);
    // Assign buffer to keyboard input
    keyboard_init(&shell_buffer);
};



/// @brief Shell main loop
void shell_run()
{
    running = 1;
    while (running)
    {
        //Check message Queue
        if (cbuffer_data_available(&shell_buffer))
        {
            // is there a command waiting - ie data with a CR
            if (cbuffer_peek(&shell_buffer) == 0xd)
            {
                char command[100];
                char len = cbuffer_first_to_CR(&shell_buffer,command,100);
                command[len-1] =0x0;
                if (00 == strlen(command)) 
                {
                    printf(command);
                    continue;
                }
                command_item_t *cmd =  find_command(command);
                if (cmd != 0x0)
                {
                    cmd->function(command);
                }
                else
                {
                    printf("Syntax Error");
                }
            }
        }
        // Respond to message Queue
        // Brief delay
        for (int a=0;a<0xffff;a++);
    }
}

/// @brief - loop though commands and fun function
command_item_t *find_command(char * command_string)
{
    if (0 == strlen(command_string))
    {
       return 0x0;  // Got this in because memcmp still passes withh empty string!!!
    }
    for (int i=0;i<COMMAND_LIST_COUNT;i++)
    {
        if (0 == memcmp(command_list[i].command_name,command_string,strlen(command_string)))
        {
            printf("Len:%d\n\r",strlen(command_string));
            return &command_list[i];
        }
    }
    return 0x0;
}

#include <kernel/shell.h>
#include <kernel/shell.h>
#include <kernel/cbuffer.h>
#include <kernel/keyboard_driver.h>
#include <kernel/eventqueue.h>
#include <kernel/command.h>
#include <kernel/error_codes.h>
#include "stdio.h"
#include "string.h"

circular_buffer_t shell_buffer={.init_status= 0};
static char running = 0;

/***********************************************************************************/
/*                          PRIVATE PROTOTYPES                                     */
/***********************************************************************************/




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
            char peek = cbuffer_peek(&shell_buffer);
            if (peek == 0xd)
            {
                char command[100];
                char len = cbuffer_first_to_CR(&shell_buffer,command,100);
                command[len-1] =0x0;
                if (00 == strlen(command)) 
                {
                    printf(command);
                    continue;
                }
                command_item_t *cmd;
                zenos_err_t result = command_item_get(command,&cmd);
                if (ERR_OK == result)
                {
                    cmd->function(command);
                }
                else
                {
                    printf("Syntax Error\n\r");
                }
            }
        }
        // Respond to message Queue
        // Brief delay
        for (int a=0;a<0xffff;a++);
    }
}



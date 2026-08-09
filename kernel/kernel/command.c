#include <kernel/shell_commands.h>
#include <kernel/command.h>
#include <kernel/error_codes.h>
#include <stdio.h>
#include <string.h>


/**
 * @brief Look up a command by name in the global command_list table.
 *
 * Scans command_list for an entry whose command_name matches
 * command_string and, on a match, points command_item at it.
 *
 * @param command_string Command name to search for.
 * @param command_item   Output pointer set to the matching entry on success.
 *                        Left unchanged if no match is found.
 *
 * @return ERR_OK on match, ERR_NOT_FOUND if no matching command was found,
 *         or ERR_FAIL if command_string is empty.
 */
zenos_err_t command_item_get(const char *command_string, command_item_t ** command_item)
{
    int i = 0;
    do
    {
        if (0 == strncmp(command_list[i].command_name,command_string,COMMAND_NAME_LENGHTH_MAX))
        {
            *command_item = &command_list[i];
            return ERR_OK;
        }
        i++;
    } while (command_list[i].function != NULL);

    return ERR_NOT_FOUND;
} 

#ifndef _COMMAND_H_
#define _COMMAND_H_
#include <kernel/error_codes.h>

/***********************************************************************/
/*                     PUBLIC DEFINES                                    */
/***********************************************************************/
#define COMMAND_NAME_LENGHTH_MAX        20
#define COMMAND_LENGTH_MAX              100



/***********************************************************************/
/*                     PUBLIC TYPES                                    */
/***********************************************************************/
typedef int (*fptr)(char*);

typedef struct {
    char command_name[COMMAND_NAME_LENGHTH_MAX];
    fptr function;
} command_item_t;

/***********************************************************************/
/*                     PUBLIC PROTOTYPES                               */
/***********************************************************************/
zenos_err_t command_item_get(const char *command_string, command_item_t ** command_item);

#endif
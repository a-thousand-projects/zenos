#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#define COMMAND_NAME_LENGHTH_MAX        20
#define COMMAND_LENGTH_MAX              100
#define COMMAND_LIST_COUNT              1;


typedef int (*fptr)(char*);

typedef struct {
    char command_name[COMMAND_NAME_LENGHTH_MAX];
    fptr function;
} command_item_t;


void terminal_init();


#endif
#include <kernel/tty.h>
int cmd_tty_clear(char * command)
{
    terminal_clear();
}

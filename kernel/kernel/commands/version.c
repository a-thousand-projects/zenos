#include <kernel/version.h>
#include <stdio.h>
int cmd_version(char * command)
{
    printf("%s\n\r",version_string);
    return 0;
}


#include <kernel/eventqueue.h>
#include <stdio.h>

event_queue_item_t event_items[EVENT_QUEUE_ITEMS_MAX] = {};
static char write_index = 0;
static char read_index = 0;


/// @brief Initialise the system event queue
void event_queue_init()
{
    

}

char event_queue_has_data()
{
    return (write_index - read_index)>0;
} 





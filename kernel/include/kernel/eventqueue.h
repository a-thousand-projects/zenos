#ifndef _EVENT_QUEUE_
#define _EVENT_QUEUE_

#define EVENT_QUEUE_MESSAGE_LEN_MAX 255
#define EVENT_QUEUE_ITEMS_MAX 10
typedef enum
{
    EVENT_QUEUE_MSG_KEYBOARD,
} event_queue_types;

typedef struct event_queue_item
{
    char id;
    event_queue_types event_type;
    char message[255];  // Todo: This should prob be a pointer
    struct event_queue_item *next;
    struct event_queue_item *prev;
} event_queue_item_t;

/*********************/
/* PUBLIC PROTOTYPES */
/*********************/
void event_queue_init();
void event_queue_add(event_queue_item_t item);


#endif
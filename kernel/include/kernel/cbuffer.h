#ifndef _CBUFFER_H_
#define _CBUFFER_H_
#include <stdint.h>

#define BUFFER_SIZE 64

#define CBUFFER_INIT_NO  0
#define CBUFFER_INIT_YES 1

typedef struct
{
    uint8_t buffer[BUFFER_SIZE];
    volatile uint8_t write_index;
    volatile uint8_t read_index;
    char init_status;
} circular_buffer_t;

void cbuffer_initialize(circular_buffer_t *cbuffer);
void cbuffer_put(circular_buffer_t *cbuffer, uint8_t data);
uint8_t cbuffer_get(circular_buffer_t *cbuffer);
uint8_t cbuffer_data_available(circular_buffer_t *cbuffer);
uint8_t cbuffer_is_empty(circular_buffer_t *cbuffer);
uint8_t cbuffer_is_full(circular_buffer_t *cbuffer);
uint8_t cbuffer_peek(circular_buffer_t *cbuffer);
uint8_t cbuffer_find(circular_buffer_t *cbuffer,uint8_t chr);
#endif
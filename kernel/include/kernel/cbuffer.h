#ifndef _CBUFFER_H_
#define CBUFFER_H_
#include <stdint.h>
#define BUFFER_SIZE 64

typedef struct
{
uint8_t buffer[BUFFER_SIZE];
volatile uint8_t write_index;
volatile uint8_t read_index;
}circular_buffer;

void cbuffer_initialize(circular_buffer *cbuffer);
void cbuffer_put(circular_buffer *cbuffer, uint8_t data);
uint8_t cbuffer_get(circular_buffer *cbuffer);
uint8_t cbuffer_data_available(circular_buffer *cbuffer);
uint8_t cbuffer_is_empty(circular_buffer *cbuffer);
uint8_t cbuffer_is_full(circular_buffer *cbuffer);


#endif
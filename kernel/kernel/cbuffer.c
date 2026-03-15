
#include "kernel/cbuffer.h" 

void cbuffer_initialize(circular_buffer *cbuffer)
{
    cbuffer->write_index = 0;
    cbuffer->read_index = 0;
}

// Check if buffer is full
uint8_t cbuffer_is_full(circular_buffer *cbuffer)
{
    return ((cbuffer->write_index + 1) % BUFFER_SIZE) == cbuffer->read_index;
}

// Check if buffer is empty
uint8_t cbuffer_is_empty(circular_buffer *cbuffer)
{
    return cbuffer->write_index == cbuffer->read_index;
}

// Put data
void cbuffer_put(circular_buffer *cbuffer, uint8_t data)
{
    if (!cbuffer_is_full(cbuffer))
    {
        cbuffer->buffer[cbuffer->write_index] = data;
        cbuffer->write_index = (cbuffer->write_index + 1) % BUFFER_SIZE;
    }
}

// Get data
uint8_t cbuffer_get(circular_buffer *cbuffer)
{
    if (cbuffer_is_empty(cbuffer))
    {
        return 0;  // or handle error
    }

    uint8_t data = cbuffer->buffer[cbuffer->read_index];
    cbuffer->read_index = (cbuffer->read_index + 1) % BUFFER_SIZE;
    return data;
}

// Data available
uint8_t cbuffer_data_available(circular_buffer *cbuffer)
{
    return (cbuffer->write_index + BUFFER_SIZE - cbuffer->read_index) % BUFFER_SIZE;
}
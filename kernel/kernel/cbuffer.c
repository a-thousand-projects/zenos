
#include "kernel/cbuffer.h" 

void cbuffer_initialize(circular_buffer_t *cbuffer)
{
    if (cbuffer->init_status == CBUFFER_INIT_YES)
    {
        cbuffer->write_index = 0;
        cbuffer->read_index = 0;
    }
}

// Check if buffer is full
uint8_t cbuffer_is_full(circular_buffer_t *cbuffer)
{
    return ((cbuffer->write_index + 1) % BUFFER_SIZE) == cbuffer->read_index;
}

// Check if buffer is empty
uint8_t cbuffer_is_empty(circular_buffer_t *cbuffer)
{
    return cbuffer->write_index == cbuffer->read_index;
}

// Put data
void cbuffer_put(circular_buffer_t *cbuffer, uint8_t data)
{
    if (!cbuffer_is_full(cbuffer))
    {
        cbuffer->buffer[cbuffer->write_index] = data;
        cbuffer->write_index = (cbuffer->write_index + 1) % BUFFER_SIZE;
    }
}

// Get data
uint8_t cbuffer_get(circular_buffer_t *cbuffer)
{
    if (cbuffer_is_empty(cbuffer))
    {
        return 0;  // or handle error
    }

    uint8_t data = cbuffer->buffer[cbuffer->read_index];
    cbuffer->read_index = (cbuffer->read_index + 1) % BUFFER_SIZE;
    return data;
}

uint8_t cbuffer_find(circular_buffer_t *cbuffer,uint8_t chr)
{
    uint8_t ptr_read = cbuffer->read_index;
    
    while (ptr_read != cbuffer->write_index)
    {
        uint8_t data = cbuffer->buffer[ptr_read];
        if (data == chr)
            return ptr_read;
        ptr_read = (ptr_read+1) % BUFFER_SIZE;
    }
    return 0;
     
}
// peek last character
uint8_t cbuffer_peek(circular_buffer_t *cbuffer)
{
    if (cbuffer_is_empty(cbuffer))
    {
        return 0;  // or handle error
    }

    uint8_t data = cbuffer->buffer[cbuffer->read_index];
    
    return data;
}

uint8_t cbuffer_first_to_CR(circular_buffer_t *cbuffer,char *data,uint8_t len)
{
    if (!cbuffer_data_available(cbuffer))
    {
        return 0;
    }
    uint8_t chr = 0x0;
    while (chr != 0x0D)
    {
        chr = cbuffer_get(cbuffer);
        *data = chr;
        data++;
    }
    return 0;
}

// Data available
uint8_t cbuffer_data_available(circular_buffer_t *cbuffer)
{
    return (cbuffer->write_index + BUFFER_SIZE - cbuffer->read_index) % BUFFER_SIZE;
}


//* Build a listerer for the keyboard - reg console as only listener. 
//** build a 'pass back string up to CR'
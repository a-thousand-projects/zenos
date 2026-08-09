
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
void cbuffer_put(circular_buffer_t *cbuffer, uint16_t data)
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

unsigned char cbuffer_find(circular_buffer_t *cbuffer,const uint16_t chr)
{
    uint8_t read_index = cbuffer->read_index;
    unsigned char data = 0x0;
    while (read_index != cbuffer->write_index && chr != data)
    {
        data = cbuffer->buffer[read_index];
        read_index = (read_index+1) % BUFFER_SIZE;
    }
    
    return chr == data;
     
}
// peek last character
uint8_t cbuffer_peek(circular_buffer_t *cbuffer)
{
    if (cbuffer_is_empty(cbuffer))
    {
        return 0x0;  // or handle error
    }
    int index = (cbuffer->write_index -1)  % BUFFER_SIZE;
    uint8_t data = cbuffer->buffer[index];
    
    return data;
}

uint8_t cbuffer_first_to_CR(circular_buffer_t *cbuffer,char *data,uint8_t len)
{
    char count = 0;
    if (!cbuffer_data_available(cbuffer))
    {
        return 0;
    }
    uint8_t chr = 0x0;
    
    do
    {
        chr = cbuffer_get(cbuffer);
        *data = chr;
        data++;
        count++;
    }
    while (chr != 0x0D && count < len-1); // len-1 to allow for mull termination
    *data = 0x0;

    return count;

}

// Data available
uint8_t cbuffer_data_available(circular_buffer_t *cbuffer)
{
    return (cbuffer->write_index + BUFFER_SIZE - cbuffer->read_index) % BUFFER_SIZE;
}


//* Build a listerer for the keyboard - reg console as only listener. 
//** build a 'pass back string up to CR'
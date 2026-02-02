#include <stdint.h>
#include <kernel/cbuffer.h>






static char buffer[CBUFFER_MAX_SIZE] = {0};





void cbuffer_initialise(cbuffer_t *cbuffer, char *buffer)
{
	cbuffer->buffer = buffer;
    cbuffer->write = buffer;
	cbuffer->read = buffer;
}

uint16_t cbuffer_length(cbuffer_t *cbuffer)
{
	return ((cbuffer->write - cbuffer->read)& (cbuffer->size-1));
}

e_cbuffer_error cbuffer_push(cbuffer_t * cbuffer, const char c)
{
	if (cbuffer_length(cbuffer) == (cbuffer->size-1))
	{
		return BUFFER_FULL;
	}
	else
	{
		cbuffer->buffer[cbuffer->write] = c;
		cbuffer->write = (cbuffer->write +1) & (cbuffer->size-1);
	}

}

void cbuffer_peek(uint16_t ahead,char* c)
{
	return 
}

char cbuffer_isFull ()
{
	return tail == head;
}


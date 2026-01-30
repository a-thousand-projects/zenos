#include <stdint.h>
#include <kernel/cbuffer.h>

static char buffer[CBUFFER_MAX_SIZE] = {0};
static char * buffer_ptr = buffer;
static int head;
static int tail;




void cbuffer_initialise()
{
    buffer_ptr = buffer;
    head = 0;
    tail = 0;
}

void cbuffer_add(const char c)

{
	buffer[tail] = c;
	tail = (tail + 1) % CBUFFER_MAX_SIZE;

	if (tail == head)
		head = (head + 1) % CBUFFER_MAX_SIZE;
}


#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

typedef struct QueueI32
{

} QueueI32;

void QueueI32_Push(QueueI32* queue, int32_t value);
int32_t QueueI32_Pop(QueueI32* queue);
int32_t QueueI32_Peek(QueueI32* queue);

#endif

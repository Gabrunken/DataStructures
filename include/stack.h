#ifndef STACK_H_
#define STACK_H_
#include <stdint.h>

//A void* is used to mimic polymorphism, altho the caller must ensure the passed value is a Stack
void Stack_Free(void* stack);
void Stack_ShrinkToFit(void* stack);

/* INT STACK */
typedef struct StackI32
{
	int32_t* start;
	size_t offset;
	size_t capacity; //In bytes
} StackI32;

StackI32 StackI32_Make(size_t elements);
//Pre-allocate a number of elements
void StackI32_Reserve(StackI32* stack, size_t elements);
//Push an element onto the stack
void StackI32_Push(StackI32* stack, int32_t value);
//Get the last element removing it
int32_t StackI32_Pop(StackI32* stack);
//Get the last element without removal
int32_t StackI32_Peek(const StackI32* stack);

#endif

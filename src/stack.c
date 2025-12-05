#include <stack.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define REALLOC_FACTOR 2
#define MINIMUM_ALLOC_SIZE 100 //IN ELEMENTS

/* GENERIC FUNCTIONS */
typedef StackI32 Stack; //Simulate a generic Stack using a Stack32I as its body

void Stack_Free(void* stack)
{
	assert(stack);

	//Every first Stack member must be the buffer pointer
	//Calling free on a NULL ptr is safe, so no checks
	free(*(void**)stack);
	*(void**)stack = NULL;
}

void Stack_ShrinkToFit(void *stack)
{
	assert(stack);

	Stack* s = (Stack*)stack;

	//If the offset is 0, free the buffer and set it to NULL
	if (!s->offset)
	{
		free(s->start);
		s->start = NULL;
		s->capacity = 0;
		return;
	}

	assert(s->start = realloc(s->start, s->offset));
	s->capacity = s->offset;
}

Stack Stack_Make(size_t elementSize, size_t elements)
{
	assert(elements && elementSize); //They both cannot be 0

	void* buf = malloc(elementSize * elements);
	assert(buf);

	return (Stack)
	{
		.start = buf,
		.offset = 0,
		.capacity = elements * elementSize,
	};
}

void Stack_Reserve(Stack *stack, size_t bytes)
{
	assert(stack);
	//The stack is empty, already freed, let's do malloc directly
	if (!stack->capacity)
		assert(stack->start = malloc(bytes));
	else
		assert(stack->start = realloc(stack->start, bytes));

	stack->capacity = bytes;
}

/* WRAPPER TO GENERIC FUNCTIONS */
StackI32 StackI32_Make(size_t elements) {return (StackI32)Stack_Make(sizeof(int32_t), elements);}
void StackI32_Reserve(StackI32 *stack, size_t elements) {Stack_Reserve(stack, elements * sizeof(int32_t));}

/* SPECIALIZED FUNCTIONS */
void StackI32_Push(StackI32* stack, int32_t value)
{
	assert(stack);
	assert(stack->start); //Cannot push on a NULL buffer

	//Not enough memory allocated
	if (stack->capacity < stack->offset + sizeof(int32_t))
	{
		//The stack has size 0, so the buffer pointer must also be NULL, allocate a minimum size
		if (!stack->capacity)
		{
			stack->start = (int32_t*)malloc(MINIMUM_ALLOC_SIZE * sizeof(int32_t));
			assert(stack->start);
			stack->capacity = MINIMUM_ALLOC_SIZE * sizeof(int32_t);
		}

		//Else allocate the current capacity * REALLOC_FACTOR
		else
		{
			stack->start = realloc(stack->start, stack->capacity * REALLOC_FACTOR);
			assert(stack->start);
			stack->capacity *= REALLOC_FACTOR;
		}
	}

	//Cast it to char* so that pointer arithmetic adds 1 and not sizeof(type)
	*(int32_t*)((char*)stack->start + stack->offset) = value;
	stack->offset += sizeof(int32_t);
}

int32_t StackI32_Pop(StackI32* stack)
{
	assert(stack);
	assert(stack->start); //If the buffer is NULL, there is no stack
	assert(stack->offset); //If the stack has offset 0, there is nothing to pop

	stack->offset -= sizeof(int32_t);
	int32_t val = *(int32_t*)((char*)stack->start + stack->offset);
	return val;
}

int32_t StackI32_Peek(const StackI32* stack)
{
	assert(stack);
	assert(stack->start); //If the buffer is NULL, there is no stack
	assert(stack->offset); //If the stack has offset 0, there is nothing to peek
	return *(int32_t*)((char*)stack->start + stack->offset - sizeof(int32_t));
}

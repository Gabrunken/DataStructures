#include "stack.h"
#include <data_structures.h>
#include <stdio.h>

int main()
{
	StackI32 stack = StackI32_Make(1);
	StackI32_Reserve(&stack, 100);

	printf("%zu\n", stack.capacity); //Should print 100 * sizeof(int32_t) = 400
	Stack_ShrinkToFit(&stack);
	printf("%zu\n", stack.capacity); //Should print 0

	Stack_Free(&stack);
}

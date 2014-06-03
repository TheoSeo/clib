/* dynarray.h dyanamic array */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _DYN_ARRAY
{
	int *array;
	size_t used;
	size_t size;
} DYN_ARRAY;

#define ELEMENT_TYPE int
#define INCREMENT_SIZE 10

DYN_ARRAY* da_initialize(int init_size)
{
	DYN_ARRAY *pa;

	pa = (DYN_ARRAY *) malloc(sizeof(DYN_ARRAY));

	pa->array = (ELEMENT_TYPE *) malloc(init_size * sizeof(ELEMENT_TYPE));
	memset(pa->array, 0, init_size * sizeof(ELEMENT_TYPE));
	pa->used = 0;
	pa->size = init_size;

	return pa;
}

void da_deinitialize(DYN_ARRAY **ppa)
{
	if (ppa && *ppa)
	{
		if ((*ppa)->array)
			free((*ppa)->array);

		free(*ppa);
		*ppa = NULL;
	}
}

void da_insert(DYN_ARRAY *pa, int idx, ELEMENT_TYPE data)
{
	if (pa == NULL || pa->array == NULL) return;

	if (pa->used == pa->size)
	{
		pa->size += INCREMENT_SIZE;
		pa->array = (ELEMENT_TYPE *) realloc(pa->array,
				pa->size * sizeof(ELEMENT_TYPE));
	}

	if (pa->used - idx > 0)
	{
		memmove(pa->array + idx + 1, pa->array + idx,
				(pa->used - idx) * sizeof(ELEMENT_TYPE));
	}

	pa->array[idx] = data;
	pa->used++;
}

void da_delete(DYN_ARRAY *pa, int idx)
{
	if (pa == NULL || pa->array == NULL || pa->size <= idx) return;

	memmove(pa->array + idx, pa->array + idx + 1,
			(pa->used - idx - 1) * sizeof(ELEMENT_TYPE));
	pa->used--;
}

void da_print_element(DYN_ARRAY *pa)
{
	int idx;

	for (idx = 0; idx < pa->size; idx++)
	{
		printf("Dynarray[%d] : %d\n", idx, pa->array[idx]);
	}
}


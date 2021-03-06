/*******************************************************************************
 * prioq.c
 * priority queue 
 *
 * @author		Theo Seo
 * @email		makeitafridaynight@gmail.com
 ******************************************************************************/

#include "prioq.h"

ARRAY_HEAP* prioq_create(int init_size)
{
	ARRAY_HEAP *p_prioq = NULL;

	p_prioq = (ARRAY_HEAP *) malloc(sizeof(ARRAY_HEAP));

	p_prioq->p_elements = (HEAP_NODE *) malloc(sizeof(HEAP_NODE) * (init_size + 1));

	memset((void *) p_prioq->p_elements, 0, sizeof(HEAP_NODE) * (init_size + 1));
	p_prioq->p_elements[0].key = -INT_MAX;

	p_prioq->heap_size = init_size;
	p_prioq->last= 0;

	return p_prioq;
}

void prioq_destroy(ARRAY_HEAP **pp_prioq)
{
	if (pp_prioq && *pp_prioq)
	{
		if ((*pp_prioq)->p_elements)
			free((*pp_prioq)->p_elements);

		free(*pp_prioq);
		*pp_prioq = NULL;
	}
}

void prioq_push(ARRAY_HEAP *p_prioq, HEAP_NODE element)
{
	int i;

	if (p_prioq == NULL) return;

	if (p_prioq->last == p_prioq->heap_size) return;

	i = ++p_prioq->last;

	while ((i != 1) && (element.key > p_prioq->p_elements[i / 2].key))
	{
		p_prioq->p_elements[i] = p_prioq->p_elements[i / 2];
		i /= 2;
	}

	p_prioq->p_elements[i] = element;
}

void prioq_pop(ARRAY_HEAP *p_prioq, HEAP_NODE *p_element)
{
	int cur, i;

	if (p_prioq == NULL || p_prioq->last == 0 || p_element == NULL)
		return;

	*p_element = p_prioq->p_elements[1];

	cur = 1, i = 2;

	while (i <= p_prioq->last)
	{
		if (i != p_prioq->last
				&& p_prioq->p_elements[i].key < p_prioq->p_elements[i + 1].key)
			i++;

		if (p_prioq->p_elements[p_prioq->last].key > p_prioq->p_elements[i].key)
			break;

		p_prioq->p_elements[cur] = p_prioq->p_elements[i];
		cur = i;
		i *= 2;
	}

	p_prioq->p_elements[cur] = p_prioq->p_elements[p_prioq->last--];
}

void prioq_peek(ARRAY_HEAP *p_prioq, HEAP_NODE *p_element)
{
	int cur, i;

	if (p_prioq == NULL || p_prioq->last == 0 || p_element == NULL)
		return;

	*p_element = p_prioq->p_elements[1];
}

/* end of file */

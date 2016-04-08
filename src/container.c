#include "container.h"
#include <stdlib.h>

/*
 * A basic container must track a reference count, hold a value, and know
 * how to free that value.
 */
struct container_base {
	void * value;
	void (*free_func)(void *);
	long refcount;
};

container * container_new(void * const value, void (*free)(void *))
{
	container * retval = malloc(sizeof(*retval));

	if (retval != NULL) {
		retval->refcount = 1;
		retval->value = value;
		retval->free_func = free;
	}

	return retval;
}

void * container_get_value(const container * const cont)
{
	if (cont == NULL) {
		return NULL;
	}

	return cont->value;
}

void container_release(container * const cont)
{
	if (cont == NULL) {
		return;
	}

	cont->refcount--;
	if (cont->refcount <= 0) {
		if (cont->free_func != NULL) {
			cont->free_func(cont->value); // Free the data pointed to.
		}
		free(cont); // Free the container itself.
	}
}

container * container_refcopy(container * const cont)
{
	if (cont == NULL) {
		return NULL;
	}

	cont->refcount++;
	return cont;
}

void container_no_free(void * unused)
{
	(void)unused;
	return;
}

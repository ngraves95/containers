/*
 * File: container.h
 * Date: 4/7/16
 * Author: Nick Graves
 */
#ifndef CONTAINER_H_
#define CONTAINER_H_

/*
 * Containers are generic objects which wrap a pointer type. They can be
 * thought of as shared pointers. A container tracks a reference count, and
 * when that reference count reaches 0, both the container and the data which
 * it points to are deleted.
 *
 * Containers are nearly drop-in replacements wherever a simple pointer is
 * needed. To use a container in place of a pointer, simply cast like the
 * following:
 *
 * int my_func(char * c);
 * container * c = container_new("Hello world", NULL);
 * my_func( *(char **) c);
 *
 * It is worth noting that the value in the container can be accessed without
 * using container_get_value.  The pointer to the value is the first item, in
 * the struct. Thus, client code can do the following:
 *
 * int a = 10;
 * container * c = container_new(&a, my_free_func);
 *
 * a = 12;
 * int b = **(int **) c; // b = 12;
 *
 * The following is also valid:
 *
 * int a = 10;
 * container * c = container_new((void*)a, my_free_func);
 *
 * a = 12;
 * int b = *(int *) c; // b = 10;
 *
 */

typedef struct container_base container;

/*
 * Allocates and initializes a container for init_value.
 * free is the function to free init_value when the reference counter reaches
 * 0.
 *
 * If free is NULL, the data will not be freed when the reference counter
 * reaches 0, but the container itself will be.
 */
container * container_new(void * const init_value, void (*free)(void *));

/*
 * Releases (frees) a container. When a container is no longer in use, the
 * container and its data are actually freed.
 */
void container_release(container * const container);

/*
 * Returns the pointer to the value that this container wraps.
 * A return value of NULL indicates an error, as NULL should never be
 * wrapped in a container.
 */
void * container_get_value(const container * const cont);

/*
 * Returns the reference to the container and increments the reference count
 * of the container.
 */
container * container_refcopy(container * const c);

/*
 * Convenience free function that won't actually free anything.
 */
void container_no_free(void * arg);

#endif

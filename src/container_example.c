#include <stdio.h>
#include <stdlib.h>

#include "container.h"

int main(void)
{

	int * mallocd_int = malloc(sizeof(*mallocd_int));
	*mallocd_int = 42;
	int a = 10;

	container * literal_val = container_new((void*)a, NULL);
	container * typical = container_new(mallocd_int, free);
	container * str_cont = container_new("Hello world", container_no_free);
	container * copy = container_refcopy(str_cont);

	printf("%d\n", *(int *) literal_val);
	printf("%d\n", *(int *) container_get_value(typical));
	printf("%s\n", *(char **) str_cont);

	container_release(str_cont);
	printf("Released str_cont...\n");
	printf("%s\n", *(char **) copy);
	printf("But the copy remains!\n");

	container_release(literal_val);
	container_release(str_cont);
	container_release(typical);
	return 0;
}

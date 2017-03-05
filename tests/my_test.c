#include "myalloc.h"
// #include <stdlib.h>
// #include <stdio.h>

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 10)
	{
		if ((addr = malloc(1024)) == NULL)
			write(2, "malloc return NULL\n", 19);
		addr[0] = 42;
		i++;
	}
	if ((addr = realloc(addr, 120)) == NULL)
		write(2, "realloc return NULL\n", 20);
	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		i++;
	}
	addr = realloc(addr, 10020);
	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(28);
		addr[0] = 42;
		realloc(addr, 500);
		i++;
	}
	addr = realloc(addr, 120);

	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(10028);
		addr[0] = 42;
		free(addr);
		i++;
	}
	free(addr);
	show_alloc_map();
	show_alloc_mem();
	free_all();
	show_alloc_map();
	show_alloc_mem();
	return (0);
}

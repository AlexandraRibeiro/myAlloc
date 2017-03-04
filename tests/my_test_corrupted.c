#include "myalloc.h"
// #include <stdlib.h>
// #include <stdio.h>

int		main()
{
	char *addr;
	char *addr2;
	int i = 0;

	while (i < 105)
	{
		addr = (char *)malloc(128);
		addr[0] = 42;
		if (i == 100)
			addr2 = addr;
		i++;
	}
	while (i < 105)
	{
		addr = (char *)malloc(128);
		addr[0] = 42;
		i++;
	}
	i = 0;
	while (i < 10000)
	{
		addr2[i] = 42;
		i++;
	}
	// free(addr);
	// realloc(addr, 1028);
	// show_alloc_map();
	// show_alloc_mem();
	free_all();

	return (0);
}

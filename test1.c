#include "memory.h"
// #include <stdlib.h>

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(24);
		addr[0] = 42;
		// free(addr);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		// free(addr);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(28);
		addr[0] = 42;
		// free(addr);
		i++;
	}
	free(addr);
	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(10028);
		addr[0] = 42;
		// free(addr);
		i++;
	}

	show_alloc_map();
	show_alloc_mem();
	return (0);
}

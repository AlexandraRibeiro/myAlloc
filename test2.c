#include "memory.h"
// #include <stdlib.h>

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i< 1024)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	show_alloc_map();
	free_all();
	show_alloc_map();
	return (0);
}

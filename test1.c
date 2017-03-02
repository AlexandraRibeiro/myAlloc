#include "memory.h"
// #include <stdlib.h>

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(10024);
		addr[0] = 42;
		i++;
	}

	show_alloc_map();
	show_alloc_mem();
	return (0);
}

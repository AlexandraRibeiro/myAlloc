#include "myalloc.h"
// #include <stdlib.h>

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 105)
	{
		addr = (char *)malloc(128);
		addr[0] = 42;
		i++;
	}
	i = 0;
	while (i < 105)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		i++;
	}
	i = 0;
	while (i < 105)
	{
		addr = (char *)malloc(10024);
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
	show_alloc_map();
	return (0);
}

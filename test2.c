#include "memory.h"
#include <stdlib.h>

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i< 1024)
	{
		addr = (char *)malloc(10024);
		addr[0] = 42;
// printf("\nVERIF ADDR de addr = %p", addr);
		free(addr);
		i++;
	}
	return (0);
}

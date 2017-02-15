#include "memory.h"

int		main()
{
	int i;
	char *addr;

	i = 0;
	while (i< 1024)
	{
		addr = (char *)my_malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

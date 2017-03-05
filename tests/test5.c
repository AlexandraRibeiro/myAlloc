#include "myalloc.h"

int		main()
{
	char *addr;

	addr = malloc(11);
	addr[0] = 42;
	addr = malloc(1024);
	addr[0] = 42;
	addr = malloc(1024 * 32);
	addr[0] = 42;
	addr = malloc(1024 * 1024);
	addr[0] = 42;
	addr = malloc(1024 * 1024 * 16);
	addr[0] = 42;
	addr = malloc(1024 * 1024 * 128);
	addr[0] = 42;
	show_alloc_mem();
	return (0);
}

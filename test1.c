#include "memory.h"
// #include <stdlib.h>

int		main()
{
	// int i;
	char *addr;
	//
	// i = 0;
	// while (i < 10)
	// {
		addr = (char *)malloc(92233720368547758077);
		addr[0] = 42;
		// i++;
	// }
	// addr = realloc(addr, 120);
	// i = 0;
	// while (i < 10)
	// {
	// 	addr = (char *)malloc(1024);
	// 	addr[0] = 42;
	// 	i++;
	// }
	// addr = realloc(addr, 10020);
	// i = 0;
	// while (i < 10)
	// {
	// 	addr = (char *)malloc(28);
	// 	addr[0] = 42;
	// 	// realloc(addr, 500);
	// 	i++;
	// }
	// addr = realloc(addr, 120);
	//
	// i = 0;
	// while (i < 10)
	// {
	// 	addr = (char *)malloc(10028);
	// 	addr[0] = 42;
	// 	// free(addr);
	// 	i++;
	// }
	// free(addr);
	// show_alloc_map();
	// show_alloc_mem();
	// free_all();
	// show_alloc_map();
	// show_alloc_mem();
	return (0);
}

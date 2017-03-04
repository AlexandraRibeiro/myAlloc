#include "myalloc.h"
// #include <stdlib.h>
// #include <stdio.h>

int		main()
{
	// int i;
	char *addr;
	// size_t size = (size_t)-1;
	// printf("size_t max == %zu\n", size);

	//
	//
	// i = 0;
	// while (i < 10)
	// {			     18446744073709551615
		addr = malloc(922337203685477580);
		// addr[0] = 42;
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
	show_alloc_mem();
	return (0);
}

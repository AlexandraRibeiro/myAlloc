/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/13 15:37:50 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		main(int ac, char *av[])
{
	int i;
	// int nb;
	// size_t nb2;
	char c;
	char *str;
	char *str2;
	// struct rlimit limits;

// 	if (ac < 3)
// 		return (0);
// 	i = 0;
// 	c = av[1][0];
// 	nb = atoi(av[2]);
// 	nb2 = (size_t)nb;
// printf ("nb2 = %d", nb);
// printf ("sizeof char = %lu\n", sizeof(char));
// 	str = mmap(0, 8200, MMAP_PROT, MMAP_FLAGS, -1, 0);
// 	// printf("getpagesize = %i\n", getpagesize());
// 	str2 = str;
// 	while (i < nb)
// 	{
// 		*str = c;
// 		str++;
// 		i++;
// 	}
// 	*str = '\0';
// 	printf("%s", str2);
	// if (munmap(str, nb + 1) == 0)
	// 	printf("\n=> SUCCESS munmap\n");
	// else
	// 	printf("\n=> ERROR munmap\n");
	// //printf("Declenche normalement un SEGFAULT: %s", str);
	//
	// /* -------------------> testing getrlimit */
	// if (getrlimit (RLIMIT_NPROC, &limits) == -1)
	// {
	// 	perror ("The call to getrlimit() failed.");
	// 	return EXIT_FAILURE;
	// }
	// else
	// {
	// 	printf ("The current maximum number of processes is %d.\n", (int) limits.rlim_cur);
	// 	printf("The hard limit on the number of processes is %d.\n", (int) limits.rlim_max);
	// }

	i = 0;
	str = (char *)my_malloc(sizeof(char) * 100);
	str2 = (char *)my_malloc(sizeof(char) * 100);
write(1, "\n-> retour main\n", 16);
printf("(debug main) ADDR 1er ptr str = %p\n", str);
printf("(debug main) ADDR 2eme ptr str2 = %p\n", str2);
	while (i < 13143)
	{
		str[i] = 'A';
		i++;
	}
	str[i] = '\0';
	printf("%s" , str);

	i = 0;
	while (i < (13143 - TINY))
	{
		str2[i] = 'B';
		i++;
	}
	str2[i] = '\0';
	printf("%s" , str2);
//
// 	str2[0] = '\0';
// 	str2[1] = 'd';
// 	str2[2] = '\0';
// 	printf("%s" , str2);
	return (0);
}

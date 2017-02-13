/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/13 18:08:45 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		main(int ac, char *av[])
{
	int i;
	// int nb;
	// size_t nb2;
	char *tiny = NULL;
	char *tiny2 = NULL;
	char *tiny3 = NULL;

	char *small = NULL;
	char *small2 = NULL;
	char *small3 = NULL;
	// tinyuct rlimit limits;

// 	if (ac < 3)
// 		return (0);
// 	i = 0;
// 	c = av[1][0];
// 	nb = atoi(av[2]);
// 	nb2 = (size_t)nb;
// printf ("nb2 = %d", nb);
// printf ("sizeof char = %lu\n", sizeof(char));
// 	tiny = mmap(0, 8200, MMAP_PROT, MMAP_FLAGS, -1, 0);
// 	// printf("getpagesize = %i\n", getpagesize());
// 	tiny2 = tiny;
// 	while (i < nb)
// 	{
// 		*tiny = c;
// 		tiny++;
// 		i++;
// 	}
// 	*tiny = '\0';
// 	printf("%s", tiny2);
	// if (munmap(tiny, nb + 1) == 0)
	// 	printf("\n=> SUCCESS munmap\n");
	// else
	// 	printf("\n=> ERROR munmap\n");
	// //printf("Declenche normalement un SEGFAULT: %s", tiny);
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

/*******************************************************************************
**								TEST TINY
*******************************************************************************/
	i = 0;
	tiny = (char *)my_malloc(sizeof(char) * 100);
	tiny2 = (char *)my_malloc(sizeof(char) * 80);
	tiny3 = (char *)my_malloc(sizeof(char) * 40);
write(1, "\n-> retour main\n", 16);
printf("(debug main) ADDR 1er ptr tiny = %p\n", tiny);
printf("(debug main) ADDR 2eme ptr tiny2 = %p, decalage avec tiny = %ld\n", tiny2, tiny2 - tiny);
printf("(debug main) ADDR 3eme ptr tiny3 = %p, decalage avec tiny2 = %ld\n", tiny3, tiny3 - tiny2);
	while (i < 126)
	{
		tiny[i] = 'A';
		i++;
	}
	tiny[i] = '\n';
	tiny[++i] = '\0';


	i = 0;
	while (i < 126)
	{
		tiny2[i] = 'B';
		i++;
	}
	tiny2[i] = '\n';
	tiny2[++i] = '\0';


	i = 0;
	while (i < 126)
	{
		tiny3[i] = 'C';
		i++;
	}
	tiny3[i] = '\n';
	tiny3[++i] = '\0';


	ft_putstr_fd(tiny, 1);
	ft_putstr_fd(tiny2, 1);
	ft_putstr_fd(tiny3, 1);

	printf("(debug main) ADDR 1er ptr tiny = %p\n", tiny);
	printf("(debug main) ADDR 2eme ptr tiny2 = %p, decalage avec tiny = %ld\n", tiny2, tiny2 - tiny);
	printf("(debug main) ADDR 3eme ptr tiny3 = %p, decalage avec tiny2 = %ld\n", tiny3, tiny3 - tiny2);

	i = 0;
	while (i < 126)
	{
		tiny3[i] = 'D';
		i++;
	}
	tiny3[i] = '\n';
	tiny3[++i] = '\0';

	i = 0;
	while (i < 126)
	{
		tiny2[i] = 'E';
		i++;
	}
	tiny2[i] = '\n';
	tiny2[++i] = '\0';

	i = 0;
	while (i < 126)
	{
		tiny[i] = 'F';
		i++;
	}
	tiny[i] = '\n';
	tiny[++i] = '\0';

	ft_putstr_fd(tiny, 1);
	ft_putstr_fd(tiny2, 1);
	ft_putstr_fd(tiny3, 1);


	/*******************************************************************************
	**								TEST SMALL
	*******************************************************************************/
	i = 0;
	small = (char *)my_malloc(sizeof(char) * 101);
	small2 = (char *)my_malloc(sizeof(char) * 200);
	small3 = (char *)my_malloc(sizeof(char) * 500);
write(1, "\n-> retour main\n", 16);
printf("(debug main) ADDR 1er ptr small = %p\n", small);
printf("(debug main) ADDR 2eme ptr small2 = %p, decalage avec small = %ld\n", small2, small2 - small);
printf("(debug main) ADDR 3eme ptr small3 = %p, decalage avec small2 = %ld\n", small3, small3 - small2);
	while (i < 254)
	{
		small[i] = 'A';
		i++;
	}
	small[i] = '\n';
	small[++i] = '\0';


	i = 0;
	while (i < 254)
	{
		small2[i] = 'B';
		i++;
	}
	small2[i] = '\n';
	small2[++i] = '\0';


	i = 0;
	while (i < 254)
	{
		small3[i] = 'C';
		i++;
	}
	small3[i] = '\n';
	small3[++i] = '\0';


	ft_putstr_fd(small, 1);
	ft_putstr_fd(small2, 1);
	ft_putstr_fd(small3, 1);

	printf("(debug main) ADDR 1er ptr small = %p\n", small);
	printf("(debug main) ADDR 2eme ptr small2 = %p, decalage avec small = %ld\n", small2, small2 - small);
	printf("(debug main) ADDR 3eme ptr small3 = %p, decalage avec small2 = %ld\n", small3, small3 - small2);

	i = 0;
	while (i < 254)
	{
		small3[i] = 'D';
		i++;
	}
	small3[i] = '\n';
	small3[++i] = '\0';

	i = 0;
	while (i < 254)
	{
		small2[i] = 'E';
		i++;
	}
	small2[i] = '\n';
	small2[++i] = '\0';

	i = 0;
	while (i < 254)
	{
		small[i] = 'F';
		i++;
	}
	small[i] = '\n';
	small[++i] = '\0';

	ft_putstr_fd(small, 1);
	ft_putstr_fd(small2, 1);
	ft_putstr_fd(small3, 1);


	return (0);
}

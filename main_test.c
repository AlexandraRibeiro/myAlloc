/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/08 13:47:47 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		main(int ac, char *av[])
{
	int i;
	int nb;
	char c;
	char *str;
	struct rlimit limits;

	if (ac < 3)
		return (0);
	i = 0;
	c = av[1][0];
	nb = atoi(av[2]);
	str = (char *)mmap(0, nb + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	printf("getpagesize = %i\n", getpagesize());
	while (i < nb)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	printf("%s", str);
	if (munmap(str, nb + 1) == 0)
		printf("\n=> SUCCESS munmap\n");
	else
		printf("\n=> ERROR munmap\n");
	//printf("Declenche normalement un SEGFAULT: %s", str);

	/* -------------------> testing getrlimit */
	if (getrlimit (RLIMIT_NPROC, &limits) == -1)
	{
		perror ("The call to getrlimit() failed.");
		return EXIT_FAILURE;
	}
	else
	{
		printf ("The current maximum number of processes is %d.\n", (int) limits.rlim_cur);
		printf("The hard limit on the number of processes is %d.\n", (int) limits.rlim_max);
	}
	return (0);
}

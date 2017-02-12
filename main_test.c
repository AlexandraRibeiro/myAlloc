/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/12 19:52:21 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		main(int ac, char *av[])
{
	int i;
	int nb;
	char c;
	char *str;
	char *str2;
	struct rlimit limits;

	// if (ac < 3)
	// 	return (0);
	// i = 0;
	// c = av[1][0];
	// nb = atoi(av[2]);
	// str = (char *)mmap(0, nb + 1, MMAP_PROT, MMAP_FLAGS, -1, 0);
	// printf("getpagesize = %i\n", getpagesize());
	// while (i < nb)
	// {
	// 	str[i] = c;
	// 	i++;
	// }
	// str[i] = '\0';
	// printf("%s", str);
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

	str = (char *)my_malloc(sizeof(char) * 100);
	// str2 = (char *)my_malloc(sizeof(char) * 100);
write(1, "ici", 3);

	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'a';
	str[3] = 'b';
	str[4] = 'a';
	str[5] = 'b';
	str[6] = 'a';
	str[7] = 'b';
	str[8] = 'a';
	str[9] = 'b';
	str[10] = '\0';
	printf("%s" , str);

	// str2[0] = '\0';
	// str2[1] = 'd';
	// str2[2] = '\0';
	// printf("%s" , str2);
	return (0);
}

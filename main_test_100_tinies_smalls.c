/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_100_tinies_smalls.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/15 15:19:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static void create_100_tinies(char *t)
{
	int i = 0;
	t = (char *)my_malloc(100);
	printf("(debug main) ADDR ptr TINY = %p\n", t);
		write(1, "boucle\n", 7);
	while (i < 95)
	{
		t[i] = 'T';
		i++;
	}
	t[i] = '\n';
	t[++i] = '\0';

	printf("%s",t);
}

static void create_100_smalls(char *s)
{
	int i = 0;
	s = (char *)my_malloc(400);
	printf("(debug main) ADDR ptr SMALL = %p\n", s);

	while (i < 254)
	{
		s[i] = 'S';
		i++;
	}
	s[i] = '\n';
	s[++i] = '\0';

	printf("%s",s);
}

int		main(int ac, char *av[])
{
	char	*t;
	char	*s;
	int 	i;


printf("_________________________________________________________________\n");
printf("sizeof t_header = %zu\n",sizeof(t_header));
printf("sizeof t_block = %zu\n",sizeof(t_block));
printf("_________________________________________________________________\n\n");

	while (i < 110)
	{
		create_100_tinies(t);
		create_100_smalls(s);
		// -------------------> testing getrlimit */
	//    if (getrlimit (RLIMIT_MEMLOCK, &limits) == -1)
	//    {
	// 	perror ("The call to getrlimit() failed.");
	// 	return EXIT_FAILURE;
	//    }
	//    else
	//    {
	// 	printf ("The current maximum number of processes is %d.\n", (int) limits.rlim_cur);
	// 	printf("The hard limit on the number of processes is %d.\n", (int) limits.rlim_max);
	//    }

		i++;
	}
	return (0);
}

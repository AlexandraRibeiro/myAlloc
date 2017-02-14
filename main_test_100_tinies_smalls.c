/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_100_tinies_smalls.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/14 18:29:38 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static void create_100_tinies(char *t)
{
	t = (char *)my_malloc(100);
	printf("(debug main) ADDR ptr TINY = %p\n", t);
}

static void create_100_smalls(char *s)
{
	s = (char *)my_malloc(400);
	printf("(debug main) ADDR ptr SMALL = %p\n", s);
}

int		main(int ac, char *av[])
{
	char	*t;
	char	*s;
	int 	i;

	while (i < 108)
	{
		create_100_tinies(t);
		create_100_smalls(s);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_100_tinies_smalls.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/04 17:32:00 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"
#include <stdlib.h>
#include <stdio.h>

static char *create_100_tinies(char *t)
{
	int i = 0;
	t = (char *)malloc(128);
	printf("(debug main) ADDR ptr TINY = %p\n", t);
	while (i < (120 - 1))
	{
		t[i] = 'T';
		i++;
	}
	t[i] = '\n';
	t[++i] = '\0';

	printf("%s",t);
	return (t);
}

static char *create_100_smalls(char *s)
{
	int i = 0;
	s = (char *)malloc(1024);
	printf("(debug main) ADDR ptr SMALL = %p\n", s);

	while (i < (1020 - 1))
	{
		s[i] = 'S';
		i++;
	}
	s[i] = '\n';
	s[++i] = '\0';

	printf("%s",s);
	return (s);
}

static char *create_100_larges(char *l)
{
	int i = 0;
	l = (char *)malloc(8000);
	printf("(debug main) ADDR ptr LARGE = %p\n", l);

	while (i < 7999)
	{
		l[i] = 'L';
		i++;
	}
	l[i] = '\n';
	l[++i] = '\0';

	printf("%s",l);
	return (l);
}

int		main()
{
	char	*t = NULL;
	char	*s = NULL;
	char 	*l = NULL;
	int 	i = 1;


	while (i < 110)
	{
		printf("\n\033[35;1mi = %d\033[0m\n", i);
		t = create_100_tinies(t);
		printf("\n\033[35;1mi = %d\033[0m\n", i);
		s = create_100_smalls(s);
		printf("\n\033[35;1mi = %d\033[0m\n", i);
		l = create_100_larges(l);
		// if (i == 50)
		// {
		// 	free(s);
		// 	// show_alloc_map();
		// }
		i++;
	}

	// show_alloc_map();

	return (0);
}

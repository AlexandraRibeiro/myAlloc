/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_100_tinies_smalls.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/16 15:58:21 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static void create_100_tinies(char *t)
{
	int i = 0;
	t = (char *)my_malloc(TI_MAX);
	printf("(debug main) ADDR ptr TINY = %p\n", t);
		write(1, "boucle\n", 7);
	while (i < (TI_PADDING - 1))
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
	s = (char *)my_malloc(SM_MAX);
	printf("(debug main) ADDR ptr SMALL = %p\n", s);

	while (i < (SM_PADDING - 1))
	{
		s[i] = 'S';
		i++;
	}
	s[i] = '\n';
	s[++i] = '\0';

	printf("%s",s);
}

static void create_100_larges(char *l)
{
	int i = 0;
	l = (char *)my_malloc(8000);
	printf("(debug main) ADDR ptr LARGE = %p\n", l);

	while (i < 7999)
	{
		l[i] = 'L';
		i++;
	}
	l[i] = '\n';
	l[++i] = '\0';

	printf("%s",l);
}

int		main(int ac, char *av[])
{
	char	*t;
	char	*s;
	char 	*l;
	int 	i = 1;

printf("_________________________________________________________________\n");
printf("sizeof t_header = %zu\n",sizeof(t_header));
printf("sizeof t_header_lg = %zu\n", sizeof(t_header_lg));
printf("sizeof t_block = %zu\n",sizeof(t_block));
printf("_________________________________________________________________\n\n");

	while (i < 110)
	{
		printf("\n\033[35;1mi = %d\033[0m\n", i);
		create_100_tinies(t);
		printf("\n\033[35;1mi = %d\033[0m\n", i);
		create_100_smalls(s);
		printf("\n\033[35;1mi = %d\033[0m\n", i);
		create_100_larges(l);

		i++;
	}
	return (0);
}

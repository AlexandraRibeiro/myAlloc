/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_free_large.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 11:29:53 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"


static void *create_print_large(char **large)
{
	char *l = *large;
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

static void *create_print_free_large(char **large)
{
	char *l = *large;
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

printf("\n\n => AVANT FREE :\n");
	printf("\n(verif ADDR dans GLOB : glob.tiny_small = %p\n", glob.tiny_small);
	printf("(verif ADDR dans GLOB : glob.large = %p\n", glob.large);
	printf("(verif VALEUR dans GLOB : glob.bonus_secu = %i\n", glob.bonus_secu);

	free(l);
	// printf("%s", l); //doit segfault
	return (l);
}

int		main()
{
	char 	*l = NULL;
	char 	*l2 = NULL;
	// int 	i = 1;

	l = create_print_large(&l);
	l2 = create_print_free_large(&l2);

	printf("\n(verif ADDR l = %p\n", l);
	free(l); // free le 1er header large

printf("\n\n => APRES FREE LARGE :\n");
	printf("\n(verif ADDR dans GLOB : glob.tiny_small = %p\n", glob.tiny_small);
	printf("(verif ADDR dans GLOB : glob.large = %p\n", glob.large);
	printf("(verif VALEUR dans GLOB : glob.bonus_secu = %i\n", glob.bonus_secu);


	// printf("%s", l); //doit segfault

	return (0);
}

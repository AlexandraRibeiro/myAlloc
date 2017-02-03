/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_munmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/03 15:00:11 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

int		main(int ac, char *av[])
{
	int i;
	int nb;
	char c;
	char *str;

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
		printf("\n=> SUCCESS munmap, le programme doit SEGFAULT apres\n");
	else
		printf("\n=> ERROR munmap\n");
	printf("Declenche normalement un SEGFAULT: %s", str);
	return (0);
}

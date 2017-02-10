/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/10 17:29:14 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/*
** mapped in multiples of the page size
*/
static size_t	setsize(size_t z)
{
	size_t	i;
	int		s;
	int		ztmp;


	s = getpagesize();
	ztmp = (int)z;
	printf(" debut ztmp = %i\n", ztmp);
	i = 0;
	while ((ztmp % s) != 0)
	{
		printf("boucle ztmp = %i\n", ztmp);
		i++;
		ztmp = ztmp + i;
		printf("apres boucle ztmp = %i\n", ztmp);
	}
	printf("ztmp = %i\n", ztmp);
	return ((size_t)ztmp);
}

/*
** tinies pages
*/
static void	*tinies(t_page **t, size_t size)
{
	t_page	*tmp;
	t_page	*prev;


	tmp = mmap(0, setsize(sizeof(t_page)), MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (*t == NULL)
	{
		/*create function pour allouer un block */
		tmp->count = 1;
		tmp->next = NULL;
		tmp->previous = NULL;
		*t = tmp;
		write(1, "ici", 3);
		printf("tinies = %p", *t);
		return (*t);
	}
	else
	{
		prev = *t;
		while (prev->next != NULL)
			prev = prev->next;
		prev->next = tmp;
		tmp->count = prev->count + 1;
		tmp->next = NULL;
		tmp->previous = prev;
		return (tmp);
	}
}

// void	*smalls(t_page **s, size_t size)
// {
// 	if (*small == NULL)
// 	{
// 	}
// 	else
// 	{
// 	}
// 	return ();
// }
//
// void	*larges(t_page **l. size_t size)
// {
// 	if (*large == NULL)
// 	{
// 	}
// 	else
// 	{
//
// 	}
// 	return ();
// }

//changer le nom de la fonction
void	*my_malloc(size_t size)
{
	t_page *t;
	t_page *s;
	t_page *l;

	t = NULL;
	s = NULL;
	l = NULL;
	if (size <= 0)
		return (NULL);
	else if  (size < 100)
		return (tinies(&t, size));
	// else if (size < 4000)
	// 	return (smalls(&s, size));
	// else
	//  	return (larges(&l, size));
	else
		return (NULL);
}

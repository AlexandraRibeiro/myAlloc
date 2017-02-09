/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/09 17:14:06 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/*
** mapped in multiples of the page size
*/
size_t	setsize(size_t z)
{
	size_t	i;

	i = 0;
	while ((getpagesize() % z) != 0)
	{
		i++;
		z = z + i;
	}
	return (z);
}

/*
** tinies pages
*/
void	*tinies(t_page **t, size_t size)
{
	t_tinies	*tmp;

	if ((tmp = mmap(0, setsize(sizeof(t_page)), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0)) == -1)
	{
		write(2, "ERROR => mmap\n", 14);
		return (NULL);
	}
	if (*tiny == NULL)
	{
		/*create function pour le block */
		*tiny = tmp;
		tmp->count = 1;
		tmp->next = null;
		tmp->previous = null;
	}
	else
	{

	}
	return ();
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
	else if (size < 4000)
		return (smalls(&s, size));
	else
	 	return (larges(&l, size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/12 15:00:51 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

t_map glob;

/*
** mapped in multiples of the page size
*/
static void	set_glob()
{
	
}

/*
** tinies pages
*/
static void	*tinies(size_t size)
{
	t_page	*tmp;
	t_page	*prev;

	if (glob)
	{

	}
	else
		set_glob();

	// tmp = mmap(0, setsize(sizeof(t_page)), MMAP_PROT, MMAP_FLAGS, -1, 0);
	// if (*t == NULL)
	// {
	// 	/*create function pour allouer un block */
	// 	tmp->count = 1;
	// 	tmp->next = NULL;
	// 	tmp->previous = NULL;
	// 	*t = tmp;
	// 	write(1, "ici", 3);
	// 	printf("tinies = %p", *t);
	// 	return (*t);
	// }
	// else
	// {
	// 	prev = *t;
	// 	while (prev->next != NULL)
	// 		prev = prev->next;
	// 	prev->next = tmp;
	// 	tmp->count = prev->count + 1;
	// 	tmp->next = NULL;
	// 	tmp->previous = prev;
	// 	return (tmp);
	// }
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
	if (size <= 0)
	{
		ft_putstr_fd("ERROR MALLOC : size <= 0", 2);
		return (NULL);
	}
	else if  (size < 101)
		return (tinies(size));
	// else if (size < 4000)
	// 	return (smalls(&s, size));
	// else
	//  	return (larges(&l, size));
	else
		return (NULL);
}

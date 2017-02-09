/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/09 14:56:02 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*tiny(t_page **tiny, size_t size)
{
	void	*block;
	if (*tiny == NULL)
	{
		block = mmap(0, (128*100), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	else
	{

	}
	return ();
}

void	*small(t_page **small, size_t size)
{
	if (*small == NULL)

	else
	return ();
}

void	*large(t_page **large. size_t size)
{
	if (*large == NULL)

	else
	return ();
}

//changer le nom de la fonction
void	*my_malloc(size_t size)
{
	t_page *tiny;
	t_page *small;
	t_page *large;

	tiny = NULL;
	small = NULL;
	large = NULL;
	if (size <= 0)
		return (NULL);
	else if  (size < 100)
		return (tiny(&tiny, size));
	else if (size < 4000)
		return (small(&small, size));
	else
	 	return (large(&large, size));
}

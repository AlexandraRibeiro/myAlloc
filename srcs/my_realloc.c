/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:54:39 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 18:52:08 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static void 	*realloc_lg(t_header_lg	**head, t_header_lg	**prev)
{

}

static void 	*search_ptr_ts_realloc(void **ptr, t_header *prev, t_block *b)
{
	t_header *ts;

	ts = glob.tiny_small;
	while (ts != NULL)
	{
		if (verif_secu(ts->secu_verif, (void *)ts) == 1)
			return ;
		b = ts->last_block;
		while (b != NULL)
		{
			if (verif_secu(b->secu_verif, (void *)b) == 1)
				return (NULL) ;
			if (b->ptr == *ptr)
				return (realloc_ts(&b, &ts, &prev));
			b = b->previous;
		}
		prev = ts;
		ts = ts->next;
	}
	ft_putstr_fd("ERROR RELLOC / NOTIFY : not valid PTR", 2);
	return (NULL);
}

static void 	*search_ptr_realloc(void **ptr)
{
	t_header_lg	*l;
	t_header_lg *prev;

	l = glob.large;
	prev = NULL;
	while (l != NULL)
	{
		if (verif_secu(l->secu_verif, (void *)l) == 1)
			return (NULL);
		if (l->ptr == *ptr)
			return (realloc_lg(&l, &prev));
		prev = l;
		l = l->next;
	}
	return (search_ptr_ts_realloc(ptr, NULL, NULL));
}

void 			*realloc(void *ptr, size_t size)
{
	if (size == 0)
		return (NULL);
	if (*ptr == NULL)
		return (malloc(size));
	return(search_ptr_realloc(&ptr));
}

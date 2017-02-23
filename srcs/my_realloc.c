/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:54:39 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 19:31:21 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

// static void 	*rea_ts()
// {
//
// }

static void 	*rea_lg(t_header_lg	**head, t_header_lg	**previous, size_t size)
{
	t_header_lg *l;
	t_header_lg *prev;
	void 		*ptr;

	l = *head;
	prev = *previous;
	if (size > l->padding)
	{
		ptr = malloc(size);
		ptr = alloc_memcpy(ptr, l->ptr, req_size);
		free_header_lg(head, previous);
		return (ptr);
	}
	else
	{
		h->req_size = size;
		return (l->ptr);
	}
}

static void 	*ptr_ts_rea(void **ptr, t_header *prev, t_block *b, size_t size)
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
				return (rea_ts(&b, &ts, &prev));
			b = b->previous;
		}
		prev = ts;
		ts = ts->next;
	}
	ft_putstr_fd("ERROR REALLOC / NOTIFY : not valid PTR", 2);
	return (NULL);
}

static void 	*search_ptr_rea(void **ptr, size_t size)
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
			return (rea_lg(&l, &prev, size));
		prev = l;
		l = l->next;
	}
	return (ptr_ts_rea(ptr, NULL, NULL, size));
}

void 			*realloc(void *ptr, size_t size)
{
	if (size == 0)
		return (NULL);
	if (*ptr == NULL)
		return (malloc(size));
	return(search_ptr_rea(&ptr, size));
}

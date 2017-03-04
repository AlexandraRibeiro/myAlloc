/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:54:39 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/04 17:31:31 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"

static void		*rea_ts(t_block **bk, t_header **hd, int padding, size_t size)
{
	t_header	*h;
	t_block		*b;
	void		*ptr;

	h = *hd;
	b = *bk;
	ptr = NULL;
	if (size > (size_t)padding)
	{
		ptr = malloc_2(size);
		ptr = oc_memcpy(ptr, b->ptr, b->req_size);
		if (h->count_alloc + 1 == h->max_alloc)
			free_2(&(b->ptr));
		else
		{
			h->count_alloc++;
			b->req_size = 0;
		}
		return (ptr);
	}
	else
	{
		b->req_size = size;
		return (b->ptr);
	}
}

static void		*rea_lg(t_header_lg **head, t_header_lg **previous, size_t size)
{
	t_header_lg	*l;
	void		*ptr;

	l = *head;
	ptr = NULL;
	if (size > (size_t)l->padding)
	{
		ptr = malloc_2(size);
		ptr = oc_memcpy(ptr, l->ptr, l->req_size);
		free_head_lg(head, previous);
		return (ptr);
	}
	else
	{
		l->req_size = size;
		return (l->ptr);
	}
}

static void		*ptr_ts_rea(void **ptr, t_header *prev, size_t size, int cas)
{
	t_block		*b;
	t_header	*ts;

	b = NULL;
	ts = glob.small;
	if (cas == TI_PADDING)
		ts = glob.tiny;
	while (ts != NULL)
	{
		verif_secu(ts->secu_verif, (void *)ts);
		b = ts->last_block;
		while (b != NULL)
		{
			verif_secu(b->secu_verif, (void *)b);
			if (b->ptr == *ptr)
				return (rea_ts(&b, &ts, cas, size));
			b = b->previous;
		}
		prev = ts;
		ts = ts->next;
	}
	return (NULL);
}

void			*realloc_2(void **ptr, size_t size)
{
	t_header_lg	*l;
	t_header_lg *prev;
	void		*ptr2;

	l = glob.large;
	prev = NULL;
	ptr2 = NULL;
	while (l != NULL)
	{
		verif_secu(l->secu_verif, (void *)l);
		if (l->ptr == *ptr)
			return (rea_lg(&l, &prev, size));
		prev = l;
		l = l->next;
	}
	ptr2 = ptr_ts_rea(ptr, NULL, size, SM_PADDING);
	if (ptr2 == NULL)
		return (ptr_ts_rea(ptr, NULL, size, TI_PADDING));
	else
		return (ptr2);
}

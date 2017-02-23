/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 18:40:07 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static void		free_ts(t_block	**bk, t_header **hd, t_header **pv)
{
	t_header	*h;
	t_block		*b;

	h = *hd;
	b = *bk;

	if (b->req_size == 0)
		return;
	h->count_alloc++;
	if (h->count_alloc > h->max_alloc)
		free_header_ts(hd, pv);
	else
		b->req_size = 0;
}


static void		search_ptr_ts(void **ptr, t_block *b, t_header *prev)
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
				return ;
			if (b->ptr == *ptr)
			{
				free_ts(&b, &ts, &prev);
				return ;
			}
			b = b->previous;
		}
		prev = ts;
		ts = ts->next;
	}
}

static void		search_ptr_free(void **ptr)
{
	t_header_lg	*l;
	t_header_lg *prev;

	l = glob.large;
	prev = NULL;
	while (l != NULL)
	{
		if (verif_secu(l->secu_verif, (void *)l) == 1)
			return;
		if (l->ptr == *ptr)
		{
			free_header_lg(&l, &prev);
			return;
		}
		prev = l;
		l = l->next;
	}
	search_ptr_ts(ptr, NULL, NULL);
	return ;
}

void			free(void *ptr)
{
	// mutex
	if (ptr == NULL)
		return ;
	if (glob.bonus_secu == 1)
	{
		ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return ;
	}
	search_ptr_free(&ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 14:33:39 by aribeiro         ###   ########.fr       */
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


static int		search_ptr_ts(void **ptr)
{
	t_header *ts;
	t_header *prev;
	t_block	*b;

	ts = glob.tiny_small;
	prev = NULL;
	b = NULL;
	while (ts != NULL)
	{
		if (verif_secu(ts->secu_verif, (void *)ts) == 1)
			return (1);
		b = ts->last_block;
		while (b != NULL)
		{
			if (verif_secu(b->secu_verif, (void *)b) == 1)
				return (1);
			if (b->ptr == *ptr)
			{
				free_ts(&b, &ts, &prev);
				return (1);
			}
			b = b->previous;
		}
		prev = ts;
		ts = ts->next;
	}
	return (0);
}

static void		search_ptr(void **ptr)
{
	t_header_lg	*l;
	t_header_lg *prev;

	l = glob.large;
	prev = NULL;

	/* Verif si dans large */
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
	/* Verif si Tiny ou Small */
	if (search_ptr_ts(ptr) == 1)
		return ;
	/*si Ici il n'a pas trouvé le ptr */
	// ft_putstr_fd("FREE / NOTIFY : void *ptr not found", 2);
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
	search_ptr(&ptr);
}

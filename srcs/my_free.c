/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 22:10:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static void		free_ts(t_block **bk, t_header **hd, t_header **pv, int cas)
{
	t_header	*h;
	t_block		*b;

	h = *hd;
	b = *bk;
	if (b->req_size == 0)
		return ;
	h->count_alloc++;
	if (h->count_alloc == h->max_alloc)
	{
		if (*pv == NULL && h->next == NULL)
		{
			b->req_size = 0;
			return ;
		}
		free_head_ts(hd, pv, cas);
	}
	else
		b->req_size = 0;
}

static int		search_ptr_ts(int cas, void **ptr, t_block *b, t_header *prev)
{
	t_header *ts;

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
			{
				free_ts(&b, &ts, &prev, cas);
				return (0);
			}
			b = b->previous;
		}
		prev = ts;
		ts = ts->next;
	}
	return (1);
}

void			free_2(void **ptr)
{
	t_header_lg	*l;
	t_header_lg *prev;

	l = glob.large;
	prev = NULL;
	while (l != NULL)
	{
		verif_secu(l->secu_verif, (void *)l);
		if (l->ptr == *ptr)
		{
			free_head_lg(&l, &prev);
			return ;
		}
		prev = l;
		l = l->next;
	}
	if (search_ptr_ts(SM_PADDING, ptr, NULL, NULL) == 1)
		search_ptr_ts(TI_PADDING, ptr, NULL, NULL);
}

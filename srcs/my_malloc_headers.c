/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc_headers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 17:20:58 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/*
** mapped in multiples of the page size
*/
size_t			get_size(int cas)
{
	size_t	i;
	size_t	req;
	int		page_size;

	page_size = getpagesize();
	if (cas == TI_PADDING || cas == SM_PADDING)
		req = sizeof(t_header) + (sizeof(t_block) * 100) + (cas * 100);
	else
		req = sizeof(t_header_lg) + cas + (cas * LG_REALLOC);
	if (req % page_size != 0)
		i = (req / page_size) + 1;
	else
		i = req / page_size;
	return (i * page_size);
}

static void		*init_1_block(t_header **page, size_t size)
{
	t_block		*b;
	t_header	*h;

	h = *page;
	b = h->last_block;
	b->secu_verif = (size_t)b;
	b->ptr = (void *)b + (sizeof(t_block) * h->count_alloc);
	b->req_size = size;
	b->previous = NULL;
	h->count_alloc--;
	return (b->ptr);
}

void			*header_init(t_header **first, int cas, size_t size)
{
	t_header	*h;
	t_header	*f;

	//getrlimit
	h = mmap(NULL, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
	f = *first;
	h->secu_verif = (size_t)h;
	h->max_alloc = (get_size(cas) - sizeof(t_header)) / (sizeof(t_block) + cas);
	h->count_alloc = h->max_alloc;
	h->last_block =  (void *)h + sizeof(t_header);
	if (*first == NULL)
	{
		h->next = NULL;
		if (cas == TI_PADDING)
			glob.tiny = h;
		else if (cas == SM_PADDING)
			glob.small = h;
	}
	else
	{
		while (f->next != NULL)
			f = f->next;
		f->next = h;
		h->next = NULL;
	}
	return (init_1_block(&h, size));
}

void			*header_lg_init(t_header_lg **first, size_t size)
{
	t_header_lg	*h;
	t_header_lg	*f;
	size_t		setsize;

	setsize = get_size((int)size);
	//getrlimit
	h = mmap(NULL, setsize, MMAP_PROT, MMAP_FLAGS, -1, 0);
	f = *first;
	h->secu_verif = (size_t)h;
	h->padding = (int)setsize;
	h->req_size = size;
	h->ptr = (void *)h + sizeof(t_header_lg);
	if (*first == NULL)
	{
		h->next = NULL;
		glob.large = h;
	}
	else
	{
		while (f->next != NULL)
			f = f->next;
		f->next = h;
		h->next = NULL;
	}
	return (h->ptr);
}

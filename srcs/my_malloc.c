/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/05 13:16:06 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"

static void		*create_block(int cas, t_header **page, size_t size)
{
	t_header	*h;
	t_block		*before;
	t_block		*current;

	h = *page;
	before = h->last_block;
	verif_secu(before->secu_verif, (void *)before);
	current = (void *)before + sizeof(t_block);
	current->secu_verif = (size_t)current;
	current->ptr = before->ptr + cas;
	current->req_size = size;
	current->previous = before;
	h->last_block = current;
	return (current->ptr);
}

static void		*search_empty_block(int cas, t_header **page, size_t size)
{
	t_block		*b;
	t_header	*h;

	h = *page;
	b = h->last_block;
	while (b != NULL)
	{
		verif_secu(b->secu_verif, (void *)b);
		if (b->req_size == 0)
		{
			b->req_size = size;
			return (b->ptr);
		}
		b = b->previous;
	}
	return (create_block(cas, page, size));
}

static void		*search_place(t_header **first, int cas, size_t size)
{
	t_header	*tmp;

	tmp = *first;
	while (1)
	{
		verif_secu(tmp->secu_verif, (void *)tmp);
		if (tmp->count_alloc > 0)
		{
			tmp->count_alloc--;
			return (search_empty_block(cas, &tmp, size));
		}
		else if (tmp->next == NULL)
			return (header_init(first, cas, size));
		else
			tmp = tmp->next;
	}
}

void			*malloc_2(size_t size)
{
	struct rlimit	limits;

	if (!getrlimit(RLIMIT_DATA, &limits) && size < limits.rlim_cur)
	{
		if (size <= TI_MAX && glob.tiny == NULL)
			return (header_init(&(glob.tiny), TI_PADDING, size));
		else if (size <= TI_MAX && glob.tiny != NULL)
			return (search_place(&(glob.tiny), TI_PADDING, size));
		else if (size <= SM_MAX && glob.small == NULL)
			return (header_init(&(glob.small), SM_PADDING, size));
		else if (size <= SM_MAX && glob.small != NULL)
			return (search_place(&(glob.small), SM_PADDING, size));
		else if (size > SM_MAX)
			return (header_lg_init(&(glob.large), size));
		else
			return (NULL);
	}
	else
		return (NULL);
}

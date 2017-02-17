/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/17 21:23:22 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		verif_secu(size_t secu, void *ptr)
{
	if (secu == (size_t)ptr)
		return (0);
	else
	{
		glob.bonus_secu = 1;
		ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (1);
	}
}

/*
** Be careful don't touch s_block->previous
*/
void	init_block(t_block **block)
{
	t_block *b;

	b = *block;
	b->ptr = NULL;
	b->req_size = NULL;
}

/*
** Be careful don't touch s_block->previous
*/
void	init_header_tiny_small(t_header **head)
{
	t_header *h;

	h = *head;
	b->count_alloc = 0
}

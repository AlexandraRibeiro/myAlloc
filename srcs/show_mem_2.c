/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 19:03:39 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/28 19:25:53 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void 		addr_blocks(void *header, t_block *b, t_block *prev)
{
	t_header *h;

	h = (t_header)header;
	if (h->count_alloc == h->max_alloc) //page vide pour malloc 1024*1024
		return;
	b = h->last_block;
	while (1)
	{
		while (b->previous != prev)
			b = b->previous;
		printf("\n ADDR du BLOCK = %p", b);
		prev = b;
		b = h->last_block;
	}
}

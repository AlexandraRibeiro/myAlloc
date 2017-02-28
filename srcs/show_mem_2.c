/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 19:03:39 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/28 22:46:20 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void 		print_in_out_addr(t_block *b, t_header_lg *hl)
{
	size_t in;
	size_t out;

	if (b != NULL && hl == NULL)
	{
		in = (size_t)b->ptr;
		out = (size_t)(b->ptr + b->req_size);
	}
	else
	{
		in = (size_t)hl->ptr;
		out = (size_t)(hl->ptr + hl->req_size);
	}
	oc_puthexa(in);
	oc_putstr_fd(" - ", 1);
	oc_puthexa(out);
	oc_putstr_fd(" : ", 1);
	oc_putnbr_fd(out - in, 1);
	oc_putstr_fd(" octets\n", 1);
}

void 		addr_blocks(void *header, t_block *b, t_block *prev)
{
	t_header *h;

	h = (t_header *)header;
	if (h->count_alloc == h->max_alloc) //page vide pour malloc 1024*1024
		return;
	b = h->last_block;
	if (b->previous == NULL)
	{
		print_in_out_addr(b, NULL);
		return ;
	}
	while (1)
	{
		while (b->previous != prev)
			b = b->previous;
		print_in_out_addr(b, NULL);
		prev = b;
		b = h->last_block;
		if (b->previous == prev)
		{
			print_in_out_addr(b, NULL);
			return ;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/05 13:49:18 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"

static void		print_infos(size_t cas, int total, int i)
{
	size_t		setsize;
	size_t		multiple;
	int			page_size;

	write(1, "\n => Allocations : ", 19);
	oc_putnbr_fd(total + i, 1);
	setsize = get_size(cas);
	page_size = getpagesize();
	multiple = setsize / page_size;
	write(1, "\n => Total pagesize : ", 22);
	oc_putnbr_fd(multiple, 1);
	write(1, " * ", 3);
	oc_putnbr_fd(page_size, 1);
	write(1, " = ", 3);
	oc_putnbr_fd(setsize, 1);
	oc_putstr_fd("\n________________________________________________\n", 1);
}

static int		print_alloc(int i, void *block, int total)
{
	t_block	*b;

	b = block;
	if (i % 10 == 0)
		oc_putchar_fd('\n', 1);
	if (b->req_size == 0)
	{
		oc_putstr_fd("\033[32;1m F \033[0m|", 1);
		total--;
	}
	else
		oc_putstr_fd("\033[33;1m M \033[0m|", 1);
	return (total);
}

static void		read_ts_alloc(t_header **first, int total, int cas, t_header *h)
{
	t_block		*b;
	int			i;

	h = *first;
	while (h != NULL)
	{
		verif_secu(h->secu_verif, (void *)h);
		i = 0;
		b = h->last_block;
		if (cas == TI_PADDING)
			oc_putstr_fd("\n TINY MAP", 1);
		else if (cas == SM_PADDING)
			oc_putstr_fd("\n SMALL MAP", 1);
		while (b != NULL)
		{
			verif_secu(b->secu_verif, (void *)b);
			total = print_alloc(i, b, total);
			i++;
			b = b->previous;
		}
		print_infos(cas, total, i);
		h = h->next;
	}
}

static int		read_large_alloc(int total)
{
	t_header_lg	*h;
	int			i;

	h = glob.large;
	while (h != NULL)
	{
		i = 0;
		verif_secu(h->secu_verif, (void *)h);
		oc_putstr_fd("\n LARGE MAP", 1);
		if (h->req_size != 0)
		{
			i++;
			oc_putstr_fd("\n\033[33;1m M \033[0m|", 1);
			print_infos(h->padding, 0, i);
		}
		total++;
		h = h->next;
	}
	return (total);
}

void			show_alloc_map(void)
{
	int	total_map_large;

	total_map_large = 0;
	oc_putstr_fd("\n________________________________________________\n", 1);
	if (glob.tiny == NULL && glob.small == NULL && glob.large == NULL)
	{
		oc_putstr_fd("\n************ NO ALLOCATIONS\n", 2);
		return ;
	}
	if (glob.tiny != NULL)
		read_ts_alloc(&(glob.tiny), 0, TI_PADDING, NULL);
	if (glob.small != NULL)
		read_ts_alloc(&(glob.small), 0, SM_PADDING, NULL);
	if (glob.large != NULL)
	{
		total_map_large = read_large_alloc(0);
		oc_putstr_fd("________________________________________________\n", 1);
		oc_putstr_fd("\n\033[35;1m************ LARGE MAP CREATED = ", 1);
		oc_putnbr_fd(total_map_large, 1);
		oc_putstr_fd("\033[0m\n\n", 1);
	}
}

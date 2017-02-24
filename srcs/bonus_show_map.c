/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_show_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/24 15:08:42 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static int	print_alloc(int i, void *block, int total)
{
	t_block	*b;

	b = block;
	if (i % 10 == 0)
		ft_putchar_fd('\n', 1);
	if (b->req_size == 0)
	{
		ft_putstr_fd("\033[32;1m F \033[0m|", 1);
		total--;
	}
	else
		ft_putstr_fd("\033[35;1m M \033[0m|", 1);
	return (total);
}

/* ajouter verif secu pour eviter les segfault */
static void read_ts_alloc(t_header **first, int total, int cas)
{
	t_header	*h;
	t_block		*b;
	int			i;

	h = *first;
	while (h != NULL)
	{
		ft_putstr_fd("__________________________________________________\n", 1);
		i = 0;
		b = h->last_block;
		if (cas == TI_PADDING)
			ft_putstr_fd("\n TINY MAP", 1);
		else if (cas == SM_PADDING)
			ft_putstr_fd("\n SMALL MAP", 1);
		while (b != NULL)
		{
			total = print_alloc(i, b, total);
			i++;
			b = b->previous;
		}
		write(1, "\n => ", 5);
		ft_putnbr_fd(total + i, 1);
		ft_putstr_fd(" allocations\n", 1);
		h = h->next;
	}
}

static int	read_large_alloc(int total)
{
	t_header_lg	*h;
	int			i;

	h = glob.large;
	while (h != NULL)
	{
		i = 0;
		ft_putstr_fd("__________________________________________________\n", 1);
		ft_putstr_fd("\n LARGE MAP", 1);
		if (h->req_size != 0)
		{
			i++;
			ft_putstr_fd("\n\033[35;1m M \033[0m|", 1);
			write(1, "\n => ", 5);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" allocation\n", 1);
		}
		total++;
		h = h->next;
	}
	return (total);
}

void 	show_alloc_map()
{
	// int	total_map_tiny;
	// int	total_map_small;
	int	total_map_large;

	// total_map_tiny = 0;
	// total_map_small = 0;
	total_map_large = 0;
	if (glob.tiny != NULL)
		read_ts_alloc(&(glob.tiny), 0, TI_PADDING);
	if (glob.small != NULL)
		read_ts_alloc(&(glob.small), 0, SM_PADDING);
	if (glob.large != NULL)
		total_map_large = read_large_alloc(0);
	ft_putstr_fd("__________________________________________________\n", 1);
	ft_putstr_fd(" \n ********** LARGE MAP CREATED = ", 1);
	ft_putnbr_fd(total_map_large, 1);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:16:32 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 14:33:11 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

static size_t	addr_header(size_t find, size_t f1, size_t f2)
{
	size_t	total;
	t_header *h;

	total = 0;
	h = (t_header *)find;
	if (find == f1 || find == f2)
	{
		if (find == f1)
			oc_putstr_fd("\033[33;1mTINY : ", 1);
		else if (find == f2)
			oc_putstr_fd("\033[33;1mSMALL : ", 1);
		oc_puthexa(find);
		oc_putstr_fd("\033[0m\n", 1);
		if (h->count_alloc != h->max_alloc)
			addr_blocks(h, NULL, NULL, &total);
	}
	else
	{
		oc_putstr_fd("\033[33;1mLARGE : ", 1);
		oc_puthexa(find);
		oc_putstr_fd("\033[0m\n", 1);
		print_in_out_addr(NULL, (t_header_lg *)find, &total);
	}
	return (total);
}

static void		smallest_addr_l(t_header_lg **first, size_t last, size_t *find)
{
	t_header_lg	*h;
	size_t		f;

	h = *first;
	f = *find;
	while (h != NULL)
	{
		verif_secu(h->secu_verif, (void *)h);
		if ((size_t)h <= last)
			h = h->next;
		else
		{
			if (f == last)
				f = (size_t)h;
			else if (f == 0 || (size_t)h < f)
				f = (size_t)h;
			h = h->next;
		}
	}
	*find = f;
}

static size_t	smallest_addr_ts(t_header **first, size_t last, size_t *find)
{
	t_header	*h;
	size_t		f;

	h = *first;
	f = *find;
	while (h != NULL)
	{
		verif_secu(h->secu_verif, (void *)h);
		if ((size_t)h <= last)
			h = h->next;
		else
		{
			if (f == last)
				f = (size_t)h;
			else if (f == 0 || (size_t)h < f)
				f = (size_t)h;
			h = h->next;
		}
	}
	*find = f;
	return (f);
}

static void		sort_addr(size_t f1, size_t f2, size_t find, size_t total)
{
	size_t last;

	last = 0;
	while (1)
	{
		if (glob.tiny != NULL)
			f1 = smallest_addr_ts(&(glob.tiny), last, &find);
		if (glob.small != NULL)
			f2 = smallest_addr_ts(&(glob.small), last, &find);
		if (glob.large != NULL)
			smallest_addr_l(&(glob.large), last, &find);
		if (find == last)
		{
			oc_putstr_fd("\033[35;1mTotal : ", 1);
			oc_putnbr_fd(total, 1);
			oc_putstr_fd(" octets\033[0m\n", 1);
			return ;
		}
		else
		{
			total += addr_header(find, f1, f2);
			last = find;
		}
	}
}

void			show_alloc_mem(void)
{
	if (glob.secu == 1)
	{
		oc_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return ;
	}
	sort_addr(0, 0, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:16:32 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/02 15:48:49 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

//ajouter verfi secu
static size_t	addr_header(size_t find, size_t f1, size_t f2)
{
	size_t	total;

	total = 0;
	if (find == f1 || find == f2)
	{
		if (find == f1)
			oc_putstr_fd("TINY : ", 1);
		else if (find == f2)
			oc_putstr_fd("SMALL : ", 1);
		oc_puthexa(find);
		oc_putchar_fd('\n', 1);
		addr_blocks((void *)find, NULL, NULL, &total);
	}
	else
	{
		oc_putstr_fd("LARGE : ", 1);
		oc_puthexa(find);
		oc_putchar_fd('\n', 1);
		print_in_out_addr(NULL, (t_header_lg *)find, &total);
	}
	return (total);
}

static void	smallest_addr_l(t_header_lg **first, size_t last, size_t *find)
{
	t_header_lg	*h;
	size_t		f;

	h = *first;
	f = *find;
	while (h != NULL)
	{
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
			oc_putstr_fd("Total : ", 1);
			oc_putnbr_fd(total, 1);
			oc_putstr_fd(" octets\n", 1);
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

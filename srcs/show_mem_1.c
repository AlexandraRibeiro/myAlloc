/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:16:32 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/28 19:21:34 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"


static void 		addr_header(size_t find, size_t f1, size_t f2, size_t f3)
{
	if (find == f1)
	{
		// printf("TINY : %p\n", (void *)find);
		oc_putstr_fd("TINY : ", 1)
		oc_puthexa(find);
		oc_putchar_fd('\n', 1);
		addr_blocks((void *)find, NULL, NULL);
	}
	else if (find == f2)
	{
		printf("SMALL : %p\n", (void *)find); //afficher tous les blocs
		// oc_puthexa(find);
		// oc_putchar_fd('\n', 1);
	}
	else if (find == f3)
		printf("LARGE : %p\n", (void *)find);
}


static size_t 		smallest_addr_l(t_header_lg **first, size_t last, size_t *find)
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
	return (f);
}


static size_t 		smallest_addr_ts(t_header **first, size_t last, size_t *find)
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

static void 		sort_addr(size_t f1, size_t f2, size_t f3)
{
	size_t last;
	size_t find;

	last = 0;
	find = 0;
	while (1)
	{
		if (glob.tiny != NULL)
			f1 = smallest_addr_ts(&(glob.tiny), last, &find);
		if (glob.small != NULL)
			f2 = smallest_addr_ts(&(glob.small), last, &find);
		if (glob.large != NULL)
			f3 = smallest_addr_l(&(glob.large), last, &find);
		if (find == last)
			return ;
		else
		{
			addr_header(find, f1, f2, f3);
			last = find;
		}
	}
}

void      	show_alloc_mem()
{
	if (glob.secu == 1)
	{
		oc_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return ;
	}
	sort_addr(0, 0, 0);
}

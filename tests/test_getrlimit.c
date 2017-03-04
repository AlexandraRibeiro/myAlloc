/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getrlimit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/04 21:32:02 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"
#include <sys/resource.h>
#include <stdio.h>

int		main(int ac, char *av[])
{
	struct rlimit limits;
	char *addr;

	// setrlimit(RLIMIT_DATA, &limits);

	/* -------------------> testing getrlimit */
	if (getrlimit(RLIMIT_DATA, &limits) == 0)
	{
		printf ("rlim_cur : %zu.\n", (size_t) limits.rlim_cur);
		printf("rlim_max : %zu.\n", (size_t) limits.rlim_max);
	}
	addr= malloc(-56);
	show_alloc_mem();
	return (0);
}

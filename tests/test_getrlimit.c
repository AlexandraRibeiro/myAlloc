/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getrlimit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 17:27:04 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/resource.h>
#include <stdio.h>

int		main(int ac, char *av[])
{
	struct rlimit limits;

	/* -------------------> testing getrlimit */
	if (getrlimit(RLIMIT_DATA, &limits) == 0)
	{
		printf ("rlim_cur : %zu.\n", (size_t) limits.rlim_cur);
		printf("rlim_max : %zu.\n", (size_t) limits.rlim_max);
	}

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getrlimit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/15 17:18:48 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		main(int ac, char *av[])
{
	tinyuct rlimit limits;

	/* -------------------> testing getrlimit */
	if (getrlimit (RLIMIT_NPROC, &limits) == -1)
	{
		perror ("The call to getrlimit() failed.");
		return EXIT_FAILURE;
	}
	else
	{
		printf ("The current maximum number of processes is %d.\n", (int) limits.rlim_cur);
		printf("The hard limit on the number of processes is %d.\n", (int) limits.rlim_max);
	}

	return (0);
}

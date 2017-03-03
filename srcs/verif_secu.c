/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_secu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 22:42:52 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void		verif_secu(size_t secu, void *ptr)
{
	char	buf[4095];
	int		i;

	i = 0;
	if (secu == (size_t)ptr)
		return ;
	while (1)
	{
		oc_putstr_fd("\n\n\033[31;1mSorry the memory is corrupted. ", 2);
		oc_putstr_fd("Have to abort now!\n", 2);
		oc_putstr_fd("=> Please press Ctrl-c to abort!\033[0m\n", 2);
		read(0, &buf, 4095);
		i = 0;
		while (i < 10000)
			i++;
	}
}

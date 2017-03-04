/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oc_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 12:27:07 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/04 17:30:23 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"

void		oc_puthexa(size_t addr)
{
	size_t	i;

	i = 0;
	if (addr)
	{
		i = addr / 16;
		oc_puthexa(i);
		if (addr % 16 < 10)
			oc_putchar_fd('0' + addr % 16, 1);
		else
			oc_putchar_fd('a' + (addr % 16) - 10, 1);
	}
	else
		oc_putstr_fd("0x", 1);
	return ;
}

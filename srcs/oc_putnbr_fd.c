/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oc_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 14:11:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/24 16:31:05 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	oc_putnbr_fd(int n, int fd)
{
	unsigned int i;

	if (n < 0)
	{
		i = -n;
		oc_putchar_fd('-', fd);
	}
	else
		i = n;
	if (i >= 10)
	{
		oc_putnbr_fd(i / 10, fd);
		oc_putnbr_fd(i % 10, fd);
	}
	else
		oc_putchar_fd(i + '0', fd);
}

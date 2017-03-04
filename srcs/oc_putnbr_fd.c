/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oc_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 14:11:43 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/04 19:55:57 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"

void	oc_putnbr_fd(size_t n, int fd)
{
	size_t i;

	i = n;
	if (i >= 10)
	{
		oc_putnbr_fd(i / 10, fd);
		oc_putnbr_fd(i % 10, fd);
	}
	else
		oc_putchar_fd(i + '0', fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oc_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:19:25 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/24 16:27:57 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void			*oc_memcpy(void *dst, const void *src, size_t n)
{
	char		*destcpy;
	const char	*srccpy;

	destcpy = dst;
	srccpy = src;
	while (n != 0)
	{
		*destcpy = *srccpy;
		destcpy++;
		srccpy++;
		n--;
	}
	return (dst);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_secu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 18:52:19 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int	verif_secu(size_t secu, void *ptr)
{
	if (secu == (size_t)ptr)
		return (0);
	else
	{
		glob.secu = 1;
		oc_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (1);
	}
}

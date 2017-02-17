/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/17 15:28:42 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"



/*changer le nom une fois la librairie faite */
void	my_free(void *ptr)
{
	if (ptr = NULL)
		return;
	search_block_malloc(&ptr);
}

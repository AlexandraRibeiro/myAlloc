/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:16:32 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/27 15:03:35 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "memory.h"
//
// static dump_ts(t_header **first, int cas, int i)
// {
// 	t_header *h;
// 	t_block *b;
//
// 	h = *first;
// 	while (h != NULL)
// 	{
// 		b = h->last_block;
// 		if (cas == TI_PADDING)
// 			oc_putstr_fd("TINY : ", 1);
// 		else if (cas == SM_PADDING)
// 			oc_putstr_fd("SMALL : ", 1);
// 	printf("ADDR TINY : %p\n".
// 		while (b != NULL)
// 			b = b->previous;
// 	}
// }
//
// void      	show_alloc_mem()
// {
// 	if (glob.secu == 1)
// 	{
// 		oc_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
// 		return (NULL);
// 	}
// 	if (glob.tiny != NULL)
// 		dump_ts(&(glob.tiny), TI_PADDING, 0);
// 	if (glob.small != NULL)
// 		dump_ts(&(glob.small), SM_PADDING, 0);
// 	if (glob.large != NULL)
// 		dump_large(&(glob.large));
// }

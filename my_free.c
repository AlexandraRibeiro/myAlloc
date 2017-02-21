/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/21 16:41:08 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

// static void		free_tiny_small(void **ptr, t_block	**block, t_header **head)
// {
// 	t_header	*h;
// 	t_block		*b;
//
// 	h = *head;
// 	b = *block;
//
// 	h->count_alloc--;
// 	if (h->count_alloc > 1)
// 	{
//
// 	}
// 	else
// 		free_header_tiny_small(head);
// }


/* attentio aux blocks vides, bien verifier la size en plus du ptr */
// static int		search_ptr_tiny_small(void **ptr)
// {
// 	t_header *ts;
// 	t_block	*b;
//
// 	ts = glob.tiny_small;
// 	b = NULL;
// 	while (ts != NULL)
// 	{
// 		if (verif_secu(ts->secu_verif, (void *)ts) == 1)
// 			return;
// 		b = ts->last_block;
// 		while (b != NULL)
// 		{
// 			if (verif_secu(b->secu_verif, (void *)b) == 1)
// 				return (1);
// 			if (b->ptr == *ptr)
// 			{
// 				free_tiny_small(ptr, &b, &ts);
// 				return (1);
// 			}
// 			b = b->previous;
// 		}
// 		ts = ts->next;
// 	}
// 	return (0);
// }

static void		search_ptr(void **ptr)
{
	t_header_lg	*l;
	t_header_lg *prev;

	l = glob.large;
	prev = NULL;

	/* Verif si dans large */
	while (l != NULL)
	{
		if (verif_secu(l->secu_verif, (void *)l) == 1)
			return;
		if (l->ptr == *ptr)
		{
			free_header_lg(&l, &prev);
			return;
		}
		prev = l;
		l = l->next;
	}
	/* Verif si Tiny ou Small */
	// if (search_ptr_tiny_small(ptr) == 1)
	// 	return ;
	/*si Ici il n'a pas trouvé le ptr */
	ft_putstr_fd("FREE / NOTIFY : void *ptr not found", 2);
	return ;
}

/*changer le nom une fois la librairie faite */
void			my_free(void *ptr)
{
	// mutex
	if (ptr == NULL)
		return ;
	if (glob.bonus_secu == 1)
	{
		ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return ;
	}
	search_ptr(&ptr);
}

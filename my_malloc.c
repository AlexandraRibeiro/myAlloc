/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/12 17:37:45 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

struct s_map glob;

/*
** mapped in multiples of the page size
*/
static size_t get_size(int cas)
{
	if (cas == TINY)
		return(((12800 + 100) / 4096) + 1);
	else
		return (0);
}

static void	init_1_block(void **block, void **data, size_t size)
{
	t_block *b;
	// t_block *prev;

	b = *block;
	// prev = *previous;
	// prev->next = b;
	b->secu_verif = (size_t)(b->secu_verif);
	b->ptr = *data;
	b->req_size = size;
	b->next = NULL;
}

/*
** tinies pages
*/
static void	*tinies(size_t size)
{
	t_page	*p;
	t_page	*tmp;

	if (glob.tiny == NULL)
	{
		//getrlimit
		p = mmap(0, get_size(TINY), MMAP_PROT, MMAP_FLAGS, -1, 0); // 1 seul appel systeme
		tmp = p;
		p->secu_verif = (size_t)(p->secu_verif);
		p->count_alloc = 100; //total des places libres
		p->b =  tmp + sizeof(t_page);
		p->data = tmp + sizeof(t_page) + (sizeof(t_block) * 100);
		init_1_block(&(p->b), &(p->data), size);
		p->next = NULL;
		p->previous = NULL;
		glob.tiny = p;
		return(glob.tiny);
	}
	else
		return (NULL);
	// else
	// {
	// 	tmp = glob.tiny;
	// 	while (1)
	// 	{
	// 		if (tmp->count != 0)
	// 			return (create_block(TINY, &tmp));
			// else if (tmp->secu_verif != (size_t)(tmp.secu_verif))
			// {
			// 	/*nettoyer la memoire*/
			// 	ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
			// 	return (NULL);
			// }
	// 		else if (tmp->next == NULL)
	// 			return (create_page(TINY, &tmp));
	// 		else
	// 			tmp = tmp->next;
	// 	}
	// }
}

//changer le nom de la fonction
void	*my_malloc(size_t size)
{
	//mutex
	if (size <= 0)
	{
		ft_putstr_fd("ERROR MALLOC : size <= 0", 2);
		return (NULL);
	}
	else if  (size < 101)
		return (tinies(size));
	// else if (size < 4000)
	// 	return (smalls(&s, size));
	// else
	//  	return (larges(&l, size));
	else
		return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/13 15:15:18 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

struct s_map glob;

/*
** mapped in multiples of the page size
*/
static size_t get_size(int cas)
{
	size_t i;

	if (cas == TINY)
	{
		i = ((sizeof(t_page) + (sizeof(t_block) * 100) + (TINY * 100)) / getpagesize()) + 1;
printf("(debug) VALEUR multiple 4096 : i = %zu, i*4096 = %zu\n", i, i*getpagesize());
		return (i * 4096);
	}
	else
		return (0);
}


static void	*create_block(int cas, t_page **page)
{
	t_page	*p;
	t_block *before;
	t_block *current;

	p = *page;
	before = p->last_block;
	current = before + (sizeof(t_block));
	current->secu_verif = (size_t)(current->secu_verif);
	current->ptr = before->ptr + cas;
	current->req_size = glob.size;
	current->next = before;
	p->last_block = current; //rempli comme une pile je change le pointeur du debut
	return (current->ptr);
}

static void	*init_1_block(t_page **page)
{
	t_block *b;
	void	*tmp;
	t_page 	*p;

printf("\n(debug) POSITION position fonction init_1_block\n");
printf("(debug) SIZE de t_block = %lu\n",sizeof(t_block));
	p = *page;
	b = p->last_block;
	tmp = b; // copie la place du pointeur
	b->secu_verif = (size_t)(b->secu_verif);
	b->ptr = tmp + (sizeof(t_block)*100);
	b->req_size = glob.size;
	b->next = NULL;
	return (b->ptr);
}

/*
** tinies pages
*/
static void	*tinies()
{
	t_page	*p;
	void	*tmp;

	if (glob.tiny == NULL)
	{
printf("(debug) POSITION position programme -> tiny = NULL\n");
		//getrlimit
		tmp = mmap(0, get_size(TINY), MMAP_PROT, MMAP_FLAGS, -1, 0);

printf("(debug) ADDR page cree par mmap = %p\n", tmp);
/* SIZE t_PAGE */
printf("\n(debug) SIZE de size_t = %lu\n",sizeof(size_t));
printf("(debug) SIZE de int = %lu\n",sizeof(int));
printf("(debug) SIZE de void * = %lu\n",sizeof(void *));
printf("(debug) SIZE de t_page = %lu\n",sizeof(t_page));

		p = tmp;
		p->secu_verif = (size_t)(p->secu_verif);
		p->count_alloc = 100; //total des places libres
		p->last_block =  tmp + sizeof(t_page);
		p->next = NULL;
		p->previous = NULL;
		glob.tiny = p;
		return(init_1_block(&p));
	}
	else
	{
printf("(debug) POSITION position programme -> tiny != NULL\n");
		return (NULL);
	}
// 	else
// 	{
// printf("(debug) POSITION programme -> tiny != NULL\n");
// 		tmp = glob.tiny;
// 		while (1)
// 		{
// 			if (tmp->count_alloc != 0)
// 			{
// 				tmp->count_alloc--;
// printf("(debug) VALEUR count_alloc = %d\n", tmp->count_alloc);
// 				return (create_block(TINY, &tmp));
// 			}
// 			else if (tmp->secu_verif != (size_t)(tmp->secu_verif))
// 			{
// 				/*nettoyer la memoire*/
// 				ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
// 				return (NULL);
// 			}
// 			// else if (tmp->next == NULL)
// 			// 	return (create_page(TINY, &tmp));
// 			else if (tmp->next == NULL)
// 					return (NULL);
// 			else
// 				tmp = tmp->next;
// 		}
	// }
}

//changer le nom de la fonction
void	*my_malloc(size_t size)
{
	//mutex
	glob.size = size;
	if (size <= 0)
	{
		ft_putstr_fd("ERROR MALLOC : size <= 0", 2);
		return (NULL);
	}
	else if  (size < 101)
		return (tinies());
	// else if (size < 4000)
	// 	return (smalls(&s, size));
	// else
	//  	return (larges(&l, size));
	else
		return (NULL);
}

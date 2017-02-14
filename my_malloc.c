/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/14 21:58:39 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

struct s_map glob;

/*
** mapped in multiples of the page size
*/
static size_t	get_size(int cas)
{
	size_t	i;
	size_t	req;
	int		page_size;

	page_size = getpagesize();

	req = sizeof(t_header) + (sizeof(t_block) * 100) + (cas * 100);
printf("\nsize requested = %zu", req);
	if (req % page_size != 0)
	{
		i = (req / page_size) + 1;
printf("\n(debug) VALEUR +1 : multiple 4096 : i = %zu, i*4096 = %zu\n", i, i * page_size);
	}
	else
	{
		i = req / page_size;
printf("\n(debug) VALEUR juste: multiple 4096 : i = %zu, i*4096 = %zu\n", i, i * page_size);
	}
	return (i * 4096);
}

static void		*create_block(int cas, t_header **page)
{
	t_header	*h;
	t_block *before;
	t_block *current;

	h = *page;
	before = h->last_block;
	current = (void *)before + sizeof(t_block);
printf("(debug) ADDR block current = %p, decalage avec addr block_before = %ld\n", current, (void *)current - (void *)before);

	// current->secu_verif = (size_t)&(current->secu_verif);
	current->ptr = before->ptr + cas;
	current->req_size = glob.requested_size;
	current->next = before;

	h->last_block = current; //rempli comme une pile je change le pointeur du debut
	return (current->ptr);
}

static void	*init_1_block(t_header **page)
{
	t_block		*b;
	t_header 	*h;

printf("\n(debug) POSITION position fonction init_1_block\n");
printf("(debug) SIZE de t_block = %lu\n",sizeof(t_block));
	h = *page;
	b = h->last_block;
printf("(debug) ADDR last_block = %p, decalage avec addr page = %ld\n", b, (void *)b - (void *)h);


	// b->secu_verif = (size_t)&(b->secu_verif);
	b->ptr = (void *)b + (sizeof(t_block) * h->count_alloc);
	b->req_size = glob.requested_size;
	b->next = NULL;
	return (b->ptr);
}

/*
** Parsing : searching an empty place || create a new page
*/
static void		*search_place(t_header **h, int cas)
{
	t_header *tmp;

	tmp = *h;
printf("\n(debug) POSITION programme -> search_place\n");
	while (1)
	{
		if (tmp->count_alloc != 0)
		{
			tmp->count_alloc--;
printf("\n(debug) VALEUR count_alloc = %d\n", tmp->count_alloc);
			return (create_block(cas, h));
		}
		else if (tmp->next == NULL)
		{
printf("h->next = NULL\n");
			return (page_init(h, cas));
		}
		else
			tmp = tmp->next;

		// else if (h->secu_verif != (size_t)&(h->secu_verif))
		// {
		// 	/*nettoyer la memoire*/
		// 	ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		// 	return (NULL);
		// }
	}
}

void		*page_init(t_header **addr, int cas)
{
	t_header	*h;
	t_header	*prev;

	//getrlimit
	h = (t_header *)mmap(0, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
printf("(debug) ****************************** APPEL SYS MMAP\n");
printf("(debug) ADDR page MMAP = %p\n", h);

	prev = *addr;

	// h->secu_verif = (size_t)(h->secu_verif);
	h->count_alloc = (get_size(cas) - sizeof(t_header)) / (sizeof(t_block) + cas); //total des places libres
	h->last_block =  (void *)h + sizeof(t_header);

printf("(debug) h->count_alloc = %d", h->count_alloc);

	if (*addr == NULL)
	{
		h->next = NULL;
		h->previous = NULL;
	}
	else
	{
		prev->next = h;
		h->previous = prev;
		h->next = NULL;
printf ("\n(debug) ADDR previous page = %p", h->previous);
printf ("\n(debug) ADDR current page = %p\n", h);
	}
	if (cas == TINY)
		glob.tiny = h;
	else if (cas == SMALL)
		glob.small = h;
	return (init_1_block(&h));
}

static void *parse_malloc_size()
{
	if  (glob.requested_size <= TI_MAX && glob.tiny == NULL)
		return (page_init(&(glob.tiny), TINY));
	else if  (glob.requested_size <= TI_MAX && glob.tiny != NULL)
		return (search_place(&(glob.tiny), TINY));
	else if  (glob.requested_size <= SM_MAX && glob.small == NULL)
		return (page_init(&(glob.small), SMALL));
	else if  (glob.requested_size <= SM_MAX && glob.small != NULL)
		return (search_place(&(glob.small), SMALL));
	else if (glob.requested_size > SM_MAX)
	{
		write(1, "\n\npas encore codé, return NULL\n", 31);
		return (NULL); //a coder
	}
	else
		return (NULL);
}

//changer le nom de la fonction
void	*my_malloc(size_t size)
{
	//mutex
	glob.requested_size = size;
	if (size <= 0)
	{
		ft_putstr_fd("ERROR MALLOC : size <= 0", 2);
		return (NULL);
	}
	return (parse_malloc_size());
}

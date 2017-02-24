/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/24 18:04:25 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

t_maps glob;



/******************************************************************************/
/******************************************************************************/
/*
** mapped in multiples of the page size
*/
size_t	get_size(int cas)
{
	size_t	i;
	size_t	req;
	int		page_size;

	page_size = getpagesize();

	if (cas == TI_PADDING || cas == SM_PADDING)
		req = sizeof(t_header) + (sizeof(t_block) * 100) + (cas * 100);
	else
		req = sizeof(t_header_lg) + cas + (cas * LG_REALLOC);
	if (req % page_size != 0)
		i = (req / page_size) + 1;
	else
		i = req / page_size;
// oc_putstr_fd("\npour cas = ", 1);
// oc_putnbr_fd(cas, 1);
// oc_putstr_fd("\nmultiple 4096 = ", 1);
// oc_putnbr_fd(i, 1);
// oc_putchar_fd('\n', 1);
	return (i * page_size);
}


/******************************************************************************/
/******************************************************************************/
static void		*create_block(int cas, t_header **page, size_t size)
{
	t_header	*h;
	t_block *before;
	t_block *current;

	h = *page;
	before = h->last_block;

	if (before->secu_verif != (size_t)before)
	{
		/*nettoyer la memoire*/
		oc_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (NULL);
	}
	current = (void *)before + sizeof(t_block);
	// printf("(debug) ADDR block current = %p, decalage avec addr block_before = %ld\n", current, (void *)current - (void *)before);

	current->secu_verif = (size_t)current;

// printf("(debug) BONUS SECU size_t secu_verif = %zu", current->secu_verif);

	current->ptr = before->ptr + cas;
	current->req_size = size;
	current->previous = before;

	h->last_block = current; //rempli comme une pile je change le pointeur du debut

// printf("(debug) ADDR last_block = %p", h->last_block);
	return (current->ptr);
}




/******************************************************************************/
/******************************************************************************/
static void		*search_empty_block(int cas, t_header **page, size_t size)
{
	t_block	*b;
	t_header *h;

	h = *page;
	b = h->last_block;
	while (b != NULL)
	{
		if (verif_secu(b->secu_verif, (void *)b) == 1)
			return (NULL);
		if (b->req_size == 0)
		{
			b->req_size = size;
			return (b->ptr);
		}
		b = b->previous;
	}
	return(create_block(cas, page, size));
}


/******************************************************************************/
/******************************************************************************/
/*
** Parsing : searching an empty place || create a new page
*/
static void		*search_place(t_header **first, int cas, size_t size)
{
	t_header *tmp;

	tmp = *first;
	while (1)
	{
		if (verif_secu(tmp->secu_verif, (void *)tmp) == 1)
			return (NULL);
		if (tmp->count_alloc > 0)
		{
			tmp->count_alloc--;
			return (search_empty_block(cas, &tmp, size));
		}
		else if (tmp->next == NULL)
			return (header_init(first, cas, size));
		else
			tmp = tmp->next;
	}
}



/******************************************************************************/
/******************************************************************************/
static void	*init_1_block(t_header **page, size_t size)
{
	t_block		*b;
	t_header 	*h;

	h = *page;
	b = h->last_block;
	b->secu_verif = (size_t)b;
	b->ptr = (void *)b + (sizeof(t_block) * h->count_alloc);
	b->req_size = size;
	b->previous = NULL;
	h->count_alloc--;
	return (b->ptr);
}


/******************************************************************************/
/******************************************************************************/
void		*header_init(t_header **first, int cas, size_t size)
{
	t_header	*h;
	t_header	*f;

	//getrlimit
oc_putstr_fd("\n\033[35;1m---------------------APPEL SYS MMAP TINY_SMALL---------------------\n", 1);
	h = mmap(NULL, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
	f = *first;
	h->secu_verif = (size_t)h;
	h->max_alloc = (get_size(cas) - sizeof(t_header)) / (sizeof(t_block) + cas); //total des places libres
	h->count_alloc = h->max_alloc;
	h->last_block =  (void *)h + sizeof(t_header);
oc_putnbr_fd(h->count_alloc, 1);
oc_putstr_fd(" allocs possibles\n\n\033[0m",1);
	if (*first == NULL)
	{
		h->next = NULL;
		if (cas == TI_PADDING)
			glob.tiny = h;
		else if (cas == SM_PADDING)
			glob.small = h;
	}
	else
	{
		while (f->next != NULL)
			f = f->next;
		f->next = h;
		h->next = NULL;
	}
	return (init_1_block(&h, size));
}




/******************************************************************************/
/******************************************************************************/
static void		*header_lg_init(t_header_lg **first, size_t size)
{
	t_header_lg	*h;
	t_header_lg	*f;
	size_t		setsize;

	setsize = get_size((int)size);
	//getrlimit
oc_putstr_fd("\n\033[35;1m---------------------APPEL SYS MMAP LARGE---------------------\n",1);
	h = mmap(NULL, setsize, MMAP_PROT, MMAP_FLAGS, -1, 0);
	f = *first;
	h->secu_verif = (size_t)h;
	h->padding = (int)setsize;
oc_putnbr_fd(h->padding, 1);
oc_putstr_fd("\n\n\033[0m",1);
	h->req_size = size;
	h->ptr = (void *)h + sizeof(t_header_lg);
	if (*first == NULL)
	{
		h->next = NULL;
		glob.large = h;
	}
	else
	{
		while (f->next != NULL)
			f = f->next;
		f->next = h;
		h->next = NULL;
	}
	return (h->ptr);
}




/******************************************************************************/
/******************************************************************************/
static void *parse_malloc_size(size_t size)
{
	if  (size <= TI_MAX && glob.tiny == NULL)
		return (header_init(&(glob.tiny), TI_PADDING, size));
	else if  (size <= TI_MAX && glob.tiny != NULL)
		return (search_place(&(glob.tiny), TI_PADDING, size));
	else if  (size <= SM_MAX && glob.small == NULL)
		return (header_init(&(glob.small), SM_PADDING, size));
	else if  (size <= SM_MAX && glob.small != NULL)
		return (search_place(&(glob.small), SM_PADDING, size));
	else if (size > SM_MAX)
		return (header_lg_init(&(glob.large), size));
	else
		return (NULL);
}




/******************************************************************************/
/******************************************************************************/
//changer le nom de la fonction
void	*malloc(size_t size)
{
	// mutex
	// show_alloc_map();
	if (glob.secu == 1)
	{
		oc_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (NULL);
	}
	if (size <= 0)
	{
		oc_putstr_fd("ERROR MALLOC : size <= 0", 2);
		return (NULL);
	}
	// show_alloc_map();
	return (parse_malloc_size(size));
}

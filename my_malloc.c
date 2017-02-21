/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/21 15:44:12 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

t_map glob;



/******************************************************************************/
/******************************************************************************/
/*
** mapped in multiples of the page size
*/
static size_t	get_size(int cas)
{
	size_t	i;
	size_t	req;
	int		page_size;

	page_size = getpagesize();

	if (cas == TI_PADDING || cas == SM_PADDING)
		req = sizeof(t_header) + (sizeof(t_block) * 100) + (cas * 100);
	else
		req = sizeof(t_header_lg) + cas + (cas * LG_REALLOC);

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
		ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (NULL);
	}
	current = (void *)before + sizeof(t_block);
	printf("(debug) ADDR block current = %p, decalage avec addr block_before = %ld\n", current, (void *)current - (void *)before);

	current->secu_verif = (size_t)current;

printf("(debug) BONUS SECU size_t secu_verif = %zu", current->secu_verif);

	current->ptr = before->ptr + cas;
	current->req_size = size;
	current->previous = before;

	h->last_block = current; //rempli comme une pile je change le pointeur du debut

printf("(debug) ADDR last_block = %p", h->last_block);
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
	// printf("\n(debug) POSITION programme -> search_place\n");
	t_header *tmp;

	tmp = *first;
	while (1)
	{
		if (tmp->secu_verif != (size_t)tmp)
		{
			ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
			glob.bonus_secu = 1;
			return (NULL);
		}
		if (tmp->padding == cas && tmp->count_alloc > 1)
		{
printf("\nok padding\n");
			tmp->count_alloc--;
		printf("\n(debug) VALEUR count_alloc = %d\n", tmp->count_alloc);
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
	printf("\n(debug) POSITION programme -> init_1_block\n\n");
	t_block		*b;
	t_header 	*h;

	h = *page;
	b = h->last_block;
	printf("(debug) ADDR last_block = %p, decalage avec addr page = %ld\n", b, (void *)b - (void *)h);


	b->secu_verif = (size_t)b;
	b->ptr = (void *)b + (sizeof(t_block) * h->count_alloc);
	b->req_size = size;
	b->previous = NULL;
	return (b->ptr);
}


/******************************************************************************/
/******************************************************************************/
void		*header_init(t_header **first, int cas, size_t size)
{
	t_header	*h;
	t_header	*f;

	//getrlimit
	printf("\n\033[35;1m---------------------APPEL SYS MMAP---------------------\n");
	h = (t_header *)mmap(0, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
	printf("(debug) ADDR page MMAP = %p\n", h);
	printf("\n---------------------------------------------------------\033[0m\n\n");


	f = *first;

	h->secu_verif = (size_t)h;
	h->padding = cas;
	h->count_alloc = (get_size(cas) - sizeof(t_header)) / (sizeof(t_block) + cas); //total des places libres
	h->last_block =  (void *)h + sizeof(t_header);

	printf("(debug) h->count_alloc = %d", h->count_alloc);

	if (*first == NULL)
	{
		h->next = NULL;
		glob.tiny_small = h;
	}
	else
	{
		while (f->next != NULL)
			f = f->next;
		f->next = h;
		h->next = NULL;
	printf("\n(debug) ADDR current page = %p\n", h);
	}

	printf("\n(debug) ADDR glob.tiny_small = %p\n", h);

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
	printf("\n\033[35;1m---------------------APPEL SYS MMAP---------------------\n");
	h = (t_header_lg *)mmap(0, setsize, MMAP_PROT, MMAP_FLAGS, -1, 0);
	printf("setsize = %zu", setsize);
	printf("(debug) ADDR page MMAP = %p\n", h);
	printf("\n---------------------------------------------------------\033[0m\n\n");

	f = *first;

	h->secu_verif = (size_t)h;
	h->padding = (int)setsize;
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
	printf("\n(debug) ADDR current page = %p\n", h);
	}

	printf("\n(debug) ADDR glob.large = %p\n", h);

	return (h->ptr);
}




/******************************************************************************/
/******************************************************************************/
static void *parse_malloc_size(size_t size)
{
	if  (size <= TI_MAX && glob.tiny_small == NULL)
		return (header_init(&(glob.tiny_small), TI_PADDING, size));
	else if  (size <= TI_MAX && glob.tiny_small != NULL)
		return (search_place(&(glob.tiny_small), TI_PADDING, size));
	else if  (size <= SM_MAX && glob.tiny_small == NULL)
		return (header_init(&(glob.tiny_small), SM_PADDING, size));
	else if  (size <= SM_MAX && glob.tiny_small != NULL)
		return (search_place(&(glob.tiny_small), SM_PADDING, size));
	else if (size > SM_MAX)
		return (header_lg_init(&(glob.large), size));
	else
		return (NULL);
}




/******************************************************************************/
/******************************************************************************/
//changer le nom de la fonction
void	*my_malloc(size_t size)
{
	// mutex
	if (glob.bonus_secu == 1)
	{
		ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (NULL);
	}
	if (size <= 0)
	{
		ft_putstr_fd("ERROR MALLOC : size <= 0", 2);
		return (NULL);
	}
	return (parse_malloc_size(size));
}

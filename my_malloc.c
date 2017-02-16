/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/16 21:10:08 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

struct s_map glob;



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
static void		*create_block(int cas, t_header **page)
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
	current->req_size = glob.requested_size;
	current->next = before;

	h->last_block = current; //rempli comme une pile je change le pointeur du debut

	return (current->ptr);
}




/******************************************************************************/
/******************************************************************************/
static void	*init_1_block(t_header **page)
{
	printf("\n(debug) POSITION programme -> init_1_block\n\n");
	t_block		*b;
	t_header 	*h;

	h = *page;
	b = h->last_block;
	printf("(debug) ADDR last_block = %p, decalage avec addr page = %ld\n", b, (void *)b - (void *)h);


	b->secu_verif = (size_t)b;
	b->ptr = (void *)b + (sizeof(t_block) * h->count_alloc);
	b->req_size = glob.requested_size;
	b->next = NULL;
	return (b->ptr);
}




/******************************************************************************/
/******************************************************************************/
/*
** Parsing : searching an empty place || create a new page
*/
static void		*search_place(t_header **h, int cas)
{
	printf("\n(debug) POSITION programme -> search_place\n");
	t_header *tmp;

	tmp = *h;
	while (1)
	{
		if (tmp->secu_verif != (size_t)tmp)
		{
			/*nettoyer la memoire*/
			ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
			return (NULL);
		}
		else if (tmp->count_alloc > 1)
		{
			tmp->count_alloc--;
	printf("\n(debug) VALEUR count_alloc = %d\n", tmp->count_alloc);
			return (create_block(cas, h));
		}
		else if (tmp->next == NULL)
			return (page_init(h, cas));
		else
			tmp = tmp->next;
	}
}




/******************************************************************************/
/******************************************************************************/
void		*page_init(t_header **addr, int cas)
{
	t_header	*h;
	t_header	*prev;

	//getrlimit
	printf("\n\033[35;1m---------------------APPEL SYS MMAP---------------------\n");
	h = (t_header *)mmap(0, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
	printf("(debug) ADDR page MMAP = %p\n", h);
	printf("\n---------------------------------------------------------\033[0m\n\n");


	prev = *addr;

	h->secu_verif = (size_t)h;
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
	printf("\n(debug) ADDR previous page = %p", h->previous);
	printf("\n(debug) ADDR current page = %p\n", h);
	}
	if (cas == TI_PADDING)
		glob.tiny = h;
	else if (cas == SM_PADDING)
		glob.small = h;
	return (init_1_block(&h));
}




/******************************************************************************/
/******************************************************************************/
static void		*page_lg_init(t_header_lg **addr)
{
	t_header_lg	*h;
	t_header_lg	*prev;
	size_t		setsize;

	setsize = get_size((int)glob.requested_size);

	//getrlimit
	printf("\n\033[35;1m---------------------APPEL SYS MMAP---------------------\n");
	h = (t_header_lg *)mmap(0, setsize, MMAP_PROT, MMAP_FLAGS, -1, 0);
	printf("setsize = %zu", setsize);
	printf("(debug) ADDR page MMAP = %p\n", h);
	printf("\n---------------------------------------------------------\033[0m\n\n");

	h->secu_verif = (size_t)h;
	h->size = setsize;
	h->req_size = glob.requested_size;
	h->ptr = (void *)h + sizeof(t_header_lg);


	if (*addr == NULL)
	{
		h->next = NULL;
		h->previous = NULL;
	}
	else
	{
		prev = *addr;
		prev->next = h;
		h->previous = prev;
		h->next = NULL;
	printf("\n(debug) ADDR previous page = %p", h->previous);
	printf("\n(debug) ADDR current page = %p\n", h);
	}
	glob.large = h;
	printf("\n(debug) ADDR glob.large = %p\n", h);

	return (h->ptr);
}




/******************************************************************************/
/******************************************************************************/
static void *parse_malloc_size()
{
	if  (glob.requested_size <= TI_MAX && glob.tiny == NULL)
		return (page_init(&(glob.tiny), TI_PADDING));
	else if  (glob.requested_size <= TI_MAX && glob.tiny != NULL)
		return (search_place(&(glob.tiny), TI_PADDING));
	else if  (glob.requested_size <= SM_MAX && glob.small == NULL)
		return (page_init(&(glob.small), SM_PADDING));
	else if  (glob.requested_size <= SM_MAX && glob.small != NULL)
		return (search_place(&(glob.small), SM_PADDING));
	else if (glob.requested_size > SM_MAX)
		return (page_lg_init(&(glob.large)));
	else
		return (NULL);
}




/******************************************************************************/
/******************************************************************************/
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

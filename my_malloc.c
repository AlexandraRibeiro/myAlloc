/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/14 12:38:49 by Alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

struct s_map glob;

/*
** mapped in multiples of the page size
*/
static size_t get_size(int cas)
{
	size_t	i;
	size_t	req;
	int		page_size;

	page_size = getpagesize();

	req = sizeof(t_header) + (sizeof(t_block) * 100) + (cas * 100);
printf("\nsize request = %zu", req);
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


static void	*create_block(int cas, t_header **page)
{
	t_header	*h;
	t_block *before;
	t_block *current;

	h = *page;
	before = h->last_block;
	current = (void *)before + sizeof(t_block);
printf("(debug) ADDR block current = %p, decalage avec addr block_before = %ld\n", current, (void *)current - (void *)before);

	current->secu_verif = (size_t)(current->secu_verif);
	current->ptr = before->ptr + cas;
	current->req_size = glob.size;
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


	b->secu_verif = (size_t)(b->secu_verif);
	b->ptr = (void *)b + (sizeof(t_block) * h->count_alloc);
	b->req_size = glob.size;
	b->next = NULL;
	return (b->ptr);
}

static void		*search_place(t_header *h, int cas)
{
printf("\n(debug) POSITION programme -> search_place\n");
	while (1)
	{
		if (h->count_alloc != 0)
		{
			h->count_alloc--;
printf("(debug) VALEUR count_alloc = %d\n", h->count_alloc);
			return (create_block(cas, &h));
		}
		else if (h->secu_verif != (size_t)(h->secu_verif))
		{
			/*nettoyer la memoire*/
			ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
			return (NULL);
		}
		// else if (h->next == NULL)
		// 	return (create_page(TINY, &h));
		else if (h->next == NULL)
			return (NULL);
		else
			h = h->next;
	}
}

static void		*page_init(t_header **addr, int cas)
{
	t_header	*h;

	//getrlimit
	h = (t_header *)mmap(0, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
printf("(debug) ****************************** APPEL SYS MMAP\n");

/* SIZE t_header */
printf("\n(debug) SIZE de size_t = %lu\n",sizeof(size_t));
printf("(debug) SIZE de int = %lu\n",sizeof(int));
printf("(debug) SIZE de void * = %lu\n",sizeof(void *));
printf("(debug) SIZE de t_header = %lu\n",sizeof(t_header));

	h->secu_verif = (size_t)(h->secu_verif);
	h->count_alloc = (get_size(cas) - sizeof(t_header)) / (sizeof(t_block) + cas); //total des places libres
printf ("(debug) VALEUR count_alloc init = %d", h->count_alloc);

	h->last_block =  (void *)h + sizeof(t_header);
	h->next = NULL;
	h->previous = NULL;

	*addr = h;
	return(init_1_block(&h));
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
	else if  (size < 101 && glob.tiny == NULL)
		return (page_init(&(glob.tiny), TINY));
	else if  (size < 101 && glob.tiny != NULL)
		return (search_place(glob.tiny, TINY));
	else if  (size < 501 && glob.small == NULL)
		return (page_init(&(glob.small), SMALL));
	else if  (size < 501 && glob.small != NULL)
		return (search_place(glob.small, SMALL));
	else
		return (NULL);
}

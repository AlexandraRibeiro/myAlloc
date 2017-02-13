/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:52:10 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/13 18:18:15 by aribeiro         ###   ########.fr       */
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

	req = sizeof(t_page) + (sizeof(t_block) * 100) + (cas * 100);
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


static void	*create_block(int cas, t_page **page)
{
	t_page	*p;
	t_block *before;
	t_block *current;

	p = *page;
	before = p->last_block;
	current = (void *)before + sizeof(t_block);
printf("(debug) ADDR block current = %p, decalage avec addr block_before = %ld\n", current, (void *)current - (void *)before);

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
	t_page 	*p;

printf("\n(debug) POSITION position fonction init_1_block\n");
printf("(debug) SIZE de t_block = %lu\n",sizeof(t_block));
	p = *page;
	b = p->last_block;
printf("(debug) ADDR last_block = %p, decalage avec addr page = %ld\n", b, (void *)b - (void *)p);


	b->secu_verif = (size_t)(b->secu_verif);
	b->ptr = (void *)b + (sizeof(t_block)*100);
	b->req_size = glob.size;
	b->next = NULL;
	return (b->ptr);
}

static void		*search_place(t_page *p, int cas)
{
printf("\n(debug) POSITION programme -> search_place\n");
	while (1)
	{
		if (p->count_alloc != 0)
		{
			p->count_alloc--;
printf("(debug) VALEUR count_alloc = %d\n", p->count_alloc);
			return (create_block(cas, &p));
		}
		else if (p->secu_verif != (size_t)(p->secu_verif))
		{
			/*nettoyer la memoire*/
			ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
			return (NULL);
		}
		// else if (tmp->next == NULL)
		// 	return (create_page(TINY, &tmp));
		else if (p->next == NULL)
			return (NULL);
		else
			p = p->next;
	}
}

static void		*page_init(t_page **addr, int cas)
{
	t_page	*p;

	//getrlimit
	p = (t_page *)mmap(0, get_size(cas), MMAP_PROT, MMAP_FLAGS, -1, 0);
printf("(debug) ****************************** APPEL SYS MMAP\n");

/* SIZE t_PAGE */
printf("\n(debug) SIZE de size_t = %lu\n",sizeof(size_t));
printf("(debug) SIZE de int = %lu\n",sizeof(int));
printf("(debug) SIZE de void * = %lu\n",sizeof(void *));
printf("(debug) SIZE de t_page = %lu\n",sizeof(t_page));

	p->secu_verif = (size_t)(p->secu_verif);
	p->count_alloc = (get_size(cas) - sizeof(t_page)) / (sizeof(t_block) + cas); //total des places libres
printf ("(debug) VALEUR count_alloc init = %d", p->count_alloc);

	p->last_block =  (void *)p + sizeof(t_page);
	p->next = NULL;
	p->previous = NULL;

	*addr = p;
	return(init_1_block(&p));
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

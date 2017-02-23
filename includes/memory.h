/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:01:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 17:58:16 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
// # include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
// # include <stdlib.h>

# define MMAP_PROT		PROT_READ | PROT_WRITE
# define MMAP_FLAGS		MAP_ANON | MAP_PRIVATE

# define TI_REALLOC		1/100
# define TI_MAX			128
# define TI_PADDING		TI_MAX + (TI_MAX * TI_REALLOC)

# define SM_REALLOC		17
# define SM_MAX			1024
# define SM_PADDING		SM_MAX + SM_REALLOC

# define LG_REALLOC		1/100

typedef struct		s_block
{
	size_t				secu_verif; // verifie si les donnees n'ont pas ete alteree
	void				*ptr; //stock le pointeur de la zone memoire allouee
	size_t				req_size; // size demandee avec le malloc
	struct s_block		*previous;
}					t_block;

typedef struct		s_header
{
	size_t				secu_verif; // verifie si les donnees n'ont pas ete alteree
	int					padding;
	int					max_alloc;
	int					count_alloc;
	void				*last_block; // debut de la structure pour les blocks (pile)
	struct s_header		*next;
}					t_header;

typedef struct		s_header_lg
{
	size_t				secu_verif;
	int					padding; //size total
	size_t				req_size;
	void				*ptr;
	struct s_header_lg	*next;
}					t_header_lg;

typedef struct		s_map
{
	int					bonus_secu;
	t_header			*tiny_small;
	t_header_lg			*large;
}					t_map;

/*
** globals
*/
extern t_map glob;



/*_______ MY MALLOC __________________________________________________________*/
void				*malloc(size_t size);
void				*header_init(t_header **addr, int cas, size_t size);
size_t				get_size(int cas);

/*_______ MY FREE ____________________________________________________________*/
void				free(void *ptr);
void				free_header_lg(t_header_lg **head, t_header_lg **previous);
void 				free_header_ts(t_header **head, t_header **previous);

/*_______ MY REALLOC _________________________________________________________*/
void				*realloc(void *ptr, size_t size);

/*_______ Show allocation memory _____________________________________________*/
// void		show_alloc_mem();

/*_______ LIBFT ______________________________________________________________*/
// void				ft_bzero(void *s, size_t n);
// void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
// void				ft_memdel(void **ap);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*_______ BONUS ______________________________________________________________*/
int					verif_secu(size_t secu, void *ptr);
void 				show_alloc_map();

// free_all (libere tous les pointeurs)
// free_all_secure (libere les ptr et reinitialise la memoire a 0 avec bzero)

#endif

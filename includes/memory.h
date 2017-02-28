/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:01:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/28 19:27:56 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
# include <stdio.h>
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

typedef struct		s_maps
{
	int					secu;
	t_header			*tiny;
	t_header			*small;
	t_header_lg			*large;
}					t_maps;

/*
** globals
*/
extern t_maps glob;



/*_______ MY MALLOC __________________________________________________________*/
void				*malloc(size_t size);
void				*header_init(t_header **addr, int cas, size_t size);
size_t				get_size(int cas);

/*_______ MY FREE ____________________________________________________________*/
void				free(void *ptr);
void				free_head_lg(t_header_lg **head, t_header_lg **previous);
void 				free_head_ts(t_header **head, t_header **previous, int cas);

/*_______ MY REALLOC _________________________________________________________*/
void				*realloc(void *ptr, size_t size);

/*_______ Show allocation memory _____________________________________________*/
void				show_alloc_mem();
void 				addr_blocks(void *header, t_block *b, t_block *prev);

/*_______ TOOLS ______________________________________________________________*/
// void				oc_bzero(void *s, size_t n);
// void				*oc_memccpy(void *dst, const void *src, int c, size_t n);
// void				oc_memdel(void **ap);
void				oc_putchar_fd(char c, int fd);
void				oc_putstr_fd(char const *s, int fd);
void 				oc_puthexa(size_t addr);
void				oc_putnbr_fd(int n, int fd);
void				*oc_memcpy(void *dst, const void *src, size_t n);
int					verif_secu(size_t secu, void *ptr);

/*_______ BONUS ______________________________________________________________*/
void 				show_alloc_map();
void 				free_all();

#endif

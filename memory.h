/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:01:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/16 14:51:13 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdlib.h>

# define MMAP_PROT		PROT_READ | PROT_WRITE
# define MMAP_FLAGS		MAP_ANON | MAP_PRIVATE

# define TI_REALLOC		5/100
# define TI_MAX			128
# define TINY			TI_MAX + (TI_MAX * TI_REALLOC)

# define SM_MAX			1024
# define SMALL			SM_MAX + 4

# define LG_REALLOC		1/100

typedef struct		s_block
{
	size_t				secu_verif; // verifie si les donnees n'ont pas ete alteree
	void				*ptr; //stock le pointeur de la zone memoire allouee
	size_t				req_size; // size demandee avec le malloc
	struct s_block		*next;
}					t_block;

/*
** void *last_block : stock ptr of the last block allocated not the first (as a pile)
*/
typedef struct		s_header
{
	size_t				secu_verif; // verifie si les donnees n'ont pas ete alteree
	int					count_alloc;
	void				*last_block; // debut de la structure pour les blocks (pile)
	struct s_header		*next;
	struct s_header		*previous;
}					t_header;

typedef struct		s_header_lg
{
	size_t				secu_verif;
	size_t				size;
	size_t				req_size;
	void				*ptr;
	struct s_header_lg	*next;
	struct s_header_lg	*previous;
}					t_header_lg;

/*
** t_header : stock ptr of the last page created not the first one (as a pile)
*/
struct				s_map
{
	int					flags;
	size_t				requested_size;
	size_t				tiny_realloc;
	size_t				small_realloc;
	size_t				large_realloc;
	t_header			*tiny;
	t_header			*small;
	t_header_lg			*large;
};

extern struct s_map glob;

/*_______ MY MALLOC __________________________________________________________*/
void				*my_malloc(size_t size);
void				*page_init(t_header **addr, int cas);

/*_______ MY FREE ____________________________________________________________*/
// void		free(void *ptr);

/*_______ MY REALLOC _________________________________________________________*/
// void		*realloc(void *ptr, size_t size);

/*_______ Show allocation memory _____________________________________________*/
// void		show_alloc_mem();

/*_______ LIBFT ______________________________________________________________*/
void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				ft_memdel(void **ap);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);

/*_______ BONUS ______________________________________________________________*/
// free_all (libere tous les pointeurs)
// free_all_secure (libere les ptr et reinitialise la memoire a 0 avec bzero)

#endif

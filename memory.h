/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:01:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/12 14:44:19 by aribeiro         ###   ########.fr       */
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

typedef struct		s_block
{
	void			*ptr; //stock le pointeur de la zone memeoire allouee
	size_t			req_size; // size demandee avec le malloc
	size_t			secure_mem; // verifie si les donnees n'ont pas ete alteree
}					t_block;

typedef struct		s_page
{
	int					count;
	t_block				b;
	struct s_page		*next;
	struct s_page		*previous;
}					t_page;

typedef struct		s_map
{
	t_page		tiny;
	t_page		small;
	t_page		large;
}					t_map;

extern t_map glob;


/*_______ MY MALLOC __________________________________________________________*/
void				*my_malloc(size_t size);

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

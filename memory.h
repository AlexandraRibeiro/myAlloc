/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:01:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/09 16:47:39 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
# include <stdio.h>
//# include <stdlib.h>
# include <sys/mman.h>
# include <sys/resource.h>

typedef struct		s_page
{
	int					count;
	void				mem[12800];
	void				ptr[100];
	struct s_tinies		*next;
	struct s_tinies		*previous;
}					t_page;

/*_______ MY MALLOC __________________________________________________________*/
// void		*malloc(size_t size);

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

/*_______ BONUS ______________________________________________________________*/
// free_all (libere tous les pointeurs)
// free_all_secure (libere les ptr et reinitialise la memoire a 0 avec bzero)

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:01:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/02 16:55:41 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>

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
	size_t				secu_verif;
	void				*ptr;
	size_t				req_size;
	struct s_block		*previous;
}					t_block;

typedef struct		s_header
{
	size_t				secu_verif;
	int					max_alloc;
	int					count_alloc;
	void				*last_block;
	struct s_header		*next;
}					t_header;

typedef struct		s_header_lg
{
	size_t				secu_verif;
	int					padding;
	size_t				req_size;
	void				*ptr;
	struct s_header_lg	*next;
}					t_header_lg;

struct				s_maps
{
	int					secu;
	t_header			*tiny;
	t_header			*small;
	t_header_lg			*large;
}				t_maps;

t_maps 				glob;
extern pthread_mutex_t g_mutex;

/*
** _______ MY MALLOC __________________________________________________________
*/
void				*malloc(size_t size);
void				*header_init(t_header **addr, int cas, size_t size);
void				*header_lg_init(t_header_lg **first, size_t size);
size_t				get_size(int cas);

/*
** _______ MY FREE ____________________________________________________________
*/
void				free(void *ptr);
void				free_head_lg(t_header_lg **head, t_header_lg **previous);
void				free_head_ts(t_header **head, t_header **previous, int cas);

/*
** _______ MY REALLOC _________________________________________________________
*/
void				*realloc(void *ptr, size_t size);

/*
** _______ Show allocation memory _____________________________________________
*/
void				show_alloc_mem(void);
void				addr_blocks(t_header *h, t_block *b, t_block *prev, size_t *t);
void				print_in_out_addr(t_block *b, t_header_lg *hl, size_t *t);

/*
** _______ TOOLS ______________________________________________________________
*/
void				oc_putchar_fd(char c, int fd);
void				oc_putstr_fd(char const *s, int fd);
void				oc_puthexa(size_t addr);
void				oc_putnbr_fd(int n, int fd);
void				*oc_memcpy(void *dst, const void *src, size_t n);

/*
** _______ BONUS ______________________________________________________________
*/
void				show_alloc_map(void);
void				free_all(void);
int					verif_secu(size_t secu, void *ptr);

#endif

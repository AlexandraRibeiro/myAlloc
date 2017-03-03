/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock_unlock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:29:13 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/03 17:10:40 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

struct s_maps			glob;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size)
{
	void *ptr;

	ptr = NULL;
	if (glob.secu == 1)
	{
		oc_putstr_fd("\nERROR MALLOC / NOTIFY : data becomes corrupted\n", 2);
		return (NULL);
	}
	if (size <= 0)
	{
		oc_putstr_fd("\nERROR MALLOC : size <= 0\n", 2);
		return (NULL);
	}
	if (pthread_mutex_lock(&g_mutex) == 0)
	{
		ptr = malloc_2(size);
		if (pthread_mutex_unlock(&g_mutex) != 0)
			oc_putstr_fd("\nERROR MALLOC PTHREAD UNLOCK\n", 2);
		return (ptr);
	}
	oc_putstr_fd("\nERROR MALLOC PTHREAD LOCK\n", 2);
	return (ptr);
}

void			free(void *ptr)
{
	if (ptr == NULL)
		return ;
	if (glob.secu == 1)
	{
		oc_putstr_fd("\nFREE / NOTIFY : data becomes corrupted\n", 2);
		return ;
	}
	if (pthread_mutex_lock(&g_mutex) == 0)
	{
		free_2(&ptr);
		if (pthread_mutex_unlock(&g_mutex) != 0)
			oc_putstr_fd("\nERROR FREE PTHREAD UNLOCK\n", 2);
		return ;
	}
	oc_putstr_fd("\nERROR FREE PTHREAD LOCK\n", 2);
}

void			*realloc(void *ptr, size_t size)
{
	void *addr;

	addr = NULL;
	if (size == 0)
		return (NULL);
	if (glob.secu == 1)
	{
		oc_putstr_fd("REALLOC / NOTIFY : data becomes corrupted", 2);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	if (pthread_mutex_lock(&g_mutex) == 0)
	{
		addr = realloc_2(&ptr, size);
		if (pthread_mutex_unlock(&g_mutex) != 0)
			oc_putstr_fd("\nERROR REALLOC PTHREAD UNLOCK\n", 2);
		return (addr);
	}
	oc_putstr_fd("\nERROR REALLOC PTHREAD LOCK\n", 2);
	return (NULL);
}

void			show_alloc_mem(void)
{
	if (glob.secu == 1)
	{
		oc_putstr_fd("ERROR SHOW_ALLOC / NOTIFY : data becomes corrupted", 2);
		return ;
	}
	if (pthread_mutex_lock(&g_mutex) == 0)
	{
		show_alloc_mem_2(0, 0, 0, 0);
		if (pthread_mutex_unlock(&g_mutex) != 0)
			oc_putstr_fd("\nERROR SHOW_ALLOC PTHREAD UNLOCK\n", 2);
		return ;
	}
	oc_putstr_fd("\nERROR SHOW_ALLOC PTHREAD LOCK\n", 2);
}

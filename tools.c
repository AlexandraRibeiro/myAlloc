/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/21 16:40:49 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		verif_secu(size_t secu, void *ptr)
{
	if (secu == (size_t)ptr)
		return (0);
	else
	{
		glob.bonus_secu = 1;
		ft_putstr_fd("ERROR MALLOC / NOTIFY : data becomes corrupted", 2);
		return (1);
	}
}

/*
** Be careful don't touch s_block->previous
*/
void	init_block(t_block **block)
{
	t_block *b;

	b = *block;
	b->req_size = 0;
}

void	free_header_lg(t_header_lg **head, t_header_lg **previous)
{
	t_header_lg *tmp;
	t_header_lg *prev;

	tmp = *head;
	prev = *previous;

	if (prev == NULL && tmp->next == NULL)
		glob.large = NULL;
	else if (prev == NULL && tmp->next != NULL)
		glob.large = tmp->next;
	else
		prev->next = tmp->next;
	if (munmap((void *)tmp, (size_t)tmp->padding) == -1)
	{
		ft_putstr_fd("ERROR MUNMAP()", 2);
		return ;
	}

}

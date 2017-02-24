/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free_munmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:53:38 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/24 16:29:29 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	free_head_lg(t_header_lg **head, t_header_lg **previous)
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
	if (munmap((void *)tmp, tmp->padding) == -1)
		oc_putstr_fd("ERROR MUNMAP()", 2);
}

void 	free_head_ts(t_header **head, t_header **previous, int cas)
{
	t_header 	*tmp;
	t_header 	*prev;
	size_t		setsize;

	tmp = *head;
	prev = *previous;
	setsize = get_size(cas);
	if (prev == NULL && tmp->next != NULL && cas == TI_PADDING)
		glob.tiny = tmp->next;
	else if (prev == NULL && tmp->next != NULL && cas == SM_PADDING)
		glob.small = tmp->next;
	else
		prev->next = tmp->next;
	if (munmap((void *)tmp, setsize) == -1)
		oc_putstr_fd("ERROR MUNMAP()", 2);
}

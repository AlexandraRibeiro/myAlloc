/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:06:09 by aribeiro          #+#    #+#             */
/*   Updated: 2017/03/04 17:29:29 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myalloc.h"

static void		loop_free_ts(t_header **first, int cas)
{
	t_header *h;
	t_header *tmp;

	h = *first;
	tmp = NULL;
	while (h != NULL)
	{
		verif_secu(h->secu_verif, (void *)h);
		free_head_ts(&h, &tmp, cas);
		if (cas == TI_PADDING)
			h = glob.tiny;
		else if (cas == SM_PADDING)
			h = glob.small;
	}
}

static void		loop_free_large(void)
{
	t_header_lg	*l;
	t_header_lg	*tmp;

	l = glob.large;
	tmp = NULL;
	while (l != NULL)
	{
		verif_secu(l->secu_verif, (void *)l);
		free_head_lg(&l, &tmp);
		l = glob.large;
	}
}

void			free_all(void)
{
	if (glob.tiny != NULL)
		loop_free_ts(&(glob.tiny), TI_PADDING);
	if (glob.small != NULL)
		loop_free_ts(&(glob.small), SM_PADDING);
	if (glob.large != NULL)
		loop_free_large();
	oc_putstr_fd("\n************ FREE ALL -> ok\n", 2);
}

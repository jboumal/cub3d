/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:23:08 by vrogiste          #+#    #+#             */
/*   Updated: 2022/08/27 02:32:47 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clst_add_back(t_list *lst, t_node *node)
{
	if (lst && node)
	{
		if (!lst->head)
		{
			lst->head = node;
			node->prev = node;
			node->next = node;
		}
		else
		{
			lst->head->prev->next = node;
			node->prev = lst->head->prev;
			lst->head->prev = node;
			node->next = lst->head;
		}
	}
}

void	clst_rotate(t_list *lst)
{
	if (lst && lst->head)
		lst->head = lst->head->next;
}

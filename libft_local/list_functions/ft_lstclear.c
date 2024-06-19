/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:33:19 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/31 23:15:14 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*this_node;
	t_list	*next_node;

	this_node = *lst;
	while (this_node != NULL)
	{
		next_node = this_node->next;
		del(this_node->content);
		free(this_node);
		this_node = next_node;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:22:03 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/31 23:15:02 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_node;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp_node = *lst;
		while (temp_node->next)
			temp_node = temp_node->next;
		temp_node->next = new;
	}
}

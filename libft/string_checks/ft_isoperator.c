/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoperator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:24:35 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/07 04:16:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isoperator(char c)
{
	int	i;

	i = 0;
	while (OPERATORS[i] != '\0')
	{
		if (c == OPERATORS[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

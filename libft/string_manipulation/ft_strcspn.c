/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:13:03 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/16 21:20:17 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strcspn(const char *str, const char *delimiter)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		j = 0;
		while (delimiter[j])
		{
			if (str[i] == delimiter[j])
				return (len);
			j++;
		}
		i++;
		len++;
	}
	return (len);
}

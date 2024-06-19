/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:45:08 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/07 04:18:51 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strpbrk(const char *str1, const char *str2)
{
	const char	*p = str1;
	const char	*spanp = str2;
	char		c;
	char		sc;

	while (1)
	{
		c = *p++;
		while (1)
		{
			sc = *spanp++;
			if (sc == '\0')
				break ;
			if (c == sc)
				return ((char *)(p - 1));
		}
		if (c == '\0')
			break ;
		spanp = str2;
	}
	return (NULL);
}

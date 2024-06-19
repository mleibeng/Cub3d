/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:42:34 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/07 04:19:28 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strspn(const char *str1, const char *str2)
{
	const char	*p = str1;
	const char	*spanp = str2;
	char		c;
	char		sc;

	while (1)
	{
		c = *p++;
		spanp = str2;
		while (1)
		{
			sc = *spanp++;
			if (sc == '\0')
				break ;
			if (c == sc)
				break ;
		}
		if (sc == '\0')
			return (p - 1 - str1);
		if (c == '\0')
			break ;
	}
	return (p - 1 - str1);
}

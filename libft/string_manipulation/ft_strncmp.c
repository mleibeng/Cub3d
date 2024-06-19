/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:50:08 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/31 23:17:51 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t			i;
	unsigned char	*scmp1;
	unsigned char	*scmp2;

	i = 0;
	scmp1 = (unsigned char *)s1;
	scmp2 = (unsigned char *)s2;
	if (size == 0)
		return (0);
	while (i < size - 1 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (scmp1[i] - scmp2[i]);
		i++;
	}
	return (scmp1[i] - scmp2[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:08:41 by cpuiu             #+#    #+#             */
/*   Updated: 2024/02/26 23:03:46 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*buff;
	int		i;

	buff = (char *)s1;
	buff = malloc(len * sizeof(char) + 1);
	if (!buff)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buff[i] = s1[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

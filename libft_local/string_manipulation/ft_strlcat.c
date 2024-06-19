/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:50:00 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/26 06:32:23 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	size_t	s_i;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	i = d_len;
	s_i = 0;
	if (size == 0)
		return (s_len);
	while (i < size - 1 && src[s_i] != '\0')
	{
		dest[i] = src[s_i];
		i++;
		s_i++;
	}
	dest[i] = '\0';
	if (i >= size)
		return (s_len + size);
	else
		return (s_len + d_len);
}

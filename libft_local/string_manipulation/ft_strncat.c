/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:26:33 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/26 06:54:27 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strncat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_i;

	d_len = ft_strlen(dest);
	s_i = 0;
	while (d_len < size - 1 && src[s_i] != '\0')
	{
		dest[d_len] = src[s_i];
		d_len++;
		s_i++;
	}
	dest[d_len] = '\0';
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 06:26:28 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/26 06:53:57 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	d_len;
	size_t	s_i;

	d_len = ft_strlen(dest);
	s_i = 0;
	if (!src)
		return (dest);
	while (src[s_i] != '\0')
	{
		dest[d_len] = src[s_i];
		d_len++;
		s_i++;
	}
	dest[d_len] = '\0';
	return (dest);
}

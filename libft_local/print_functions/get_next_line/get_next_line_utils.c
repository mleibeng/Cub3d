/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:35:34 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:43 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	if (str == NULL)
		return (NULL);
	i = 0;
	ch = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char *)&str[i]);
		i++;
	}
	if (ch == 0 && str[i] == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_s;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	new_s = (char *)malloc(s_len + 1);
	if (new_s == NULL)
		return (NULL);
	while (i < s_len && s[i] != '\0')
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

// void	*ft_memcpy(void *dest, const void *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dest == NULL && src == NULL)
// 		return (0);
// 	while (i < size)
// 	{
// 		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
// 		i++;
// 	}
// 	return (dest);
// }

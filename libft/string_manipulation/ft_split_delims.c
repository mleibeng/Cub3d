/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delims.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:51 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/16 21:53:17 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_substr_len(char const *str, char const *c)
{
	size_t	count_len;

	count_len = 0;
	while (str && *str != '\0' && !ft_strchr(c, *str))
	{
		count_len++;
		str++;
	}
	return (count_len);
}

size_t	split_arr_len(char const *s, char const *c)
{
	size_t	string_count;
	size_t	alarm;

	string_count = 0;
	alarm = 0;
	while (ft_strchr(c, *s) && *s)
		s++;
	while (*s)
	{
		if (!ft_strchr(c, *s) && alarm == 0)
		{
			alarm = 1;
			string_count++;
		}
		if (ft_strchr(c, *s) && alarm == 1)
			alarm = 0;
		s++;
	}
	return (string_count);
}

void	*ft_free(char **split_arr, size_t i)
{
	while (i--)
		free(split_arr[i]);
	free(split_arr);
	return (NULL);
}

char	**ft_split_delims(char const *s, char *delimiters)
{
	char	**split_arr;
	size_t	string_count;
	size_t	i;
	size_t	j;
	size_t	s_len;

	i = 0;
	string_count = split_arr_len(s, delimiters);
	split_arr = (char **)malloc((string_count + 1) * sizeof(char *));
	while (*s && ft_strchr(delimiters, *s))
		s++;
	while (i < string_count && *s)
	{
		split_arr[i] = malloc((s_len = ft_substr_len(s, delimiters)) + 1);
		if (!split_arr[i])
			return (ft_free(split_arr, i));
		j = 0;
		while (j < s_len)
			split_arr[i][j++] = *s++;
		split_arr[i++][s_len] = '\0';
		while (*s && ft_strchr(delimiters, *s))
			s++;
	}
	split_arr[i] = NULL;
	return (split_arr);
}

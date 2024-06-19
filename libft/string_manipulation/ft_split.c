/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:51 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/23 20:16:22 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_ssubstr_len(char const *str, char c)
{
	size_t	count_len;

	count_len = 0;
	while (str && *str != '\0' && *str != c)
	{
		count_len++;
		str++;
	}
	return (count_len);
}

size_t	ssplit_arr_len(char const *s, char c)
{
	size_t	string_count;
	size_t	alarm;

	string_count = 0;
	alarm = 0;
	while (*s)
	{
		if (*s != c && alarm == 0)
		{
			alarm = 1;
			string_count++;
		}
		if (*s == c && alarm == 1)
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

char	**ft_split(char const *s, char c)
{
	char	**split_arr;
	size_t	string_count;
	size_t	i;
	size_t	j;
	size_t	s_len;

	i = 0;
	string_count = ssplit_arr_len(s, c);
	split_arr = (char **)malloc((string_count + 1) * sizeof(char *));
	while (i < string_count && *s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		split_arr[i] = malloc((s_len = ft_ssubstr_len(s, c)) + 1);
		if (!split_arr[i])
			return (ft_free(split_arr, i));
		j = 0;
		while (j < s_len)
			split_arr[i][j++] = *s++;
		split_arr[i++][s_len] = '\0';
	}
	split_arr[i] = NULL;
	return (split_arr);
}

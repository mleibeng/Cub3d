/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 02:59:46 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/05 23:11:47 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// I need this at last :(

size_t	ft_token_len(char const *str, char const *c)
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

char	*ft_strtok(char *in, const char *delimiters)
{
	int			substr_len;
	char		*out;
	static char	*breakpoint;

	if (in != NULL)
		breakpoint = in;
	if (breakpoint == NULL || *breakpoint == '\0')
		return (NULL);
	substr_len = ft_token_len(breakpoint, delimiters);
	out = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, breakpoint, substr_len + 1);
	while (*breakpoint != '\0' && !ft_strchr(delimiters, *breakpoint))
		breakpoint++;
	if (*breakpoint != '\0')
		breakpoint++;
	else
		breakpoint = NULL;
	return (out);
}

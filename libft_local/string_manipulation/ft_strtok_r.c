/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:48:48 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:17:22 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtok_r(char *str, const char *delim, char **save_ptr)
{
	char	*tok;

	if (!str)
		str = *save_ptr;
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}
	tok = str;
	str = ft_strpbrk(tok, delim);
	if (!str)
		*save_ptr = ft_strchr(tok, '\0');
	else
	{
		*str = '\0';
		*save_ptr = str + 1;
	}
	return (tok);
}

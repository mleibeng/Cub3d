/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:53 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:16:40 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char *)&str[i]);
		i++;
	}
	if (ch == '\0' && str[i] == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

// #include <stdio.h>

// int main(void)
// {
//     char s[ ] = "abcbc";
//     printf( "this should return (cbc so it is %s\n", ft_strchr(s, 'c')));
//     return (0);
// }
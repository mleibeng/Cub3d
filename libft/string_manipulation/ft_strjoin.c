/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:58 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/26 12:31:51 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_s;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL)
		len_s1 = 0;
	else
		len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_s = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_memcpy(new_s, s1, len_s1);
	ft_memcpy(new_s + len_s1, s2, len_s2);
	new_s[len_s2 + len_s1] = '\0';
	return (new_s);
}

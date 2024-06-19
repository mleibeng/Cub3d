/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:59:46 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:16:48 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_s;

	s_len = ft_strlen(s);
	new_s = (char *)malloc(s_len + 1);
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s, s_len + 1);
	return (new_s);
}

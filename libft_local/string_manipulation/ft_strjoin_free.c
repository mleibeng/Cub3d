/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:19:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/04/01 22:52:15 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char *new_var, char *value, int i)
{
	char	*joined;
	int		len1;
	int		len2;

	len1 = ft_strlen(new_var);
	len2 = ft_strlen(value);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, new_var, len1);
	ft_memcpy(joined + len1, value, len2);
	joined[len1 + len2] = '\0';
	if (i == 1)
		free(new_var);
	else if (i == 2)
		free(value);
	else if (i == 3)
	{
		free(new_var);
		free(value);
	}
	return (joined);
}

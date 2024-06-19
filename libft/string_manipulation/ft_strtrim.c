/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:50:16 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/05 23:15:28 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s_trim;
	size_t	e_trim;

	s_trim = 0;
	e_trim = ft_strlen(s1);
	while (s_trim < e_trim)
	{
		if (ft_strchr(set, s1[s_trim]) == NULL)
			break ;
		s_trim++;
	}
	while (e_trim > 0)
	{
		if (ft_strchr(set, s1[e_trim - 1]) == NULL)
			break ;
		e_trim--;
	}
	return (ft_substr(s1, s_trim, e_trim - s_trim));
}

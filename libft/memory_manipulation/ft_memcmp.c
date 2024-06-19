/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:32 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/31 23:15:55 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *a1, const void *a2, size_t size)
{
	size_t				i;
	const unsigned char	*as1;
	const unsigned char	*as2;

	i = 0;
	as1 = ((const unsigned char *)a1);
	as2 = ((const unsigned char *)a2);
	while (i < size)
	{
		if (as1[i] != as2[i])
			return (as1[i] - as2[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:36 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:20 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_movedown(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = size - 1;
	while (i > 0)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i--;
	}
	((unsigned char *)dest)[0] = ((const unsigned char *)src)[0];
}

static void	ft_moveup(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*memdst;
	const unsigned char	*memsrc;

	memdst = (unsigned char *)dest;
	memsrc = (const unsigned char *)src;
	if (dest == src || size == 0)
	{
		return (dest);
	}
	if ((memdst) > (memsrc))
		ft_movedown(memdst, memsrc, size);
	else
		ft_moveup(memdst, memsrc, size);
	return (dest);
}

// void	*ft_memmove(void *dest, const void *src, size_t size)
// {
// 	size_t				i;

// 	if (dest == src || size == 0)
// 		return (dest);
// 	if (((unsigned char *)dest) > ((const unsigned char *)src))
// 	{
// 		i = size - 1;
// 		while (i > 0)
// 		{
// 			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
// 			i--;
// 		}
// 		((unsigned char *)dest)[0] = ((const unsigned char *)src)[0];
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (i < size)
// 		{
// 			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
// 			i++;
// 		}
// 	}
// 	return (dest);
// }

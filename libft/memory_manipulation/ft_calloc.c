/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:35:58 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/31 23:15:48 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*allocate_memory;

	total_size = num_elements * element_size;
	allocate_memory = malloc(total_size * sizeof(char));
	if (allocate_memory != NULL)
	{
		ft_memset(allocate_memory, 0, total_size);
		return (allocate_memory);
	}
	else
		return (NULL);
}

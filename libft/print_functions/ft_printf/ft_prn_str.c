/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prn_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:58:39 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:37 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prn_str(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (write(1, s, i));
}

int	ft_test_str(const char *format)
{
	size_t	len;

	if (format == NULL)
	{
		len = ft_prn_str("(null)");
		return ((int)len);
	}
	else
		len = ft_prn_str(format);
	return ((int)len);
}

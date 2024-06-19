/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prn_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:23:54 by mleibeng          #+#    #+#             */
/*   Updated: 2023/10/16 16:21:11 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prn_hex(unsigned int n, char format)
{
	const char	*hex_small;
	const char	*hex_big;
	const char	*hexdigit;
	int			len;
	int			result;

	hex_small = "0123456789abcdef";
	hex_big = "0123456789ABCDEF";
	if (format == 'x')
		hexdigit = hex_small;
	else
		hexdigit = hex_big;
	len = 1;
	if (n / 16 != 0)
	{
		result = ft_prn_hex(n / 16, format);
		if (result == -1)
			return (result);
		len += result;
	}
	result = ft_prn_char(hexdigit[n % 16]);
	if (result == -1)
		return (result);
	return (len);
}

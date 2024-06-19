/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prn_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:27:23 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define BUF_SIZE 32

int	ft_prn_ptr(uintptr_t ptr)
{
	char	buf[BUF_SIZE];
	int		len;
	int		i;
	int		result;

	len = 0;
	if (ptr == 0)
		buf[len++] = '0';
	else
		len = ft_calc_hex(ptr, len, buf);
	buf[len++] = 'x';
	buf[len++] = '0';
	i = len - 1;
	while (i >= 0)
	{
		result = ft_prn_char(buf[i]);
		if (result == -1)
			return (result);
		i--;
	}
	return (len);
}

int	ft_calc_hex(uintptr_t address, int len, char *buf)
{
	int		digits;
	char	hex;

	digits = address % 16;
	if (digits < 10)
		hex = '0' + digits;
	else
		hex = 'a' + digits - 10;
	buf[len++] = hex;
	if (address >= 16)
		len = ft_calc_hex(address / 16, len, buf);
	return (len);
}

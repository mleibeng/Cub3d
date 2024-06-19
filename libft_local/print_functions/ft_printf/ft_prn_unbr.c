/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prn_unbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:09:03 by mleibeng          #+#    #+#             */
/*   Updated: 2024/02/16 21:48:32 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_calc(unsigned int n)
{
	int	len;
	int	result;

	len = 1;
	result = ft_prn_char('-');
	if (result == -1)
		return (result);
	n = -n;
	len++;
	if (n / 10 != 0)
	{
		result = ft_putnbr_calc(n / 10);
		if (result == -1)
			return (result);
		len += result;
	}
	result = ft_prn_char(n % 10 + '0');
	if (result == -1)
		return (result);
	return (len);
}

int	ft_prn_unbr(unsigned int n)
{
	if (n == 0)
		return (ft_prn_char('0'));
	else
		return (ft_putunbr_calc(n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prn_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:54:59 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:33 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// need to change all my standardized functions to int
// so they return a value that i can give back to printf

int	ft_putnbr_calc(int n)
{
	int	len;
	int	result;

	len = 1;
	if (n < 0)
	{
		result = ft_prn_char('-');
		if (result == -1)
			return (result);
		n = -n;
		len++;
	}
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

int	ft_prn_nbr(int n)
{
	if (n == 0)
		return (ft_prn_char('0'));
	else if (n == -2147483648)
		return (ft_prn_str("-2147483648"));
	else
		return (ft_putnbr_calc(n));
}

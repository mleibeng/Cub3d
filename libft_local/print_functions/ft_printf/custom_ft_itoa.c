/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_ft_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:02:15 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/07 01:15:16 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_zero_or_neg(int *is_neg, int *n, int *i, char *buf)
{
	if (*n == 0)
	{
		buf[(*i)++] = '0';
		buf[(*i)] = '\0';
		return (1);
	}
	if (*n < 0)
	{
		*is_neg = 1;
		*n = -(*n);
	}
	return (0);
}

void	custom_ft_itoa(int n, char *buf)
{
	int	i;
	int	is_neg;
	int	temp;

	i = 0;
	is_neg = 0;
	if (is_zero_or_neg(&is_neg, &n, &i, buf))
		return ;
	temp = n;
	while (temp)
	{
		i++;
		temp /= 10;
	}
	buf[i] = '\0';
	i--;
	if (is_neg)
		buf[0] = '-';
	while (n)
	{
		buf[is_neg + i--] = (n % 10) + '0';
		n /= 10;
	}
}

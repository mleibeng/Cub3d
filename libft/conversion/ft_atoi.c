/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:17 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/10 03:31:25 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_space_checker(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_calcs(char c)
{
	int	number;

	number = c - '0';
	return (number);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		alarm;
	long	result;

	if (!str)
		return (0);
	i = ft_space_checker(str);
	result = 0;
	alarm = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		alarm = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + ft_calcs(str[i]);
		else if (str[i] < '0' || str[i] > '9')
			return (alarm * result);
		i++;
	}
	return (alarm * result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:04:21 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/07 02:51:16 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_whitespace_checker(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_calc(char c)
{
	int	number;

	number = c - '0';
	return (number);
}

void	signcheck(const char *str, int *i, int *alarm)
{
	if (str[(*i)] == '+')
		(*i)++;
	else if (str[(*i)] == '-')
	{
		*alarm = -1;
		(*i)++;
	}
}

int	ft_strtoi(const char *str, char **end)
{
	int		i;
	int		alarm;
	long	result;

	if (!str)
		return (0);
	i = ft_whitespace_checker(str);
	result = 0;
	alarm = 1;
	signcheck(str, &i, &alarm);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + ft_calc(str[i]);
		else
			break ;
		i++;
	}
	if (end)
		*end = (char *)&str[i];
	return (alarm * result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *end;
// 	printf("%d, %c", ft_strtoi("2147483647", &end), *end);
// 	return (0);
// }
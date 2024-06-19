/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:26 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/06 13:22:24 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_switch(char *a, long arr_size)
{
	int		i;
	char	b;

	i = 0;
	while (i < arr_size)
	{
		b = a[i];
		a[i] = a[arr_size];
		a[arr_size] = b;
		i++;
		arr_size--;
	}
}

size_t	ft_check_negative(long m)
{
	size_t	i;

	i = 0;
	if (m < 0)
		i = 1;
	return (i);
}

char	*ft_fillarray(char *a, long m)
{
	size_t	i;
	size_t	minus;

	i = 0;
	minus = 0;
	if (ft_check_negative(m) == 1)
	{
		m = -m;
		minus = 1;
	}
	while (m != 0)
	{
		a[i] = m % 10 + '0';
		m = m / 10;
		i++;
	}
	if (minus == 1)
	{
		a[i] = '-';
		i++;
	}
	a[i] = '\0';
	return (a);
}

int	ft_count_digits(long m)
{
	int	digits;
	int	temp;
	int	negative;

	negative = ft_check_negative(m);
	digits = 0;
	temp = m;
	if (negative == 1)
		digits++;
	if (temp == 0)
		return (1);
	while (temp != 0)
	{
		temp /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	long	m;
	int		digits;
	size_t	i;
	char	*a;

	m = n;
	digits = ft_count_digits(m);
	i = 0;
	a = (char *)malloc((digits + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	if (m == 0)
	{
		a[i] = '0';
		i++;
	}
	else
	{
		a = ft_fillarray(a, m);
		i = ft_strlen(a);
		ft_switch(a, i - 1);
	}
	a[i] = '\0';
	return (a);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     int num = 0;
//     char *result = ft_itoa(num);
//     if (result != NULL) {
//         printf("Integer as a string: %s\n", result);
//         free(result);
//     } else {
//         printf("Memory allocation failed.\n");
//     }
//     return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:49:46 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:57 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int				len;
	unsigned int	nb;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		nb = -n;
	}
	else
		nb = n;
	if (nb >= 10)
		len += ft_putnbr_fd(nb / 10, fd);
	len += ft_putchar_fd(nb % 10 + '0', fd);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:38:13 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/07 01:15:23 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(int fd, const char *format, ...)
{
	int		len;
	va_list	args;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
				len += ft_putstr_fd(va_arg(args, char *), fd);
			else if (*format == 'd')
				len += ft_putnbr_fd(va_arg(args, int), fd);
			else if (*format == 'c')
				len += ft_putchar_fd(va_arg(args, int), fd);
		}
		else
			len += ft_putchar_fd(*format, fd);
		format++;
	}
	va_end(args);
	return (len);
}

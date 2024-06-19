/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:11:41 by mleibeng          #+#    #+#             */
/*   Updated: 2024/03/25 23:15:28 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prn_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_va_arg_con(va_list args, const char format)
{
	if (format == 'c')
		return (ft_prn_char(va_arg(args, int)));
	else if (format == 's')
		return (ft_test_str(va_arg(args, const char *)));
	else if (format == 'p')
		return (ft_prn_ptr(va_arg(args, uintptr_t)));
	else if (format == 'i' || format == 'd')
		return (ft_prn_nbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_prn_unbr(va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_prn_hex(va_arg(args, unsigned int), format));
	else if (format == '%')
		return (ft_prn_char('%'));
	else
		return (-1);
}

int	ft_print_string(const char *format, va_list args)
{
	size_t	i;
	int		len;
	int		result;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			result = ft_va_arg_con(args, *(format + ++i));
			if (result == -1)
				return (result);
			len += result;
		}
		else
		{
			result = ft_prn_char(format[i]);
			if (result == -1)
				return (result);
			len += result;
		}
		i++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	if (format == NULL || *format == '\0')
		return (0);
	len = ft_print_string(format, args);
	va_end(args);
	return (len);
}

// Things I need:
// 	* switch(not allowed) statement to handle all different format specifiers.
// 	(Probably going to use a if->if/else function which checks for these cases)
// 	* a va_arg list which takes a variable number of arguments
//	(needs va_start/va_end and maybe va_copy for struct handling !
//	Need to inform myself of how they work!!!!)
// 	Each va_arg list node should have a corresponding function
//		to printf out the specified value
//	i.e.: %d should use itoa.c or putnbr_fd
// 	to convert and print

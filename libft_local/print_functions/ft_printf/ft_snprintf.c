/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:22:24 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/04/23 19:55:12 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_format_specifier(t_helper *helper, int size)
{
	if (*helper->fmt == 's')
		handle_s(helper, size);
	else if (*helper->fmt == 'd')
		handle_d(helper, size);
	else if (*helper->fmt == 'c')
		handle_c(helper, size);
	helper->fmt++;
}

void	process_format_specifiers(t_helper *helper, int size)
{
	while (*helper->fmt && (helper->ptr - helper->str) < size - 1)
	{
		if (*helper->fmt == '%')
		{
			helper->fmt++;
			handle_format_specifier(helper, size);
		}
		else
		{
			if ((helper->ptr - helper->str) < size - 1)
			{
				*helper->ptr++ = *helper->fmt++;
				helper->len++;
			}
			else
			{
				helper->len = -1;
				break ;
			}
		}
	}
}

int	ft_snprintf(char *str, int size, const char *format, ...)
{
	t_helper	helper;

	va_start(helper.args, format);
	init_helper(&helper, str, format);
	process_format_specifiers(&helper, size);
	if (size > 0)
		*helper.ptr = '\0';
	va_end(helper.args);
	if (helper.len >= 0)
		return (helper.len);
	else
		return (helper.len + size);
}

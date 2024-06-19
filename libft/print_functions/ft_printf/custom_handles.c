/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_handles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:33:22 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/23 19:55:38 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_helper(t_helper *helper, char *str, const char *format)
{
	helper->len = 0;
	helper->ptr = str;
	helper->str = str;
	helper->fmt = format;
}

void	handle_s(t_helper *helper, int size)
{
	helper->str_val = va_arg(helper->args, char *);
	helper->num_len = ft_strlen(helper->str_val);
	if (helper->num_len < size - (helper->ptr - helper->buf))
	{
		ft_strcpy(helper->ptr, helper->str_val);
		helper->ptr += helper->num_len;
	}
	else
	{
		ft_strncpy(helper->ptr, helper->str_val, size - (helper->ptr
				- helper->buf) - 1);
		helper->ptr += size - (helper->ptr - helper->buf) - 1;
	}
	helper->len += helper->num_len;
}

void	handle_d(t_helper *helper, int size)
{
	helper->int_val = va_arg(helper->args, int);
	custom_ft_itoa(helper->int_val, helper->buf);
	helper->num_len = ft_strlen(helper->buf);
	if (helper->num_len < size - (helper->ptr - helper->buf))
	{
		ft_strcpy(helper->ptr, helper->buf);
		helper->ptr += helper->num_len;
	}
	else
	{
		ft_strncpy(helper->ptr, helper->buf, size - (helper->ptr - helper->buf)
			- 1);
		helper->ptr += size - (helper->ptr - helper->buf) - 1;
	}
	helper->len += helper->num_len;
}

void	handle_c(t_helper *helper, int size)
{
	helper->char_val = (char)va_arg(helper->args, int);
	if ((helper->ptr - helper->buf) < size - 1)
	{
		*helper->ptr++ = helper->char_val;
		helper->len++;
	}
	else
		helper->len = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:34:35 by mleibeng          #+#    #+#             */
/*   Updated: 2024/04/23 19:41:32 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "../../libft.h"

typedef struct s_helper
{
	va_list		args;
	int			len;
	const char	*fmt;
	char		*ptr;
	char		*str;
	char		*str_val;
	int			int_val;
	int			num_len;
	char		char_val;
	char		buf[20];
}				t_helper;

/*Printf functions*/
int				ft_va_arg_con(va_list args, const char format);
int				ft_printf(const char *format, ...);
/*Calc functions*/
int				ft_calc_hex(uintptr_t address, int len, char *buf);
int				ft_putnbr_calc(int n);
int				ft_putunbr_calc(unsigned int n);
/*Conversion functions*/
int				ft_test_str(const char *format);
int				ft_prn_ptr(uintptr_t ptr);
int				ft_prn_nbr(int n);
int				ft_prn_unbr(unsigned int n);
int				ft_prn_hex(unsigned int n, char x);
void			custom_ft_itoa(int n, char *buf);
/*utils*/
int				ft_prn_str(const char *s);
int				ft_prn_char(char c);
size_t			ft_strlen(const char *s);
void			init_helper(t_helper *helper, char *str, const char *format);
void			handle_s(t_helper *helper, int size);
void			handle_d(t_helper *helper, int size);
void			handle_c(t_helper *helper, int size);

#endif
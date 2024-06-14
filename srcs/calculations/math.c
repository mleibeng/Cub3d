/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:22:29 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/14 18:24:03 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	rounds the fractional part of an float number down to an int
int	ft_ro(float num)
{
	if (get_fractional_part(num) < 0.005f)
		return (round(num));
	return ((int)num);
}

//	function to normalize an angle, so it stays in the range of 2 x PI (radians)
float	norm_ang(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

//	function to get the fractional part of a number in double or float
double	get_fractional_part(double num)
{
	double	integral_part;
	double	fractional_part;

	fractional_part = modf(num, &integral_part);
	return (fractional_part);
}

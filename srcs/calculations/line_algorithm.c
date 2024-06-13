/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:25 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/13 20:41:13 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to check if there is an error with the pixel position
int	check_error_pixel(t_coord *pt_a, t_coord *pt_b, int *x0, int *y0)
{
	static int	err = INT_MAX;

	if (err == INT_MAX)
		err = abs(pt_b->xw - pt_a->xw) - abs(pt_b->yw - pt_a->yw);
	if (*x0 == (pt_b->xw) && *y0 == pt_b->yw)
		return (err = INT_MAX, err);
	if ((2 * err) > -abs(pt_b->yw - pt_a->yw))
	{
		err -= abs(pt_b->yw - pt_a->yw);
		if (pt_a->xw < pt_b->xw)
			*x0 += 1;
		else
			*x0 -= 1;
	}
	else if ((2 * err) < abs(pt_b->xw - pt_a->xw))
	{
		err += abs(pt_b->xw - pt_a->xw);
		if (pt_a->yw < pt_b->yw)
			*y0 += 1;
		else
			*y0 -= 1;
	}
	return (err);
}

//	function to check, if a point is on a line between two points:
//	((Px - Ax)(By - Ay) - (Py -Ay)(Bx - Ax)) == 0 (A = cur, B = next)
//	then a check if point is between the points A and B
//	laslty calculate the z axis of P with , and dislpay it
void	draw_line(t_app *app, t_coord point_a, t_coord point_b)
{
	int		x0;
	int		y0;
	int		err;

	if (app == NULL)
		return ;
	x0 = point_a.xw;
	y0 = point_a.yw;
	while (1)
	{
		if (x0 > 0 && x0 < app->window_width
			&& y0 > 0 && y0 < app->window_height)
			mlx_put_pixel(app->compass, x0, y0, point_a.color);
		err = check_error_pixel(&point_a, &point_b, &x0, &y0);
		if (err == INT_MAX)
			break ;
	}
}

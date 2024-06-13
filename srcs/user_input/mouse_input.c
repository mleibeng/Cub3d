/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 08:40:59 by flo               #+#    #+#             */
/*   Updated: 2024/06/13 22:15:56 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	checks if the mouse button clicked and the pointer in the image
int	check_mouse_clicked(t_app *app, int x, int y, enum mouse_key key)
{
	if (mlx_is_mouse_down(app->mlx, key))
	{
		if (x > 0 && x < app->window_width && y > 0 && y < app->window_height)
		{
			return (1);
		}
		if (x > 0 && x < app->window_width && y > 0 && y < app->window_height)
		{
			app->weapon->state = ACTIVE;
			return (1);
		}
	}
	return (0);
}

//	calculates the shift of the rotation, with the left button clicked
int	mouse_shift(t_app *app)
{
	static int	previous_x = -1;
	int			x;
	int			y;
	int			change_x;

	mlx_get_mouse_pos(app->mlx, &x, &y);
	if (check_mouse_clicked(app, x, y, MLX_MOUSE_BUTTON_LEFT) == 1)
	{
		if (previous_x != -1 && previous_x != x)
		{
			change_x = x - previous_x;
			app->player.angle += change_x * 0.005;
		}
		previous_x = x;
	}
	else
	{
		previous_x = -1;
	}
	return (0);
}

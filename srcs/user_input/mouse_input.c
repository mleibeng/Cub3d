/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 08:40:59 by flo               #+#    #+#             */
/*   Updated: 2024/06/19 18:34:59 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// checks if the mouse button is clicked and the pointer is in the image
int	check_mouse_clicked(t_app *app, int x, int y, enum mouse_key key)
{
	static int	right_key_pressed = 0;

	if (mlx_is_mouse_down(app->mlx, key))
	{
		if (key == MLX_MOUSE_BUTTON_RIGHT)
		{
			if (!right_key_pressed)
			{
				right_key_pressed = 1;
				mlx_set_mouse_pos(app->mlx, app->window_width / 2,
					app->window_height / 2);
				return (1);
			}
		}
		if (x > 0 && x < app->window_width && y > 0 && y < app->window_height)
			return (1);
	}
	else if (key == MLX_MOUSE_BUTTON_RIGHT)
		right_key_pressed = 0;
	return (0);
}

// calculates the shift of the rotation, with the left button clicked
int	mouse_shift(t_app *app)
{
	static int	previous_x = -1;
	static int	mouse_set = 0;
	int			x;
	int			y;

	mlx_get_mouse_pos(app->mlx, &x, &y);
	if (check_mouse_clicked(app, x, y, MLX_MOUSE_BUTTON_LEFT) == 1
		&& mouse_set == 0)
		mouse_set = 1;
	if (check_mouse_clicked(app, x, y, MLX_MOUSE_BUTTON_RIGHT) == 1)
		mouse_set = 0;
	if (mouse_set == 1)
	{
		if (previous_x != -1 && previous_x != x)
			app->player.angle += (x - previous_x) * 0.005;
		mlx_set_mouse_pos(app->mlx, app->window_width / 2,
			app->window_height / 2);
		mlx_get_mouse_pos(app->mlx, &x, &y);
		return (previous_x = x, 0);
	}
	mlx_set_mouse_pos(app->mlx, app->window_width / 2, app->window_height / 2);
	return (previous_x = -1, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:37:06 by flo               #+#    #+#             */
/*   Updated: 2024/06/09 23:33:58 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Function to clear the compass background
void	clear_compass(mlx_image_t *img, int32_t background_color)
{
	int	y;
	int	x;
	int	dx;
	int	dy;

	y = 0;
	while (y < COMPASS_SIZE)
	{
		x = 0;
		while (x < COMPASS_SIZE)
		{
			dx = x - CENTER;
			dy = y - CENTER;
			if (dx * dx + dy * dy <= CENTER * CENTER)
				mlx_put_pixel(img, x, y, background_color);
			x++;
		}
		y++;
	}
}

//	draw the compass ring
void	draw_compass_ring(mlx_image_t *compass, int32_t color)
{
	int	thickness;
	int	angle;
	int	x;
	int	y;

	thickness = 0;
	while (thickness < 3)
	{
		angle = 0;
		while (angle < 360)
		{
			x = CENTER + (CENTER - 1 - thickness) * cos(angle * M_PI / 180);
			y = CENTER + (CENTER - 1 - thickness) * sin(angle * M_PI / 180);
			if (x > 0 && y > 0 && x <= WINDOW_WIDTH && y <= WINDOW_HEIGHT)
				mlx_put_pixel(compass, x, y, color);
			angle += 5;
		}
		thickness++;
	}
}

// Function to create and display the compass
void	display_compass(t_app *app, float player_angle)
{
	int32_t	color;
	int		needle_length;
	int32_t	background_color;

	color = CLEAR;
	background_color = BLACK;
	//clear_compass(app->compass, background_color);
	draw_compass_ring(app->compass, color);
	draw_line(app, init_coord(CENTER, CENTER, color),
		init_coord(CENTER, COMPASS_SIZE, color));
	draw_line(app, init_coord(CENTER, CENTER, color),
		init_coord(CENTER, -COMPASS_SIZE, color));
	draw_line(app, init_coord(CENTER, CENTER, color),
		init_coord(CENTER + COMPASS_SIZE, CENTER, color));
	draw_line(app, init_coord(CENTER, CENTER, color),
		init_coord(CENTER - COMPASS_SIZE, CENTER, color));
	needle_length = CENTER - 5;
	app->needle_x = CENTER + needle_length * cos(player_angle);
	app->needle_y = CENTER + needle_length * sin(player_angle);
	draw_line(app, init_coord(CENTER, CENTER, 0xFF0000CC),
		init_coord(app->needle_x, app->needle_y, 0xFF0000CC));
}

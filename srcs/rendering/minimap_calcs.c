/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_calcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:25:52 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 19:20:27 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_mini_map(mlx_image_t *img, int32_t background_color)
{
	int	y;
	int	x;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		y = 0;
		while (y < MINIMAP_SIZE)
		{
			mlx_put_pixel(img, x, y, background_color);
			y++;
		}
		x++;
	}
}

void	rotate_point(t_vec *xy, float angle, int cy)
{
	int		new_x;
	int		new_y;
	float	s;
	float	c;

	s = sin(angle);
	c = cos(angle);
	new_x = (int)(((xy->x - cy) * c - (xy->y - cy) * s) + cy);
	new_y = (int)(((xy->x - cy) * s + (xy->y - cy) * c) + cy);
	xy->x = new_x;
	xy->y = new_y;
}

void	put_player_mini(t_app *app)
{
	int	py;
	int	px;

	px = -2;
	while (px <= 2)
	{
		py = -2;
		while (py <= 2)
		{
			mlx_put_pixel(app->minimap_img, app->mini_info.half_size + px,
				app->mini_info.half_size + py, RED);
			py++;
		}
		px++;
	}
}

void	calculate_xy_coordinates(t_app *app, t_vec map, t_vec minimap)
{
	app->mini_info.xy.x = (map.x * app->mini_info.wall_size + minimap.x)
		- app->player.x * app->mini_info.wall_size + app->mini_info.half_size;
	app->mini_info.xy.y = (map.y * app->mini_info.wall_size + minimap.y)
		- app->player.y * app->mini_info.wall_size + app->mini_info.half_size;
	app->mini_info.xy.x = MINIMAP_SIZE - app->mini_info.xy.y - 1;
}

int	is_within_minimap_bounds(t_app *app)
{
	return (app->mini_info.xy.x >= 0 && app->mini_info.xy.x < MINIMAP_SIZE
		&& app->mini_info.xy.y >= 0 && app->mini_info.xy.y < MINIMAP_SIZE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:01:46 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/09 22:43:26 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_mini_map(mlx_image_t *img, int32_t background_color)
{
	int	y;
	int	x;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			mlx_put_pixel(img, x, y, background_color);
			x++;
		}
		y++;
	}
}

void	rotate_point(int *x, int *y, float angle, int cx, int cy)
{
	int		new_x;
	int		new_y;
	float	s;
	float	c;

	s = sin(angle);
	c = cos(angle);
	new_x = (int)(((*x - cx) * c - (*y - cy) * s) + cx);
	new_y = (int)(((*x - cx) * s + (*y - cy) * c) + cy);
	*x = new_x;
	*y = new_y;
}

void	put_player_mini(t_app *app)
{
	int	py;
	int	px;

	py = -2;
	while (py <= 2)
	{
		px = -2;
		while (px <= 2)
		{
			mlx_put_pixel(app->minimap_img, app->mini_info.half_size + px,
				app->mini_info.half_size + py, RED);
			px++;
		}
		py++;
	}
}

void	calculate_xy_coordinates(t_app *app, int map_x, int map_y,
		int minimap_x, int minimap_y)
{
	app->mini_info.xy.x = (map_y * app->mini_info.wall_size + minimap_y)
		- app->player.y * app->mini_info.wall_size + app->mini_info.half_size;
	app->mini_info.xy.y = (map_x * app->mini_info.wall_size + minimap_x)
		- app->player.x * app->mini_info.wall_size + app->mini_info.half_size;
	app->mini_info.xy.y = MINIMAP_SIZE - app->mini_info.xy.y - 1;
}

int	is_within_minimap_bounds(t_app *app)
{
	return (app->mini_info.xy.x >= 0 && app->mini_info.xy.x < MINIMAP_SIZE
		&& app->mini_info.xy.y >= 0 && app->mini_info.xy.y < MINIMAP_SIZE);
}

void	draw_minimap_wall(t_app *app, int map_x, int map_y)
{
	int	minimap_y;
	int	minimap_x;

	minimap_y = 0;
	while (minimap_y < app->mini_info.wall_size)
	{
		minimap_x = 0;
		while (minimap_x < app->mini_info.wall_size)
		{
			calculate_xy_coordinates(app, map_x, map_y, minimap_x, minimap_y);
			rotate_point(&app->mini_info.xy.x, &app->mini_info.xy.y,
				-app->player.angle, app->mini_info.half_size,
				app->mini_info.half_size);
			if (is_within_minimap_bounds(app))
				mlx_put_pixel(app->minimap_img, app->mini_info.xy.x,
					app->mini_info.xy.y, WHITE);
			minimap_x++;
		}
		minimap_y++;
	}
}



void	draw_minimap_walls(t_app *app)
{
	int	map_y;
	int	map_x;

	map_y = 0;
	while (map_y < app->map_height)
	{
		map_x = 0;
		while (map_x < app->map_width)
		{
			if (app->map[map_y][map_x] == '1')
				draw_minimap_wall(app, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap(t_app *app)
{
	app->mini_info.wall_size = MINIMAP_SIZE / app->map_height;
	app->mini_info.half_size = MINIMAP_SIZE / 2;
	if (app->map_height == 0 || app->map_width == 0)
	{
		printf("Invalid map dimensions.\n");
		return ;
	}
	draw_minimap_walls(app);
	put_player_mini(app);
}

// Function to create and display the compass
void	display_minimap(t_app *app)
{
	clear_mini_map(app->minimap_img, BLACK);
	draw_minimap(app);
	mlx_image_to_window(app->mlx, app->minimap_img, 0, 0);
}

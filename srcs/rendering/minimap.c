/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:01:46 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 19:25:02 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_wall(t_app *app, t_vec map)
{
	t_vec	minimap;

	minimap.x = 0;
	while (minimap.x < app->mini_info.wall_size)
	{
		minimap.y = 0;
		while (minimap.y < app->mini_info.wall_size)
		{
			calculate_xy_coordinates(app, map, minimap);
			rotate_point(&app->mini_info.xy, +app->player.angle,
				app->mini_info.half_size);
			if (is_within_minimap_bounds(app))
				mlx_put_pixel(app->minimap_img, app->mini_info.xy.x,
					app->mini_info.xy.y, WHITE);
			minimap.y++;
		}
		minimap.x++;
	}
}

void	draw_minimap_door(t_app *app, t_vec map, int32_t color)
{
	t_vec	minimap;

	minimap.x = 0;
	while (minimap.x < app->mini_info.wall_size)
	{
		minimap.y = 0;
		while (minimap.y < app->mini_info.wall_size)
		{
			calculate_xy_coordinates(app, map, minimap);
			rotate_point(&app->mini_info.xy, +app->player.angle,
				app->mini_info.half_size);
			if (is_within_minimap_bounds(app))
				mlx_put_pixel(app->minimap_img, app->mini_info.xy.x,
					app->mini_info.xy.y, color);
			minimap.y++;
		}
		minimap.x++;
	}
}

void	draw_minimap_walls(t_app *app)
{
	t_vec	map;

	map.x = 0;
	while (map.x < app->map_width)
	{
		map.y = 0;
		while (map.y < app->map_height)
		{	
			printf("1\n");
			if (app->map[map.x][map.y] == '1')
				draw_minimap_wall(app, map);
			printf("2\n");
			if (app->map[map.x][map.y] == 'D')
			{
				if (app->walked_map[map.x][map.y] == 3)
					draw_minimap_door(app, map, CYAN);
				else if (app->walked_map[map.x][map.y] == 4)
					draw_minimap_door(app, map, GREEN);
			}
			printf("3\n");
			map.x++;
		}
		map.y++;
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
	printf("1\n");
	put_player_mini(app);
}

void	display_minimap(t_app *app)
{
	clear_mini_map(app->minimap_img, BLACK);
	draw_minimap(app);
}

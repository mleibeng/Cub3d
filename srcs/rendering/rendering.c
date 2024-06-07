/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:00:43 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/07 11:14:33 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	combines rgb and alpha(transparency) values into single color
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//	function to draw a partial ray
void	draw_part_ray(t_app *app, int start, int end, int32_t color)
{
	int	y;

	y = start;
	while (y < end)
	{
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width
			&& y >= 0 && y < app->window_height)
			mlx_put_pixel(app->img, app->cur_ray, y, color);
		y++;
	}
}

//	function to draw one ray
void	draw_ray(t_app *app, t_tar *wall)
{
	int		shade;
	int		wall_start;
	int		wall_end;
	int32_t	sky_color;
	int32_t	floor_color;

	shade = 150 / (1.0 + wall->distance * 0.3);
	wall_start = (app->window_height - wall->wall_height) / 2;
	wall_end = (app->window_height + wall->wall_height) / 2;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > app->window_height)
		wall_end = app->window_height;
	wall->color += shade;
	sky_color = ft_pixel(app->textures->skybox[0],
			app->textures->skybox[1], app->textures->skybox[2], 150);
	floor_color = ft_pixel(app->textures->floor[0],
			app->textures->floor[1], app->textures->floor[2], shade / 2);
	draw_part_ray(app, 0, wall_start - 1, sky_color);
	draw_part_ray(app, wall_start, wall_end, wall->color);
	draw_part_ray(app, wall_end, app->window_height, floor_color);
}

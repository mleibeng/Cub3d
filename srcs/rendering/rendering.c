/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:50:08 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/15 10:06:44 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mix_and_print_text(t_app *app, int32_t color, float percentage, int y)
{
	int32_t	new_color;
	int		alpha;

	alpha = (color & 0x000000FF);
	new_color = ft_pixel(((color >> 24) & 0xFF), 1
			+ ((color >> 16) & 0xFF) * percentage, 1
			+ ((color >> 8) & 0xFF) * percentage, 0);
	new_color = (color & 0xFFFFFF00) | (uint8_t)(alpha * percentage);
	if (app->cur_ray <= MINIMAP_SIZE && y <= MINIMAP_SIZE)
		new_color = (color & 0xFFFFFF00);
	mlx_put_pixel(app->img, app->cur_ray, y, new_color);
}

//	function to draw a partial ray (floor or ceiling)
void	draw_sky_ceiling(t_app *app, int start, int end, int32_t color, char dir)
{
	int		y;
	float	percentage;

	y = start;
	while (y < end)
	{
		if (dir == 'C')
			percentage = 1.0f - ((float)(y - start)
					/ (float)(app->window_height - start));
		else
			percentage = (float)(((float)(y - end) / y) * 0.9);
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width
			&& y >= 0 && y < app->window_height)
		{
			mix_and_print_text(app, color, percentage, y);
		}
		y++;
	}
}

//	function to draw one ray for the floor or the ceiling
void	draw_wall(t_app *app, t_tar *wall, int y_start, int y_end)
{
	int		y;
	int		texture_x;
	int		texture_y;
	int		shade;
	xpm_t	*tyle;

	tyle = get_text(app, wall->side);
	shade = 256 / (1.0 + wall->distance * 0.03);
	texture_x = tyle->texture.width * wall->pos_x_cur_tyle;
	y = y_start;
	while (y < y_end)
	{
		texture_y = round(tyle->texture.height
				* ((float)(y - y_start) / (y_end - y_start)));
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width
			&& y >= 0 && y < app->window_height
			&& app->cur_ray > 0 && app->cur_ray < app->window_width
			&& y > 0 && y < app->window_height)
		{
			if (wall->distance >= 25.0f && wall->distance < 50.0f)
				shade = (int)wall->distance;
			if (shade <= 0 || wall->distance >= 50.0f)
				shade = 1;
			mix_and_put_color(app,
				get_texture_pixel(&tyle->texture, texture_x, texture_y, shade),
				1.0 - (wall->distance * 0.02), shade, y);
		}
		y++;
	}
}

//	function to draw one ray from the sky, to the textured walls, to the ceiling
void	draw_ray(t_app *app, t_tar *wall)
{
	int		wall_start;
	int		wall_end;
	int32_t	sky_color;
	int32_t	floor_color;

	wall_start = (app->window_height - wall->wall_height) / 2;
	wall_end = (app->window_height + wall->wall_height) / 2;
	sky_color = ft_pixel(app->textures->skybox[0],
			app->textures->skybox[1], app->textures->skybox[2], 150);
	floor_color = ft_pixel(app->textures->floor[0],
			app->textures->floor[1], app->textures->floor[2], 150);
	draw_sky_ceiling(app, 0, wall_start - 1, sky_color, 'C');
	draw_wall(app, wall, wall_start, wall_end);
	draw_sky_ceiling(app, wall_end, app->window_height, floor_color, 'F');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/12 21:04:50 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

xpm_t *get_text(t_app *app, int side)
{
	if (side == 1)
		return (app->textures->n_text);
	else if (side == 2)
		return (app->textures->e_text);
	else if (side == 3)
		return (app->textures->s_text);
	else if (side == 4)
		return (app->textures->w_text);
	return (NULL);
}

//	combines rgb and alpha(transparency) values into single color
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//	function to draw a partial ray
void draw_sky_ceiling(t_app *app, int start, int end, int32_t color, char dir)
{
	int		y;
	uint8_t	alpha;
	float	percentage;
	int32_t	new_color;

	y = start;
	alpha = (color & 0x000000FF);
	percentage = 1.0f;
	while (y < end)
	{
		if (dir == 'C')
			percentage = 1.0f - ((float)(y - start) / (float)(app->window_height - start));
		else
		{
			percentage = (float)(((float)(y - end) / y) * 0.9);
		}
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width
			&& y >= 0 && y < app->window_height)
		{
			new_color = ft_pixel(((color >> 24) & 0xFF), 1 + ((color >> 16) & 0xFF) * percentage, 1 + ((color >> 8) & 0xFF) * percentage, 0);
			new_color = (color & 0xFFFFFF00) | (uint8_t)(alpha * percentage);
			if (app->cur_ray <= MINIMAP_SIZE && y <= MINIMAP_SIZE)
				new_color = (color & 0xFFFFFF00);
			mlx_put_pixel(app->img, app->cur_ray, y, new_color);
		}
		y++;
	}
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y, int shade)
{
	int		index;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
	{
		return (0);
	}
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	red = texture->pixels[index];
	green = texture->pixels[index + 1];
	blue = texture->pixels[index + 2];
	alpha = 0;
	return ((ft_pixel(red, green, blue, alpha) + shade));
}


void	draw_wall(t_app *app, t_tar *wall, int y_start, int y_end)
{
	int		y;
	int		texture_x, texture_y;
	int32_t	color;
	float	percentage;
	int		shade;
	xpm_t	*tyle;
	double	factor = 1.0 - (wall->distance * 0.02);
	tyle = get_text(app, wall->side);
	shade = 256 / (1.0 + wall->distance * 0.03);
	texture_x = tyle->texture.width * wall->pos_x_cur_tyle;
	y = y_start;
	while (y < y_end)
	{
		percentage = (float)(y - y_start) / (y_end - y_start);
		texture_y = round(tyle->texture.height * percentage);
		color = get_texture_pixel(&tyle->texture, texture_x, texture_y, shade);
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width
			&& y >= 0 && y < app->window_height
			&& app->cur_ray > 0 && app->cur_ray < app->window_width
			&& y > 0 && y < app->window_height)
		{
			if (app->cur_ray >= MINIMAP_SIZE || y >= MINIMAP_SIZE)
			{
				(void)factor;
				color = ft_pixel(((color >> 24) & 0xFF), ((color >> 16) & 0xFF) * factor, ((color >> 8) & 0xFF) * factor, color & 0xFF);
				color += shade;
				mlx_put_pixel(app->img, app->cur_ray, y, color);
			}

		}
		y++;
	}
}

void draw_ray(t_app *app, t_tar *wall)
{
	int wall_start;
	int wall_end;
	int32_t sky_color;
	int32_t floor_color;

	wall_start = (app->window_height - wall->wall_height) / 2;
	wall_end = (app->window_height + wall->wall_height) / 2;
	sky_color = ft_pixel(app->textures->skybox[0],
			app->textures->skybox[1], app->textures->skybox[2], 150);
	floor_color = ft_pixel(app->textures->floor[0],
			app->textures->floor[1], app->textures->floor[2], 150);
	draw_sky_ceiling(app, 0, wall_start - 1, sky_color, 'C');
	draw_wall(app, wall, wall_start, wall_end);
	draw_sky_ceiling(app, wall_end - 4, app->window_height, floor_color, 'F');
}

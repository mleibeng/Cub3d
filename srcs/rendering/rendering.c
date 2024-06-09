/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:00:43 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/10 00:24:34 by mleibeng         ###   ########.fr       */
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

uint32_t get_texture_pixel(mlx_texture_t *texture, int x, int y, int shade)
{
	int	index;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

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


void	draw_textured_ray(t_app *app, t_tar *wall, xpm_t *tyle, int y_start, int y_end, int shade)
{
	int		y;
	int		texture_x, texture_y;
	int		draw_y;
	int32_t	color;
	float	percentage;

	texture_x = (int)(tyle->texture.width * wall->pos_x_cur_tyle);
	y = y_start;
	while (y < y_end)
	{
		percentage = (float)(y - y_start) / (y_end - y_start);
		texture_y = (int)(tyle->texture.height * percentage);
		color = get_texture_pixel(&tyle->texture, texture_x, texture_y, shade);
		draw_y = y;
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width &&
			draw_y >= 0 && draw_y < app->window_height &&
			app->cur_ray > 0 && app->cur_ray < app->window_width &&
			draw_y > 0 && draw_y < app->window_height)
		{
			mlx_put_pixel(app->img, app->cur_ray, draw_y, color);
		}
		y++;
	}
}

void draw_ray(t_app *app, t_tar *wall)
{
	int shade;
	int wall_start;
	int wall_end;
	int32_t sky_color;
	int32_t floor_color;

	shade = 256 / (1.0 + wall->distance * 0.1);
	wall_start = (app->window_height - wall->wall_height) / 2;
	wall_end = (app->window_height + wall->wall_height) / 2;
	wall->color += shade;
	sky_color = ft_pixel(app->textures->skybox[0], app->textures->skybox[1], app->textures->skybox[2], 150);
	floor_color = ft_pixel(app->textures->floor[0], app->textures->floor[1], app->textures->floor[2], shade);

	draw_part_ray(app, 0, wall_start - 1, sky_color);
	draw_textured_ray(app, wall, get_text(app, wall->side), wall_start, wall_end, shade);
	draw_part_ray(app, wall_end, app->window_height, floor_color);
}

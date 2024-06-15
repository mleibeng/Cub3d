/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:35:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/15 10:05:30 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// combines rgb and alpha(transparency) values into single color
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//	function to put the pixel on the screen and calculating the redshift and
//	brightness based on the wall ray distance
void	mix_and_put_color(t_app *app, int32_t color, float factor, int shade, int y)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = (color >> 24) & 0xFF;
	g = ((color >> 16) & 0xFF) * factor;
	b = ((color >> 8) & 0xFF) * factor;
	a = (color & 0xFF);
	if ((app->cur_ray >= MINIMAP_SIZE || y >= MINIMAP_SIZE)
		&& app->cur_ray > 0 && y > 0 && app->cur_ray < app->window_width
		&& y < app->window_height)
	{
		if (shade == 1)
			color = ft_pixel(230, 5, 5, shade);
		else
			color = ft_pixel(r, g, b, a) + shade;
		mlx_put_pixel(app->img, app->cur_ray, y, color);
	}
}

//	function to get the texture based on the wall side, in which player looks
xpm_t	*get_text(t_app *app, int side)
{
	if (side == NORTH)
		return (app->textures->n_text);
	else if (side == EAST)
		return (app->textures->e_text);
	else if (side == SOUTH)
		return (app->textures->s_text);
	else if (side == WEST)
		return (app->textures->w_text);
	else if (side == DOOR)
		return (app->textures->d_text);
	return (NULL);
}

//	getting the colors from the texture based on the percentage of the text
uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y, int shade)
{
	int		index;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	if (x == -1)
		return (ft_pixel(5, 5, 5, 5));
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
	{
		return (0);
	}
	index = round((y * texture->width + x) * texture->bytes_per_pixel);
	red = texture->pixels[index];
	green = texture->pixels[index + 1];
	blue = texture->pixels[index + 2];
	alpha = 0;
	return ((ft_pixel(red, green, blue, alpha) + shade));
}

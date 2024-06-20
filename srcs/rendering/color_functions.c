/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:35:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 20:39:01 by mleibeng         ###   ########.fr       */
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
void	mix_and_put_color(t_app *app, t_put_col info)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = (info.color >> 24) & 0xFF;
	g = ((info.color >> 16) & 0xFF) * info.factor;
	b = ((info.color >> 8) & 0xFF) * info.factor;
	a = (info.color & 0xFF);
	if ((app->cur_ray >= MINIMAP_SIZE || info.y >= MINIMAP_SIZE)
		&& app->cur_ray > 0 && info.y > 0 && app->cur_ray < app->window_width
		&& info.y < app->window_height)
	{
		if (info.shade == 1)
			info.color = ft_pixel(230, 5, 5, info.shade);
		else
			info.color = ft_pixel(r, g, b, a) + info.shade;
		mlx_put_pixel(app->img, app->cur_ray, info.y, info.color);
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
	t_color	colors;

	if (x == -1)
		return (ft_pixel(5, 5, 5, 5));
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
	{
		return (0);
	}
	index = round((y * texture->width + x) * texture->bytes_per_pixel);
	colors.red = texture->pixels[index];
	colors.green = texture->pixels[index + 1];
	colors.blue = texture->pixels[index + 2];
	colors.alpha = 0;
	return ((ft_pixel(colors.red, colors.green, colors.blue, colors.alpha)
			+ shade));
}

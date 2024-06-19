/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:44:27 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 19:09:28 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

//	function to get a pixel color feom a texture at a certain point (x, y)
int32_t	get_pixel_from_text(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixel;
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (x > image->width || y > image->height)
		return (0);
	pixel = image->pixels + (y * image->width + x) * sizeof(int32_t);
	a = pixel[0];
	r = pixel[1];
	g = pixel[2];
	b = pixel[3];
	return (ft_pixel(a, r, g, b));
}

//	returns one if a pixel at a ceratin position is not null, or 0 if yes
int	check_pixel_is_not_null(mlx_image_t *img, uint32_t x, uint32_t y)
{
	int32_t	color;

	color = get_pixel_from_text(img, x, y);
	if (color != 0 && color != 0x333333)
	{
		return (1);
	}
	return (0);
}

//	function to replace a part of the image with another image starting at x y
void	put_img_to_img(mlx_image_t *img, mlx_image_t *src, int x, int y)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			if (check_pixel_is_not_null(src, i, j) == 1
				&& (x + i) > 0 && (x + i) < WINDOW_WIDTH
				&& (y + j) > 0 && (y + j) < WINDOW_HEIGHT)
			{
				mlx_put_pixel(img, x + i, y + j, get_pixel_from_text(src, i,
						j));
			}
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:44:27 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 01:44:59 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (get_pixel_from_text(img, x, y) != 0)
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
			if (check_pixel_is_not_null(src, i, j))
			{
				mlx_put_pixel(img, x + i, y + j, get_pixel_from_text(src, i,
						j));
			}
			j++;
		}
		i++;
	}
}

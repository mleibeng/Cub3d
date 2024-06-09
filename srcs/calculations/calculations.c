/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/09 00:41:24 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

//	function to normalize an angle, so it stays in the range of 2 x PI
float	norm_ang(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

double	get_fractional_part(double num)
{
	double	integral_part;
	double	fractional_part;

	fractional_part = modf(num, &integral_part);
	return (fractional_part);
}

float	find_tyle_pos(t_tar *wall)
{
	if (wall->hit_vertical == 0)
		return (get_fractional_part(wall->target_x));
	else
		return (get_fractional_part(wall->target_y));
}

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
float	cast_ray(t_app *app, float ray_angle, t_tar *wall)
{
	float	depth;
	float	max_units;
	float	hit_x;
	float	hit_y;

	depth = 0.0f;
	max_units = 1.0f * (int)fmax(app->rows, app->cols);
	wall->hit_vertical = 0;
	while (depth < max_units)
	{
		wall->target_x = app->player.x + depth * cos(ray_angle);
		wall->target_y = app->player.y + depth * sin(ray_angle);
		if (wall->target_y > 0 && wall->target_x > 0
			&& wall->target_y < app->rows && wall->target_x < app->cols
			&& app->walked_map[(int)wall->target_y][(int)wall->target_x] == 1)
		{
			hit_x = fabs(wall->target_x - round(wall->target_x));
			hit_y = fabs(wall->target_y - round(wall->target_y));
			wall->hit_vertical = hit_x < 0.005f && hit_x < hit_y;
			wall->pos_x_cur_tyle = find_tyle_pos(wall);
			return (depth * cos(app->player.angle - ray_angle));
		}
		depth += 0.005f;
	}
	return (max_units * cos(app->player.angle - ray_angle));
}

//	function to calculate which direction faces tile from players perpective
void	calc_side(float ray_angle, t_tar *wall)
{
	if (wall->hit_vertical == 1)
	{
		if (cos(ray_angle) >= 0)
		{
			wall->side = 1;
			//wall->color = ft_pixel(1.0 + wall->distance * 0.1, 0, 255 / (1.0 + wall->distance * 0.05), 0);
		}
		else
		{
			wall->side = 2;
			//wall->color = ft_pixel(255, 255 / (1.0 + wall->distance * 0.05), 0, 0);
		}
	}
	else
	{
		if (sin(ray_angle) >= 0)
		{
			wall->side = 3;
			//wall->color = ft_pixel(1.0 + wall->distance * 0.1, 255 / (1.0 + wall->distance * 0.05), 0, 0);
		}
		else
		{
			wall->side = 4;
			//wall->color = ft_pixel(255, 0 / (1.0 + wall->distance * 0.05), 0, 0);
		}
	}
}

//	function to draw the lines of the map
void	calc_walls(t_app *app)
{
	float	ray_angle;
	float	correction;
	t_tar	wall;

	wall.color = 0;
	app->cur_ray = 0;
	while (app->cur_ray < app->num_rays)
	{
		correction = app->cur_ray - app->num_rays / 2;
		ray_angle = app->player.angle + atan(correction / app->num_rays * tan(app->fov / 2));
		ray_angle = norm_ang(ray_angle);
		wall.distance = cast_ray(app, ray_angle, &wall);
		wall.wall_height = (int)(app->window_height / (wall.distance + 0.01f));
		calc_side(ray_angle, &wall);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

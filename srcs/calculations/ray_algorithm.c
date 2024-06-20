/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:15:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/20 04:20:41 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	finer algorithm when a rounded target on the map is found
void	fine_tuning_algorithm(t_app *app, t_tar *wall, float ang, float depth)
{
	float	start;
	float	end;

	start = depth - 0.01f;
	end = depth + 0.01f;
	while (end - start > 0.00003f)
	{
		depth = (start + end) / 2;
		wall->tar_x = app->player.x + depth * cos(ang);
		wall->tar_y = app->player.y + depth * sin(ang);
		if (app->val_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 1)
		{
			wall->hit = VERTICAL;
			end = depth;
		}
		else if (app->val_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 3)
		{
			wall->hit = DOOR_VERTIKAL;
			end = depth;
		}
		else
			start = depth;
	}
}

void	adjust_depth_increment(float *depth, float max_depth)
{
	float	trans;
	float	max_inc;
	float	min_inc;
	float	interpolation;

	trans = 2.0f;
	max_inc = 0.1f;
	min_inc = 0.0007f;
	if (*depth > max_depth)
	{
		*depth += max_inc;
	}
	else if (*depth > trans)
	{
		interpolation = (*depth - trans) / (max_depth - trans);
		*depth += min_inc + (max_inc - min_inc) * interpolation;
	}
	else
		*depth += min_inc;
}

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
//	improved algorithm, higher accuracy for smaller distances
float	cast_ray(t_app *app, float ray_angle, t_tar *wall)
{
	float	depth;
	float	max_units;

	depth = 0.00f;
	max_units = 1.0f * (int)fmax(app->rows, app->cols);
	if (max_units > 100.0f)
		max_units = 100.0f;
	wall->tar_x = 0.00f;
	wall->tar_y = 0.00f;
	while (depth < max_units)
	{
		wall->tar_x = app->player.x + depth * cos(ray_angle);
		wall->tar_y = app->player.y + depth * sin(ray_angle);
		if (wall->tar_y > 0.0f && wall->tar_x > 0.0f
			&& wall->tar_y < app->rows && wall->tar_x < app->cols
			&& (app->val_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 1
				|| app->val_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 3))
			break ;
		adjust_depth_increment(&depth, max_units);
	}
	if (depth >= max_units)
		return (wall->hit = NONVERTICAL, max_units * cos(app->player.angle
				- ray_angle));
	fine_tuning_algorithm(app, wall, ray_angle, depth);
	return (depth * cos(app->player.angle - ray_angle));
}

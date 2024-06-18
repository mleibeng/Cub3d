/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 01:00:50 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// adjust the tyle direction based on the angle facing to the wall
float	find_tyle_pos(t_tar *wall)
{
	if (wall->hit == VERTICAL || wall->hit == DOOR_VERTIKAL)
		return (get_fractional_part(wall->tar_x));
	else
		return (get_fractional_part(wall->tar_y));
}

int	is_integer(float x)
{
	return (fabsf(x - roundf(x)) < 1e-15);
}

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
//	improved algorithm, higher accuracy for smaller distances
float	cast_ray(t_app *app, float ray_angle, t_tar *wall)
{
	float	depth;
	float	max_units;
	float	start;
	float	end;

	depth = -0.01f;
	max_units = 1.0f * (int)fmax(app->rows, app->cols);
	if (max_units > 100.0f)
		max_units = 100.0f;
	wall->tar_x = 0.01f;
	wall->tar_y = 0.01f;
	while (depth < max_units)
	{
		wall->tar_x = app->player.x + depth * cos(ray_angle);
		wall->tar_y = app->player.y + depth * sin(ray_angle);
		if (wall->tar_y >= 0 && wall->tar_x >= 0 && wall->tar_y <= app->rows
			&& wall->tar_x <= app->cols
			&& (app->walked_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 1
				|| app->walked_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 3))
			break ;
		depth += 0.01f;
	}
	start = depth - 0.01f;
	end = depth + 0.01f;
	if (depth >= max_units)
	{
		wall->hit = NONVERTICAL;
		return (max_units * cos(app->player.angle - ray_angle));
	}
	while (end - start > 0.00003f)
	{
		depth = (start + end) / 2;
		wall->tar_x = app->player.x + depth * cos(ray_angle);
		wall->tar_y = app->player.y + depth * sin(ray_angle);
		if (wall->tar_y >= 0 && wall->tar_x >= 0 && wall->tar_y <= app->rows
			&& wall->tar_x <= app->cols)
		{
			if (app->walked_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 1)
				wall->hit = VERTICAL, end = depth;
			else if (app->walked_map[(int)(wall->tar_y)][(int)(wall->tar_x)] == 3)
				wall->hit = DOOR_VERTIKAL, end = depth;
			else
				start = depth;
		}
		else
			start = depth;
	}
	return (depth * cos(app->player.angle - ray_angle));
}

//	function to calculate which direction faces tile from players perpective
void	calc_side(float ray_angle, t_tar *wall)
{
	// if (wall->distance >= 50.0f)
	// 	return ; // This causes the segfault!! so I took it out.
	if (wall->hit == NONVERTICAL)
	{
		if (cos(ray_angle) > 0)
			wall->side = NORTH;
		else
			wall->side = EAST;
	}
	else if (wall->hit == DOOR_HOR || wall->hit == DOOR_VERTIKAL)
	{
		wall->side = DOOR;
	}
	else
	{
		if (sin(ray_angle) > 0)
			wall->side = SOUTH;
		else
			wall->side = WEST;
	}
}

//	function to draw the lines of the map
void	calc_walls(t_app *app)
{
	float	ray_angle;
	float	correction;
	t_tar	wall;

	app->cur_ray = 0;
	while (app->cur_ray <= app->num_rays)
	{
		correction = app->cur_ray - (float)(app->num_rays) / 2;
		ray_angle = app->player.angle + atan(correction / app->num_rays
				* tan(app->fov / 1.5));
		ray_angle = norm_ang(ray_angle);
		wall.distance = cast_ray(app, ray_angle, &wall);
		if (wall.hit == VERTICAL || wall.hit == DOOR_VERTIKAL)
		{
			if ((fabsf(wall.tar_y - roundf(wall.tar_y))) > (fabsf(wall.tar_x
						- roundf(wall.tar_x))))
			{
				if (wall.hit == VERTICAL)
					wall.hit = NONVERTICAL;
				else if (wall.hit == DOOR_VERTIKAL)
					wall.hit = DOOR_HOR;
			}
		}
		wall.pos_x_cur_tyle = find_tyle_pos(&wall);
		wall.wall_height = (int)(app->window_height / (wall.distance));
		calc_side(ray_angle, &wall);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

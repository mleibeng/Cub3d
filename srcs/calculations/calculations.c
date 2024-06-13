/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/13 20:41:00 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// adjust the tyle direction based on the angle facing to the wall
float	find_tyle_pos(t_tar *wall)
{
	if (wall->hit == 0)
		return (get_fractional_part(wall->tar_x));
	else
		return (get_fractional_part(wall->tar_y));
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

	depth = 0.0f;
	max_units = 1.0f * (int)fmax(app->rows * 1.3, app->cols * 1.3);
	wall->hit = 0;
	wall->tar_x = 0;
	wall->tar_y = 0;
	while (depth < max_units)
	{
		wall->tar_x = app->player.x + depth * cos(ray_angle);
		wall->tar_y = app->player.y + depth * sin(ray_angle);
		if (wall->tar_y >= 0 && wall->tar_x >= 0
			&& wall->tar_y <= app->rows && wall->tar_x <= app->cols
			&& (app->walked_map[(ft_ro)(wall->tar_y)][(ft_ro)(wall->tar_x)] == 1
				|| app->walked_map[(ft_ro)(wall->tar_y)][(ft_ro)(wall->tar_x)] == 3))
			break ;
		depth += 0.01f;
	}
	start = depth - 0.01f;
	end = depth;
	while (end - start > 0.00005f)
	{
		depth = (start + end) / 2;
		wall->tar_x = app->player.x + depth * cos(ray_angle);
		wall->tar_y = app->player.y + depth * sin(ray_angle);
		if (wall->tar_y >= 0 && wall->tar_x >= 0
			&& wall->tar_y <= app->rows && wall->tar_x <= app->cols)
		{
			if (app->walked_map[(int)fabsf(wall->tar_y)][(int)fabsf(wall->tar_x)] == 1)
				wall->hit = 0, end = depth;
			else if (app->walked_map[(int)fabsf(wall->tar_y)][(int)fabsf(wall->tar_x)] == 3)
				wall->hit = 2, end = depth;
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
	if (wall->hit == 1)
	{
		if (cos(ray_angle) > 0)
			wall->side = 1;
		else
			wall->side = 2;
	}
	else if (wall->hit == 2)
	{
		wall->side = 5;
	}
	else
	{
		if (sin(ray_angle) > 0)
			wall->side = 3;
		else
			wall->side = 4;
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
		ray_angle = app->player.angle + atan(correction
				/ app->num_rays * tan(app->fov / 1.5));
		ray_angle = norm_ang(ray_angle);
		wall.distance = cast_ray(app, ray_angle, &wall);
		if (wall.hit == 0)
			wall.hit = (fabs(wall.tar_y - roundf(wall.tar_y)) - 0.0005f)
				> (fabs(wall.tar_x - roundf(wall.tar_x)) - 0.002);
		wall.pos_x_cur_tyle = find_tyle_pos(&wall);
		wall.wall_height = (int)(app->window_height / (wall.distance + 0.01f));
		calc_side(ray_angle, &wall);
		draw_ray(app, &wall);
		wall.hit = 0;
		app->cur_ray++;
	}
}

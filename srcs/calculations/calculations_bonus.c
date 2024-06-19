/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 20:38:53 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// adjust the tyle direction based on the angle facing to the wall
float	find_tyle_pos(t_tar *wall)
{
	if (wall->hit == VERTICAL || wall->hit == DOOR_VERTIKAL)
		return (get_fractional_part(wall->tar_x));
	else
		return (get_fractional_part(wall->tar_y));
}

//	function to calculate which direction faces tile from players perpective
void	calc_side(float ray_angle, t_tar *wall)
{
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

void	check_vertical_hit(t_tar *wall)
{
	if (wall->hit == VERTICAL || wall->hit == DOOR_VERTIKAL)
	{
		if ((fabsf(wall->tar_y - roundf(wall->tar_y))) > (fabsf(wall->tar_x
					- roundf(wall->tar_x))))
		{
			if (wall->hit == VERTICAL)
				wall->hit = NONVERTICAL;
			else if (wall->hit == DOOR_VERTIKAL)
				wall->hit = DOOR_HOR;
		}
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
		check_vertical_hit(&wall);
		wall.pos_x_cur_tyle = find_tyle_pos(&wall);
		wall.wall_height = (int)(app->window_height / (wall.distance));
		calc_side(ray_angle, &wall);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

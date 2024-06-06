/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/06 20:59:14 by fkeitel          ###   ########.fr       */
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

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
float	cast_ray(t_player *player, float ray_angle, t_tar *wall)
{
	float	depth;
	float	max_units;
	float	hit_x;
	float	hit_y;

	depth = 0.0f;
	max_units = 1.0f * (MAP_HEIGHT + 10);
	while (depth < max_units)
	{
		wall->target_x = player->x + depth * cos(ray_angle);
		wall->target_y = player->y + depth * sin(ray_angle);
		if (g_map[(int)wall->target_y][(int)wall->target_x] == 1)
		{
			hit_x = fabs(wall->target_x - round(wall->target_x));
			hit_y = fabs(wall->target_y - round(wall->target_y));
			wall->hit_vertical = hit_x < 0.005f && hit_x <= hit_y;
			return (depth * cos(player->angle - ray_angle));
		}
		depth += 0.005f;
	}
	return (max_units * cos(player->angle - ray_angle));
}

//	function to calculate which direction faces tile from players perpective
void	calc_side(float ray_angle, t_tar *wall)
{
	if (wall->hit_vertical == 1)
	{
		if (cos(ray_angle) >= 0)
		{
			wall->color = ft_pixel(0, 0, 255, 0);
		}
		else
			wall->color = ft_pixel(255, 255, 0, 0);
	}
	else
	{
		if (sin(ray_angle) >= 0)
		{
			wall->color = ft_pixel(0, 255, 0, 0);
		}
		else
		{
			wall->color = ft_pixel(255, 0, 0, 0);
		}
	}
}

//	function to draw the lines of the map
void	calc_walls(t_app *app)
{
	float	ray_angle;
	t_tar	wall;

	wall.color = 0;
	direction_change_hook(app);
	view_change_hook(app);
	app->cur_ray = 0;
	while (app->cur_ray < app->num_rays)
	{
		ray_angle = norm_ang(app->player.angle - app->fov / 4
				+ app->cur_ray * app->fov / app->num_rays);
		wall.distance = cast_ray(&app->player, ray_angle, &wall);
		wall.wall_height = (int)(app->window_height / (wall.distance + 0.01f));
		calc_side(ray_angle, &wall);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

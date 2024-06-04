/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/04 19:28:41 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
float	cast_ray(t_player *player, float ray_angle, t_tar *wall)
{
	float	depth;
	float	max_units;

	depth = 0.0f;
	max_units = 1.0f * MAP_HEIGHT;
	while (depth < max_units)
	{
		wall->target_x = player->x + depth * cos(ray_angle);
		wall->target_y = player->y + depth * sin(ray_angle);
		if (wall->target_x >= MAP_WIDTH || wall->target_y >= MAP_HEIGHT
			|| wall->target_x < 0 || wall->target_y < 0
			|| g_map[(int)wall->target_y][(int)wall->target_x] == 1)
		{
			return (depth * cos(player->angle - ray_angle));
		}
		depth += 0.005f;
	}
	return (max_units * cos(player->angle - ray_angle));
}

void	calc_side(t_app *app, float ray_angle, t_tar *wall)
{
	//if (cos(app->player.angle))
	//{
	//	wall->color = ft_pixel(250, 30, 30, 0);
	//}
	//else if (cos(app->player.x) )
	//{
	//	wall->color = ft_pixel(250, 30, 30, 0);
	//}
	//else if (cos(app->player.x) )
	//{
	//	wall->color = ft_pixel(250, 30, 30, 0);
	//}
	//else if (cos(app->player.x) )
	//{
	//	wall->color = ft_pixel(250, 30, 30, 0);
	//}
	(void)app;
	(void)ray_angle;
	wall->color = ft_pixel(230, 30, 30, 0);
}

//	function to draw the lines of the map
void	calc_walls(t_app *app)
{
	float	ray_angle;
	t_tar	wall;

	wall.color = 0;
	ft_hook_key(app);
	app->cur_ray = 0;
	while (app->cur_ray < app->num_rays)
	{
		ray_angle = app->player.angle - app->fov / 2
			+ app->cur_ray * app->fov / app->num_rays;
		wall.distance = cast_ray(&app->player, ray_angle, &wall);
		wall.wall_height = (int)(app->window_height / (wall.distance + 0.01f));
		calc_side(app, ray_angle, &wall);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

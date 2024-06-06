/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/05 22:32:14 by flo              ###   ########.fr       */
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

	depth = 0.0f;
	max_units = 1.0f * (MAP_HEIGHT + 10);
	while (depth < max_units)
	{
		wall->target_x = player->x + depth * cos(ray_angle);
		wall->target_y = player->y + depth * sin(ray_angle);
		if (g_map[(int)wall->target_y][(int)wall->target_x] == 1)
		{
			float hit_x = fabs(wall->target_x - round(wall->target_x));
			float hit_y = fabs(wall->target_y - round(wall->target_y));
			wall->hit_vertical = hit_x < 0.005f && hit_x <= hit_y;
			return (depth * cos(player->angle - ray_angle));
		}
		depth += 0.005f;
	}
	return (max_units * cos(player->angle - ray_angle));
}

void	calc_side(t_app *app, float ray_angle, t_tar *wall)
{
	(void)app;
	if (wall->hit_vertical) {
		if (fabs(cos(ray_angle)) > 0.9999) {
			// Close to perpendicular angle, treat as east or west based on target_x
			if (round(wall->target_x) < round(app->player.x)) {
				wall->color = ft_pixel(255, 255, 0, 0); // Yellow for West
			} else {
				wall->color = ft_pixel(0, 0, 255, 0); // Blue for East
			}
		} else if (cos(ray_angle) > 0.0) {
			if (fabs(wall->target_x - floor(wall->target_x + 0.5f)) < 0.01f) {
				wall->color = ft_pixel(0, 0, 255, 0); // Blue for East
			} else {
				wall->color = ft_pixel(255, 255, 0, 0); // Yellow for West
			}
		} else {
			if (fabs(wall->target_x - floor(wall->target_x + 0.5f)) < 0.01f) {
				wall->color = ft_pixel(255, 255, 0, 0); // Yellow for West
			} else {
				wall->color = ft_pixel(0, 0, 255, 0); // Blue for East
			}
		}
	} else {
		if (fabs(sin(ray_angle)) > 0.999) {
			// Close to perpendicular angle, treat as north or south based on target_y
			if (round(wall->target_y) < round(app->player.y)) {
				wall->color = ft_pixel(255, 0, 0, 0); // Red for North
			} else {
				wall->color = ft_pixel(0, 255, 0, 0); // Green for South
			}
		} else if (sin(ray_angle) > 0.0) {
			if (fabs(wall->target_y - floor(wall->target_y + 0.5f)) < 0.01f) {
				wall->color = ft_pixel(0, 255, 0, 0); // Green for South
			} else {
				wall->color = ft_pixel(255, 0, 0, 0); // Red for North
			}
		} else {
			if (fabs(wall->target_y - floor(wall->target_y + 0.5f)) < 0.01f) {
				wall->color = ft_pixel(255, 0, 0, 0); // Red for North
			} else {
				wall->color = ft_pixel(0, 255, 0, 0); // Green for South
			}
		}
	}
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
		ray_angle = norm_ang(app->player.angle - app->fov / 2
			+ app->cur_ray * app->fov / app->num_rays);
		wall.distance = cast_ray(&app->player, ray_angle, &wall);
		wall.wall_height = (int)(app->window_height / (wall.distance + 0.01f));
		calc_side(app, ray_angle, &wall);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

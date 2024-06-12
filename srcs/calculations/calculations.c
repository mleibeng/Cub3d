/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/12 20:56:59 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

float	find_tyle_pos(t_tar *wall)
{
	if (wall->hit_vertical == 0)
		return (get_fractional_part(wall->target_x));
	else
		return (get_fractional_part(wall->target_y));
}

int	check_range(float num)
{
	if (get_fractional_part(num) < 0.005f)
		return (round(num));
	return ((int)num);
}

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
//	improved algorithm, higher accuracy for smaller distances
float	cast_ray(t_app *app, float ray_angle, t_tar *wall)
{
	float	depth;
	float	max_units;
	double	hit_x;
	double	hit_y;
	float	step_size = 0.01f;
	float	start;
	float	end;

	depth = 0.0f;
	max_units = 1.0f * (int)fmax(app->rows * 1.3, app->cols * 1.3);
	wall->hit_vertical = 0;
	while (depth < max_units)
	{
		wall->target_x = app->player.x + depth * cos(ray_angle);
		wall->target_y = app->player.y + depth * sin(ray_angle);
		if (wall->target_y >= 0 && wall->target_x >= 0
			&& wall->target_y <= app->rows && wall->target_x <= app->cols
			&& app->walked_map[(check_range)(wall->target_y)][(check_range)(wall->target_x)] == 1)
		{
			break;
		}
		depth += step_size;
	}

	start = depth - step_size;
	end = depth;
	while (end - start > 0.0005f)
	{
		depth = (start + end) / 2;
		wall->target_x = app->player.x + depth * cos(ray_angle);
		wall->target_y = app->player.y + depth * sin(ray_angle);
		if (wall->target_y >= 0 && wall->target_x >= 0
			&& wall->target_y <= app->rows && wall->target_x <= app->cols
			&& app->walked_map[check_range(wall->target_y)][check_range(wall->target_x)] == 1)
		{
			end = depth;
		}
		else
			start = depth;
	}
	hit_x = fabs(wall->target_x - round(wall->target_x));
	hit_y = fabs(wall->target_y - round(wall->target_y));
	wall->hit_vertical = (hit_y - 0.0005f) > (hit_x - 0.002);
	wall->pos_x_cur_tyle = find_tyle_pos(wall);
	return (depth * cos(app->player.angle - ray_angle));
}

//	function to calculate which direction faces tile from players perpective
void calc_side(float ray_angle, t_tar *wall, t_app *app)
{
    float dx = wall->target_x - app->player.x;
    float dy = wall->target_y - app->player.y;

    if (wall->hit_vertical)
    {
        if (dx == 0)
        {
            // Ray is parallel to the vertical wall
            wall->side = (sin(ray_angle) > 0) ? 1 : 2; // East or West
        }
        else if (dx < 0)
            wall->side = 1; // East
        else
            wall->side = 2; // West
    }
    else
    {
        if (dy == 0)
        {
            // Ray is parallel to the horizontal wall
            wall->side = (cos(ray_angle) < 0) ? 3 : 4; // South or North
        }
        else if (dy < 0)
            wall->side = 3; // South
        else
            wall->side = 4; // North
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
		wall.wall_height = (int)(app->window_height / (wall.distance + 0.01f));
		calc_side(ray_angle, &wall, app);
		draw_ray(app, &wall);
		app->cur_ray++;
	}
}

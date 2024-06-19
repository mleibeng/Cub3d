/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:01:27 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 18:08:20 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d_bonus.h"

int	check_wall_collision(t_app *app, float new_x, float new_y)
{
	float	player_radius;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;

	player_radius = PLAYER_SIZE;
	min_x = (int)(new_x - player_radius);
	max_x = (int)(new_x + player_radius);
	min_y = (int)(new_y - player_radius);
	max_y = (int)(new_y + player_radius);
	if (min_x < 0 || max_x >= app->cols || min_y < 0 || max_y >= app->rows)
		return (1);
	if (app->val_map[min_y][min_x] == 1 || app->val_map[min_y][max_x] == 1
		|| app->val_map[max_y][min_x] == 1
		|| app->val_map[max_y][max_x] == 1)
		return (1);
	if (app->val_map[min_y][min_x] == 3 || app->val_map[min_y][max_x] == 3
		|| app->val_map[max_y][min_x] == 3
		|| app->val_map[max_y][max_x] == 3)
		return (2);
	return (0);
}

void	move_sideways(t_app *app, float *new_x, float *new_y)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_D) && !mlx_is_key_down(app->mlx,
			MLX_KEY_A))
	{
		*new_x = app->player.x - PLAYER_MOVE_SPEED * sin(app->player.angle);
		*new_y = app->player.y + PLAYER_MOVE_SPEED * cos(app->player.angle);
		if (check_wall_collision(app, *new_x, app->player.y) == 0)
			app->player.x = *new_x;
		if (check_wall_collision(app, app->player.x, *new_y) == 0)
			app->player.y = *new_y;
	}
	else if (mlx_is_key_down(app->mlx, MLX_KEY_A) && !mlx_is_key_down(app->mlx,
			MLX_KEY_D))
	{
		*new_x = app->player.x + PLAYER_MOVE_SPEED * sin(app->player.angle);
		*new_y = app->player.y - PLAYER_MOVE_SPEED * cos(app->player.angle);
		if (check_wall_collision(app, *new_x, app->player.y) == 0)
			app->player.x = *new_x;
		if (check_wall_collision(app, app->player.x, *new_y) == 0)
			app->player.y = *new_y;
	}
}

void	speed_change(float *speed_mode, float *speed, t_app *app)
{
	*speed = *speed_mode;
	if (*speed_mode <= 0.99f && mlx_is_key_down(app->mlx, MLX_KEY_EQUAL))
		*speed_mode += 0.01f;
	if (*speed_mode >= 0.05f && mlx_is_key_down(app->mlx, MLX_KEY_MINUS))
		*speed_mode -= 0.05f;
}

void	move_for_back(t_app *app, float *new_x, float *new_y)
{
	static float	speed_mode = PLAYER_MOVE_SPEED;
	float			speed;

	speed_change(&speed_mode, &speed, app);
	if (mlx_is_key_down(app->mlx, MLX_KEY_W) && !mlx_is_key_down(app->mlx,
			MLX_KEY_S))
	{
		*new_x = app->player.x + speed * cos(app->player.angle);
		*new_y = app->player.y + speed * sin(app->player.angle);
		if (check_wall_collision(app, *new_x, app->player.y) == 0)
			app->player.x = *new_x;
		if (check_wall_collision(app, app->player.x, *new_y) == 0)
			app->player.y = *new_y;
	}
	else if (mlx_is_key_down(app->mlx, MLX_KEY_S) && !mlx_is_key_down(app->mlx,
			MLX_KEY_W))
	{
		*new_x = app->player.x - speed * cos(app->player.angle);
		*new_y = app->player.y - speed * sin(app->player.angle);
		if (check_wall_collision(app, *new_x, app->player.y) == 0)
			app->player.x = *new_x;
		if (check_wall_collision(app, app->player.x, *new_y) == 0)
			app->player.y = *new_y;
	}
}

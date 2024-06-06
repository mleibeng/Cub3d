/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/06 21:11:38 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	key functions
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app		*app;
	t_player	player;

	app = (t_app *)param;
	player = app->player;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(app->mlx);
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		printf("Position X: %f Y : %f deg: %f\n", player.x, player.y,
			cos(player.angle));
		printf("%f", player.x * (player.angle - player.std_angle));
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		player.x = player.std_x;
		player.y = player.std_y;
		player.angle = player.std_angle;
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		app->compass->instances[0].z *= -1;
		mlx_clear_image(app->mlx, app->compass);

	}
}

//	this function calculates the shift of the coordinates with W and S keys
void	direction_change_hook(t_app *app)
{
	float	move_x;
	float	move_y;
	float	max_dis_x;
	float	max_dis_y;

	move_x = PLAYER_MOVE_SPEED * cos(app->player.angle);
	move_y = PLAYER_MOVE_SPEED * sin(app->player.angle);
	max_dis_x = MAP_HEIGHT - 1.2f;
	max_dis_y = MAP_WIDTH - 1.2f;
	if (mlx_is_key_down(app->mlx, MLX_KEY_UP)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_DOWN))
	{
		if (app->player.x + move_x < max_dis_x && app->player.x + move_x > 1.2f)
			app->player.x = norm_ang(app->player.x + move_x);
		if (app->player.y + move_y < max_dis_y && app->player.y + move_y > 1.2f)
			app->player.y = norm_ang(app->player.y + move_y);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_UP))
	{
		if (app->player.x - move_x < max_dis_x && app->player.x - move_x > 1.2f)
			app->player.x = norm_ang(app->player.x - move_x);
		if (app->player.y - move_y < max_dis_y && app->player.y - move_y > 1.2f)
			app->player.y = norm_ang(app->player.y - move_y);
	}
}

//	this function calculates the shift of the coordinates with the A and D keys
void	view_change_hook(t_app *app)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		app->player.angle -= PLAYER_ROTATE_SPEED;
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		app->player.angle += PLAYER_ROTATE_SPEED;
}

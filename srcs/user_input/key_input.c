/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/14 18:51:56 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to check and change the door status (open or closed)
void	door_open_close(t_app *app)
{
	float	new_x;
	float	new_y;

	new_x = app->player.x;
	new_y = app->player.y;
	if ((app->player.angle > ((M_PI * 2) - M_PI_4)
			&& app->player.angle < ((M_PI * 2)))
		|| (app->player.angle > 0 && app->player.angle < M_PI_4))
		new_x += 1.0f;
	else if (app->player.angle > (M_PI_2 - M_PI_4)
		&& app->player.angle < (M_PI_2 + M_PI_4))
		new_y += 1.0f;
	else if (app->player.angle > (M_PI - M_PI_4)
		&& app->player.angle < (M_PI + M_PI_4))
		new_x -= 1.0f;
	else if (app->player.angle > ((M_PI * 3) / 2 - M_PI_4)
		&& app->player.angle < ((M_PI * 3) / 2 + M_PI_4))
		new_y -= 1.0f;
	if (app->walked_map[(int)new_y][(int)new_x] == 3)
	{
		if (app->last_open_door_y != -1 && app->last_open_door_x != -1
			&& app->walked_map[app->last_open_door_y][app->last_open_door_x] == 4)
			app->walked_map[app->last_open_door_y][app->last_open_door_x] = 3;
		app->closing_counter = 0;
		app->walked_map[(int)new_y][(int)new_x] = 4;
		app->closing_counter = 100;
		app->last_open_door_x = (int)new_x;
		app->last_open_door_y = (int)new_y;
	}
}

//	key functions
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app		*app;
	t_player	player;

	app = (t_app *)param;
	if (!app)
		return ;
	player = app->player;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(app->mlx);
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		printf("Position X: %f Y : %f deg: %f map_pos: %d\n", player.x,
			player.y, player.angle,
			app->walked_map[(int)app->player.y][(int)app->player.x]);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		app->player.x = player.std_x;
		app->player.y = player.std_y;
		app->player.angle = player.std_angle;
	}
	if ((keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS))
		door_open_close(app);
}

void	direction_change_hook(t_app *app)
{
	float	new_x;
	float	new_y;

	new_x = 0.0f;
	new_y = 0.0f;
	move_for_back(app, &new_x, &new_y);
	move_sideways(app, &new_x, &new_y);
}


//	this function calculates the shift of the coordinates with the A and D keys
void	view_change_hook(t_app *app)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT) && !mlx_is_key_down(app->mlx,
			MLX_KEY_RIGHT))
		app->player.angle = norm_ang(app->player.angle - PLAYER_ROTATE_SPEED);
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT) && !mlx_is_key_down(app->mlx,
			MLX_KEY_LEFT))
		app->player.angle = norm_ang(app->player.angle + PLAYER_ROTATE_SPEED);
}

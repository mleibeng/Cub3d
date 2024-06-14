/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/14 14:33:57 by fkeitel          ###   ########.fr       */
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
		app->walked_map[(int)new_y][(int)new_x] = 4;
	else if (app->walked_map[(int)new_y][(int)new_x] == 4)
		app->walked_map[(int)new_y][(int)new_x] = 3;
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
		player.x = player.std_x;
		player.y = player.std_y;
		player.angle = player.std_angle;
	}
	if ((keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS))
		door_open_close(app);
}

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
	if (app->walked_map[min_y][min_x] == 1 || app->walked_map[min_y][max_x] == 1
		|| app->walked_map[max_y][min_x] == 1
		|| app->walked_map[max_y][max_x] == 1)
		return (1);
	if (app->walked_map[min_y][min_x] == 3 || app->walked_map[min_y][max_x] == 3
		|| app->walked_map[max_y][min_x] == 3
		|| app->walked_map[max_y][max_x] == 3)
		return (2);
	return (0);
}

//	this function calculates the shift of the coordinates with W and S keys
void	direction_change_hook(t_app *app)
{
	float	new_x;
	float	new_y;

	if (mlx_is_key_down(app->mlx, MLX_KEY_UP) && !mlx_is_key_down(app->mlx,
			MLX_KEY_DOWN))
	{
		new_x = app->player.x + PLAYER_MOVE_SPEED * cos(app->player.angle);
		new_y = app->player.y + PLAYER_MOVE_SPEED * sin(app->player.angle);
		if (check_wall_collision(app, new_x, app->player.y) == 0)
			app->player.x = new_x;
		if (check_wall_collision(app, app->player.x, new_y) == 0)
			app->player.y = new_y;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN) && !mlx_is_key_down(app->mlx,
			MLX_KEY_UP))
	{
		new_x = app->player.x - PLAYER_MOVE_SPEED * cos(app->player.angle);
		new_y = app->player.y - PLAYER_MOVE_SPEED * sin(app->player.angle);
		if (check_wall_collision(app, new_x, app->player.y) == 0)
			app->player.x = new_x;
		if (check_wall_collision(app, app->player.x, new_y) == 0)
			app->player.y = new_y;
	}
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

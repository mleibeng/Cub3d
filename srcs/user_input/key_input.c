/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/09 02:14:22 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		mlx_close_window(app->mlx);
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		printf("Position X: %f Y : %f deg: %f map_pos: %d\n", player.x,
			player.y, cos(player.angle),
			app->walked_map[(int)app->player.y][(int)app->player.x]);
		// printf("angle%f\n", player.x * (player.angle - player.std_angle));
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		player.x = player.std_x;
		player.y = player.std_y;
		player.angle = player.std_angle;
	}
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
	return (0);
}

//	this function calculates the shift of the coordinates with W and S keys
void	direction_change_hook(t_app *app)
{
	float		move_x;
	float		move_y;
	float		new_x;
	float		new_y;
	static int	key_pressed = 0;

	move_x = PLAYER_MOVE_SPEED * cos(app->player.angle);
	move_y = PLAYER_MOVE_SPEED * sin(app->player.angle);
	if (mlx_is_key_down(app->mlx, MLX_KEY_UP) && !mlx_is_key_down(app->mlx,
			MLX_KEY_DOWN))
	{
		new_x = app->player.x + move_x;
		new_y = app->player.y + move_y;
		if (check_wall_collision(app, new_x, app->player.y) == 0)
			app->player.x = norm_ang(new_x);
		if (check_wall_collision(app, app->player.x, new_y) == 0)
			app->player.y = norm_ang(new_y);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN) && !mlx_is_key_down(app->mlx,
			MLX_KEY_UP))
	{
		new_x = app->player.x - move_x;
		new_y = app->player.y - move_y;
		if (check_wall_collision(app, new_x, app->player.y) == 0)
			app->player.x = norm_ang(new_x);
		if (check_wall_collision(app, app->player.x, new_y) == 0)
			app->player.y = norm_ang(new_y);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_C) && key_pressed == 0)
	{
		if (app->compass->instances[0].z == 10)
		{
			app->compass->instances[0].z = 0;
		}
		else
		{
			app->compass->instances[0].z = 10;
		}
		mlx_image_to_window(app->mlx, app->compass, app->window_width
			- COMPASS_SIZE - 10, 10);
		key_pressed = 1;
	}
	else if (!mlx_is_key_down(app->mlx, MLX_KEY_C))
		key_pressed = 0;
}

//	this function calculates the shift of the coordinates with the A and D keys
void	view_change_hook(t_app *app)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT) && !mlx_is_key_down(app->mlx,
			MLX_KEY_RIGHT))
		app->player.angle -= PLAYER_ROTATE_SPEED;
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT) && !mlx_is_key_down(app->mlx,
			MLX_KEY_LEFT))
		app->player.angle += PLAYER_ROTATE_SPEED;
	mouse_shift(app);
}

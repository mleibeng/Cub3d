/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/04 16:40:12 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	key functions
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(app->mlx);
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		printf("Position X: %f Y : %f deg: %f\n", app->player.x, app->player.y,
			cos(app->player.angle));
		printf("%f", app->player.x * (app->player.angle - app->player.std_angle));
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		app->player.x = app->player.std_x;
		app->player.y = app->player.std_y;
		app->player.angle = app->player.std_angle;
	}
}

//	this function calculates the shift of the coordinates with the arrow keys
int	ft_hook_key(t_app *app)
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
			app->player.x += move_x;
		if (app->player.y + move_y < max_dis_y && app->player.y + move_y > 1.2f)
			app->player.y += move_y;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_UP))
	{
		if (app->player.x - move_x < max_dis_x && app->player.x - move_x > 1.2f)
			app->player.x -= move_x;
		if (app->player.y - move_y < max_dis_y && app->player.y - move_y > 1.2f)
			app->player.y -= move_y;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
	{
		app->player.angle -= PLAYER_ROTATE_SPEED;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
	{
		app->player.angle += PLAYER_ROTATE_SPEED;
	}
	return (0);
}

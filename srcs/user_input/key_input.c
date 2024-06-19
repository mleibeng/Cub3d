/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:49:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 18:30:49 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function enables the manual
// int	information(t_app *app)
// {
// 	static int	key_pressed = OFF;
// 	static int	manual_status = ON;

// 	if (mlx_is_key_down(app->mlx, MLX_KEY_I) && key_pressed == OFF)
// 	{
// 		if (manual_status == OFF)
// 		{
// 			remove_manual_from_app(app);
// 			manual_status = ON;
// 		}
// 		else if (manual_status == ON)
// 		{
// 			manual_status = OFF;
// 			print_manual(app);
// 		}
// 		key_pressed = ON;
// 		return (1);
// 	}
// 	else if (!mlx_is_key_down(app->mlx, MLX_KEY_I))
// 		key_pressed = OFF;
// 	return (0);
// }

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
			app->val_map[(int)app->player.y][(int)app->player.x]);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		app->player.x = player.std_x;
		app->player.y = player.std_y;
		app->player.angle = player.std_angle;
	}
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

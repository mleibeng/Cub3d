/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:08:05 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 00:07:18 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_position(t_app *app, float new_x, float new_y)
{
	if (app->walked_map[(int)new_y][(int)new_x] == 3)
	{
		if (app->l_op_door_y != -1 && app->l_op_door_x != -1
			&& app->walked_map[app->l_op_door_y][app->l_op_door_x] == 4)
			app->walked_map[app->l_op_door_y][app->l_op_door_x] = 3;
		app->closing_counter = 0;
		app->walked_map[(int)new_y][(int)new_x] = 4;
		app->closing_counter = 100;
		app->l_op_door_x = (int)new_x;
		app->l_op_door_y = (int)new_y;
	}
}

void	calculate_new_position(t_app *app, float *new_x, float *new_y)
{
	*new_x = app->player.x;
	*new_y = app->player.y;
	if ((app->player.angle > ((M_PI * 2) - M_PI_4) && app->player.angle < ((M_PI
					* 2))) || (app->player.angle > 0
			&& app->player.angle < M_PI_4))
		*new_x += 1.0f;
	else if (app->player.angle > (M_PI_2 - M_PI_4)
		&& app->player.angle < (M_PI_2 + M_PI_4))
		*new_y += 1.0f;
	else if (app->player.angle > (M_PI - M_PI_4) && app->player.angle < (M_PI
			+ M_PI_4))
		*new_x -= 1.0f;
	else if (app->player.angle > ((M_PI * 3) / 2 - M_PI_4)
		&& app->player.angle < ((M_PI * 3) / 2 + M_PI_4))
		*new_y -= 1.0f;
}

void	door_open_close(t_app *app)
{
	float	new_x;
	float	new_y;

	calculate_new_position(app, &new_x, &new_y);
	update_player_position(app, new_x, new_y);
}

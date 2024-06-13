/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:34:11 by flo               #+#    #+#             */
/*   Updated: 2024/06/13 18:28:08 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//This try also doesnt work...
void	door_hook(t_app *app)
{
	static int	cooldown_counter = 0;
	int			x;
	int			y;

	const int cooldown_duration = 0;
	if (mlx_is_key_down(app->mlx, MLX_KEY_SPACE))
	{
		x = (int)(app->player.x + 0.5 * cos(app->player.angle));
		y = (int)(app->player.y + 0.5 * sin(app->player.angle));
		if ((app->walked_map[x][y] == 3 || app->walked_map[x][y] == 4)
			&& cooldown_counter == 0)
		{
			app->walked_map[x][y] = (app->walked_map[x][y] == 3) ? 4 : 3;
			cooldown_counter = cooldown_duration;
			write(1, &app->walked_map[x][y], 1);
		}
	}
	if (cooldown_counter > 0)
	{
		cooldown_counter--;
	}
}
//	function to handle all key and mouse hooks
void	user_input_hook(t_app *app)
{
	view_change_hook(app);
	mouse_shift(app);
	door_hook(app);
	direction_change_hook(app);
}

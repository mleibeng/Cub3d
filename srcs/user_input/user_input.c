/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:34:11 by flo               #+#    #+#             */
/*   Updated: 2024/06/13 16:28:13 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void door_hook(t_app *app)
{
    static int cooldown_counter = 0;
    const int cooldown_duration = 0; // Cooldown duration in frames

    if (mlx_is_key_down(app->mlx, MLX_KEY_SPACE))
    {
        int x = (int)(app->player.x + 0.5 * cos(app->player.angle));
        int y = (int)(app->player.y + 0.5 * sin(app->player.angle));

        if ((app->walked_map[x][y] == 3 || app->walked_map[x][y] == 4) && cooldown_counter == 0)
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

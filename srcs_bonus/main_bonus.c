/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/19 18:31:18 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

//	function to close a door after certain time
void	close_last_door(t_app *app)
{
	if (app->closing_counter > 0 && (int)app->player.x != app->l_op_door_x
		&& (int)app->player.y != app->l_op_door_y)
		app->closing_counter--;
	if (app->l_op_door_x != -1 && app->l_op_door_y != -1
		&& app->closing_counter == 0 && (int)app->player.x != app->l_op_door_x
		&& (int)app->player.y != app->l_op_door_y)
	{
		app->val_map[app->l_op_door_y][app->l_op_door_x] = 3;
		app->l_op_door_x = -1;
		app->l_op_door_y = -1;
	}
}

//	main loop function, if there is a change in movement
void	main_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	user_input_hook(app);
	calc_walls(app);
	display_minimap(app);
	display_compass(app, app->player.angle);
	draw_weapon(app);
	close_last_door(app);
}

int	is_not_cub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (1);
	return (ft_strcmp(file + len - 4, ".cub"));
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (printf("Error\nNo *.cub file as argument\n"));
	if (is_not_cub(argv[1]))
		return (printf("Error\nNo .cub file handed as argument\n"));
	app.map = map_validate(&app, argv[1]);
	if (!app.map)
		emergency_exit(&app, app.textures, app.map);
	if (_init_app(&app))
		return (1);
	mlx_set_cursor_mode(app.mlx, MLX_MOUSE_HIDDEN);
	if (app.map)
	{
		mlx_key_hook(app.mlx, key_hook, &app);
		mlx_loop_hook(app.mlx, main_loop, &app);
		mlx_loop(app.mlx);
		mlx_delete_image(app.mlx, app.img);
		mlx_terminate(app.mlx);
		free_all_resources(&app);
	}
	return (0);
}

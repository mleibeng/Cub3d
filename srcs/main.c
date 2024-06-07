/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/07 12:17:02 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// int			g_map[MAP_WIDTH][MAP_HEIGHT] = {
// 	{1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1},
// };

//	main loop function, if there is a change in movement
void	loop_hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app)
		return ;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	calc_walls(app);
	mlx_image_to_window(app->mlx, app->img, 0, 0);
	display_compass(app, app->player.angle);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (1);
	if (!(app.map = map_validate(&app, argv[1])))
		return (1);
	if (_init_app(&app))
		return (1);
	print_info(&app);
	mlx_image_to_window(app.mlx, app.compass, app.window_width - COMPASS_SIZE
		- 10, 10);
	app.compass->instances->z = 1;
	if (app.map)
	{
		mlx_key_hook(app.mlx, key_hook, &app);
		mlx_loop_hook(app.mlx, loop_hook, &app);
		mlx_loop(app.mlx);
		mlx_delete_image(app.mlx, app.img);
		mlx_terminate(app.mlx);
	}
	return (0);
}

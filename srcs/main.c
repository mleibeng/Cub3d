/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/05 23:43:25 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int				g_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1},
};

void	loop_hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	calc_walls(app);
	mlx_image_to_window(app->mlx, app->img, 0, 0);
	display_compass(app, app->player.angle);
}

int	main(void)
{
	t_app app;
	app.player.x = 2;
	app.player.y = 2;
	app.player.angle = M_PI / 2;
	app.player.std_x = app.player.x;
	app.player.std_y = app.player.y;
	app.player.std_angle = app.player.angle;
	app.fov = (M_PI / 3);
	app.window_width = 640;
	app.window_height = 640;
	app.num_rays = app.window_width;
	app.cur_ray = 0;
	app.mlx = mlx_init(app.window_height, app.window_height, "cub3d", true);
	if (!app.mlx)
		return (1);
	app.compass = mlx_new_image(app.mlx, COMPASS_SIZE, COMPASS_SIZE);
	app.img = mlx_new_image(app.mlx, app.window_width, app.window_height);
	if (!app.img || !app.compass)
	{
		mlx_terminate(app.mlx);
		return (1);
	}
	mlx_image_to_window(app.mlx, app.compass, app.window_width - COMPASS_SIZE - 10, 10);
	app.compass->instances->z = 1;
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_loop(app.mlx);
	mlx_delete_image(app.mlx, app.img);
	mlx_terminate(app.mlx);
	return (0);
}

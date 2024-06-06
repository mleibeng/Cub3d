/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/06 21:07:22 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int	g_map[MAP_WIDTH][MAP_HEIGHT] = {
{1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1},
};

//	main loop function, if there is a change in movement
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

//	main function
int	main(void)
{
	t_app	app;

	app.player.x = 2;
	app.player.y = 2;
	app.player.angle = M_PI / 2;
	app.player.std_x = app.player.x;
	app.player.std_y = app.player.y;
	app.player.std_angle = app.player.angle;
	app.fov = (M_PI / 3);
	app.window_width = 620;
	app.window_height = 480;
	app.num_rays = app.window_width;
	app.cur_ray = 0;
	app.mlx = mlx_init(app.window_width, app.window_height, "cub3d", true);
	if (!app.mlx)
	{
		ft_printf("Failed to initialize MLX.\n");
		return (1);
	}
	ft_printf("MLX initialized successfully.\n");

	app.img = mlx_new_image(app.mlx, app.window_width, app.window_height);
	if (!app.img)
	{
		ft_printf("Failed to create main image.\n");
		mlx_terminate(app.mlx);
		return (1);
	}
	app.img->count = 1;
	app.img->instances = malloc(sizeof(app.img->instances)
			* app.img->count);
	if (!app.img->instances)
	{
		ft_printf("Failed to allocate memory for img instances.\n");
		mlx_terminate(app.mlx);
		return (1);
	}
	app.img->instances[0].z = 0;
	ft_printf("Main image created successfully.\n");
	if (init_compass(&app) == 1)
	{
		ft_printf("Failed to initialize compass.\n");
		mlx_terminate(app.mlx);
		return (1);
	}
	ft_printf("Compass image initialized successfully.\n");
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_loop(app.mlx);
	mlx_delete_image(app.mlx, app.img);
	mlx_terminate(app.mlx);
	return (0);
}

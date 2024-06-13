/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/13 19:52:37 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	main loop function, if there is a change in movement

void	free_all_resources(t_app *app)
{
	if (app->map)
	{
		free_map((void **)app->map);
		app->map = NULL;
	}
	// if (app->walked_map)
	// {
	// 	free_map((void**)app->walked_map);
	// 	app->walked_map = NULL;
	// }
	// if (app->minimap)
	// {
	// 	free_map((void**)app->minimap);
	// 	app->minimap = NULL;
	// }
	if (app->textures)
	{
		free(app->textures);
	}
}

void	main_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	user_input_hook(app);
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	calc_walls(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1)
		exit(1);
	display_minimap(app);
	display_compass(app, app->player.angle);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (1);
	app.map = map_validate(&app, argv[1]);
	if (!app.map)
		return (1);
	if (_init_app(&app))
		return (1);
	print_info(&app);
	if (app.map)
	{
		mlx_key_hook(app.mlx, key_hook, &app);
		mlx_loop_hook(app.mlx, main_loop, &app);
		mlx_loop(app.mlx);
		mlx_delete_image(app.mlx, app.img);
		mlx_delete_image(app.mlx, app.minimap_img);
		mlx_delete_image(app.mlx, app.compass);
		mlx_terminate(app.mlx);
		free_all_resources(&app);
	}
	return (0);
}

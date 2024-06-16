/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:42:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/16 13:15:13 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// initialite a coordinate point
t_coord	init_coord(int point_x, int point_y, int32_t color)
{
	t_coord	new_coord;

	new_coord.xw = point_x;
	new_coord.yw = point_y;
	new_coord.color = color;
	return (new_coord);
}

void	init_directions(t_vec *directions)
{
	directions[0].x = 0;
	directions[0].y = -1;
	directions[1].x = 0;
	directions[1].y = 1;
	directions[2].x = -1;
	directions[2].y = 0;
	directions[3].x = 1;
	directions[3].y = 0;
}

//	function to initiliaze the start values of the minimap

void	_init_vars(t_app *app)
{
	app->map_height = app->rows;
	app->map_width = app->cols;
	app->player.x = (float)app->player.start_x + PLAYER_SIZE;
	app->player.y = (float)app->player.start_y + PLAYER_SIZE;
	app->player.std_x = app->player.x;
	app->player.std_y = app->player.y;
	app->player.std_angle = app->player.angle;
	app->fov = (M_PI / 3);
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	app->num_rays = app->window_width;
	app->cur_ray = 0;
	app->minimap_img = NULL;
	app->compass = NULL;
	app->closing_counter = 0;
	app->l_op_door_x = -1;
	app->l_op_door_y = -1;
	app->manual = NULL;
}

//	function to initialize all the application struct
int	_init_app(t_app *app)
{
	_init_vars(app);
	app->mlx = mlx_init(app->window_width, app->window_height, "cub3d", false);
	if (!app->mlx)
		return (1);
	app->weapon = _init_weapon(app);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return (mlx_terminate(app->mlx), 1);
	app->img->count = 1;
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1 || init_compass(app)
		|| init_minimap(app))
		return (1);
	app->man = mlx_new_image(app->mlx, app->window_width, app->window_height);
	app->man = mlx_put_string(app->mlx, "Press <I> for manual",
			app->window_width / 2 - 100, 8);
	if (!app->man || create_manual(app) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (load_textures(app), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:42:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/08 19:52:01 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	initialite a coordinate point
t_coord	init_coord(int point_x, int point_y, int32_t color)
{
	t_coord	new_coord;

	new_coord.xw = point_x;
	new_coord.yw = point_y;
	new_coord.color = color;
	return (new_coord);
}

//	function to inititialize the compass and assiging the default values
int	init_compass(t_app *app)
{
	app->compass = mlx_new_image(app->mlx, COMPASS_SIZE, COMPASS_SIZE);
	if (!app->compass)
		return (mlx_terminate(app->mlx), 1);
	app->compass->count = 2;
	app->compass->instances = malloc(sizeof(mlx_instance_t)
			* app->compass->count);
	if (!app->compass->instances)
	{
		ft_printf("Failed to allocate memory for compass instances.\n");
		mlx_terminate(app->mlx);
		return (1);
	}
	if (app->compass->instances != NULL && app->compass->count > 0)
	{
		app->compass->instances[0].z = 10;
		app->compass->instances[0].enabled = true;

	}
	else
	{
		free(app->compass->instances);
		ft_printf("Error: Compass instances are not properly initialized.\n");
		return (1);
	}
	if (mlx_image_to_window(app->mlx, app->compass,
		app->window_width - COMPASS_SIZE - 10, 10) == -1)
		return (1);
	return (0);
}

void	_init_texture(t_texture *texture)
{
	texture->e_path = NULL;
	texture->n_path = NULL;
	texture->s_path = NULL;
	texture->w_path = NULL;
	ft_memset(texture->floor, 0, sizeof(texture->floor));
	ft_memset(texture->skybox, 0, sizeof(texture->skybox));
}

void load_textures(t_app *app)
{
	app->textures->n_text = mlx_load_xpm42(app->textures->n_path);
	app->textures->s_text = mlx_load_xpm42(app->textures->s_path);
	app->textures->e_text = mlx_load_xpm42(app->textures->e_path);
	app->textures->w_text = mlx_load_xpm42(app->textures->w_path);
	if (!app->textures->n_text)
		printf("hello\n");
}

int	_init_app(t_app *app)
{
	app->player.x = (float)app->player.start_x + 0.5;
	app->player.y = (float)app->player.start_y + 0.5;
	app->player.std_x = app->player.x;
	app->player.std_y = app->player.y;
	app->player.std_angle = app->player.angle;
	app->fov = (M_PI / 3);
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	app->num_rays = app->window_width;
	app->cur_ray = 0;
	app->mlx = mlx_init(app->window_width, app->window_height, "cub3d", true);
	if (!app->mlx)
		return (1);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
	{
		mlx_terminate(app->mlx);
		return (1);
	}
	app->img->count = 2;
	app->img->instances = malloc(sizeof(mlx_instance_t)
			* app->img->count);
	if (!app->img->instances)
	{
		ft_printf("Failed to allocate memory for img instances.\n");
		mlx_terminate(app->mlx);
		return (1);
	}
	if (app->img->instances != NULL && app->img->count > 0)
	{
		app->img->instances[1].enabled = true;
		app->img->instances[0].z = 5;
	}
	else
	{
		free(app->img->instances);
		ft_printf("Error: img instances are not properly initialized.\n");
		return (1);
	}
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1
		|| init_compass(app) == 1)
		return (1);
	load_textures(app);
	return (0);
}

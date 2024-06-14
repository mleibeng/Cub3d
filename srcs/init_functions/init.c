/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:42:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/14 17:11:31 by fkeitel          ###   ########.fr       */
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

//	function to initiliaze the start values of the minimap
int	init_minimap(t_app *app)
{
	app->minimap_img = mlx_new_image(app->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!app->minimap_img)
		return (mlx_terminate(app->mlx), 1);
	app->player_on_mini = mlx_new_image(app->mlx, MINIMAP_PLAYER,
			MINIMAP_PLAYER);
	if (!app->minimap_img)
		return (mlx_terminate(app->mlx), 1);
	app->minimap_img->count = 1;
	app->player_on_mini->count = 1;
	if (mlx_image_to_window(app->mlx, app->minimap_img, 0, 0) == -1)
		return (1);
	if (mlx_image_to_window(app->mlx, app->player_on_mini, MINIMAP_SIZE / 2,
			MINIMAP_SIZE / 2) == -1)
		return (1);
	return (0);
}

//	function to inititialize the compass and assiging the default values
int	init_compass(t_app *app)
{
	app->compass = mlx_new_image(app->mlx, COMPASS_SIZE, COMPASS_SIZE);
	if (!app->compass)
		return (mlx_terminate(app->mlx), 1);
	app->compass->count = 1;
	if (mlx_image_to_window(app->mlx, app->compass, app->window_width
			- COMPASS_SIZE - 10, 10) == -1)
		return (1);
	return (0);
}

void	_init_texture(t_texture *texture)
{
	texture->e_path = NULL;
	texture->n_path = NULL;
	texture->s_path = NULL;
	texture->w_path = NULL;
	texture->d_path = NULL;
	ft_memset(texture->floor, 0, sizeof(texture->floor));
	ft_memset(texture->skybox, 0, sizeof(texture->skybox));
}

void	load_textures(t_app *app)
{
	app->textures->n_text = mlx_load_xpm42(app->textures->n_path);
	app->textures->s_text = mlx_load_xpm42(app->textures->s_path);
	app->textures->e_text = mlx_load_xpm42(app->textures->e_path);
	app->textures->w_text = mlx_load_xpm42(app->textures->w_path);
	app->textures->d_text = mlx_load_xpm42(app->textures->d_path);
	if (!app->textures->n_text)
		printf("hello\n");
}

t_weapon	*_init_weapon(t_app *app)
{
	t_weapon	*weapon;

	weapon = malloc(sizeof(t_weapon));
	if (!weapon)
		free_all_resources(app);
	weapon->sprite = mlx_load_png("./textures/PCComputer-Wolfenstein3D-Weapons-ezgif.com-crop.png");
	if (!weapon->sprite)
		free_all_resources(app);
	weapon->sprite_act = mlx_load_png("./textures/weapon_with_transparency.png");
	if (!weapon->sprite_act)
		free_all_resources(app);
	weapon->img = mlx_texture_to_image(app->mlx, weapon->sprite);
	weapon->state = HOLSTERED;
	return (weapon);
}

int	_init_app(t_app *app)
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
	app->last_open_door_x = -1;
	app->last_open_door_y = -1;
	app->mlx = mlx_init(app->window_width, app->window_height, "cub3d", true);
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
	return (load_textures(app), 0);
}

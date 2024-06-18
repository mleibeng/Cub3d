/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:53:54 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 01:54:03 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function toi nitialize the texture of the tyles
void	_init_texture(t_texture *texture)
{
	texture->e_path = NULL;
	texture->n_path = NULL;
	texture->s_path = NULL;
	texture->w_path = NULL;
	texture->d_path = NULL;
	texture->d_text = NULL;
	texture->n_text = NULL;
	texture->s_text = NULL;
	texture->w_text = NULL;
	texture->e_text = NULL;
	ft_memset(texture->floor, -1, sizeof(texture->floor));
	ft_memset(texture->skybox, -1, sizeof(texture->skybox));
}

//	function to convert the texture paths to texture structs
void	load_textures(t_app *app)
{
	app->textures->n_text = mlx_load_xpm42(app->textures->n_path);
	app->textures->s_text = mlx_load_xpm42(app->textures->s_path);
	app->textures->e_text = mlx_load_xpm42(app->textures->e_path);
	app->textures->w_text = mlx_load_xpm42(app->textures->w_path);
	if (app->textures->d_path)
		app->textures->d_text = mlx_load_xpm42(app->textures->d_path);
	if (!app->textures->n_text)
		emergency_exit(app, app->textures, NULL);
}

//	funciton to initlialize all minmap image instances
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
	if (mlx_image_to_window(app->mlx, app->compass, WINDOW_WIDTH / 1.1,
			WINDOW_HEIGHT / 75) == -1)
		return (1);
	return (0);
}

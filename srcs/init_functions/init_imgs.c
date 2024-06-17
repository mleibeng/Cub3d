/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:53:54 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/17 04:27:46 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_weapon	*_init_weapon(t_app *app)
{
	t_weapon	*weapon;

	weapon = malloc(sizeof(t_weapon));
	if (!weapon)
		free_all_resources(app);
	weapon->sprite = mlx_load_png("./textures/Jagknife.png");
	if (!weapon->sprite)
		free_all_resources(app);
	weapon->sprite_act = mlx_load_png("./textures/Jagknife.png");
	if (!weapon->sprite_act)
		free_all_resources(app);
	weapon->state = HOLSTERED;
	return (weapon);
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
	if (app->textures->d_path)
		app->textures->d_text = mlx_load_xpm42(app->textures->d_path);
	if (!app->textures->n_text)
		printf("hello\n");
}

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
	if (mlx_image_to_window(app->mlx, app->compass, WINDOW_WIDTH / 1.1, WINDOW_HEIGHT / 75) == -1)
		return (1);
	return (0);
}

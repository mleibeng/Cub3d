/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:53:54 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/17 17:20:23 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to initialize the weapon struct
t_weapon	*_init_weapon(t_app *app)
{
	t_weapon	*weapon;

	weapon = malloc(sizeof(t_weapon));
	if (!weapon)
		free_all_resources(app);
	weapon->sprite = mlx_load_png("./textures/weapons/Jagknife.png");
	if (!weapon->sprite)
		free_all_resources(app);
	weapon->sprite_act = mlx_load_png("./textures/weapons/Jagpistol.png");
	if (!weapon->sprite_act)
		free_all_resources(app);
	weapon->state = HOLSTERED;
	weapon->weapon = 0;
	weapon->animation[0] = mlx_load_png("./textures/FPS Weapon Sprites/frames/punch1.png");
	weapon->animation[1] = mlx_load_png("./textures/FPS Weapon Sprites/frames/punch2.png");
	weapon->animation[2] = mlx_load_png("./textures/FPS Weapon Sprites/frames/punch3.png");
	weapon->animation[3] = mlx_load_png("./textures/FPS Weapon Sprites/frames/pistol1.png");
	weapon->animation[4] = mlx_load_png("./textures/FPS Weapon Sprites/frames/pistol2.png");
	weapon->animation[5] = mlx_load_png("./textures/FPS Weapon Sprites/frames/pistol3.png");
	weapon->animation[6] = mlx_load_png("./textures/FPS Weapon Sprites/frames/pistol4.png");
	weapon->animation[7] = mlx_load_png("./textures/FPS Weapon Sprites/frames/pistol5.png");
	weapon->animation[8] = mlx_load_png("./textures/FPS Weapon Sprites/frames/shotgun1.png");
	weapon->animation[9] = mlx_load_png("./textures/FPS Weapon Sprites/frames/shotgun2.png");
	weapon->animation[10] = mlx_load_png("./textures/FPS Weapon Sprites/frames/shotgun3.png");
	weapon->animation[11] = mlx_load_png("./textures/FPS Weapon Sprites/frames/shotgun4.png");
	weapon->animation[12] = mlx_load_png("./textures/FPS Weapon Sprites/frames/shotgun5.png");
	weapon->animation[13] = NULL;
	weapon->img = mlx_texture_to_image(app->mlx, weapon->sprite);
	weapon->active_image = mlx_texture_to_image(app->mlx, weapon->sprite_act);
	mlx_resize_image(weapon->img, weapon->img->width * 3,
		weapon->img->height * 3);
	mlx_resize_image(weapon->active_image, weapon->active_image->width * 3,
		weapon->active_image->height * 3);
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		weapon->punch[j] =  mlx_texture_to_image(app->mlx, weapon->animation[i++]);
		mlx_resize_image(weapon->punch[j], weapon->punch[j]->width * 3,
			weapon->punch[j]->height * 3);
		j++;
	}
	weapon->punch[j] = NULL;
	j = 0;
	while (j < 5)
	{
		weapon->pistol[j] =  mlx_texture_to_image(app->mlx, weapon->animation[i++]);
		mlx_resize_image(weapon->pistol[j], weapon->pistol[j]->width * 3,
			weapon->pistol[j]->height * 3);
		j++;
	}
	weapon->pistol[j] = NULL;
	j = 0;
	while (j < 5)
	{
		weapon->shotgun[j] =  mlx_texture_to_image(app->mlx, weapon->animation[i++]);
		mlx_resize_image(weapon->shotgun[j], weapon->shotgun[j]->width * 3,
			weapon->shotgun[j]->height * 3);
		j++;
	}
	weapon->shotgun[j] = NULL;
	return (weapon);
}

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
	ft_memset(texture->floor, 0, sizeof(texture->floor));
	ft_memset(texture->skybox, 0, sizeof(texture->skybox));
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
		printf("hello\n");
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
	if (mlx_image_to_window(app->mlx, app->compass,
			WINDOW_WIDTH / 1.1, WINDOW_HEIGHT / 75) == -1)
		return (1);
	return (0);
}

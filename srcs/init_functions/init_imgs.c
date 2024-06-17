/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:53:54 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 01:51:09 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	**animation_file_names(void)
{
	static const char	*animation_filenames[] = {"./textures/FPS Weapon Sprites/frames/punch1.png",
			"./textures/FPS Weapon Sprites/frames/punch2.png",
			"./textures/FPS Weapon Sprites/frames/punch3.png",
			"./textures/FPS Weapon Sprites/frames/pistol1.png",
			"./textures/FPS Weapon Sprites/frames/pistol2.png",
			"./textures/FPS Weapon Sprites/frames/pistol3.png",
			"./textures/FPS Weapon Sprites/frames/pistol4.png",
			"./textures/FPS Weapon Sprites/frames/pistol5.png",
			"./textures/FPS Weapon Sprites/frames/shotgun1.png",
			"./textures/FPS Weapon Sprites/frames/shotgun2.png",
			"./textures/FPS Weapon Sprites/frames/shotgun3.png",
			"./textures/FPS Weapon Sprites/frames/shotgun4.png",
			"./textures/FPS Weapon Sprites/frames/shotgun5.png", NULL};

	return (animation_filenames);
}

mlx_texture_t	*load_image(t_app *app, const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		free_all_resources(app);
	return (texture);
}

void	load_and_resize_animation(t_app *app, mlx_image_t **animation,
		const char **ani_fnames, int frame_count)
{
	int				i;
	int				j;
	mlx_texture_t	*texture;

	i = 0;
	j = 0;
	while (j < frame_count)
	{
		texture = load_image(app, ani_fnames[i++]);
		animation[j] = mlx_texture_to_image(app->mlx, texture);
		mlx_resize_image(animation[j], animation[j]->width * 3,
			animation[j]->height * 3);
		j++;
	}
	animation[j] = NULL;
}

//	function to initialize the weapon struct
t_weapon	*_init_weapon(t_app *app)
{
	t_weapon	*weapon;
	const char	**ani_fnames = animation_file_names();
	int			i;

	weapon = malloc(sizeof(t_weapon));
	if (!weapon)
		free_all_resources(app);
	weapon->sprite = load_image(app, "./textures/weapons/Jagknife.png");
	weapon->sprite_act = load_image(app, "./textures/weapons/Jagpistol.png");
	weapon->state = HOLSTERED;
	weapon->weapon = 0;
	i = 0;
	while (ani_fnames[i] != NULL)
	{
		weapon->animation[i] = load_image(app, ani_fnames[i]);
		i++;
	}
	weapon->img = mlx_texture_to_image(app->mlx, weapon->sprite);
	weapon->active_image = mlx_texture_to_image(app->mlx, weapon->sprite_act);
	load_and_resize_animation(app, weapon->punch, ani_fnames, 3);
	load_and_resize_animation(app, weapon->pistol, ani_fnames + 3, 5);
	load_and_resize_animation(app, weapon->shotgun, ani_fnames + 8, 5);
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

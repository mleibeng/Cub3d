/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_weap_anims_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:53:51 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/20 03:36:19 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

const char	**animation_file_names(void)
{
	static const char	*ani_fname[] = {"./textures/FPS/frames/punch1.png",
		"./textures/FPS/frames/punch2.png",
		"./textures/FPS/frames/punch3.png",
		"./textures/FPS/frames/punch4.png",
		"./textures/FPS/frames/punch5.png",
		"./textures/FPS/frames/pistol1.png",
		"./textures/FPS/frames/pistol2.png",
		"./textures/FPS/frames/pistol3.png",
		"./textures/FPS/frames/pistol4.png",
		"./textures/FPS/frames/pistol5.png",
		"./textures/FPS/frames/shotgun1.png",
		"./textures/FPS/frames/shotgun2.png",
		"./textures/FPS/frames/shotgun3.png",
		"./textures/FPS/frames/shotgun4.png",
		"./textures/FPS/frames/shotgun5.png", NULL};

	return (ani_fname);
}

mlx_texture_t	*load_image(t_app *app, const char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		free_all_resources_bonus(app);
	return (texture);
}

void	load_and_resize_animation(t_app *app, mlx_image_t **animation,
		const char **ani_fnames, int frame_count)
{
	int				j;
	mlx_texture_t	*texture;

	j = 0;
	while (j < frame_count)
	{
		texture = load_image(app, ani_fnames[j]);
		animation[j] = mlx_texture_to_image(app->mlx, texture);
		mlx_delete_texture(texture);
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

	weapon = malloc(sizeof(t_weapon));
	if (!weapon)
		free_all_resources_bonus(app);
	weapon->state = HOLSTERED;
	weapon->weapon = 0;
	weapon->punch[0] = NULL;
	weapon->pistol[0] = NULL;
	weapon->shotgun[0] = NULL;
	load_and_resize_animation(app, weapon->punch, ani_fnames, 5);
	load_and_resize_animation(app, weapon->pistol, ani_fnames + 5, 5);
	load_and_resize_animation(app, weapon->shotgun, ani_fnames + 10, 5);
	return (weapon);
}

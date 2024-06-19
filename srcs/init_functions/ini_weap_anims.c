/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_weap_anims.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:53:51 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/19 21:50:25 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	**animation_file_names(void)
{
	static const char	*ani_fname[] = {"./textures/FPS/frames/punch1.png",
		"./textures/FPS/frames/punch2.png",
		"./textures/FPS/frames/punch3.png",
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
	weapon->state = HOLSTERED;
	weapon->weapon = 0;
	i = 0;
	while (ani_fnames[i] != NULL)
	{
		weapon->animation[i] = load_image(app, ani_fnames[i]);
		i++;
	}
	load_and_resize_animation(app, weapon->punch, ani_fnames, 3);
	load_and_resize_animation(app, weapon->pistol, ani_fnames + 3, 5);
	load_and_resize_animation(app, weapon->shotgun, ani_fnames + 8, 5);
	return (weapon);
}

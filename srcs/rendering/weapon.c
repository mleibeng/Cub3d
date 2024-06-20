/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:47:07 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/20 03:33:55 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to animate the weapon firing
void	create_animation(t_app *app, mlx_image_t **weapon)
{
	static int	animate = 0;
	int			set_back;
	int			new_value;

	set_back = 2;
	new_value = animate / set_back;
	app->weapon->x = app->window_width / 2 - weapon[new_value]->width / 2;
	app->weapon->y = app->window_height - weapon[new_value]->height;
	put_img_to_img(app->img, weapon[new_value], app->weapon->x, app->weapon->y);
	if (++animate == 5 * set_back)
	{
		animate = 0;
		app->weapon->animation_start = HOLSTERED;
		put_img_to_img(app->img, weapon[0], app->weapon->x, app->weapon->y);
	}
}

//	function to select the right weapon
void	draw_weapon(t_app *app)
{
	static mlx_image_t	**cur_weapon = NULL;

	if (app->weapon->weapon == 0)
		cur_weapon = NULL;
	else if (app->weapon->weapon == 1)
		cur_weapon = app->weapon->pistol;
	else if (app->weapon->weapon == 2)
		cur_weapon = app->weapon->shotgun;
	else
		cur_weapon = app->weapon->punch;
	if (cur_weapon && app->weapon->animation_start == ANIMATE)
		create_animation(app, cur_weapon);
	else if (cur_weapon)
	{
		app->weapon->x = app->window_width / 2 - cur_weapon[0]->width / 2;
		app->weapon->y = app->window_height - cur_weapon[0]->height;
		put_img_to_img(app->img, cur_weapon[0], app->weapon->x, app->weapon->y);
	}
}

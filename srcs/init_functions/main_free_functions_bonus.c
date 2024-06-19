/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free_functions_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:32:03 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/20 00:16:31 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_weapon(t_app *app, t_weapon *weapon)
{
	int	i;

	i = 0;
	while (weapon->pistol[i])
		mlx_delete_image(app->mlx, weapon->pistol[i++]);
	i = 0;
	while (weapon->shotgun[i])
		mlx_delete_image(app->mlx, weapon->shotgun[i++]);
	i = 0;
	free(weapon);
}

void	free_all_resources_bonus(t_app *app)
{
	if (app->map)
	{
		free_map(app->map);
		app->map = NULL;
	}
	if (app->val_map)
	{
		free_intmap(app->val_map, app->rows);
		app->val_map = NULL;
	}
	if (app->minimap)
	{
		free_intmap(app->minimap, app->rows);
		app->minimap = NULL;
	}
	free_textures(app->textures);
	if (app->weapon)
		free_weapon(app, app->weapon);
	if (app->manual)
		free_manual(&app->manual);
}

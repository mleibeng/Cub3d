/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:42:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/06 20:54:31 by fkeitel          ###   ########.fr       */
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

	app->compass->count = 1;
	app->compass->instances = malloc(sizeof(app->compass->instances)
			* app->compass->count);
	if (!app->compass->instances)
	{
		ft_printf("Failed to allocate memory for compass instances.\n");
		mlx_terminate(app->mlx);
		return (1);
	}
	if (app->compass->instances != NULL && app->compass->count > 0)
		app->compass->instances[0].z = 10;
	else
	{
		free(app->compass->instances);
		ft_printf("Error: Compass instances are not properly initialized.\n");
		return (1);
	}
	mlx_image_to_window(app->mlx, app->compass,
		app->window_width - COMPASS_SIZE - 10, 10);
	return (0);
}

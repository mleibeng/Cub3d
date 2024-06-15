/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/15 20:01:23 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	main loop function, if there is a change in movement

void	free_all_resources(t_app *app)
{
	if (app->map)
	{
		free_map((void **)app->map);
		app->map = NULL;
	}
	if (app->walked_map)
	{
		free_map((void **)app->walked_map);
		app->walked_map = NULL;
	}
	if (app->minimap)
	{
		free_map((void **)app->minimap);
		app->minimap = NULL;
	}
	free_textures(app->textures);
	mlx_delete_texture(app->weapon->sprite);
	mlx_delete_texture(app->weapon->sprite_act);
	free(app->weapon);
	free_manual(&app->manual);
}

void	draw_weapon(t_app *app)
{
	mlx_texture_t	*current_texture;

	if (app->weapon->state == ACTIVE)
		current_texture = app->weapon->sprite_act;
	else
		current_texture = app->weapon->sprite;
	app->weapon->x = app->window_width / 2 - current_texture->width / 2;
	app->weapon->y = app->window_height - current_texture->height;
	if (app->weapon->img == NULL)
	{
		app->weapon->img = mlx_texture_to_image(app->mlx, current_texture);
		mlx_image_to_window(app->mlx, app->weapon->img, app->weapon->x,
			app->weapon->y);
	}
}

//	function to close a door after certain time
void	close_last_door(t_app *app)
{
	if (app->closing_counter > 0 && (int)app->player.x != app->l_op_door_x
		&& (int)app->player.y != app->l_op_door_y)
		app->closing_counter--;
	if (app->l_op_door_x != -1 && app->l_op_door_y != -1
		&& app->closing_counter == 0
		&& (int)app->player.x != app->l_op_door_x
		&& (int)app->player.y != app->l_op_door_y)
	{
		app->walked_map[app->l_op_door_y][app->l_op_door_x] = 3;
		app->l_op_door_x = -1;
		app->l_op_door_y = -1;
	}
}

void	main_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	user_input_hook(app);
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	calc_walls(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1)
		exit(1);
	display_minimap(app);
	display_compass(app, app->player.angle);
	draw_weapon(app);
	close_last_door(app);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (1);
	app.map = map_validate(&app, argv[1]);
	if (!app.map)
		return (1);
	if (_init_app(&app))
		return (1);
	print_info(&app);
	if (app.map)
	{
		mlx_key_hook(app.mlx, key_hook, &app);
		mlx_loop_hook(app.mlx, main_loop, &app);
		mlx_loop(app.mlx);
		mlx_delete_image(app.mlx, app.img);
		mlx_delete_image(app.mlx, app.minimap_img);
		mlx_delete_image(app.mlx, app.compass);
		mlx_terminate(app.mlx);
		free_all_resources(&app);
	}
	return (0);
}

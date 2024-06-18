/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/18 02:43:57 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to get a pixel color feom a texture at a certain point (x, y)
int32_t	get_pixel_from_text(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixel;
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	if (x > image->width || y > image->height)
		return (0);
	pixel = image->pixels + (y * image->width + x) * sizeof(int32_t);
	a = pixel[0];
	r = pixel[1];
	g = pixel[2];
	b = pixel[3];
	return (ft_pixel(a, r, g, b));
}

//	returns one if a pixel at a ceratin position is not null, or 0 if yes
int	check_pixel_is_not_null(mlx_image_t *img, uint32_t x, uint32_t y)
{
	if (get_pixel_from_text(img, x, y) != 0)
	{
		return (1);
	}
	return (0);
}

//	function to replace a part of the image with another image starting at x y
void	put_img_to_img(mlx_image_t *img, mlx_image_t *src, int x, int y)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			if (check_pixel_is_not_null(src, i, j))
			{
				mlx_put_pixel(img, x + i, y + j,
					get_pixel_from_text(src, i, j));
			}
			j++;
		}
		i++;
	}
}

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

//	function to animate the weapon firing
void	create_animation(t_app *app, mlx_image_t **weapon)
{
	static int	animate = 0;
	int			set_back;
	int			new_value;
	int			stop;

	set_back = 2;
	new_value = animate / set_back;
	app->weapon->x = app->window_width / 2 - weapon[new_value]->width / 2;
	app->weapon->y = app->window_height - weapon[new_value]->height;
	put_img_to_img(app->img, weapon[new_value],
		app->weapon->x, app->weapon->y);
	if (!weapon[new_value + 1])
	{
		stop = new_value + 1;
	}
	else
		stop = 3;
	if (++animate == 5 * set_back)
	{
		animate = 0;
		app->weapon->animation_start = HOLSTERED;
		put_img_to_img(app->img, weapon[0],
			app->weapon->x, app->weapon->y);
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
		put_img_to_img(app->img, cur_weapon[0],
			app->weapon->x, app->weapon->y);
	}
	else
	{
		app->weapon->x = app->window_width / 2
			- app->weapon->active_image->width / 2;
		app->weapon->y = app->window_height - app->weapon->active_image->height;
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

//	main loop function, if there is a change in movement
void	main_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	user_input_hook(app);
	calc_walls(app);
	display_minimap(app);
	display_compass(app, app->player.angle);
	draw_weapon(app);
	close_last_door(app);
}

int	is_not_cub(char *file)
{
	int len = ft_strlen(file);
	if (len < 4)
		return (1);
	return(ft_strcmp(file + len - 4, ".cub"));
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
	{
		printf("Error\nNo *.cub file as argument\n");
		return (1);
	}
	if (is_not_cub(argv[1]))
	{
		printf("Error\nNo .cub file handed as argument\n");
		return (1);
	}
	app.map = map_validate(&app, argv[1]);
	if (!app.map)
		return (1);
	if (_init_app(&app))
		return (1);
	//print_info(&app);
	mlx_set_cursor_mode(app.mlx, MLX_MOUSE_HIDDEN);
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

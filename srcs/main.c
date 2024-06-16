/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/16 16:16:27 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, int a) {
  return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * In MLX42 Colors are as follows:
 * 0000 0000 A (1st byte) -> uint8_t because it's 8 bits
 * 0000 0000 R (2nd byte)
 * 0000 0000 G (3rd byte)
 * 0000 0000 B (4th byte)
 **/
int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y) {
  if (x > image->width || y > image->height)
    return 0x00000000;
  uint8_t* pixelstart = image->pixels + (y * image->width + x) * sizeof(int32_t);
  return get_rgba(*(pixelstart), *(pixelstart + 1),
    * (pixelstart + 2), *(pixelstart + 3));
}

static int put_pixel_valid(mlx_image_t* img, uint32_t x, uint32_t y) {
    return (mlx_get_pixel(img, x, y) != 0);
}

void  put_img_to_img(mlx_image_t* dst, mlx_image_t* src, int x, int y) {
  uint32_t i;
  uint32_t j;

  i = 0;
  while(i < src->width) {
    j = 0;
    while (j < src->height) {
      if (put_pixel_valid(src, i, j))
        mlx_put_pixel(dst, x + i, y + j, mlx_get_pixel(src, i, j));
      j++;
    }
    i++;
  }
}

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
	app->weapon->img = mlx_texture_to_image(app->mlx, current_texture);
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
	display_minimap(app);
	draw_weapon(app);
	display_compass(app, app->player.angle);
	put_img_to_img(app->img, app->compass, app->window_width - app->compass->width, 0);
	if (app->weapon->state == ACTIVE)
		put_img_to_img(app->img, app->weapon->img, app->weapon->x,app->weapon->y);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1)
		exit(1);
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
	//print_info(&app);
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

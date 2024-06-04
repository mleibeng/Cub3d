/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/04 08:05:16 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int				g_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1},
};

# define PLAYER_MOVE_SPEED 0.01
# define PLAYER_ROTATE_SPEED 0.01

//	function for raycasting the return value will be taken with the cos
//	from the player angle and the actual angle (fisheye)
float	cast_ray(t_player *player, float ray_angle)
{
	float	depth;
	float	target_x;
	float	target_y;
	float	max_units;

	depth = 0.0f;
	max_units = 1.0f * MAP_HEIGHT;
	while (depth < max_units)
	{
		target_x = player->x + depth * cos(ray_angle);
		target_y = player->y + depth * sin(ray_angle);
		if (target_x >= MAP_WIDTH || target_y >= MAP_HEIGHT || target_x < 0
			|| target_y < 0 || g_map[(int)target_y][(int)target_x] == 1)
		{
			return (depth * cos(player->angle - ray_angle));
		}
		depth += 0.005f;
	}
	return (max_units * cos(player->angle - ray_angle));
}

//	combines rgb and alpha(transparency) values into single color
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//	this function calculates the shift of the coordinates with the arrow keys
int	ft_hook_key(t_app *app)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_UP)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_DOWN))
	{
			app->player.x += PLAYER_MOVE_SPEED * cos(app->player.angle);
			app->player.y += PLAYER_MOVE_SPEED * sin(app->player.angle);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_UP))
	{
		app->player.x -= PLAYER_MOVE_SPEED * cos(app->player.angle);
		app->player.y -= PLAYER_MOVE_SPEED * sin(app->player.angle);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
	{
		app->player.angle -= PLAYER_ROTATE_SPEED;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
	{
		app->player.angle += PLAYER_ROTATE_SPEED;
	}
	return (0);
}

//	function to draw a partial ray
void	draw_part_ray(t_app *app, int start, int end, int32_t color)
{
	int	y;

	y = start;
	while (y < end)
	{
		if (app->cur_ray >= 0 && app->cur_ray < app->window_width &&  y >= 0 && y < app->window_height)
			mlx_put_pixel(app->img, app->cur_ray, y, color);
		y++;
	}
}

//	function to draw one ray
void	draw_ray(t_app *app, int wall_height, float distance)
{
	int shade;
	int	wall_start;
	int	wall_end;

	shade = 150 / (1.0 + distance * 0.3);
	wall_start = (app->window_height - wall_height) / 2;
	wall_end = (app->window_height + wall_height) / 2;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end > app->window_height)
		wall_end = app->window_height;
	draw_part_ray(app, 0, wall_start - 1, ft_pixel(240, 30, 30, 150));
	draw_part_ray(app, wall_start, wall_end, ft_pixel(30, 240, 30, shade));

}

//	function to draw the lines of the map
void	draw_walls(t_app *app)
{
	float	ray_angle;
	float	distance;
	int		wall_height;

	ft_hook_key(app);
	app->cur_ray = 0;
	while (app->cur_ray < app->num_rays)
	{
		ray_angle = app->player.angle - app->fov / 2 + app->cur_ray * app->fov / app->num_rays;
		distance = cast_ray(&app->player, ray_angle);
		wall_height = (int)(app->window_height / (distance + 0.01f));
		draw_ray(app, wall_height, distance);
		app->cur_ray++;
	}
}

//	key functions
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(app->mlx);
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		printf("Position X: %f Y : %f deg: %f\n", app->player.x, app->player.y,
			app->player.angle);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		app->player.x = app->player.std_x;
		app->player.y = app->player.std_y;
		app->player.angle = app->player.std_angle;
	}
}

void	loop_hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	draw_walls(app);
	mlx_image_to_window(app->mlx, app->img, 0, 0);
}

int	main(void)
{
	t_app app;
	app.player.x = 2;
	app.player.y = 2;
	app.player.angle = 30.0;
	app.player.std_x = app.player.x;
	app.player.std_y = app.player.y;
	app.player.std_angle = app.player.angle;
	app.fov = (M_PI / 3);
	app.window_width = 640;
	app.window_height = 480;
	app.num_rays = app.window_width;
	app.cur_ray = 0;
	app.mlx = mlx_init(app.window_width, app.window_height, "cub3d", true);
	if (!app.mlx)
		return (1);
	app.img = mlx_new_image(app.mlx, app.window_width, app.window_height);
	if (!app.img)
	{
		mlx_terminate(app.mlx);
		return (1);
	}
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_loop(app.mlx);
	mlx_delete_image(app.mlx, app.img);
	mlx_terminate(app.mlx);
	return (0);
}

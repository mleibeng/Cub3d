/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/03 17:49:58 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int				g_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
};
typedef struct s_player
{
	float		x;
	float		y;
	float		std_x;
	float		std_y;
	float		std_angle;
	float		angle;
}				t_player;
typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
}				t_app;
float	cast_ray(t_player *player, float ray_angle)
{
	float	depth;
	float	target_x;
	float	target_y;

	depth = 0.0f;
	while (depth < 20.0f)
	{
		target_x = player->x + depth * cos(ray_angle);
		target_y = player->y + depth * sin(ray_angle);
		if (target_x >= MAP_WIDTH || target_y >= MAP_HEIGHT || target_x < 0
			|| target_y < 0 || g_map[(int)target_y][(int)target_x] == 1)
		{
			return (depth);
		}
		depth += 0.01f;
	}
	return (20.0f);
}
void	draw_walls(t_app *app)
{
	int		i;
	float	ray_angle;
	float	distance;
	int		wall_height;
	int		clr;
	int		x;
	int		y;
	int		y_start;
	int		y_end;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = app->player.angle - FOV / 2 + i * FOV / NUM_RAYS;
		distance = cast_ray(&app->player, ray_angle);
		distance *= cos(app->player.angle - ray_angle);
		wall_height = (int)(SCREEN_HEIGHT / (distance + 0.0001f));
		clr = 255 / (1 + distance * distance * 0.0001f);
		x = i * SCREEN_WIDTH / NUM_RAYS;
		y_start = (SCREEN_HEIGHT - wall_height) / 2;
		y_end = (SCREEN_HEIGHT + wall_height) / 2;
		if (y_start < 0)
			y_start = 0;
		if (y_end > SCREEN_HEIGHT)
			y_end = SCREEN_HEIGHT;
		y = y_start;
		while (y < y_end)
		{
			if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
			{
				mlx_put_pixel(app->img, x, y, (clr << 16) | (clr << 8) | clr);
			}
			y++;
		}
		i++;
	}
}
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(app->mlx);
	}
	if (keydata.key == MLX_KEY_UP)
	{
		app->player.x += PLAYER_MOVE_SPEED * cos(app->player.angle);
		app->player.y += PLAYER_MOVE_SPEED * sin(app->player.angle);
	}
	if (keydata.key == MLX_KEY_DOWN)
	{
		app->player.x -= PLAYER_MOVE_SPEED * cos(app->player.angle);
		app->player.y -= PLAYER_MOVE_SPEED * sin(app->player.angle);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		app->player.angle -= PLAYER_ROTATE_SPEED;
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		app->player.angle += PLAYER_ROTATE_SPEED;
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
	app->img = mlx_new_image(app->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
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
	app.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray Casting", true);
	if (!app.mlx)
		return (1);
	app.img = mlx_new_image(app.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
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
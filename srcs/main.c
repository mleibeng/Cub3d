/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/05 03:21:33 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int		g_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1},
};

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

int	_init_app(t_app *app)
{
	app->player.x = 2;
	app->player.y = 2;
	app->player.angle = 0.0;
	app->player.std_x = app->player.x;
	app->player.std_y = app->player.y;
	app->player.std_angle = app->player.angle;
	app->fov = (M_PI / 3);
	app->window_width = 1920;
	app->window_height = 1080;
	app->num_rays = app->window_width;
	app->cur_ray = 0;
	app->mlx = mlx_init(app->window_width, app->window_height, "cub3d", true);
	if (!app->mlx)
		return (1);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
	{
		mlx_terminate(app->mlx);
		return (1);
	}
	return (0);
}

void emergency_exit(void *malloc)
{
	if(!malloc)
		exit(1);
}

void _init_texture(t_texture *texture)
{
	texture = malloc(sizeof(t_texture));
	emergency_exit(texture);

	texture->e_text = NULL;
	texture->n_text = NULL;
	texture->s_text = NULL;
	texture->w_text = NULL;

}

void parse_textures(char *line, int fd, t_texture *texture)
{
	while (line = get_next_line(fd) && (!texture->e_text || !texture->w_text || !texture->s_text || !texture->n_text))
	{
		if (ft_strlen(line) > 0)
		{
			if (!ft_strncmp(line, "NO ", 3))
				texture->n_text = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "WE ", 3))
				texture->w_text = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "SO ", 3))
				texture->s_text = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "EA ", 3))
				texture->e_text = ft_strdup(line + 3);
			else
				continue;
		}
		if (!line)
		{
			perror ("invalid textures");
			emergency_exit(line);
		}
	}
}

void save_rgb(char *line, int *color)
{
	int i = 0;
	while (line[i])
	{

	}
}

void parse_floor_ceiling(char *line, int fd, t_texture *texture)
{
	if (!ft_strncmp(line, "F ", 3))
		save_rgb(line, texture->floor);
	else if (!ft_strncmp(line, "C ", 3))
		save_rgb(line, texture->skybox);
}

t_texture	*read_map(char *file, char ***map, int *rows, int *columns)
{
	int	fd;
	char buffer[MAX_LINE_LENGTH];
	char **new_map;
	char *line;
	t_texture *texture;

	_init_texture(texture);
	if (fd = open(file, O_RDONLY) == -1)
		return (NULL);
	new_map = malloc(MAX_LINE_LENGTH * sizeof(char *));
	emergency_exit(new_map);
	parse_textures(line, fd, texture);
	parse_floor_ceiling(line, fd, texture);
	while (line = get_next_line(fd))
	{
		if (ft_strlen > 0)
		{
			new_map[*rows] = malloc((ft_strlen(line) + 1) * sizeof(char));
			emergency_exit(new_map[*rows]);
		}
	}
}

char	**map_validate(t_app *app, char *file)
{
	int	fd;
	int	rows;
	int	columns;
	char **map;

	rows = 0;
	columns = 0;
	app->textures = read_map(file, &map, &rows, &columns);
	if (!app->textures)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (1);
	if (map_validate(&app, argv[1]))
		return (1);
	if (_init_app(&app))
		return (1);
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_loop(app.mlx);
	mlx_delete_image(app.mlx, app.img);
	mlx_terminate(app.mlx);
	return (0);
}
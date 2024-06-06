/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/06 23:42:36 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

int			g_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1},
};

void	loop_hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	calc_walls(app);
	mlx_image_to_window(app->mlx, app->img, 0, 0);
	display_compass(app, app->player.angle);
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

void	emergency_exit(void *malloc)
{
	if (!malloc)
		exit(1);
}

void	_init_texture(t_texture *texture)
{
	texture = malloc(sizeof(t_texture));
	emergency_exit(texture);
	texture->e_text = NULL;
	texture->n_text = NULL;
	texture->s_text = NULL;
	texture->w_text = NULL;
}

void	parse_textures(char *line, int fd, t_texture *texture)
{
	while (line = get_next_line(fd) && (!texture->e_text || !texture->w_text
			|| !texture->s_text || !texture->n_text))
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
				continue ;
		}
		if (!line)
		{
			perror("invalid filestop at texture readin");
			emergency_exit(line);
		}
	}
}

void	color_validation(char *end, char *line, int val)
{
	if (end == line || *end != ',')
	{
		perror("invalid RGB values");
		exit(1);
	}
	if (val < 0 || val > 255)
	{
		perror("RGB values must be between 0 and 255");
		exit(1);
	}
}

void	save_rgb(char *line, int *color)
{
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_strtoi(line, &end);
	color_validation(end, line, r);
	line = end + 1;
	g = ft_strtoi(line, &end);
	color_validation(end, line, g);
	line = end + 1;
	b = ft_strtoi(line, &end);
	color_validation(end, line, b);
	line = end + 1;
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void	parse_floor_ceiling(char *line, int fd, t_texture *texture)
{
	while (line = get_next_line(fd) && (!texture->floor || !texture->skybox))
	{
		if (ft_strlen(line) > 0)
		{
			if (!ft_strncmp(line, "F ", 3))
				save_rgb(line + 2, texture->floor);
			else if (!ft_strncmp(line, "C ", 3))
				save_rgb(line + 2, texture->skybox);
			else
				continue ;
		}
	}
	if (!line)
	{
		perror("invalid filestop at floor/ceiling parse");
		emergency_exit(line);
	}
}

void	parse_map(char *line, char ***map, int *rows, int *columns)
{
	if (ft_strlen(line) > 0)
	{
		if (*rows == 0)
		{
			*map = malloc(MAX_LINE_LENGTH * sizeof(char *));
			emergency_exit(*map);
		}
		(*map)[*rows] = strdup(line);
		emergency_exit((*map)[*rows]);
		if (ft_strlen(line) > *columns)
			*columns = ft_strlen(line);
		(*rows)++;
	}
	free(line);
}

t_texture	*read_map(char *file, char ***map, int *rows, int *columns)
{
	int			fd;
	char		buffer[MAX_LINE_LENGTH];
	char		**new_map;
	char		*line;
	t_texture	*texture;

	_init_texture(texture);
	if (fd = open(file, O_RDONLY) == -1)
		return (NULL);
	new_map = malloc(MAX_LINE_LENGTH * sizeof(char *));
	emergency_exit(new_map);
	parse_textures(line, fd, texture);
	parse_floor_ceiling(line, fd, texture);
	while (line = get_next_line(fd))
		parse_map(line, map, rows, columns);
	close(fd);
	return (texture);
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == "E");
}

void	free_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	free(map);
	map = NULL;
}

void	free_textures(t_texture *textures)
{
	int	i;

	i = 0;
	if (textures->n_text)
		free(textures->n_text);
	if (textures->e_text)
		free(textures->n_text);
	if (textures->w_text)
		free(textures->n_text);
	if (textures->s_text)
		free(textures->n_text);
	free(textures);
}

int	character_validation(char ***map, int *rows, int *columns,
		t_texture *textures)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < *rows)
	{
		while (j < ft_strlen(*map[i]))
		{
			if (!is_valid(*map[i][j]))
			{
				perror("invalid char inside of map");
				free_maps(map);
				free_textures(textures);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	f_player_start(char **map, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
				|| map[i][j] == 'E')
			{
				*player_x = j;
				*player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	*player_x = -1;
	*player_y = -1;
}

int fill_map(char **map, t_app *app, int *direct_x, int *direct_y)
{
	int end = 0;
	int start = 0;

	app->check_queue[end++] = (t_vec){app->player.x, app->player.y};

}

int	closed_map(char **map, int rows, int columns, t_app *app)
{
	int	i;
	int	direct_x[] = {0, 0, -1, 1};
	int	direct_y[] = {-1, 1, 0, 0};

	i = 0;
	app->walked_map = malloc(rows * sizeof(int *));
	emergency_exit(app->walked_map);
	while (i < rows)
	{
		app->walked_map[i] = ft_calloc(columns, sizeof(int));
		emergency_exit(app->walked_map[i]);
	}
	app->check_queue = malloc(rows * columns * sizeof(t_vec));
	emergency_exit(app->check_queue);
	return (fill_map(map, app, &direct_x, &direct_y));
}

int	_validate_field(char **map, int *rows, int *columns, t_app *app)
{
	f_player_start(map, &app->player.x, &app->player.y);
	if (app->player.y == -1)
	{
		perror("no player found");
		free_map(map);
		free_textures(app->textures);
		exit(1);
	}
	if (!closed_map(map, rows, columns, app))
	{
		perror("map has leaky walls...");
		free_map(map);
		free_textures(app->textures);
		exit(1);
	}
}

char	**map_validate(t_app *app, char *file)
{
	int		fd;
	int		rows;
	int		columns;
	char	**map;

	rows = 0;
	columns = 0;
	app->textures = read_map(file, &map, &rows, &columns);
	if (!app->textures)
		exit(1);
	if (character_validation(&map, &rows, &columns, app->textures))
		exit(1);
	if (_validate_field)
		exit(1);
	// Now i need to start on flood fill for player and bounds validation//
	// find the players position and from there walk through and keep in memory which were traversed.
	// I need to watch some yt vids on the topic
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
	mlx_image_to_window(app.mlx, app.compass, app.window_width - COMPASS_SIZE
		- 10, 10);
	app.compass->instances->z = 1;
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_loop(app.mlx);
	mlx_delete_image(app.mlx, app.img);
	mlx_terminate(app.mlx);
	return (0);
}

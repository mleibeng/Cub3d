/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:35:57 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/08 21:20:38 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	emergency_exit(void *malloc)
{
	if (!malloc)
	{
		perror("Memory alloc fail");
		exit(1);
	}
}

void	parse_textures(int fd, t_texture *texture)
{
	char	*line;

	while ((!texture->e_text || !texture->w_text || !texture->s_text
			|| !texture->n_text) && (line = get_cut_next_line(fd)))
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
		}
		free(line);
	}
	if (!line)
	{
		perror("invalid filestop at texture readin");
		emergency_exit(line);
	}
}

void	color_validation(char *end, char *line, int val)
{
	if (end != line && *end != ',')
	{
		perror("invalid RGB values\n");
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
	if (b < 0 || b > 255)
	{
		perror("RGB values must be between 0 and 255");
		exit(1);
	}
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = 0;
}

void	parse_floor_ceiling(int fd, t_texture *texture)
{
	char	*line;

	while ((!texture->floor[0] || !texture->skybox[0])
		&& (line = get_cut_next_line(fd)))
	{
		if (ft_strlen(line) > 0)
		{
			if (!ft_strncmp(line, "F ", 2))
				save_rgb(line + 2, texture->floor);
			else if (!ft_strncmp(line, "C ", 2))
				save_rgb(line + 2, texture->skybox);
		}
		free(line);
	}
	if (!line)
	{
		perror("invalid filestop at floor/ceiling parse");
		exit(1);
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
		(*map)[*rows] = malloc((ft_strlen(line) + 1) * sizeof(char));
		emergency_exit((*map)[*rows]);
		ft_strlcpy((*map)[*rows], line, ft_strlen(line) + 1);
		if ((int)ft_strlen(line) > *columns)
			*columns = (int)ft_strlen(line);
		(*rows)++;
	}
	free(line);
}

t_texture	*read_map(char *file, char ***map, int *rows, int *columns)
{
	int			fd;
	char		*line;
	t_texture	*texture;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), NULL);
	texture = malloc(sizeof(t_texture));
	emergency_exit(texture);
	_init_texture(texture);
	parse_textures(fd, texture);
	parse_floor_ceiling(fd, texture);
	while ((line = get_cut_next_line(fd)))
		parse_map(line, map, rows, columns);
	(*map)[*rows] = NULL;
	close(fd);
	return (texture);
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E');
}

void	free_map(char **map)
{
	int	i;

	i = 0;
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

int	character_validation(char **map, int *rows, t_texture *textures)
{
	int	i;
	int	j;

	i = 0;
	while (i < *rows)
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]) - 1)
		{
			if (ft_isspace(map[i][j]))
				j++;
			if (!is_valid(map[i][j]))
			{
				perror("invalid char inside of map");
				free_map(map);
				free_textures(textures);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

float	check_start_angle(char direction)
{
	float	start_angle;

	start_angle = 0.0;
	if (direction == 'N')
		start_angle = M_PI + M_PI_2;
	else if (direction == 'E')
		start_angle = 0.0;
	else if (direction == 'S')
		start_angle = M_PI - M_PI_2;
	else if (direction == 'W')
		start_angle = M_PI;
	return (start_angle);
}

void	f_player_start(t_app *app, char **map, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
				|| map[i][j] == 'E')
			{
				*player_x = j;
				*player_y = i;
				app->player.angle = check_start_angle(map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
	*player_x = -1;
	*player_y = -1;
}

void	free_queue(t_app *app)
{
	int	i;

	i = -1;
	free(app->check_queue);
	while (i < app->rows)
	{
		free(app->walked_map[i]);
		i++;
	}
	free(app->walked_map);
}

int	check_column_bound(t_app *app)
{
	int	j;

	j = 0;
	while (j < app->cols)
	{
		if (app->walked_map[0][j] == 2)
		{
			perror("error in check_bounds: invalid 2 found\n");
			free_queue(app);
			return (0);
		}
		j++;
	}
	j = 0;
	while (j < app->cols)
	{
		if (app->walked_map[app->rows - 1][j] == 2)
		{
			perror("error in check_bounds: invalid 2 found\n");
			free_queue(app);
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_row_bound(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->rows)
	{
		if (app->walked_map[i][0] == 2)
		{
			perror("error in check_bounds: invalid 2 found\n");
			free_queue(app);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < app->rows)
	{
		if (app->walked_map[i][app->cols - 1] == 2)
		{
			perror("error in check_bounds: invalid 2 found\n");
			free_queue(app);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_bounds(t_app *app)
{
	if (!check_column_bound(app))
		return (0);
	if (!check_row_bound(app))
		return (0);
	return (1);
}

int	fill_bounds(int next_x, int next_y, t_app *app, char **map)
{
	if (next_x >= 0 && next_x < app->cols && next_y >= 0 && next_y < app->rows
		&& !app->walked_map[next_y][next_x])
	{
		if (map[next_y][next_x] == '0')
		{
			app->check_queue[app->end++] = (t_vec){next_x, next_y};
			app->walked_map[next_y][next_x] = 2;
		}
		else if (map[next_y][next_x] == '1')
			app->walked_map[next_y][next_x] = 1;
		else
		{
			perror("error in fill_bounds\n");
			free_queue(app);
			return (0);
		}
	}
	return (1);
}

void	fill_minimap_bounds(char **map, int **mini_map, int *i, int *j)
{
	if (*j < (int)ft_strlen(map[*i]))
	{
		if (map[*i][*j] == '1')
			mini_map[*i][*j] = 1;
		else if (map[*i][*j] == '0')
			mini_map[*i][*j] = 0;
		else if (map[*i][*j] == 'N' || map[*i][*j] == 'W' || map[*i][*j] == 'S'
			|| map[*i][*j] == 'E')
			mini_map[*i][*j] = 2;
	}
	else
		mini_map[*i][*j] = 0;
}

int	fill_map(char **map, t_app *app, int *direct_x, int *direct_y)
{
	int	next_x;
	int	next_y;
	int	j;

	app->end = 0;
	app->start = 0;
	app->check_queue[app->end++] = (t_vec){app->player.start_x,
		app->player.start_y};
	app->walked_map[app->player.start_y][app->player.start_x] = 2;
	while (app->start < app->end)
	{
		app->pos = app->check_queue[app->start++];
		j = 0;
		while (j < 4)
		{
			next_x = app->pos.x + direct_x[j];
			next_y = app->pos.y + direct_y[j];
			if (!fill_bounds(next_x, next_y, app, map))
				return (perror("fill_maperror"), 0);
			j++;
		}
	}
	if (!check_bounds(app))
		return (perror("maperror"), 0);
	// free_queue(app);
	return (1);
}

int	**create_map(int rows, int columns)
{
	int		i;
	int		**map;

	i = 0;
	map = malloc(rows * sizeof(int *));
	emergency_exit(map);
	while (i < rows)
	{
		map[i] = ft_calloc(columns, sizeof(int));
		emergency_exit(map[i]);
		i++;
	}
	return (map);
}

void	fill_minimap(char **map, int **mini_map, int rows, int columns)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			fill_minimap_bounds(map, mini_map, &i, &j);
			j++;
		}
		i++;
	}
}

int	closed_map(char **map, int rows, int columns, t_app *app)
{
	int	i;
	int	direct_x[] = {0, 0, -1, 1};
	int	direct_y[] = {-1, 1, 0, 0};

	i = 0;
	app->walked_map = create_map(rows, columns);
	app->minimap = create_map(rows, columns);
	app->check_queue = malloc(rows * columns * sizeof(t_vec));
	emergency_exit(app->check_queue);
	fill_minimap(map, app->minimap, rows, columns);
	return (fill_map(map, app, direct_x, direct_y));
}

void	_validate_field(char **map, int *rows, int *columns, t_app *app)
{
	f_player_start(app, map, &app->player.start_x, &app->player.start_y);
	if (app->player.start_y == -1)
	{
		perror("no player found");
		free_map(map);
		free_textures(app->textures);
		exit(1);
	}
	if (!closed_map(map, *rows, *columns, app))
	{
		perror("map has leaky walls...");
		free_map(map);
		free_textures(app->textures);
		exit(1);
	}
}

char	**map_validate(t_app *app, char *file)
{
	int		rows;
	int		columns;
	char	**map;

	map = NULL;
	rows = 0;
	columns = 0;
	app->textures = read_map(file, &map, &rows, &columns);
	if (!app->textures)
	{
		perror("Error in textures");
		exit(1);
	}
	if (character_validation(map, &rows, app->textures))
	{
		perror("Error in char_validation");
		exit(1);
	}
	app->cols = columns;
	app->rows = rows;
	_validate_field(map, &rows, &columns, app);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:35:57 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/15 10:06:50 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_texture *textures)
{
	if (textures->n_path)
		free(textures->n_path);
	if (textures->e_path)
		free(textures->e_path);
	if (textures->w_path)
		free(textures->w_path);
	if (textures->s_path)
		free(textures->s_path);
	if (textures->d_path)
		free(textures->d_path);
	free(textures);
}

void	emergency_exit(t_app *app, t_texture *texture, char **map)
{
	if (texture)
		free_textures(texture);
	if (map)
		free_map((void **)map);
	if (app)
	{
		if (app->walked_map)
			free_map((void **)app->walked_map);
		if (app->minimap)
			free_map((void **)app->minimap);
		if (app->check_queue)
			free(app->check_queue);
	}
	perror("Memory allocation failure or other error");
	exit(EXIT_FAILURE);
}

void	parse_textures(int fd, t_texture *texture)
{
	char	*line;

	line = NULL;
	while ((!texture->e_path || !texture->w_path || !texture->s_path
			|| !texture->n_path)
		&& (line = get_cut_next_line(fd)))
	{
		if (ft_strlen(line) > 0)
		{
			if (!ft_strncmp(line, "NO ", 3))
				texture->n_path = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "WE ", 3))
				texture->w_path = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "SO ", 3))
				texture->s_path = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "EA ", 3))
				texture->e_path = ft_strdup(line + 3);

		}
		free(line);
	}
	if (!line)
	{
		perror("invalid filestop at texture readin");
		emergency_exit(NULL, texture, NULL);
	}
}

void parse_door_text(char *file, t_texture *texture)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error reopening file");
		emergency_exit(NULL, texture, NULL);
	}
	line = NULL;
	while ((line = get_cut_next_line(fd)))
	{
		if (ft_strlen(line) > 0 && !ft_strncmp(line, "DO ", 3 ))
		{
			texture->d_path = ft_strdup(line + 3);
			free(line);
			break;
		}
		free(line);
	}
	close(fd);
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

	line = NULL;
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
		emergency_exit(NULL, texture, NULL);
}

void	parse_map(char *line, char ***map, int *rows, int *columns)
{
	if (ft_strlen(line) > 0)
	{
		if (*rows == 0)
		{
			*map = malloc(MAX_LINE_LENGTH * sizeof(char *));
			if (!*map)
			{
				free(line);
				emergency_exit(NULL, NULL, *map);
			}
		}
		(*map)[*rows] = malloc((ft_strlen(line) + 1) * sizeof(char));
		if (!(*map)[*rows])
		{
			free(line);
			emergency_exit(NULL, NULL, *map);
		}
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
	t_texture	*texture;
	char		*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	texture = malloc(sizeof(t_texture));
	if (!texture)
	{
		close(fd);
		emergency_exit(NULL, NULL, NULL);
	}
	_init_texture(texture);
	parse_textures(fd, texture);
	parse_floor_ceiling(fd, texture);
	line = NULL;
	while ((line = get_cut_next_line(fd)))
		parse_map(line, map, rows, columns);
	if (*rows > 0)
		(*map)[*rows] = NULL;
	close(fd);
	parse_door_text(file, texture);
	return (texture);
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'D');
}

void	free_map(void **map)
{
	int	i;

	i = 0;
	if (map)
	{
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
	}
	map = NULL;
}

int	character_validation(char **map, int rows, t_texture *textures)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]) - 1)
		{
			if (ft_isspace(map[i][j]))
				continue ;
			if (!is_valid(map[i][j]))
			{
				perror("Invalid character inside map");
				free_map((void **)map);
				free_textures(textures);
				return (1);
			}
			if(!textures->d_path && map[i][j] == 'D')
				map[i][j] = '1';
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
	if (app->check_queue)
		free(app->check_queue);
}

int	check_column_bound(t_app *app)
{
	int	j;

	j = 0;
	while (j < app->cols)
	{
		if (app->walked_map[0][j] == 2 || app->walked_map[0][j] == 3)
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
		if (app->walked_map[app->rows - 1][j] == 2 || app->walked_map[app->rows
			- 1][j] == 3)
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
		if (app->walked_map[i][0] == 2 || app->walked_map[i][0] == 3)
		{
			perror("error in check_bounds: invalid 2/3 found\n");
			free_queue(app);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < app->rows)
	{
		if (app->walked_map[i][app->cols - 1] == 2
			|| app->walked_map[i][app->cols - 1] == 3)
		{
			perror("error in check_bounds: invalid 2/3 found\n");
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
		else if (map[next_y][next_x] == 'D')
		{
			app->walked_map[next_y][next_x] = 3;
			app->check_queue[app->end++] = (t_vec){next_x, next_y};
		}
		else
		{
			perror("error in fill_bounds\n");
			free_queue(app);
			return (0);
		}
	}
	return (1);
}

void	fill_minimap_bounds(char **map, int **mini_map, t_vec *ij)
{
	if (ij->y < (int)ft_strlen(map[ij->x]))
	{
		if (map[ij->x][ij->y] == '1')
			mini_map[ij->x][ij->y] = 1;
		else if (map[ij->x][ij->y] == '0')
			mini_map[ij->x][ij->y] = 0;
		else if (map[ij->x][ij->y] == 'N' || map[ij->x][ij->y] == 'W' || map[ij->x][ij->y] == 'S'
			|| map[ij->x][ij->y] == 'E')
			mini_map[ij->x][ij->y] = 2;
		else if (map[ij->x][ij->y] == 'D')
			mini_map[ij->x][ij->y] = 3;
	}
	else
		mini_map[ij->x][ij->y] = 0;
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
	free_queue(app);
	return (1);
}

int	**create_map(int rows, int columns)
{
	int	i;
	int	**map;

	i = 0;
	map = malloc((rows + 1) * sizeof(int *));
	if (!map)
		return (NULL);
	while (i < rows)
	{
		map[i] = ft_calloc(columns, sizeof(int));
		if (!map[i])
		{
			perror("Memory allocation failed for map row");
			while (i-- > 0)
				free(map[i]);
			free(map);
			exit(1);
		}
		i++;
	}
	map[rows] = NULL;
	return (map);
}

void	fill_minimap(char **map, int **mini_map, t_app *app)
{
	t_vec	ij;

	ij.x = 0;
	while (ij.x < app->rows)
	{
		ij.y = 0;
		while (ij.y < app->cols)
		{
			fill_minimap_bounds(map, mini_map, &ij);
			ij.y++;
		}
		ij.x++;
	}
}

void replace_adj_door(t_app *app, char **map, int y, int x, int dy, int dx)
{
	int ny = y + dy;
	int nx = x + dx;

	if (ny >= 0 && ny < app->rows && nx >= 0 && nx < app->cols &&
		nx < (int)ft_strlen(map[ny]) && app->walked_map[ny][nx] == 3)
	{
		app->walked_map[y][x] = 1;
		app->walked_map[ny][nx] = 1;
		map[y][x] = '1';
		map[ny][nx] = '1';
	}
}

void check_adj_doors(t_app *app, char **map, int y, int x)
{
	if (app->walked_map[y][x] == 3 && app->textures->d_path)
	{
		replace_adj_door(app, map, y, x, 0, 1);
		replace_adj_door(app, map, y, x, 0, -1);
		replace_adj_door(app, map, y, x, 1, 0);
		replace_adj_door(app, map, y, x, -1, 0);
	}
}

void replace_adj_doors(t_app *app, char **map)
{
	int y;
	int x;

	y = 0;
	while (y < app->rows)
	{
		x = 0;
		while (x < app->cols)
		{
			check_adj_doors(app, map, y, x);
			x++;
		}
		y++;
	}
}


int	closed_map(char **map, t_vec *rowcol, t_app *app)
{
	int	direct_x[] = {0, 0, -1, 1};
	int	direct_y[] = {-1, 1, 0, 0};

	app->walked_map = create_map(rowcol->x, rowcol->y);
	app->minimap = create_map(rowcol->x, rowcol->y);
	app->check_queue = malloc(rowcol->x * rowcol->y * sizeof(t_vec));
	if (!app->check_queue)
	{
		perror("Memory allocation failed for check_queue");
		free_map((void **)app->walked_map);
		free_map((void **)app->minimap);
		exit(1);
	}
	fill_minimap(map, app->minimap, app);
	if (!fill_map(map, app, direct_x, direct_y))
	{
		free_map((void **)app->walked_map);
		free_map((void **)app->minimap);
		return (0);
	}
	replace_adj_doors(app, map);
	return (1);
}

void	_validate_field(char **map, t_vec *rowcol,  t_app *app)
{
	f_player_start(app, map, &app->player.start_x, &app->player.start_y);
	if (app->player.start_y == -1)
	{
		perror("No player found");
		free_map((void **)map);
		free_textures(app->textures);
		exit(EXIT_FAILURE);
	}
	if (!closed_map(map, rowcol, app))
	{
		perror("Map has leaky walls");
		free_map((void **)map);
		free_textures(app->textures);
		exit(EXIT_FAILURE);
	}
}

char	**map_validate(t_app *app, char *file)
{
	t_vec	rowcol;
	char	**map;

	rowcol.x = 0;
	rowcol.y = 0;
	map = NULL;
	app->textures = read_map(file, &map, &rowcol.x, &rowcol.y);
	if (!app->textures)
	{
		perror("Error in textures");
		exit(EXIT_FAILURE);
	}
	if (character_validation(map, rowcol.x, app->textures))
	{
		perror("Error in character validation");
		exit(EXIT_FAILURE);
	}
	app->cols = rowcol.y;
	app->rows = rowcol.x;
	_validate_field(map, &rowcol, app);
	return (map);
}

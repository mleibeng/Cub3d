/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:35:57 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/28 12:38:59 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		printf("Error opening file");
		return (-1);
	}
	return (fd);
}

t_texture	*read_map(char *file, char ***map, t_vec *rows_cols)
{
	int			fd;
	t_texture	*texture;

	fd = open_file(file);
	if (fd == -1)
		return (NULL);
	texture = init_texture();
	if (parse_file(fd, texture, map, rows_cols))
	{
		close(fd);
		emergency_exit(NULL, texture, *map);
	}
	close(fd);
	if (parse_door_text(file, texture))
		emergency_exit(NULL, texture,*map);
	return (texture);
}

int	closed_map(char **map, t_app *app)
{
	t_vec	directions[4];

	init_directions(directions);
	app->val_map = create_map(app->rows, app->cols, app);
	app->minimap = create_map(app->rows, app->cols, app);
	app->check_queue = malloc(app->rows * app->cols * sizeof(t_vec));
	if (!app->check_queue)
	{
		printf("Error\n");
		printf("Memory allocation failed for check_queue\n");
		emergency_exit(app, app->textures, map);
	}
	fill_minimap(map, app->minimap, app);
	if (!fill_map(map, app, directions))
	{
		printf("Error\n");
		printf("Map could not be filled\n");
		emergency_exit(app, app->textures, map);
		return (0);
	}
	validate_doors(app, map);
	return (1);
}

int	parse_door_text(char *file, t_texture *texture)
{
	int		fd;
	char	*line;
	int		final_status;

	final_status = 0;
	line = NULL;
	fd = open_file(file);
	if (!fd)
		return (1);
	final_status = door_text_loop(fd, line, texture);
	if (line)
		free(line);
	close(fd);
	return (final_status);
}

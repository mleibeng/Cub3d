/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:35:57 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 01:34:01 by fkeitel          ###   ########.fr       */
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
	parse_file(fd, texture, map, rows_cols);
	close(fd);
	parse_door_text(file, texture);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:43 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 23:15:02 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		printf("Error opening texture file\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

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
	if (textures->n_text)
		mlx_delete_xpm42(textures->n_text);
	if (textures->s_text)
		mlx_delete_xpm42(textures->s_text);
	if (textures->e_text)
		mlx_delete_xpm42(textures->e_text);
	if (textures->w_text)
		mlx_delete_xpm42(textures->w_text);
	if (textures->d_text)
		mlx_delete_xpm42(textures->d_text);
	free(textures);
}

void	emergency_exit(t_app *app, t_texture *texture, char **map)
{
	if (texture)
		free_textures(texture);
	if (map)
		free_map(map);
	if (app)
	{
		if (app->walked_map)
			free_intmap(app->walked_map, app->rows);
		if (app->minimap)
			free_intmap(app->minimap, app->rows);
		if (app->check_queue)
			free(app->check_queue);
	}
	exit(EXIT_FAILURE);
}

void free_intmap(int **map, int rows)
{
	int i;

	if (map)
	{
		i = 0;
		while (i < rows)
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
}

void	free_map(char **map)
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

void	free_queue(t_app *app)
{
	if (app->check_queue)
		free(app->check_queue);
	app->check_queue = NULL;
}

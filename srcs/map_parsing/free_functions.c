/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:43 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/18 05:07:30 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_path(char *path, t_texture *text, char **map)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		printf("Error opening texture file\n");
		close(fd);
		emergency_exit(NULL, text, map);
	}
	close(fd);
	return ;
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
	exit(EXIT_FAILURE);
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

void	free_queue(t_app *app)
{
	if (app->check_queue)
		free(app->check_queue);
	app->check_queue = NULL;
}

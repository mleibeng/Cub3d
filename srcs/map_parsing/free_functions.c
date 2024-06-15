/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:33:43 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/15 19:47:16 by mleibeng         ###   ########.fr       */
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
}

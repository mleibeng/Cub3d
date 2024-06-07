/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuging.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:39:07 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/07 23:57:28 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void print_map(char **map)
{
	if (!map)
		return;
	int i = 0;
	while (map[i] != NULL)
	{
		int j = 0;
		while (map[i][j])
		{
			printf("%c ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}


void print_walkedmap(int **map, int rows, int cols)
{
	if (!map)
		return;

	for (int i = 0; i < rows; i++)
	{
		if (!map[i])
			break ;

		for (int j = 0; j < cols; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void	print_info(t_app *app)
{
	if (app == NULL)
	{
		printf("Struct is empty!\n");
		return;
	}
	// Print the map
	printf("\n-----Struct data-----\n\n");
	if (app->map)
		print_map(app->map);
	if (app->walked_map)
		print_walkedmap(app->walked_map, app->rows, app->cols);
	//Print the mlx and image information
	if (app->mlx)
		printf("mlx: %p\n", app->mlx);
	if (app->img)
	{
		printf("img:\n%p\n", app->img);
		printf("width: %d\n", app->img->width);
		printf("height: %d\n", app->img->height);
	}
	if (app->compass)
		printf("compass: %p\n", app->compass);
	printf("\n");
	//Print the texture information
	if (app->textures) {
		printf("textures:\n%p\n", app->textures);
		if (app->textures->n_text)
			printf("NO: %s\n", app->textures->n_text);
		if (app->textures->s_text)
			printf("SO: %s\n", app->textures->s_text);
		if (app->textures->w_text)
			printf("WE: %s\n", app->textures->w_text);
		if (app->textures->e_text)
			printf("EA: %s\n", app->textures->e_text);
		printf("floor: (%d, %d, %d)\n", app->textures->floor[0],
			app->textures->floor[1], app->textures->floor[2]);
		printf("ceiling: (%d, %d, %d)\n", app->textures->skybox[0],
			app->textures->skybox[1], app->textures->skybox[2]);
	}
	printf("\n");
	//Print the player information
	printf("player:\nstart x: %d\n", app->player.start_x);
	printf("start y: %d\n", app->player.start_y);
	printf("x: %.2f\n", app->player.x);
	printf("y: %.2f\n", app->player.y);
	printf("std_x: %.2f\n", app->player.std_x);
	printf("std_y: %.2f\n", app->player.std_y);
	printf("std_angle: %.2f\n", app->player.std_angle);
	printf("angle: %.2f\n", app->player.angle);
	printf("\n");
	//Print the window and map information
	printf("window and map:\nwindow width: %d\n", app->window_width);
	printf("window height: %d\n", app->window_height);
	printf("map height: %d\n", app->map_height);
	printf("map width: %d\n", app->map_width);
	printf("\n");
	//Print the FOV and ray information
	printf("FOV: %.2f\n", app->fov);
	printf("num rays: %d\n", app->num_rays);
	printf("cur ray: %d\n", app->cur_ray);
	//Print the check queue and walked map information
	printf("check queue: %p\n", app->check_queue);
	printf("cols: %d\n", app->cols);
	printf("rows: %d\n", app->rows);
	printf("end: %d\n", app->end);
	printf("start: %d\n", app->start);
	printf("----------------------------------------\n");
}


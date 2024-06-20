/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:39:07 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/19 20:38:15 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to print the map
void	print_map(char **map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
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

//	function to print the parsed map
void	print_walkedmap(int **map, int rows, int cols)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	while (i < cols)
	{
		if (!map[i])
			break ;
		j = 0;
		while (j < rows + 30)
		{
			printf("%d ", map[i][j++]);
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	print_more_statements(t_app *app)
{
	if (app->img)
	{
		printf("img:\n%p\n", app->img);
		printf("width: %d\n", app->img->width);
		printf("height: %d\n", app->img->height);
	}
	if (app->compass)
		printf("compass: %p\n", app->compass);
	printf("\n");
	if (app->textures)
	{
		printf("textures:\n%p\n", app->textures);
		if (app->textures->n_path)
			printf("NO: %s\n", app->textures->n_path);
		if (app->textures->s_path)
			printf("SO: %s\n", app->textures->s_path);
		if (app->textures->w_path)
			printf("WE: %s\n", app->textures->w_path);
		if (app->textures->e_path)
			printf("EA: %s\n", app->textures->e_path);
		printf("floor: (%d, %d, %d)\n", app->textures->floor[0],
			app->textures->floor[1], app->textures->floor[2]);
		printf("ceiling: (%d, %d, %d)\n", app->textures->skybox[0],
			app->textures->skybox[1], app->textures->skybox[2]);
	}
}

void	print_statements(t_app *app)
{
	printf("\n");
	printf("player:\nstart x: %d\n", app->player.start_x);
	printf("start y: %d\n", app->player.start_y);
	printf("x: %.2f\n", app->player.x);
	printf("y: %.2f\n", app->player.y);
	printf("std_x: %.2f\n", app->player.std_x);
	printf("std_y: %.2f\n", app->player.std_y);
	printf("std_angle: %.2f\n", app->player.std_angle);
	printf("angle: %.2f\n", app->player.angle);
	printf("\n");
	printf("window and map:\nwindow width: %d\n", app->window_width);
	printf("window height: %d\n", app->window_height);
	printf("map height: %d\n", app->map_height);
	printf("map width: %d\n", app->map_width);
	printf("\n");
	printf("FOV: %f\n", app->fov);
	printf("num rays: %d\n", app->num_rays);
	printf("cur ray: %d\n", app->cur_ray);
	printf("check queue: %p\n", app->check_queue);
	printf("cols: %d\n", app->cols);
	printf("rows: %d\n", app->rows);
	printf("end: %d\n", app->end);
	printf("start: %d\n", app->start);
	printf("----------------------------------------\n");
}

//	print all informations from the main struct
void	print_info(t_app *app)
{
	if (app == NULL)
	{
		printf("Struct is empty!\n");
		return ;
	}
	printf("\n-----Struct data-----\n\n");
	if (app->map)
	{
		printf("Original map\n");
		print_map(app->map);
	}
	if (app->val_map)
	{
		printf("Validated map\n");
		print_walkedmap(app->val_map, app->rows, app->cols);
	}
	if (app->minimap)
	{
		printf("Mini_map\n");
		print_walkedmap(app->minimap, app->rows, app->cols);
	}
	if (app->mlx)
		printf("mlx: %p\n", app->mlx);
	print_more_statements(app);
	print_statements(app);
}

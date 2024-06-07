/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuging.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:39:07 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/07 22:42:49 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void print_map(char **map)
{
    if (!map)
        return;

    for (int i = 0; map[i] != NULL; i++)
    {
        if (!map[i])
            break ;

        for (int j = 0; map[i][j] && map[i][j] != '\0'; j++)
        {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
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
}


void	print_info(t_app *app)
{
	if (app == NULL)
		return;

	// Print the map
	if (app->map)
		print_map(app->map);

	if (app->walked_map)
		print_walkedmap(app->walked_map, app->rows, app->cols);
	// Print the mlx and image information
	printf("mlx: %p\n", app->mlx);
	if (app->img) {
		printf("img: %p\n", app->img);
		printf("img width: %d\n", app->img->width);
		printf("img height: %d\n", app->img->height);
	}
	printf("compass: %p\n", app->compass);
	// Print the texture information
	if (app->textures) {
		printf("textures: %p\n", app->textures);
		if (app->textures->n_text)
			printf("texture NO: %s\n", app->textures->n_text);
		if (app->textures->s_text)
			printf("texture SO: %s\n", app->textures->s_text);
		if (app->textures->w_text)
			printf("texture WE: %s\n", app->textures->w_text);
		if (app->textures->e_text)
			printf("texture EA: %s\n", app->textures->e_text);
		printf("texture floor: (%d, %d, %d)\n", app->textures->floor[0],
			app->textures->floor[1], app->textures->floor[2]);
		printf("texture ceiling: (%d, %d, %d)\n", app->textures->skybox[0],
			app->textures->skybox[1], app->textures->skybox[2]);
	}
	// Print the player information
	printf("player start x: %d\n", app->player.start_x);
	printf("player start y: %d\n", app->player.start_y);
	printf("player x: %.2f\n", app->player.x);
	printf("player y: %.2f\n", app->player.y);
	printf("player std_x: %.2f\n", app->player.std_x);
	printf("player std_y: %.2f\n", app->player.std_y);
	printf("player std_angle: %.2f\n", app->player.std_angle);
	printf("player angle: %.2f\n", app->player.angle);
	// Print the window and map information
	printf("window width: %d\n", app->window_width);
	printf("window height: %d\n", app->window_height);
	printf("map height: %d\n", app->map_height);
	printf("map width: %d\n", app->map_width);
	// Print the FOV and ray information
	printf("FOV: %.2f\n", app->fov);
	printf("num rays: %d\n", app->num_rays);
	printf("cur ray: %d\n", app->cur_ray);
	// Print the check queue and walked map information
	printf("check queue: %p\n", app->check_queue);
	printf("cols: %d\n", app->cols);
	printf("rows: %d\n", app->rows);
	printf("end: %d\n", app->end);
	printf("start: %d\n", app->start);
}


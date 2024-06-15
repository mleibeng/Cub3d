/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:10:14 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/15 13:46:54 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	main loop function, if there is a change in movement

void	lstadd_back(t_man **lst, t_man *new)
{
	t_man	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

//	function to free the manual
void	free_manual(t_man **stack)
{
	t_man	*tmp;

	while (*stack)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp->string);
		tmp->string = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_all_resources(t_app *app)
{
	if (app->map)
	{
		free_map((void **)app->map);
		app->map = NULL;
	}
	if (app->walked_map)
	{
		free_map((void **)app->walked_map);
		app->walked_map = NULL;
	}
	if (app->minimap)
	{
		free_map((void **)app->minimap);
		app->minimap = NULL;
	}
	free_textures(app->textures);
	free(app->weapon);
	free_manual(&app->manual);
}

void draw_weapon(t_app *app)
{
	mlx_texture_t *current_texture;

	if (app->weapon->state == ACTIVE)
		current_texture = app->weapon->sprite_act;
	else
		current_texture = app->weapon->sprite;
	app->weapon->x = app->window_width / 2 - current_texture->width / 2;
	app->weapon->y = app->window_height - current_texture->height;
	if (app->weapon->img == NULL)
	{
		app->weapon->img = mlx_texture_to_image(app->mlx, current_texture);
		mlx_image_to_window(app->mlx, app->weapon->img, app->weapon->x, app->weapon->y);
	}
	//else
	//{
	//	// Update the existing image with the new texture

	//}
}

//	function to close a door after certain time
void	close_last_door(t_app *app)
{
	if (app->closing_counter > 0
		&& (int)app->player.x != app->last_open_door_x
		&& (int)app->player.y != app->last_open_door_y)
		app->closing_counter--;
	if (app->last_open_door_x != -1 && app->last_open_door_y != -1
		&& app->closing_counter == 0
		&& (int)app->player.x != app->last_open_door_x
		&& (int)app->player.y != app->last_open_door_y)
	{
		app->walked_map[app->last_open_door_y][app->last_open_door_x] = 3;
		app->last_open_door_x = -1;
		app->last_open_door_y = -1;
	}
}

void	main_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	user_input_hook(app);
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img)
		return ;
	calc_walls(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1)
		exit(1);
	display_minimap(app);
	display_compass(app, app->player.angle);
	//draw_weapon(app);
	close_last_door(app);
}

//	function to remove the manual from the window and replace it
void	remove_manual_from_app(t_app *app)
{
	t_man		*initial_manual;

	initial_manual = app->manual;
	while (app->manual)
	{
		mlx_delete_image(app->mlx, app->manual->str);
		app->manual = app->manual->next;
	}
	app->manual = initial_manual;
	app->man = mlx_put_string(app->mlx, "Press <I> for Manual", MINIMAP_SIZE + 8, 8);
}

// function to print the manual given as a txt.file to the window
void	print_manual(t_app *app)
{
	int		y;
	int		distance;
	t_man	*temp;

	temp = app->manual;
	y = 8;
	distance = 16;
	mlx_delete_image(app->mlx, app->man);
	while (temp)
	{
		temp->str = mlx_put_string(app->mlx, temp->string, MINIMAP_SIZE + 8, y);
		temp = temp->next;
		y += distance;
	}
}

//	reading the lines from the manual and assigning them in a list of images
int	create_manual(t_app *app)
{
	char	*manual_line;
	int		fd;
	t_man	*new_node;

	fd = open("manual.txt", O_RDONLY);
	manual_line = get_next_line(fd);
	if (!manual_line)
	{
		close(fd);
		perror("manual damaged");
		return (0);
	}
	app->manual = NULL;
	while (manual_line)
	{
		new_node = malloc(sizeof(t_man));
		if (!new_node)
			return (EXIT_FAILURE);
		new_node->string = manual_line;
		new_node->next = NULL;
		lstadd_back(&app->manual, new_node);
		manual_line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (1);
	app.map = map_validate(&app, argv[1]);
	if (!app.map)
		return (1);
	if (_init_app(&app))
		return (1);
	//print_info(&app);
	if (app.map)
	{
		mlx_key_hook(app.mlx, key_hook, &app);
		mlx_loop_hook(app.mlx, main_loop, &app);
		mlx_loop(app.mlx);
		mlx_delete_image(app.mlx, app.img);
		mlx_delete_image(app.mlx, app.minimap_img);
		mlx_delete_image(app.mlx, app.compass);
		mlx_terminate(app.mlx);
		free_all_resources(&app);
	}
	return (0);
}

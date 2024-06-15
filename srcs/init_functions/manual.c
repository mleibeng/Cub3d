/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:00:03 by fkeitel           #+#    #+#             */
/*   Updated: 2024/06/15 19:46:40 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	function to add line to the manual list
void	read_manual(t_man **lst, char **string, int fd)
{
	t_man	*current;
	t_man	*new;

	new = malloc(sizeof(t_man));
	if (!new)
		exit(1);
	new->next = NULL;
	new->string = strdup(*string);
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	free(*string);
	*string = get_next_line(fd);
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

//	function to remove the manual from the window and replace it
void	remove_manual_from_app(t_app *app)
{
	t_man	*initial_manual;

	initial_manual = app->manual;
	while (app->manual)
	{
		mlx_delete_image(app->mlx, app->manual->str);
		app->manual = app->manual->next;
	}
	app->manual = initial_manual;
	app->man = mlx_put_string(app->mlx, "Press <I> for Manual",
			app->window_width / 2 - 100, 8);
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
		temp->str = mlx_put_string(app->mlx, temp->string, MINIMAP_SIZE + 3, y);
		temp = temp->next;
		y += distance;
	}
}

//	reading the lines from the manual and assigning them in a list of images
int	create_manual(t_app *app)
{
	char	*manual_line;
	int		fd;
	mode_t	permissions;

	fd = open("manual.txt", O_RDONLY);
	manual_line = get_next_line(fd);
	if (!manual_line)
	{
		permissions = S_IRUSR | S_IRGRP | S_IROTH;
		if (chmod("manual.txt", permissions) == -1)
		{
			close(fd);
			perror("chmod");
			perror("manual damaged or permission denied!\n");
			return (0);
		}
		printf("changed permission from manual!\n");
		create_manual(app);
	}
	while (manual_line)
		read_manual(&app->manual, &manual_line, fd);
	close(fd);
	if (chmod("manual.txt", 0) == -1)
		return (perror("chmod"), 1);
	return (EXIT_SUCCESS);
}

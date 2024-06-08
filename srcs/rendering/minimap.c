/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:01:46 by mleibeng          #+#    #+#             */
/*   Updated: 2024/06/09 00:24:20 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// // Function to clear the compass background
// void	clear_minimap(mlx_image_t *img, int32_t background_color)
// {
// 	int	y;
// 	int	x;

// 	// int	dx;
// 	// int	dy;
// 	y = 0;
// 	while (y < MINIMAP_SIZE)
// 	{
// 		x = 0;
// 		while (x < MINIMAP_SIZE)
// 		{
// 			// dx = x - CENTER;
// 			// dy = y - CENTER;
// 			// if (dx * dx + dy * dy <= CENTER * CENTER)
// 			mlx_put_pixel(img, x, y, background_color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_map_logic(t_app *app)
// {
// 	int i, j;
// 	int minimap_x, minimap_y;
// 	int scale = MINIMAP_SIZE / app->cols; // Assuming minimap is square
// 	for (i = 0; i < app->rows; i++)
// 	{
// 		for (j = 0; j < app->cols; j++)
// 		{
// 			// Calculate the position on the minimap
// 			minimap_x = j * scale;
// 			minimap_y = i * scale;
// 			// Check the minimap data and draw the appropriate pixel
// 			if (app->minimap[i][j] == 1) // Wall
// 			{
// 				// Draw a wall pixel
// 				for (int map_y = 0; map_y < scale; map_y++)
// 				{
// 					for (int map_x = 0; map_x < scale; map_x++)
// 					{
// 						mlx_put_pixel(app->minimap_img, minimap_x + map_x,
// 							minimap_y + map_y, 0xFFFFFF);
// 							// White color for walls
// 					}
// 				}
// 			}
// 			else if (app->minimap[i][j] == 2) // Player
// 			{
// 				// Draw a player pixel
// 				for (int map_y = 0; map_y < scale; map_y++)
// 				{
// 					for (int map_x = 0; map_x < scale; map_x++)
// 					{
// 						mlx_put_pixel(app->minimap_img, minimap_x + map_x,
// 							minimap_y + map_y, 0xFF0000);
// 							// Red color for player
// 					}
// 				}
// 			}
// 			else // Floor
// 			{
// 				// Draw a floor pixel
// 				for (int map_y = 0; map_y < scale; map_y++)
// 				{
// 					for (int map_x = 0; map_x < scale; map_x++)
// 					{
// 						mlx_put_pixel(app->minimap_img, minimap_x + map_x,
// 							minimap_y + map_y, 0x00FF00);
// 							// Green color for floors
// 					}
// 				}
// 			}
// 		}
// 	}
// }

// //	draw the compass ring
// void	draw_minimap(t_app *app)
// {
// 	int32_t	colour;
// 	int32_t	background_colour;
// 	int		minimap_player_x;
// 	int		minimap_player_y;
// 	int		x;
// 	int		y;

// 	colour = CLEAR;
// 	background_colour = BLACK;
// 	x = 0;
// 	y = 0;
// 	clear_minimap(app->minimap_img, background_colour);
// 	draw_map_logic(app);
// 	minimap_player_x = app->window_width / 2 - MINIMAP_PLAYER / 2;
// 	minimap_player_y = app->window_height / 2 - MINIMAP_PLAYER / 2;
// 	while (y < MINIMAP_PLAYER)
// 	{
// 		while (x < MINIMAP_PLAYER)
// 		{
// 			mlx_put_pixel(app->player_on_mini, x, y, BRIGHTRED);
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (mlx_image_to_window(app->mlx, app->player_on_mini, minimap_player_x,
// 			minimap_player_y) == -1)
// 		printf("error in minimap player display");
// }

// // Function to create and display the compass
// void	display_minimap(t_app *app)
// {
// 	draw_minimap(app);
// 	// center_minimap(app);
// 	// rotate_minimap(app, app->player.angle);
// }

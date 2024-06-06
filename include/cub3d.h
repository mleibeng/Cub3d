/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/05 23:22:11 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
------------------------------- initial setup ----------------------------------
 */

#if !defined(CUB3D_H)
# define CUB3D_H

# include "../libft/libft.h"
# include "MLX42/MLX42.h"
# include <limits.h>
# include "color.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* -------------------- non-adjustable pre-settings ------------------------- */

# define MAP_WIDTH 5
# define MAP_HEIGHT 6
# define COMPASS_SIZE 100 // Size of the compass image
# define CENTER (COMPASS_SIZE / 2) // Center of the compass

/* ----------------------- adjustable pre-settings -------------------------- */

# define PLAYER_MOVE_SPEED 0.03
# define PLAYER_ROTATE_SPEED 0.03

extern int g_map[MAP_WIDTH][MAP_HEIGHT];

/* -------------------------------- structs --------------------------------- */

typedef struct s_tar
{
	float	target_x;
	float	target_y;
	float	distance;
	int		hit_vertical;
	int		wall_height;
	int32_t		color;
}	t_tar;

//	coordinates of the player
typedef struct s_player
{
	float		x;
	float		y;
	float		std_x;
	float		std_y;
	float		std_angle;
	float		angle;
}				t_player;

typedef enum
{
	EMPTY_TILE,
	WALL_TILE,
	ITEM_TILE,
	GROUND_TILE,
	DOOR_TILE,
	EXIT_TILE,
	SKY_TILE,
	NORTH_TILE,
	EAST_TILE,
	SOUTH_TILE,
	WEST_TILE
}				t_tile;

typedef t_tile	**t_map;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*compass;
	int			needle_x;
	int			needle_y;
	t_player	player;
	int			window_width;
	int			window_height;
	int			map_height;
	int			map_width;
	float		fov;
	int			num_rays;
	int			cur_ray;
}				t_app;

/*
--------------------------------- functions ------------------------------------
*/

// ----------------------------- calculations ----------------------------------

//	calculations.c
float	cast_ray(t_player *player, float ray_angle, t_tar *wall);
void	calc_walls(t_app *app);
float	norm_ang(float angle);

// ------------------------------ rendering ------------------------------------

//	rendering.c
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	draw_part_ray(t_app *app, int start, int end, int32_t color);
void	draw_ray(t_app *app, t_tar *wall);
//	compass.c
void display_compass(t_app *app, float player_angle);
// ------------------------------ user input -----------------------------------

//	user_input.c
void	key_hook(mlx_key_data_t keydata, void *param);
int		ft_hook_key(t_app *app);
#endif

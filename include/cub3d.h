/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/06 20:33:22 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(CUB3D_H)
# define CUB3D_H

# include "../libft/libft.h"
# include "MLX42/MLX42.h"
# include "color.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MAP_WIDTH 5
# define MAP_HEIGHT 6
# define MAX_LINE_LENGTH 1024

/* ----------------------- adjustable pre-settings -------------------------- */

# define PLAYER_MOVE_SPEED 0.03
# define PLAYER_ROTATE_SPEED 0.03

extern int		g_map[MAP_WIDTH][MAP_HEIGHT];

/* -------------------------------- structs --------------------------------- */

typedef struct s_tar
{
	float		target_x;
	float		target_y;
	float		distance;
	int			wall_height;
	int32_t		color;
}				t_tar;

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

typedef struct s_texture
{
	char		*n_text;
	char		*e_text;
	char		*s_text;
	char		*w_text;
	int			floor[3];
	int			skybox[3];
}				t_texture;

typedef enum
{
	EMPTY_TILE = BLACK,
	WALL_TILE = WHITE,
	ITEM_TILE = RED,
	GROUND_TILE = LIME,
	DOOR_TILE = BLUE,
	EXIT_TILE = YELLOW,
	SKY_TILE = MAGENTA,
	NORTH_TILE = MAROON,
	EAST_TILE = TEAL,
	SOUTH_TILE = NAVY,
	WEST_TILE = PURPLE
}				t_tile;

typedef t_tile	**t_map;

typedef struct s_data
{
	int			map_length;
	int			map_width;
	t_map		map;

	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	int			window_width;
	int			window_height;
	int			map_height;
	int			map_width;
	float		fov;
	int			num_rays;
	int			cur_ray;
	char		**map;
	t_texture	*textures;
}				t_app;

/*
--------------------------------- functions ------------------------------------
*/

// ----------------------------- calculations ----------------------------------

//	calculations.c
float			cast_ray(t_player *player, float ray_angle, t_tar *wall);
void			calc_walls(t_app *app);

// ------------------------------ rendering ------------------------------------

//	rendering.c
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_part_ray(t_app *app, int start, int end, int32_t color);
void			draw_ray(t_app *app, t_tar *wall);
// ------------------------------ user input -----------------------------------

//	user_input.c
void			key_hook(mlx_key_data_t keydata, void *param);
int				ft_hook_key(t_app *app);
#endif

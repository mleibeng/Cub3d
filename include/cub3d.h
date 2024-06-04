/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/04 07:44:32 by flo              ###   ########.fr       */
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

# define MAP_WIDTH 5
# define MAP_HEIGHT 6

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
	t_player	player;
	int			window_width;
	int			window_height;
	int			map_height;
	int			map_width;
	float		fov;
	int			num_rays;
	int			cur_ray;
}				t_app;

typedef struct s_rendering
{
}				t_rendering;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/03 17:50:14 by mleibeng         ###   ########.fr       */
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
# define MAP_HEIGHT 5
# define NUM_RAYS 200
# define FOV (M_PI / 3)
# define PLAYER_MOVE_SPEED 0.1
# define PLAYER_ROTATE_SPEED 0.05
# define WIDTH 512
# define HEIGHT 512

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

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

typedef struct s_data
{
	int			map_length;
	int			map_width;
	t_vec		position;
	t_vec		direction;
	t_map		map;

	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_data;

typedef struct s_rendering
{
}				t_rendering;

#endif

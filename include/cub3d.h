/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvinleibenguth <marvinleibenguth@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/05/21 10:54:55 by marvinleibe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(CUB3D_H)
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <errno.h>
#include "color.h"
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#define WIDTH 512
#define HEIGHT 512

typedef struct s_vec
{
    double x;
    double y;
} t_vec;

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
} t_tile;

typedef t_tile  **t_map;

typedef struct s_data
{

    int map_length;
    int map_width;
    t_vec position;
    t_vec direction;
    t_map map;

    mlx_t *mlx;
    mlx_image_t *img;
}   t_data;

typedef struct s_rendering
{
    
}   t_rendering;

#endif

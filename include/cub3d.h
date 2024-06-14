/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/14 01:29:30 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
------------------------------- initial setup ----------------------------------
 */

#if !defined(CUB3D_H)
# define CUB3D_H

# include "../libft/libft.h"
# include "MLX42/MLX42.h"
# include "color.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*--------------------- OS-specific constant definitions--------------------- */

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338328 // Pi
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923132169164 // Pi/2
# endif
# ifndef M_PI_4
#  define M_PI_4 0.78539816339744830961566084582 // Pi/4
# endif

/* -------------------- non-adjustable pre-settings ------------------------- */

# define COMPASS_SIZE 81           // Size of the compass image
# define CENTER (COMPASS_SIZE / 2) // Center of the compass
# define MINIMAP_SIZE 100
# define MINIMAP_PLAYER 5
# define MAX_LINE_LENGTH 1024
# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 960
/* ----------------------- adjustable pre-settings -------------------------- */

# define PLAYER_MOVE_SPEED 0.03
# define PLAYER_ROTATE_SPEED 0.06
# define PLAYER_SIZE 0.1

/*--------------------------------- Macros ---------------------------------- */

/* -------------------------------- structs --------------------------------- */

typedef struct s_vec
{
	int			x;
	int			y;
}				t_vec;

//	struct for one coordinate point on the map for drawing a line
typedef struct s_coord
{
	int			xw;
	int			yw;
	int32_t		color;
}				t_coord;

typedef struct s_tar
{
	float		tar_x;
	float		tar_y;
	float		distance;
	int			hit;
	int			wall_height;
	int			side;
	int			x;
	float		pos_x_cur_tyle;
	int32_t		color;
}				t_tar;

//	coordinates of the player
typedef struct s_player
{
	int			start_x;
	int			start_y;
	float		x;
	float		y;
	float		std_x;
	float		std_y;
	float		std_angle;
	float		angle;
}				t_player;

typedef enum s_state
{
	HOLSTERED,
	ACTIVE
}				t_state;

typedef struct s_weapon
{
	mlx_image_t *img;
	mlx_texture_t	*sprite;
	mlx_texture_t	*sprite_act;
	int			x;
	int			y;
	t_state		state;
}				t_weapon;

typedef struct s_texture
{
	char		*n_path;
	char		*e_path;
	char		*s_path;
	char		*w_path;
	xpm_t		*n_text;
	xpm_t		*e_text;
	xpm_t		*s_text;
	xpm_t		*w_text;
	char		*d_path;
	xpm_t		*d_text;
	int			floor[4];
	int			skybox[4];
}				t_texture;

typedef struct s_minimap
{
	int			half_size;
	t_vec		xy;
	int			wall_size;
	int			minimap_x;
	int			minimap_y;
	int			map_x;
	int			map_y;
}				t_minimap;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*compass;
	mlx_image_t	*minimap_img;
	mlx_image_t	*player_on_mini;
	t_weapon	*weapon;
	t_texture	*textures;
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
	t_vec		pos;
	t_vec		*check_queue;
	int			**walked_map;
	int			**minimap;
	t_minimap	mini_info;
	int			cols;
	int			rows;
	int			end;
	int			start;
	char		**map;
}				t_app;

/*
--------------------------------- functions ------------------------------------
*/

// ----------------------------- calculations ----------------------------------

//	calculations.c
float			cast_ray(t_app *app, float ray_angle, t_tar *wall);
void			calc_walls(t_app *app);
float			norm_ang(float angle);
//	line_algorithm.c
void			draw_line(t_app *app, t_coord point_a, t_coord point_b);
//	math.c
int				ft_ro(float num);
float			norm_ang(float angle);
double			get_fractional_part(double num);

// -------------------------------- init.c -------------------------------------

//	init.c
t_coord			init_coord(int point_x, int point_y, int32_t color);
int				init_compass(t_app *app);
void			_init_texture(t_texture *texture);
int				_init_app(t_app *app);

// ----------------------------- map_parsing -----------------------------------

//	map_parsing.c
char			**map_validate(t_app *app, char *file);
void			print_walkedmap(int **map, int rows, int cols);
void			print_map(char **map);
void			free_map(void **map);
void			free_textures(t_texture *textures);
void			free_all_resources(t_app *app);

// ------------------------------ rendering ------------------------------------

//	color_functions.c
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			mix_and_put_color(t_app *app, int32_t color, float factor,
					int shade, int y);
uint32_t		get_texture_pixel(mlx_texture_t *texture, int x, int y,
					int shade);
xpm_t			*get_text(t_app *app, int side);

//	rendering.c
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_part_ray(t_app *app, int start, int end, int32_t color,
					char dir);
void			draw_ray(t_app *app, t_tar *wall);
//	minimap.c
int				init_minimap(t_app *app);
//	compass.c
void			display_compass(t_app *app, float player_angle);
void			display_minimap(t_app *app);
// ------------------------------ user input -----------------------------------

//	key_input.c
void			key_hook(mlx_key_data_t keydata, void *param);
void			direction_change_hook(t_app *app);
void			view_change_hook(t_app *app);
//	mouse_input.c
int				mouse_shift(t_app *app);
//		user_input.c
void			user_input_hook(t_app *app);

// ------------------------------  debugging -----------------------------------
void			print_info(t_app *app);
#endif

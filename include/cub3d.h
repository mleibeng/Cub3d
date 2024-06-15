/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:14:31 by marvinleibe       #+#    #+#             */
/*   Updated: 2024/06/15 20:06:04 by mleibeng         ###   ########.fr       */
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
# include <sys/stat.h> //	for chmod()
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

# define COMPASS_SIZE 81
# define CENTER 40
# define MINIMAP_SIZE 100
# define MINIMAP_PLAYER 5
# define MAX_LINE_LENGTH 1024
# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 960
# define OFF 1
# define ON 2
# define VERTICAL 0
# define NONVERTICAL 1
# define DOOR_VERTIKAL 2
# define DOOR_HOR 3
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define DOOR 5

/* ----------------------- adjustable pre-settings -------------------------- */

# define PLAYER_MOVE_SPEED 0.06
# define PLAYER_ROTATE_SPEED 0.06
# define PLAYER_SIZE 0.1

/*--------------------------------- Macros ---------------------------------- */

/* -------------------------------- structs --------------------------------- */

typedef struct s_vec
{
	int				x;
	int				y;
}					t_vec;

//	struct for one coordinate point on the map for drawing a line

typedef struct s_color
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	uint8_t			alpha;
}					t_color;

typedef struct s_put_col
{
	int32_t			color;
	float			factor;
	int				shade;
	int				y;
}					t_put_col;

typedef struct s_coord
{
	int				xw;
	int				yw;
	int32_t			color;
}					t_coord;

/**
 * Struct for the current ray wall data
 * @param tar_x x coordinate where the ray will hit.
 * @param tar_y y coordinate where the ray will hit.
 * @param distance distance to the target from player.
 * @param hit how ray will hit the target,
 * 	vertikal/ horizontal or at a door.
 * @param wall_height height of the wall at the current ray.
 * @param side which side 1 - 4 for direwctions, 5 for a door.
 * @param x cur position in x

* @param pos_x_cur_tyle which position at the current tyle the ray hits
 * @param color color of the current ray
 */
typedef struct s_tar
{
	float			tar_x;
	float			tar_y;
	float			distance;
	int				hit;
	int				wall_height;
	int				side;
	int				x;
	float			pos_x_cur_tyle;
	int32_t			color;
}					t_tar;

/**
 * Main application structure containing all necessary data for the game.
 * @param start_x start position x coordinate.
 * @param start_y start position x coordinate.
 * @param x current pos x coordinate.
 * @param y current pos y coordinate.
 * @param std_x start pos x coordinate.
 * @param std_y start pos y coordinate.
 * @param std_angle start angle in radial
 * @param angle current angle in radial
 */
typedef struct s_player
{
	int				start_x;
	int				start_y;
	float			x;
	float			y;
	float			std_x;
	float			std_y;
	float			std_angle;
	float			angle;
}					t_player;

typedef enum s_state
{
	HOLSTERED,
	ACTIVE
}					t_state;

typedef struct s_weapon
{
	mlx_image_t		*img;
	mlx_texture_t	*sprite;
	mlx_texture_t	*sprite_act;
	int				x;
	int				y;
	t_state			state;
}					t_weapon;

/**
 * Texture struct, where all informations of the textures are.
 * @param n_path path to the tyles xpm42 files (d = door, n = north,
 * s = south, ...).
 * @param n_text texture struct (d = door, n = north, s = south, ...).
 * @param floor rgba colorcode of the floor/ ceiling
 * @param skybox rgba colorcode of the sky
 */
typedef struct s_texture
{
	char			*n_path;
	char			*e_path;
	char			*s_path;
	char			*w_path;
	xpm_t			*n_text;
	xpm_t			*e_text;
	xpm_t			*s_text;
	xpm_t			*w_text;
	char			*d_path;
	xpm_t			*d_text;
	int				floor[4];
	int				skybox[4];
}					t_texture;

typedef struct s_minimap
{
	int				half_size;
	t_vec			xy;
	int				wall_size;
	int				minimap_x;
	int				minimap_y;
	int				map_x;
	int				map_y;
}					t_minimap;

//	struct for images for the manual, independent from the map
typedef struct s_manual
{
	mlx_image_t		*str;
	char			*string;
	struct s_manual	*next;
}					t_man;

/**
 * Main application structure containing all necessary data for the game.
 * @param mlx Main MLX handle, manages window and graphical context.
 * @param img Main image buffer for rendering.
 * @param compass Image for the compass overlay.
 * @param minimap_img Image for the minimap display.
 * @param player_on_mini Image for the player icon on the minimap.
 * @param weapon Current weapon data.
 * @param textures Collection of game textures.
 * @param needle_x X-coordinate for the compass needle.
 * @param needle_y Y-coordinate for the compass needle.
 * @param player Player data and state.
 * @param window_width Width of the game window.
 * @param window_height Height of the game window.
 * @param map_height Height of the game map in tiles.
 * @param map_width Width of the game map in tiles.
 * @param fov Field of view for the player's perspective.
 * @param num_rays Number of rays cast for rendering the scene.
 * @param cur_ray Current ray being processed.
 * @param pos Current position vector of the player.
 * @param check_queue Queue for pathfinding or other checks.
 * @param walked_map 2D array tracking tiles the player has walked on.
 * @param minimap 2D array representing the minimap data.
 * @param mini_info Information and settings for the minimap.
 * @param cols Number of columns in the map.
 * @param rows Number of rows in the map.
 * @param end End position or flag in the map or game logic.
 * @param start Start position or flag in the map or game logic.
 * @param map 2D array representing the map layout.
 * @param l_op_door_x X-coordinate of the last opened door.
 * @param l_op_door_y Y-coordinate of the last opened door.
 * @param closing_counter Counter for door closing animation or timing.
 */
typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*compass;
	mlx_image_t		*minimap_img;
	mlx_image_t		*player_on_mini;
	t_weapon		*weapon;
	t_texture		*textures;
	int				needle_x;
	int				needle_y;
	t_player		player;
	int				window_width;
	int				window_height;
	int				map_height;
	int				map_width;
	float			fov;
	int				num_rays;
	int				cur_ray;
	t_vec			pos;
	t_vec			*check_queue;
	int				**walked_map;
	int				**minimap;
	t_minimap		mini_info;
	int				cols;
	int				rows;
	int				end;
	int				start;
	char			**map;
	int				l_op_door_x;
	int				l_op_door_y;
	int				closing_counter;
	mlx_image_t		*man;
	t_man			*manual;
}					t_app;

/*
--------------------------------- functions ------------------------------------
*/

// ----------------------------- calculations ----------------------------------

//	calculations.c
float				cast_ray(t_app *app, float ray_angle, t_tar *wall);
void				calc_walls(t_app *app);
float				norm_ang(float angle);
//	line_algorithm.c
void				draw_line(t_app *app, t_coord point_a, t_coord point_b);
//	math.c
int					ft_ro(float num);
float				norm_ang(float angle);
double				get_fractional_part(double num);

// -------------------------------- init.c -------------------------------------

//	init.c
t_coord				init_coord(int point_x, int point_y, int32_t color);
int					init_compass(t_app *app);
void				_init_texture(t_texture *texture);
int					_init_app(t_app *app);

// init_imgs.c
t_weapon			*_init_weapon(t_app *app);
void				load_textures(t_app *app);

// ----------------------------- map_parsing -----------------------------------

// free_functions
void				free_queue(t_app *app);
void				emergency_exit(t_app *app, t_texture *texture, char **map);

//	map_parsing.c
char				**map_validate(t_app *app, char *file);
void				print_walkedmap(int **map, int rows, int cols);
void				print_map(char **map);
void				free_map(void **map);
void				free_textures(t_texture *textures);
void				free_all_resources(t_app *app);

// ------------------------------ rendering ------------------------------------

//	color_functions.c
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void				mix_and_put_color(t_app *app, t_put_col info);
uint32_t			get_texture_pixel(mlx_texture_t *texture, int x, int y,
						int shade);
xpm_t				*get_text(t_app *app, int side);
//	rendering.c
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
// void				draw_part_ray(t_app *app, int start, int end, int32_t color,
// 						char dir);
void				draw_ray(t_app *app, t_tar *wall);

void				init_directions(t_vec *directions);
void				f_player_start(t_app *app, char **map, int *player_x,
						int *player_y);
float				check_start_angle(char direction);
void				fill_minimap_bounds(char **map, int **mini_map, t_vec *ij);
int					fill_bounds(int next_x, int next_y, t_app *app, char **map);
int					check_bounds(t_app *app);
int					check_row_bound(t_app *app);
int					check_column_bound(t_app *app);
void				parse_floor_ceiling(int fd, t_texture *texture);
void				save_rgb(char *line, int *color);
void				color_validation(char *end, char *line, int val);
void				replace_adj_doors(t_app *app, char **map);
void				fill_minimap(char **map, int **mini_map, t_app *app);
int					**create_map(int rows, int columns);
int					fill_map(char **map, t_app *app, t_vec *direct);
void				parse_file(int fd, t_texture *texture, char ***map,
						t_vec *rows_cols);
void				parse_map(char *line, char ***map, t_vec *rows_cols);
int					is_valid(char c);
int					character_validation(char **map, int rows,
						t_texture *textures);
void				_validate_field(char **map, t_vec *rowcol, t_app *app);
char				**map_validate(t_app *app, char *file);
int					open_file(char *file);
t_texture			*read_map(char *file, char ***map, t_vec *rows_cols);
int					closed_map(char **map, t_vec *rowcol, t_app *app);
void				parse_door_text(char *file, t_texture *texture);
void				dup_door_path(char *line, int *keep_reading,
						t_texture *texture);
void				parse_textures(int fd, t_texture *texture);
void				compare_textures(t_texture *texture, char *line);
t_texture			*init_texture(void);
// minimap_cals.c
int					is_within_minimap_bounds(t_app *app);
void				calculate_xy_coordinates(t_app *app, t_vec map,
						t_vec minimap);
void				put_player_mini(t_app *app);
void				rotate_point(t_vec *xy, float angle, int cy);
void				clear_mini_map(mlx_image_t *img, int32_t background_color);
//	minimap.c
int					init_minimap(t_app *app);
//	compass.c
void				display_compass(t_app *app, float player_angle);
void				display_minimap(t_app *app);
// ------------------------------ user input -----------------------------------

//	door_logic.c
void				door_open_close(t_app *app);
//	key_input.c
void				key_hook(mlx_key_data_t keydata, void *param);
void				direction_change_hook(t_app *app);
void				view_change_hook(t_app *app);
//	mouse_input.c
int					mouse_shift(t_app *app);
//	player_move.c
int					check_wall_collision(t_app *app, float new_x, float new_y);
void				move_sideways(t_app *app, float *new_x, float *new_y);
void				move_for_back(t_app *app, float *new_x, float *new_y);
//		user_input.c
void				user_input_hook(t_app *app);

// ------------------------------  debugging -----------------------------------
void				print_info(t_app *app);

//	manual.c
void				remove_manual_from_app(t_app *app);
void				print_manual(t_app *app);
int					create_manual(t_app *app);
void				free_manual(t_man **stack);

#endif
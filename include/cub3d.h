/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:25:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/21 14:33:20 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ############################## INCLUDES ############################### */

// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// Boolean
# include <stdbool.h>

// Error
# include <errno.h>

// Math
# include <math.h>
// Graphics
# include "../mlx/mlx.h"
// Keyboard keys library / X11 events
# include <X11/keysym.h>
# include <X11/X.h>

// Colors
# include "color.h"
// Libft
# include "../libft/Includes/libft.h"
// Shapes
# include "shapes.h"
// Parsing
# include "parsing.h"

/* ################################ DEFINES ################################ */

// Screen size
# define WIDTH 1270
# define HEIGHT 720

// Limits

// Protection against division by zero
// # define INFINITY 1e30 (present in math.h)

/* ############################# ENUMERATIONS ############################## */

/**
 * @brief Enum for the keys
 * @param RELEASED The released key
 * @param PRESSED The pressed key
*/
enum e_key
{
	RELEASED,
	PRESSED
};

/**
 * @brief Enum for the tiles
 * @param EMPTY The empty tile
 * @param WALL The wall tile
*/
enum e_tile
{
	GROUND,
	WALL,
	DOOR,
	PLAYER,
	EMPTY
};

/**
 * @brief Enum for the side
 * @param EW The east/west side
 * @param NS The north/south side
*/
enum e_side
{
	NS,
	EW
};

/**
 * @brief Enum for the textures
 * @param NORTH The north texture
 * @param SOUTH The south texture
 * @param EAST The east texture
 * @param WEST The west texture
*/
enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

/* ############################## STRUCTURES ############################### */

/**
 * @brief Struct for the keys
 * @param key_w The W key
 * @param key_a The A key
 * @param key_s The S key
 * @param key_d The D key
 * @param key_left The left arrow key
 * @param key_right The right arrow key
*/
typedef struct s_keys
{
	enum e_key	key_w;
	enum e_key	key_a;
	enum e_key	key_s;
	enum e_key	key_d;
	enum e_key	key_left;
	enum e_key	key_right;
}	t_keys;

/**
 * @brief Struct for the mlx
 * @param mlx The mlx pointer
 * @param win The window pointer
*/
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

/**
 * @brief Struct for the image
 * @param img The image
 * @param addr The address of the image
 * @param bpp Bits per pixel
 * @param line_len The length of the line
 * @param endian The endian 
 * (big or little endian - 0 or 1 - depending on the system's architecture)
*/
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/**
 * @brief Player infos struct
 * @param pos_x The x position of the player
 * @param pos_y The y position of the player
 * @param fov The field of view of the player
 * @param dir_x The x direction of the player
 * @param dir_y The y direction of the player
 * @param plane_x The x camera plane of the player
 * @param plane_y The y camera plane of the player
*/
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		fov;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

/**
 * @brief Struct for the map
 * @param width The width of the map
 * @param height The height of the map
 * @param map The map[height][width]
*/
typedef struct s_map
{
	int			width;
	int			height;
	enum e_tile	**map;
}	t_map;

/**
 * @brief Struct for the texture
 * @param type The type of the texture
 * @param path The path to the texture
 * @param img The img struct
 * @param width The width of the texture
 * @param height The height of the texture
*/
typedef struct s_texture
{
	enum e_texture	type;
	char			*path;
	t_img			img;
	int				width;
	int				height;
}	t_texture;

/**
 * @brief Struct for the textures
 * @param north The north texture
 * @param south The south texture
 * @param east The east texture
 * @param west The west texture
 * @param floor_color The floor color
 * @param ceiling_color The ceiling color
*/
typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	int			floor_color;
	int			ceiling_color;
}	t_textures;

/**
 * @brief Struct for the ray
 * @param camera_x The x position of the camera
 * @param camera_y The y position of the camera
 * @param ray_dir_x The x direction of the ray
 * @param ray_dir_y The y direction of the ray
 * @param map_x The current x position in the map grid of the cell
 * @param map_y The current y position in the map grid of the cell
 * @param side_dist_x The distance to the side in the x axis
 * @param side_dist_y The distance to the side in the y axis
 * @param delta_dist_x The distance to the next x side
 * @param delta_dist_y The distance to the next y side
 * @param perp_wall_dist The perpendicular wall distance
 * (used to calculate the length of the ray)
 * @param step_x The step in the x axis
 * @param step_y The step in the y axis
 * @param hit The hit status (true if the ray hit a wall, false otherwise)
 * @param side The side of the hitted wall	(0 = NS, 1 = EW)
 * @param x The x coordinate of the ray in the screen (used to draw the line)
 * @param y The y coordinate of the ray in the screen (used to draw the line)
 * @param line_height The height of the line to draw
 * @param draw_start The start of the line to draw
 * @param draw_end The end of the line to draw
 * @param color The color of the line to draw (if no texture is used)
 * @param tile The tile that was hit
 * @param texture The texture side of the wall/tile type
 * @param wall_x The x coordinate of the tile that was hit. Needed to calculate
 * the x coordinate of the texture that will be used to draw the wall/tile type
 * @param tex_x The x coordinate of the texture that will be used 
 * to draw the wall
 * @param tex_y The y coordinate of the texture that will be used
 * to draw the wall
 * @param tex_coord The texture coordinate to draw the line
 * @param tex_step The texture step (increment the texture coordinate)
 * @note Using double gives more precision to the ray calculations
 * (but it's slower than using float)
*/
typedef struct s_ray
{
	double				camera_x;
	double				camera_y;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	bool				hit;
	enum e_side			side;

	int					x;
	int					y;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					color;

	enum e_tile			tile;
	t_texture			*texture;
	double				wall_x;
	int					tex_x;
	int					tex_y;
	double				tex_coord;
	double				tex_step;
}	t_ray;

/**
 * @brief Struct for the game
 * @param mlx The mlx struct
 * @param img The img struct
*/
typedef struct s_game
{
	t_mlx		mlx;
	t_img		img;
	t_keys		keys;
	t_map		map;
	t_player	player;
	t_textures	textures;
	int			mouse_x;
	int			mouse_y;
}	t_game;

/* ############################## PROTOTYPES ############################### */

// Setup

bool	ft_setup_textures(t_game *game);
bool	ft_setup_map(t_game *game);
bool	ft_setup_player(t_game *game);
bool	ft_setup(t_game *game);

// Graphics

// Raycasting

void	raycasting(t_game *game);
void	calculate_perp_wall_dist(t_ray *ray);
void	calculate_line_params(t_ray *ray);

	// Textures
void	find_wall_texture(t_game *game, t_ray *ray);
void	draw_texture_line(t_game *game, t_ray *ray);

	// Simple color
void	find_wall_color(t_game *game, t_ray *ray);

// Movement

void	update_movement(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

// Pixel

void	pixel_put(t_img *img, int x, int y, int color);

// Colors

int		create_argb(int a, int r, int g, int b);
int		get_alpha(int argb);
int		get_red(int argb);
int		get_green(int argb);
int		get_blue(int argb);

// Events

void	ft_events(t_game *game);

// Exit

void	ft_free_all(t_game *game);
int		ft_exit(t_game *game);

/* ################################ SHAPES ################################# */

// Line

void	draw_horizontal_line(t_img *img, t_point p1, t_point p2, int color);
void	draw_vertical_line(t_img *img, t_point p1, t_point p2, int color);
void	line(t_img *img, t_point p1, t_point p2, int color);

// Rectangle

void	rectangle(t_img *img, t_point start, t_point end, int color);
void	fill_rectangle(t_img *img, t_point start, t_point end, int color);

/* ################################ PARSING ################################ */

// parsing_map.c

void	parsing_map_single(t_game *game);
void	parsing_map_closed_and_single(t_game *game);
void	parse_map(t_game *game, t_fds fd);

// parsing_map_utils.c

void	parsing_find_start_index(t_game *game, int *i_start, int *j_start);
void	parsing_fill_test_map(t_game *game, t_map *test_map);
void	parsing_check_nb_island(t_game *game, t_map *test_map);
void	parsing_fill_first_island(t_map *map, int i, int j);
void	free_parse_map(t_game *game, int fd2);

// parsing_map_valid_tiles.c

int		is_edge(t_map map, int i, int j);
int		unclosed_ground(t_map map, int i, int j);
void	parsing_count_player_map(t_game *game);

// parsing_map_collect.c

void	parsing_fill_submap(t_game *game, char *buffer, int i, t_fds fd);
void	parsing_collect_map(t_game *game, t_fds fd);

// parsing_map_size.c

int		is_char_to_trim(char c, char const *to_trim);
char	*right_strtrim(char *src, char *to_trim);
char	*right_trim_gnl(t_game *game, t_fds fd);
void	parsing_check_if_end_of_map(t_game *game, t_fds fd, char *prev_buffer);
void	parsing_width_height_map(t_game *game, t_fds fd);

// parsing_colors.c

void	parsing_set_color(t_game *game, char *identifier, char *color_rgb,
			t_fds fd);
void	parsing_char_color(t_game *game, char *color_rgb, t_fds fd);
void	parsing_color_format(t_game *game, char *color_rgb, t_fds fd);
void	parsing_color_range(t_game *game, int *texture_color,
			char *color_rgb, t_fds fd);

// parsing_colors_utils.c

void	parsing_free_color(t_game *game, char *color_rgb, t_fds fd);
int		parsing_count_digits(char *color_rgb, int *i);

// parsing_free.c

void	parsing_free(t_game *game);
void	parsing_free_textures(t_game *game);
int		parsing_clean_end(t_game *game);
void	parsing_exit_error(t_game *game);
void	parsing_free_test_map(t_game *game, t_map *test_map, int success);

// parsing_textures.c

void	parsing_set_texture(t_game *game, char **buffer, char *identifier,
			t_fds fd);
void	parsing_textures(t_game *game, t_fds fd);
void	allocate_data_texture(t_game *game, t_texture *face, char *texture_path,
			t_fds fd);
void	parsing_free_error_textures(t_game *game, t_fds fd,
			char *buffer);

// parsing_utils.c

char	*trimed_gnl(t_fds fd, const char *to_trim);
char	*parsing_add_count(t_count_id *nb_identifier, char *identifier);
int		count_id(t_count_id nb_identifier);
char	*parsing_found_identifier(char *buffer, t_count_id *nb_textures);
int		ft_strcmp(char *s1, char *s2);

// parsing_init.c

void	parsing_init(t_game *game);
void	parsing_init_textures(t_game *game);
void	parsing_init_test_map(t_game *game, t_map *test_map);

// parsing.c

void	parsing_file_name_and_format(t_game *game, char *filename);
void	parsing(t_game *game, char *filename);

#endif
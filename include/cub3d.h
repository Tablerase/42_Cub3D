/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:25:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/03/13 17:27:37 by rcutte           ###   ########.fr       */
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

/* ################################ DEFINES ################################ */

// Screen size
# define WIDTH 1270
# define HEIGHT 720

// Limits

// Protection against division by zero
// # define INFINITY 1e30 (present in math.h)

/* ############################## STRUCTURES ############################### */

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
	int		pos_x;
	int		pos_y;
	double	dir_x;
	double	dir_y;
	int		fov;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

/**
 * @brief Enum for the tiles
 * @param EMPTY The empty tile
 * @param WALL The wall tile
*/
enum e_tile
{
	EMPTY,
	WALL,
	DOOR
};

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
 * @brief Enum for the side
 * @param EW The east/west side
 * @param NS The north/south side
*/
enum e_side
{
	EW,
	NS
};

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
 * @param line_height The height of the line to draw
 * @param draw_start The start of the line to draw
 * @param draw_end The end of the line to draw
 * @param color The color of the line to draw
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

	int					line_height;
	int					draw_start;
	int					draw_end;
	int					color;
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
	int			mouse_x;
	int			mouse_y;
	t_map		map;
	t_player	player;
}	t_game;

/* ############################## PROTOTYPES ############################### */

// Setup

bool	ft_setup_map(t_game *game);
bool	ft_setup_player(t_game *game);
bool	ft_setup(t_game *game);

// Graphics

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

int		ft_exit(t_game *game);

#endif
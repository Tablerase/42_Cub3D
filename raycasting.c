/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:25:12 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/11 18:09:36 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		exit(1);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "./cub3d");
	if (mlx->mlx_win == NULL)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->mlx_img = malloc(sizeof(t_img));
	if (mlx->mlx_img == NULL)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->mlx_img->img = mlx_new_image(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mlx->mlx_img->img == NULL)
	{
		free(mlx->mlx_img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->mlx_img->addr = mlx_get_data_addr(mlx->mlx_img->img, &mlx->mlx_img->bits_per_pixel,
			&mlx->mlx_img->line_height, &mlx->mlx_img->endian);
	if (mlx->mlx_img->addr == NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img->img);
		free(mlx->mlx_img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->player = malloc(sizeof(t_player));
	if (mlx->player == NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img->img);
		free(mlx->mlx_img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->player->posX = 22;
	mlx->player->posY = 12;
	mlx->player->dirX = -1; // initial direction vector
	mlx->player->dirY = 0;
	mlx->player->planeX = 0;
	mlx->player->planeY = 0.66;
	mlx->raycast = malloc(sizeof(t_raycast));
	if (mlx->raycast == NULL)
	{
		free(mlx->player);
		mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img->img);
		free(mlx->mlx_img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->keys = malloc(sizeof(t_keys));
	if (mlx->keys == NULL)
	{
		free(mlx->raycast);
		free(mlx->player);
		mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img->img);
		free(mlx->mlx_img);
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(1);
	}
	mlx->keys->key_a = 0;
	mlx->keys->key_s = 0;
	mlx->keys->key_w = 0;
	mlx->keys->key_d = 0;
	mlx->keys->key_left = 0;
	mlx->keys->key_right = 0;
}

void	end(t_mlx *mlx)
{
	free(mlx->keys);
	free(mlx->raycast);
	free(mlx->player);
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img->img);
	free(mlx->mlx_img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

void	moves(t_mlx *mlx)
{
	double	rotSpeed = 0.02; // should adjust of size screen changes
	double	moveSpeed = 0.05; // should adjust of size screen changes

	if (mlx->keys->key_w == 1)
	{
		if (map[(int)(mlx->player->posX + mlx->player->dirX * moveSpeed)][(int)mlx->player->posY] == 0)
			mlx->player->posX += mlx->player->dirX * moveSpeed;
		if (map[(int)(mlx->player->posX)][(int)(mlx->player->posY + mlx->player->dirY * moveSpeed)] == 0)
			mlx->player->posY += mlx->player->dirY * moveSpeed;
	}
	if (mlx->keys->key_s == 1)
	{
		if (map[(int)(mlx->player->posX - mlx->player->dirX * moveSpeed)][(int)mlx->player->posY] == 0)
			mlx->player->posX -= mlx->player->dirX * moveSpeed;
		if (map[(int)(mlx->player->posX)][(int)(mlx->player->posY - mlx->player->dirY * moveSpeed)] == 0)
			mlx->player->posY -= mlx->player->dirY * moveSpeed;
	}
	if (mlx->keys->key_a == 1)
	{
		if (map[(int)(mlx->player->posX)][(int)(mlx->player->posY - moveSpeed)] == 0)
			mlx->player->posY -=  moveSpeed * mlx->player->dirY;
	}
	if (mlx->keys->key_d == 1)
	{
		if (map[(int)(mlx->player->posX)][(int)(mlx->player->posY + (mlx->player->dirY) * moveSpeed)] == 0)
			mlx->player->posY += (mlx->player->dirY) * moveSpeed * 10;
	}
	if (mlx->keys->key_right == 1)
	{
		double	oldDirX = mlx->player->dirX;
		double	oldPlaneX = mlx->player->planeX;
		mlx->player->dirX = mlx->player->dirX * cos(rotSpeed) - mlx->player->dirY * sin(-rotSpeed);
		mlx->player->dirY = oldDirX * sin(-rotSpeed) + mlx->player->dirY * cos(rotSpeed);
		mlx->player->planeX = mlx->player->planeX * cos(rotSpeed) - mlx->player->planeY * sin(-rotSpeed);
		mlx->player->planeY = oldPlaneX * sin(-rotSpeed) + mlx->player->planeY * cos(rotSpeed);
	}
	if (mlx->keys->key_left == 1)
	{
		double	oldDirX = mlx->player->dirX;
		double	oldPlaneX = mlx->player->planeX;
		mlx->player->dirX = mlx->player->dirX * cos(rotSpeed) - mlx->player->dirY * sin(rotSpeed);
		mlx->player->dirY = oldDirX * sin(rotSpeed) + mlx->player->dirY * cos(rotSpeed);
		mlx->player->planeX = mlx->player->planeX * cos(rotSpeed) - mlx->player->planeY * sin(rotSpeed);
		mlx->player->planeY = oldPlaneX * sin(rotSpeed) + mlx->player->planeY * cos(rotSpeed);
	}
}

int	raycaster(t_mlx *mlx)
{
	int		x;
	int		hit; // was there a wall hit?
	int		side; // was a NS or a EW wall hit?
	double	cameraX;

	x = 0;
	moves(mlx);
	while (x < SCREEN_WIDTH)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
		mlx->raycast->rayDirX = mlx->player->dirX + mlx->player->planeX * cameraX;
		mlx->raycast->rayDirY = mlx->player->dirY + mlx->player->planeY * cameraX;
		
		mlx->raycast->mapX = (int)mlx->player->posX;
		mlx->raycast->mapY = (int)mlx->player->posY;

		mlx->raycast->deltaDistX = (mlx->raycast->rayDirX == 0) ? 1e30 : fabs(1 / mlx->raycast->rayDirX);
		mlx->raycast->deltaDistY = (mlx->raycast->rayDirY == 0) ? 1e30 : fabs(1 / mlx->raycast->rayDirY);
		
		hit = 0;

		if (mlx->raycast->rayDirX < 0) // ray <-
		{
			mlx->raycast->stepX = -1;
			mlx->raycast->sideDistX = (mlx->player->posX - (double)mlx->raycast->mapX) * mlx->raycast->deltaDistX;
		}
		else // ray -> or |
		{
			mlx->raycast->stepX = 1;
			mlx->raycast->sideDistX = ((double)mlx->raycast->mapX + 1.0 - mlx->player->posX) * mlx->raycast->deltaDistX;
		}
		
		if (mlx->raycast->rayDirY < 0) // ray <-
		{
			mlx->raycast->stepY = -1;
			mlx->raycast->sideDistY = (mlx->player->posY - (double)mlx->raycast->mapY) * mlx->raycast->deltaDistY;
		}
		else // ray -> or |
		{
			mlx->raycast->stepY = 1;
			mlx->raycast->sideDistY = ((double)mlx->raycast->mapY + 1.0 - mlx->player->posY) * mlx->raycast->deltaDistY;
		}
		
		while (hit == 0)
		{
			if (mlx->raycast->sideDistX < mlx->raycast->sideDistY)
			{
				mlx->raycast->sideDistX += mlx->raycast->deltaDistX;
				mlx->raycast->mapX += mlx->raycast->stepX;
				side = 0;
			}
			else
			{
				mlx->raycast->sideDistY += mlx->raycast->deltaDistY;
				mlx->raycast->mapY += mlx->raycast->stepY;
				side = 1;
			}
			if (map[mlx->raycast->mapX][mlx->raycast->mapY] > 0)
				hit = 1;
		}

		if (side == 0)
		{
			mlx->raycast->perpWallDist = (mlx->raycast->sideDistX - mlx->raycast->deltaDistX);
		}
		else
			mlx->raycast->perpWallDist = (mlx->raycast->sideDistY - mlx->raycast->deltaDistY);
		
		int	lineHeight = (int)(SCREEN_HEIGHT / mlx->raycast->perpWallDist);
		int	drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		int	color;
		if (map[mlx->raycast->mapX][mlx->raycast->mapY] == 1)
			color = 0xD51B21;
		if (map[mlx->raycast->mapX][mlx->raycast->mapY] == 2)
			color = 0x52c220;
		if (map[mlx->raycast->mapX][mlx->raycast->mapY] == 3)
			color = 0x2052c2;
		if (map[mlx->raycast->mapX][mlx->raycast->mapY] == 4)
			color = 0xFFFFFF;
		else
			color = 0xf0f96d;
		
		if (side == 1)
		{
			color = color / 2;
		}
		
		int y = 0;
		while (y < drawStart)
		{
			char *dest = mlx->mlx_img->addr + (y * mlx->mlx_img->line_height + x * (mlx->mlx_img->bits_per_pixel / 8));
			*(unsigned int *)dest = 0x009990;
			y++;
		}
		while (y < drawEnd)
		{
			char *dest = mlx->mlx_img->addr + (y * mlx->mlx_img->line_height + x * (mlx->mlx_img->bits_per_pixel / 8));
			*(unsigned int *)dest = color;
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			char *dest = mlx->mlx_img->addr + (y * mlx->mlx_img->line_height + x * (mlx->mlx_img->bits_per_pixel / 8));
			*(unsigned int *)dest = 0x006800;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->mlx_img->img, 0, 0);
	return (1);
}

int	on_click(int keycode, t_mlx *mlx)
{
	if (keycode == XK_a)
		mlx->keys->key_a = 1;
	if (keycode == XK_s)
		mlx->keys->key_s = 1;
	if (keycode == XK_w)
		mlx->keys->key_w = 1;
	if (keycode == XK_d)
		mlx->keys->key_d = 1;
	if (keycode == XK_Left)
		mlx->keys->key_left = 1;
	if (keycode == XK_Right)
		mlx->keys->key_right = 1;
	if (keycode == XK_Escape)
		end(mlx);
	return (1);
}

int	on_release(int keycode, t_mlx *mlx)
{
	if (keycode == XK_a)
		mlx->keys->key_a = 0;
	if (keycode == XK_s)
		mlx->keys->key_s = 0;
	if (keycode == XK_w)
		mlx->keys->key_w = 0;
	if (keycode == XK_d)
		mlx->keys->key_d = 0;
	if (keycode == XK_Left)
		mlx->keys->key_left = 0;
	if (keycode == XK_Right)
		mlx->keys->key_right = 0;
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	init(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, &raycaster, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, &on_click, &mlx);
	mlx_hook(mlx.mlx_win, KeyRelease, KeyReleaseMask, &on_release, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
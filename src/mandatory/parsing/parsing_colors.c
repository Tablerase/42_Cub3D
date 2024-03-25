/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:41:54 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/25 11:53:14 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	parsing_set_color(
			t_game *game,
			char *identifier,
			char *color_rgb,
			t_fds fd)
{
	parsing_color_format(game, color_rgb, fd);
	if (ft_strcmp("F", identifier) == 0)
		parsing_color_range(game, &(game->textures.floor_color), color_rgb,
			fd);
	else
		parsing_color_range(game, &(game->textures.ceiling_color), color_rgb,
			fd);
}

void	parsing_char_color(t_game *game, char *color_rgb, t_fds fd)
{
	int	i;
	int	comas;

	i = 0;
	comas = 0;
	while (color_rgb[i] != '\0')
	{
		if (!(ft_isdigit(color_rgb[i])
				|| color_rgb[i] == ' ' || color_rgb[i] == ','))
		{
			parsing_free_color(game, color_rgb, fd, "Invalid color format\n");
		}
		if (color_rgb[i] == ',')
			comas++;
		i++;
	}
	if (comas != 2)
		parsing_free_color(game, color_rgb, fd, "Invalid color format\n");
}

void	parsing_color_format(t_game *game, char *color_rgb, t_fds fd)
{
	int	i;
	int	nb_digits;

	parsing_char_color(game, color_rgb, fd);
	i = 0;
	nb_digits = 0;
	while (color_rgb[i] != '\0')
	{
		if (color_rgb[i] == ' ' && nb_digits != 0
			&& ft_isdigit(color_rgb[i + 1]))
			break ;
		if ((color_rgb[i] == ',' && nb_digits == 0) || nb_digits > 3)
			break ;
		else if (color_rgb[i] == ',')
			nb_digits = 0;
		else if (ft_isdigit(color_rgb[i]))
			nb_digits = parsing_count_digits(&color_rgb[i], &i);
		i++;
	}
	if (color_rgb[i] != '\0' || nb_digits > 3
		|| (color_rgb[i] == '\0' && ft_isdigit(color_rgb[i - 1]) == 0))
	{
		parsing_free_color(game, color_rgb, fd, "Invalid color format\n");
	}
}

void	parsing_color_range(
			t_game *game,
			int *texture_color,
			char *color_rgb,
			t_fds fd)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (color_rgb[i] != '\0' && color_rgb[i] != ',' && color_rgb[i] != ' ')
		r = r * 10 + color_rgb[i++] - '0';
	while (color_rgb[i] == ',' || color_rgb[i] == ' ')
		i++;
	while (color_rgb[i] != '\0' && color_rgb[i] != ',' && color_rgb[i] != ' ')
		g = g * 10 + color_rgb[i++] - '0';
	while (color_rgb[i] == ',' || color_rgb[i] == ' ')
		i++;
	while (color_rgb[i] != '\0' && color_rgb[i] != ',' && color_rgb[i] != ' ')
		b = b * 10 + color_rgb[i++] - '0';
	if (r > 255 || g > 255 || b > 255)
	{
		parsing_free_color(game, color_rgb, fd, "Invalid color format\n");
	}
	*texture_color = (r << 16) | (g << 8) | b;
}

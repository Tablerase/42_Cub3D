/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:06:05 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/21 18:16:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_count_id
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_count_id;

typedef struct s_fds
{
	int	fd1;
	int	fd2;
}	t_fds;

typedef struct s_minimap
{
	int	start_i;
	int	end_i;
	int	start_j;
	int	end_j;
	int	pixel_x;
	int	pixel_y;
	int	color;
}	t_minimap;

#endif
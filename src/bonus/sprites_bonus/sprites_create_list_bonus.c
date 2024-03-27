/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_create_list_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:21:36 by abourgeo          #+#    #+#             */
/*   Updated: 2024/03/27 12:44:21 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	sprite_init_tab(char **tab)
{
	tab[0] = "assets/textures/fire/white1.xpm";
	tab[1] = "assets/textures/fire/white2.xpm";
	tab[2] = "assets/textures/fire/white3.xpm";
	tab[3] = "assets/textures/fire/white4.xpm";
	tab[4] = "assets/textures/fire/white5.xpm";
	tab[5] = "assets/textures/fire/white6.xpm";
	tab[6] = "assets/textures/fire/white7.xpm";
	tab[7] = "assets/textures/fire/white8.xpm";
	tab[8] = NULL;
}

t_sprite_list	*sprite_new_node(void *mlx_ptr, char *path)
{
	t_sprite_list	*new_node;

	new_node = malloc(sizeof(t_sprite_list));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->img.type = TEX_SPRITE;
	new_node->img.path = path;
	new_node->img.img.img = mlx_xpm_file_to_image(mlx_ptr, path,
			&new_node->img.width, &new_node->img.height);
	if (new_node->img.img.img == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->img.img.addr = mlx_get_data_addr(new_node->img.img.img,
			&new_node->img.img.bpp, &new_node->img.img.line_len,
			&new_node->img.img.endian);
	if (new_node->img.img.addr == NULL)
	{
		mlx_destroy_image(mlx_ptr, new_node->img.img.img);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	sprite_create_list(t_game *game, char **tab)
{
	int				i;
	t_sprite_list	*tmp;

	i = 1;
	tmp = game->sprite.img;
	while (tab[i] != NULL)
	{
		tmp->next = sprite_new_node(game->mlx.mlx, tab[i]);
		if (tmp->next == NULL)
			parsing_exit_error(game, "Allocation failed\n");
		tmp->next->is_on_screen = false;
		tmp->next->is_tail = false;
		tmp = tmp->next;
		i++;
	}
	tmp->next = game->sprite.img;
	tmp->is_tail = true;
}

void	parsing_allocate_sprite(t_game *game)
{
	char	*tab[9];

	sprite_init_tab(tab);
	game->sprite.img = sprite_new_node(game->mlx.mlx, tab[0]);
	if (game->sprite.img == NULL)
		parsing_exit_error(game, "Allocation failed\n");
	game->sprite.img->is_on_screen = true;
	game->sprite.img->is_tail = false;
	game->sprite.img->next = game->sprite.img;
	sprite_create_list(game, tab);
	game->sprite.img->on_screen = game->sprite.img;
}

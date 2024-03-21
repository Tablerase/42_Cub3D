# include "mlx/mlx.h"
# include "libft/Includes/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_sprite
{
	int				last;
	t_img			img;
	struct s_sprite	*next;
}	t_sprite;

typedef struct s_data
{
	t_sprite	**head;
	t_sprite	*on_screen;
	void		*mlx_ptr;
	void		*mlx_win;
	int			time;
}	t_data;

t_sprite	*sprite_new_node(void *mlx_ptr, char *path);
void		sprite_init_tab(char **tab);
void		sprite_create_list(t_data *data, char **tab);
void		sprite_new_sprite(t_data *data);
void		sprite_free_list(t_data *data);
int			sprite_exit_error(t_data *data);
int			display(t_data *data);

t_sprite	*sprite_new_node(void *mlx_ptr, char *path)
{
	int			width;
	int			height;
	t_sprite	*new_node;

	new_node = malloc(sizeof(t_sprite));
	if (new_node == NULL)
		return (new_node);
	new_node->next = NULL;
	new_node->img.img = mlx_xpm_file_to_image(mlx_ptr, path, &width, &height);
	if (new_node->img.img == NULL)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	sprite_init_tab(char **tab)
{
	tab[0] = "assets/textures/WaterFall/WaterFallWall1.xpm";
	tab[1] = "assets/textures/WaterFall/WaterFallWall2.xpm";
	tab[2] = "assets/textures/WaterFall/WaterFallWall3.xpm";
	tab[3] = "assets/textures/WaterFall/WaterFallWall4.xpm";
	tab[4] = "assets/textures/WaterFall/WaterFallWall5.xpm";
	tab[5] = "assets/textures/WaterFall/WaterFallWall6.xpm";
	tab[6] = NULL;
}

void	sprite_create_list(t_data *data, char **tab)
{
	int	i;
	t_sprite	*tmp;

	i = 1;
	tmp = *(data->head);
	while (tab[i] != NULL)
	{
		tmp->next = sprite_new_node(data->mlx_ptr, tab[i]);
		if (tmp->next == NULL)
			sprite_exit_error(data);
		tmp->last = 0;
		tmp = tmp->next;
		i++;
	}
	tmp->next = *(data->head);
	tmp->last = 1;
}

void	sprite_new_sprite(t_data *data)
{
	char	*tab[8];

	sprite_init_tab(tab);
	data->head = malloc(sizeof(t_sprite *));
	if (data->head == NULL)
		sprite_exit_error(data);
	*(data->head) = sprite_new_node(data->mlx_ptr, tab[0]);
	if (*(data->head) == NULL)
		sprite_exit_error(data);
	(*(data->head))->last = 0;
	(*(data->head))->next = *(data->head);
	sprite_create_list(data, tab);
	data->on_screen = (*(data->head))->next;
}

void	sprite_free_list(t_data *data)
{
	int			end;
	t_sprite	*tmp;
	t_sprite	*to_free;

	if (data->head == NULL)
		return ;
	end = 0;
	tmp = *(data->head);
	while (tmp != NULL && end == 0)
	{
		to_free = tmp;
		if (to_free->last == 1)
			end = 1;
		tmp = tmp->next;
		mlx_destroy_image(data->mlx_ptr, to_free->img.img);
		free(to_free);
	}
	free(data->head);
}

int	sprite_exit_error(t_data *data)
{
	if (data == NULL)
		exit(1);
	sprite_free_list(data);
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(1);
}

int	display(t_data *data)
{
	data->time++;
	if (data->time > 10000)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->on_screen->img.img, 0, 0);
		if (data->on_screen->next != NULL)
			data->on_screen = data->on_screen->next;
		data->time = 0;
	}
	return (1);
}

int	main(void)
{
	t_data	data;

	data.mlx_win = NULL;
	data.time = 0;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	sprite_new_sprite(&data);
	data.mlx_win = mlx_new_window(data.mlx_ptr, 1024, 600, "sprite");
	if (data.mlx_win == NULL)
		sprite_exit_error(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, (*(data.head))->img.img, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &display, &data);
	mlx_hook(data.mlx_win, 17, 0, &sprite_exit_error, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

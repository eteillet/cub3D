/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 09:17:20 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 09:33:40 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int				destroy(t_all *all)
{
	free_struct(all);
	exit(0);
	return (0);
}

static int		game_loop(t_all *all)
{
	mlx_clear_window(all->window->mlx_ptr, all->window->win_ptr);
	key_move(all);
	raycasting(all, all->player, all->window, all->ray);
	if (all->window->res_x >= 600 && all->window->res_y >= 500)
	{
		hud(all->window);
		minimap(all);
	}
	return (0);
}

static void		init_mlx(t_all *all)
{
	all->window->mlx_ptr = mlx_init();
	adjust_resolution(all);
	all->window->win_ptr = mlx_new_window(all->window->mlx_ptr,
		all->window->res_x, all->window->res_y, "Cub3D");
	get_texture(all);
	all->image->img_ptr = mlx_new_image(all->window->mlx_ptr,
			all->window->res_x, all->window->res_y);
	all->image->data = mlx_get_data_addr(all->image->img_ptr,
			&(all->image->bpp), &(all->image->size_line),
			&(all->image->endian));
	if (all->window->mlx_ptr == NULL || all->window->win_ptr == NULL ||
			all->image->img_ptr == NULL || all->image->data == NULL)
		clean_exit("Problem initializing the mlx\n", all);
}

static void		treatment(t_all *all, char *argv, int save)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	all->save = save;
	if (read_cubfile(all, argv, ret, line))
	{
		init_mlx(all);
		if (all->save == 1)
			raycasting(all, all->player, all->window, all->ray);
		mlx_hook(all->window->win_ptr, KEY_PRESS, 1L << 0, key_press, all);
		mlx_hook(all->window->win_ptr, KEY_RELEASE, 1L << 1, key_release, all);
		mlx_hook(all->window->win_ptr, KEY_DESTROY, 1L << 17, destroy, all);
		mlx_hook(all->window->win_ptr, CROSS, 1L << 17, destroy, all);
		mlx_loop_hook(all->window->mlx_ptr, game_loop, all);
		mlx_loop(all->window->mlx_ptr);
	}
	clean_exit(NULL, all);
}

int				main(int argc, char **argv)
{
	int		save;
	t_all	*all;

	save = -1;
	if (argc == 3 && check_cub_name(argv[1]) && check_save_name(argv[2]))
		save = 1;
	else if (argc == 2 && check_cub_name(argv[1]))
		save = 0;
	if (save == -1)
	{
		ft_putstr_fd("Error\nInvalid arguments\n", 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		all = init_all_struct();
		if (all == NULL)
		{
			ft_putstr_fd("Error\nImpossible to create the game structure\n", 1);
			exit(EXIT_FAILURE);
		}
		treatment(all, argv[1], save);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 09:35:48 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:18:01 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void		free_texture(t_texture *texture, t_window *window)
{
	if (texture->path)
		free(texture->path);
	if (texture->img_ptr)
		mlx_destroy_image(window->mlx_ptr, texture->img_ptr);
	free(texture);
}

static void		free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->tmp_map)
		free(map->tmp_map);
	if (map->map)
	{
		while (i < map->height)
			free(map->map[i++]);
		free(map->map);
	}
	free(map);
}

static void		free_mlx(t_all *all)
{
	if (all->image->img_ptr)
		mlx_destroy_image(all->window->mlx_ptr, all->image->img_ptr);
	free(all->image);
	if (all->window->win_ptr)
		mlx_destroy_window(all->window->mlx_ptr, all->window->win_ptr);
	if (all->window->mlx_ptr)
		mlx_destroy_display(all->window->mlx_ptr);
	if (all->window->mlx_ptr)
		free(all->window->mlx_ptr);
	free(all->window);
}

void			free_struct(t_all *all)
{
	free(all->color);
	free(all->key);
	free(all->player);
	free_texture(all->texture_no, all->window);
	free_texture(all->texture_so, all->window);
	free_texture(all->texture_we, all->window);
	free_texture(all->texture_ea, all->window);
	free_texture(all->sprite, all->window);
	free_map(all->map);
	free_mlx(all);
	free(all);
}

void			clean_exit(char *error, t_all *all)
{
	if (error)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		if (all->error_res != 0)
			ft_putstr_fd("Problem with parsing resolution\n", STDERR_FILENO);
		else if (all->error_color != 0)
			ft_putstr_fd("Problem with parsing color\n", STDERR_FILENO);
		else if (all->error_text_sp != 0)
			ft_putstr_fd("Problem with parsing texture/sprite\n",
				STDERR_FILENO);
		else if (all->error_flag != 0)
			ft_putstr_fd("Flag problem / element missing\n", STDERR_FILENO);
		else if (all->error_wrong_cubline != 0)
			ft_putstr_fd("Problem with cubline(s)\n", STDERR_FILENO);
		else if (all->error_map != 0)
			ft_putstr_fd("Problem with parsing map\n", STDERR_FILENO);
		else
			ft_putstr_fd(error, STDERR_FILENO);
	}
	free_struct(all);
	exit(0);
}

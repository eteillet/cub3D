/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_store_and_sort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:30:26 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 16:32:17 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int					count_sprites(t_map *map, t_all *all)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '2')
				i++;
			x++;
		}
		y++;
	}
	all->nb_sprites = i;
	if (all->nb_sprites == 0)
		return (0);
	return (1);
}

static void			sprites_coordinates(t_all *all, t_map *map)
{
	int		x;
	int		y;
	int		i;

	if (!(all->tab_sp = malloc(sizeof(t_sprite) * all->nb_sprites)))
		clean_exit("Problem to mallocate spritetab\n", all);
	i = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '2')
			{
				all->tab_sp[i].x = x + 0.5;
				all->tab_sp[i].y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void			sprites_dist(t_all *all)
{
	int		i;

	i = -1;
	while (++i < all->nb_sprites)
	{
		all->tab_sp[i].dist = (all->player->pos_x - all->tab_sp[i].x) *
			(all->player->pos_x - all->tab_sp[i].x) +
			(all->player->pos_y - all->tab_sp[i].y) *
			(all->player->pos_y - all->tab_sp[i].y);
	}
}

static void			bubsort_sprites(t_all *all)
{
	int			i;
	int			j;
	t_sprite	swap_sp;

	i = 0;
	j = 0;
	while (i < all->nb_sprites)
	{
		j = 0;
		while (j < (all->nb_sprites - i - 1))
		{
			if (all->tab_sp[j].dist < all->tab_sp[j + 1].dist)
			{
				swap_sp = all->tab_sp[j];
				all->tab_sp[j] = all->tab_sp[j + 1];
				all->tab_sp[j + 1] = swap_sp;
			}
			j++;
		}
		i++;
	}
}

void				treat_sprites(t_all *all, t_ray *ray)
{
	int		i;

	i = 0;
	sprites_coordinates(all, all->map);
	sprites_dist(all);
	bubsort_sprites(all);
	while (i < all->nb_sprites)
	{
		calculate_sprite(all, all->player, i);
		display_sprite(all, ray->z_buffer);
		i++;
	}
	free(all->tab_sp);
}

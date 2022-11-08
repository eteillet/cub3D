/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:21:23 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 17:22:51 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int		check_up(t_all *all, int y, int x)
{
	while (y >= 0)
	{
		if (all->map->map[y][x] == '1')
			return (1);
		if (all->map->map[y][x] == ' ')
			return (2);
		y--;
	}
	return (0);
}

static int		check_down(t_all *all, int y, int x)
{
	while (y < all->map->height)
	{
		if (all->map->map[y][x] == '1')
			return (1);
		if (all->map->map[y][x] == ' ')
			return (2);
		y++;
	}
	return (0);
}

static int		check_left(t_all *all, int y, int x)
{
	while (x >= 0)
	{
		if (all->map->map[y][x] == '1')
			return (1);
		if (all->map->map[y][x] == ' ')
			return (2);
		x--;
	}
	return (0);
}

static int		check_right(t_all *all, int y, int x)
{
	while (x < all->map->width)
	{
		if (all->map->map[y][x] == '1')
			return (1);
		if (all->map->map[y][x] == ' ')
			return (2);
		x++;
	}
	return (0);
}

void			check_surrounded_map(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (y < all->map->height)
	{
		x = 0;
		while (x < all->map->width)
		{
			if (all->map->map[y][x] == '0' || all->map->map[y][x] == '2' ||
			is_in_player_list(all->map->map[y][x]))
			{
				if (!check_up(all, y, x) || !check_down(all, y, x) ||
						!check_left(all, y, x) || !check_right(all, y, x))
					clean_exit("The map has to be surrounded by walls\n", all);
				else if (check_up(all, y, x) == 2 ||
						check_down(all, y, x) == 2 ||
						check_left(all, y, x) == 2 ||
						check_right(all, y, x) == 2)
					clean_exit("Spaces forbidden in map\n", all);
			}
			x++;
		}
		y++;
	}
}

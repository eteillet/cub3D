/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:12:01 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 11:13:21 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void		init_player(t_all *all)
{
	all->player->dir_x = 0;
	all->player->dir_y = 0;
	all->player->plan_x = 0;
	all->player->plan_y = 0;
	if (all->map->dir_player == 'N')
	{
		all->player->dir_y = -1;
		all->player->plan_x = 0.66;
	}
	if (all->map->dir_player == 'S')
	{
		all->player->dir_y = 1;
		all->player->plan_x = -0.66;
	}
	if (all->map->dir_player == 'W')
	{
		all->player->dir_x = -1;
		all->player->plan_y = -0.66;
	}
	if (all->map->dir_player == 'E')
	{
		all->player->dir_x = 1;
		all->player->plan_y = 0.66;
	}
}

static void		is_already_player(t_all *all)
{
	if (all->map->dir_player != -1)
		clean_exit("Too many players in this game\n", all);
}

static void		no_player(t_all *all)
{
	if (all->map->dir_player == -1)
		clean_exit("There is no player in this game\n", all);
}

int				is_in_player_list(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void			get_player(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (y < all->map->height)
	{
		x = 0;
		while (x < all->map->width)
		{
			if (is_in_player_list(all->map->map[y][x]))
			{
				is_already_player(all);
				all->player->pos_x = x;
				all->player->pos_y = y;
				all->map->dir_player = all->map->map[y][x];
				all->map->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	no_player(all);
	init_player(all);
}

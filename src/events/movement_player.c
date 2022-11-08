/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:27:46 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 15:45:39 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void			move_forward(t_map *map, t_player *player)
{
	if (map->map[(int)(player->pos_y)]
			[(int)(player->pos_x + player->dir_x * player->speed)] == '0')
		player->pos_x += player->dir_x * player->speed;
	if (map->map[(int)(player->pos_y + player->dir_y * player->speed)]
			[(int)(player->pos_x)] == '0')
		player->pos_y += player->dir_y * player->speed;
}

void			move_backward(t_map *map, t_player *player)
{
	if (map->map[(int)(player->pos_y)]
			[(int)(player->pos_x - player->dir_x * player->speed)] == '0')
		player->pos_x += -(player->dir_x * player->speed);
	if (map->map[(int)(player->pos_y - player->dir_y * player->speed)]
			[(int)(player->pos_x)] == '0')
		player->pos_y += -(player->dir_y * player->speed);
}

void			move_right(t_map *map, t_player *player)
{
	if (map->map[(int)(player->pos_y)]
			[(int)(player->pos_x + player->plan_x * player->speed)] == '0')
		player->pos_x += player->plan_x * player->speed;
	if (map->map[(int)(player->pos_y + player->plan_y * player->speed)]
			[(int)(player->pos_x)] == '0')
		player->pos_y += player->plan_y * player->speed;
}

void			move_left(t_map *map, t_player *player)
{
	if (map->map[(int)(player->pos_y)]
			[(int)(player->pos_x - player->plan_x * player->speed)] == '0')
		player->pos_x += -(player->plan_x * player->speed);
	if (map->map[(int)(player->pos_y - player->plan_y * player->speed)]
			[(int)(player->pos_x)] == '0')
		player->pos_y += -(player->plan_y * player->speed);
}

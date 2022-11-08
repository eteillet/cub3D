/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:27:03 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 15:27:40 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** when the player rotates, the camera rotates
** (= rotation of direction and plane vector)
** To rotate a vector, multiply it with the rotation matrix
*/

void	rot_left(t_player *player)
{
	double	last_dir_x;
	double	last_plan_x;

	last_dir_x = player->dir_x;
	player->dir_x = cos(-(player->rot_speed)) * player->dir_x -
		sin(-(player->rot_speed)) * player->dir_y;
	player->dir_y = sin(-(player->rot_speed)) * last_dir_x +
		cos(-(player->rot_speed)) * player->dir_y;
	last_plan_x = player->plan_x;
	player->plan_x = cos(-(player->rot_speed)) * player->plan_x -
		sin(-(player->rot_speed)) * player->plan_y;
	player->plan_y = sin(-(player->rot_speed)) * last_plan_x +
		cos(-(player->rot_speed)) * player->plan_y;
}

void	rot_right(t_player *player)
{
	double	last_dir_x;
	double	last_plan_x;

	last_dir_x = player->dir_x;
	player->dir_x = cos(player->rot_speed) * player->dir_x -
		sin(player->rot_speed) * player->dir_y;
	player->dir_y = sin(player->rot_speed) * last_dir_x +
		cos(player->rot_speed) * player->dir_y;
	last_plan_x = player->plan_x;
	player->plan_x = cos(player->rot_speed) * player->plan_x -
		sin(player->rot_speed) * player->plan_y;
	player->plan_y = sin(player->rot_speed) * last_plan_x +
		cos(player->rot_speed) * player->plan_y;
}

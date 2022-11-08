/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:02:49 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 17:04:37 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		key_press(int key, t_all *all)
{
	if (key == KEY_W)
		all->key->w = 1;
	else if (key == KEY_A)
		all->key->a = 1;
	else if (key == KEY_S)
		all->key->s = 1;
	else if (key == KEY_D)
		all->key->d = 1;
	else if (key == KEY_LEFT)
		all->key->left = 1;
	else if (key == KEY_RIGHT)
		all->key->right = 1;
	else if (key == KEY_ESC)
		all->key->esc = 1;
	return (0);
}

int		key_release(int key, t_all *all)
{
	if (key == KEY_W)
		all->key->w = 0;
	else if (key == KEY_A)
		all->key->a = 0;
	else if (key == KEY_S)
		all->key->s = 0;
	else if (key == KEY_D)
		all->key->d = 0;
	else if (key == KEY_LEFT)
		all->key->left = 0;
	else if (key == KEY_RIGHT)
		all->key->right = 0;
	else if (key == KEY_ESC)
		all->key->esc = 0;
	return (0);
}

void	key_move(t_all *all)
{
	if (all->key->w == 1)
		move_forward(all->map, all->player);
	else if (all->key->a == 1)
		move_left(all->map, all->player);
	else if (all->key->s == 1)
		move_backward(all->map, all->player);
	else if (all->key->d == 1)
		move_right(all->map, all->player);
	else if (all->key->left == 1)
		rot_left(all->player);
	else if (all->key->right == 1)
		rot_right(all->player);
	else if (all->key->esc == 1)
		destroy(all);
}

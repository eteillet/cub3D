/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:29:16 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/11 16:30:00 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	hud(t_window *window)
{
	int		color;

	color = 255;
	color = (color << 8) + 255;
	color = (color << 8) + 255;
	mlx_string_put(window->mlx_ptr, window->win_ptr,
			window->res_x / 20, window->res_y / 25, color,
			"Hello gamer, here are the commands :");
	mlx_string_put(window->mlx_ptr, window->win_ptr,
			window->res_x / 12, window->res_y / 13, color,
			"->  Forward : W   Backward : S   Left : A   Right : D");
	mlx_string_put(window->mlx_ptr, window->win_ptr,
			window->res_x / 12, window->res_y / 9, color,
			"->  Rotate left : <    Rotate right : >");
	mlx_string_put(window->mlx_ptr, window->win_ptr,
			window->res_x / 12, window->res_y / 7, color,
			"->  Exit game : ESC");
}

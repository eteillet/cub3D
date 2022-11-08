/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:00:49 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/13 12:02:12 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void		put_pixels(int x, int y, t_window *window, int color)
{
	int		paint_y;
	int		paint_x;
	int		tmp_x;

	paint_y = y + 2;
	paint_x = x + 2;
	tmp_x = x;
	while (y < paint_y)
	{
		x = tmp_x;
		while (x < paint_x)
		{
			mlx_pixel_put(window->mlx_ptr, window->win_ptr,
					x, y, color);
			x++;
		}
		y++;
	}
}

void			minimap(t_all *all)
{
	int		y;
	int		x;
	int		draw_y;
	int		draw_x;

	draw_y = all->window->res_y - all->window->res_y / 4;
	y = 0;
	while (all->map->map[y])
	{
		x = 0;
		draw_x = all->window->res_x / 25;
		while (all->map->map[y][x])
		{
			if (x == (int)all->player->pos_x && y == (int)all->player->pos_y)
				put_pixels(draw_x, draw_y, all->window, 0xFF0000);
			else if (all->map->map[y][x] == '1')
				put_pixels(draw_x, draw_y, all->window, 0xFFE60A);
			else if (all->map->map[y][x] == '0' || all->map->map[y][x] == '2')
				put_pixels(draw_x, draw_y, all->window, 0);
			x++;
			draw_x += 2;
		}
		y++;
		draw_y += 2;
	}
}

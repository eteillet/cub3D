/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:58:06 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 16:26:48 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** sprite_x and sprite_y = translation sprite position to relative a camera
** invdet = useful for matrix multiplication
** loop_display_sprite = check that the color is != 0 so as not to display
** the transparency part of the sprite in black on the image
*/

static void		sprite_width_height(t_all *all, t_window *window)
{
	all->spinfos.height = abs((int)(window->res_y / all->spinfos.transform_y));
	all->spinfos.drawstart_y = -(all->spinfos.height) / 2 + window->res_y / 2;
	if (all->spinfos.drawstart_y < 0)
		all->spinfos.drawstart_y = 0;
	all->spinfos.drawend_y = all->spinfos.height / 2 + window->res_y / 2;
	if (all->spinfos.drawend_y >= window->res_y)
		all->spinfos.drawend_y = window->res_y - 1;
	all->spinfos.width = abs((int)(window->res_y / all->spinfos.transform_y));
	all->spinfos.drawstart_x = -(all->spinfos.width) / 2
		+ all->spinfos.screen_x;
	if (all->spinfos.drawstart_x < 0)
		all->spinfos.drawstart_x = 0;
	all->spinfos.drawend_x = all->spinfos.width / 2 + all->spinfos.screen_x;
	if (all->spinfos.drawend_x >= window->res_x)
		all->spinfos.drawend_x = window->res_x - 1;
}

void			calculate_sprite(t_all *all, t_player *player, int i)
{
	all->spinfos.sprite_x = all->tab_sp[i].x - player->pos_x;
	all->spinfos.sprite_y = all->tab_sp[i].y - player->pos_y;
	all->spinfos.invdet = 1.0 / (player->plan_x * player->dir_y - player->dir_x
			* player->plan_y);
	all->spinfos.transform_x = all->spinfos.invdet * (player->dir_y
			* all->spinfos.sprite_x - player->dir_x * all->spinfos.sprite_y);
	all->spinfos.transform_y = all->spinfos.invdet * (-(player->plan_y)
			* all->spinfos.sprite_x + player->plan_x * all->spinfos.sprite_y);
	all->spinfos.screen_x = (int)((all->window->res_x / 2)
			* (1 + all->spinfos.transform_x / all->spinfos.transform_y));
	sprite_width_height(all, all->window);
}

static void		draw_sprite(t_all *all, int y, int stripe)
{
	int		index;
	int		index_sprite;

	index = y * all->image->size_line + stripe * all->image->bpp / 8;
	index_sprite = all->spinfos.tex_y * all->sprite->size_line
		+ all->spinfos.tex_x * all->sprite->bpp / 8;
	all->image->data[index] = all->sprite->data[index_sprite];
	all->image->data[index + 1] = all->sprite->data[index_sprite + 1];
	all->image->data[index + 2] = all->sprite->data[index_sprite + 2];
}

static void		loop_display_sprite(int stripe, int y, t_all *all)
{
	int	d;
	int	index;

	d = y * all->sprite->size_line - all->window->res_y * all->sprite->size_line
		/ 2 + all->spinfos.height * all->sprite->size_line / 2;
	all->spinfos.tex_y = ((d * all->sprite->height) / all->spinfos.height)
		/ all->sprite->size_line;
	index = all->spinfos.tex_y * all->sprite->size_line + all->spinfos.tex_x
		* all->sprite->bpp / 8;
	if ((all->sprite->data[index] + all->sprite->data[index + 1]
		+ all->sprite->data[index + 2]) != 0)
		draw_sprite(all, y, stripe);
}

void			display_sprite(t_all *all, double *buf)
{
	int		stripe;
	int		y;

	stripe = all->spinfos.drawstart_x;
	while (stripe < all->spinfos.drawend_x)
	{
		all->spinfos.tex_x = (int)(256 * (stripe - (-(all->spinfos.width) / 2
						+ all->spinfos.screen_x)) * all->sprite->width
				/ all->spinfos.width) / 256;
		if (all->spinfos.transform_y > 0 && stripe > 0 && stripe
				< all->window->res_x && all->spinfos.transform_y < buf[stripe])
		{
			y = all->spinfos.drawstart_y;
			while (y < all->spinfos.drawend_y)
			{
				loop_display_sprite(stripe, y, all);
				y++;
			}
		}
		stripe++;
	}
}

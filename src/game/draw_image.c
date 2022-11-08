/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:21:50 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 15:24:21 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** draw_vertical_line = define start (top) and end (bottom) of the texture to
** draw and coordinates on this texture (text_x and text_y)
**
** my_pixel_put = as size_line differs from the window width, we have to
** calculate the memory offset to know where to write
*/

static void		my_pixel_put(t_texture *image, int x, int y, int color)
{
	unsigned char	*s;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				index;

	s = (unsigned char *)&color;
	r = s[0];
	g = s[1];
	b = s[2];
	index = y * image->size_line + x * image->bpp / 8;
	image->data[index++] = r;
	image->data[index++] = g;
	image->data[index] = b;
}

static void		draw_color(t_all *all, t_ray *ray)
{
	int		y;

	y = 0;
	while (y < ray->draw_start)
		my_pixel_put(all->image, ray->x, y++, all->color->ceiling);
	y = ray->draw_end + 1;
	while (y < all->window->res_y)
		my_pixel_put(all->image, ray->x, y++, all->color->floor);
}

t_texture		*dispatch_sides(t_texture *texture, int side, t_all *all)
{
	if (side == 0)
		texture = all->texture_we;
	else if (side == 1)
		texture = all->texture_ea;
	else if (side == 2)
		texture = all->texture_no;
	else if (side == 3)
		texture = all->texture_so;
	return (texture);
}

void			draw_vertical_line(t_all *all, t_window *window, t_ray *ray)
{
	t_texture	*texture;

	ray->draw_start = -ray->line_height / 2 + window->res_y / 2;
	ray->draw_end = window->res_y - ray->draw_start;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= window->res_y)
		ray->draw_end = window->res_y - 1;
	texture = NULL;
	texture = dispatch_sides(texture, ray->side, all);
	ray->text_x = (int)(ray->wall_x * (double)texture->width);
	if (((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0) ||
		((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0))
		ray->text_x = texture->width - ray->text_x - 1;
	draw_texture(all, texture, ray);
	draw_color(all, ray);
}

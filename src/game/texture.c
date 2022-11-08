/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:00:44 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 17:01:07 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Between draw_start and draw_and, we display the texture.
** As size_line differs from the window width, we have to
** calculate the memory offset to know where to write
*/

void			draw_texture(t_all *all, t_texture *texture, t_ray *ray)
{
	int	d;
	int index;
	int index_text;

	ray->y = ray->draw_start;
	while (ray->y <= ray->draw_end)
	{
		d = ray->y * texture->size_line - all->window->res_y
			* texture->size_line / 2 + ray->line_height *
			texture->size_line / 2;
		ray->text_y = ((d * texture->height) / ray->line_height)
			/ texture->size_line;
		index = ray->y * all->image->size_line
			+ ray->x * (all->image->bpp / 8);
		index_text = ray->text_y * texture->size_line
			+ ray->text_x * (texture->bpp / 8);
		all->image->data[index] = texture->data[index_text];
		all->image->data[index + 1] = texture->data[index_text + 1];
		all->image->data[index + 2] = texture->data[index_text + 2];
		ray->y++;
	}
}

static void		init_texture(t_all *all, t_texture *texture)
{
	texture->img_ptr = mlx_xpm_file_to_image(all->window->mlx_ptr,
					texture->path, &texture->width, &texture->height);
	if (texture->img_ptr == NULL)
		clean_exit("Can't load the texture\n", all);
	texture->data = mlx_get_data_addr(texture->img_ptr, &(texture->bpp),
			&(texture->size_line), &(texture->endian));
	if (texture->data == NULL)
		clean_exit("Can't load the texture\n", all);
}

void			get_texture(t_all *all)
{
	init_texture(all, all->texture_no);
	init_texture(all, all->texture_so);
	init_texture(all, all->texture_we);
	init_texture(all, all->texture_ea);
	if (all->sprite->path)
		init_texture(all, all->sprite);
}

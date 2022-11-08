/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:28:04 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:29:50 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_player		*init_struct_player(void)
{
	t_player	*player;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (NULL);
	player->pos_x = 0.5;
	player->pos_y = 0.5;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plan_x = 0.;
	player->plan_y = 0.;
	player->dir = '0';
	player->speed = 0.1;
	player->rot_speed = 0.025;
	return (player);
}

t_texture		*init_struct_texture(void)
{
	t_texture	*texture;

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	texture->path = NULL;
	texture->img_ptr = NULL;
	texture->data = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->size_line = 0;
	texture->endian = 0;
	return (texture);
}

t_color			*init_struct_color(void)
{
	t_color		*color;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	color->r = 0;
	color->g = 0;
	color->b = 0;
	color->floor = -1;
	color->ceiling = -1;
	return (color);
}

t_map			*init_struct_map(void)
{
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->tmp_map = NULL;
	map->map = NULL;
	map->map_init = 0;
	map->nb_empty_lines = 0;
	map->emptyline = 0;
	map->width = 0;
	map->height = 0;
	map->dir_player = -1;
	return (map);
}

t_all			*init_all_struct(void)
{
	t_all		*all;

	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (NULL);
	if (!(all->texture_no = init_struct_texture()) ||
			!(all->texture_so = init_struct_texture()) ||
			!(all->texture_we = init_struct_texture()) ||
			!(all->texture_ea = init_struct_texture()) ||
			!(all->sprite = init_struct_texture()) ||
			!(all->color = init_struct_color()) ||
			!(all->map = init_struct_map()) ||
			!(all->image = init_struct_texture()) ||
			!(all->key = init_struct_key()) ||
			!(all->window = init_struct_window()) ||
			!(all->player = init_struct_player()))
		return (NULL);
	return (all);
}

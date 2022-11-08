/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:29:55 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:32:01 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_key		*init_struct_key(void)
{
	t_key	*key;

	if (!(key = (t_key *)malloc(sizeof(t_key))))
		return (NULL);
	key->left = 0;
	key->right = 0;
	key->up = 0;
	key->down = 0;
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->esc = 0;
	return (key);
}

t_window	*init_struct_window(void)
{
	t_window	*window;

	if (!(window = (t_window *)malloc(sizeof(t_window))))
		return (NULL);
	window->res_x = -1;
	window->res_y = -1;
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	return (window);
}

void		init_error_types(t_all *all)
{
	all->error_wrong_cubline = 0;
	all->error_flag = 0;
	all->error_res = 0;
	all->error_color = 0;
	all->error_text_sp = 0;
	all->error_map = 0;
}

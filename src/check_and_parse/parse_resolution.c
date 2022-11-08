/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:15:34 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 11:15:57 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** resolution between 200/100 (arbitrary) and res_x/res_y
*/

static void		adjust_small_resolution(t_all *all)
{
	if (all->window->res_x < 200)
		all->window->res_x = 200;
	if (all->window->res_y < 100)
		all->window->res_y = 100;
}

void			adjust_resolution(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (all->window->res_x == 0 || all->window->res_y == 0)
		clean_exit("0 isn't a valid resolution\n", all);
	if (all->save == 0)
	{
		mlx_get_screen_size(all->window->mlx_ptr, &x, &y);
		if (x <= all->window->res_x)
			all->window->res_x = x - 1;
		if (y <= all->window->res_y)
			all->window->res_y = y - 1;
	}
	else if (all->save == 1)
	{
		if (all->window->res_x > 10000)
			all->window->res_x = 10000;
		if (all->window->res_y > 10000)
			all->window->res_y = 10000;
	}
	adjust_small_resolution(all);
}

static void		init_res(t_all *all)
{
	all->window->res_x = 0;
	all->window->res_y = 0;
}

void			parse_resolution(t_all *all, char *line)
{
	char	**split;

	if (all->window->res_x != -1 || all->window->res_y != -1)
		all->error_res = 1;
	else
		init_res(all);
	split = ft_split_set(line, " \t");
	if (count_split(split) == 3)
	{
		all->window->res_x = ft_atoi(split[1]);
		all->window->res_y = ft_atoi(split[2]);
	}
	else
		all->error_res = 1;
	if (all->window->res_x < 0 || all->window->res_y < 0)
		all->error_res = 1;
	free_split(split);
}

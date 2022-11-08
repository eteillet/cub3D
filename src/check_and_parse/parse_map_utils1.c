/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:24:34 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 17:39:47 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	get_map_width(t_all *all)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (all->map->tmp_map[i])
	{
		if (all->map->tmp_map[i] == '\n')
		{
			if (len > all->map->width)
				all->map->width = len;
			len = -1;
		}
		len++;
		i++;
	}
}

static void	get_map_height(t_all *all)
{
	int		i;
	int		j;

	i = ft_strlen(all->map->tmp_map) - 1;
	j = 0;
	all->map->height = 1;
	while (all->map->tmp_map[i] && (all->map->tmp_map[i] == ' ' ||
				all->map->tmp_map[i] == '\t' || all->map->tmp_map[i] == '\n'))
		i--;
	while (j <= i)
	{
		if (all->map->tmp_map[j] == '\n')
			all->map->height++;
		j++;
	}
}

static int	is_empty_line_in_map(char *tmp_map)
{
	int		i;
	int		j;
	int		count;

	i = ft_strlen(tmp_map) - 1;
	j = 0;
	count = 0;
	while (tmp_map[i] && (tmp_map[i] == ' ' || tmp_map[i] == '\t' ||
				tmp_map[i] == '\n'))
		i--;
	while (j <= i)
	{
		while (tmp_map[j] && tmp_map[j] != '\n')
		{
			if (tmp_map[j] != ' ' && tmp_map[j] != '\t')
				count++;
			j++;
		}
		if (count == 0)
			return (1);
		else
			count = 0;
		j++;
	}
	return (0);
}

static int	invalid_char(char *tmp_map)
{
	int		i;

	i = 0;
	while (tmp_map[i])
	{
		if (tmp_map[i] != '\n' && tmp_map[i] != '\t' && tmp_map[i] != ' '
				&& tmp_map[i] != '0' && tmp_map[i] != '1' && tmp_map[i] != '2'
				&& tmp_map[i] != 'N' && tmp_map[i] != 'S' && tmp_map[i] != 'W'
				&& tmp_map[i] != 'E')
			return (1);
		i++;
	}
	return (0);
}

void		get_map_info(t_all *all)
{
	if (missing_flag(all))
		all->error_flag = 1;
	get_map_width(all);
	get_map_height(all);
	if (is_empty_line_in_map(all->map->tmp_map)
		|| invalid_char(all->map->tmp_map))
		all->error_map = 1;
}

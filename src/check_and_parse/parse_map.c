/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:08:00 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 11:10:16 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int		corner_empty(int y, int x, t_map *map)
{
	if (map->map[y][x - 1] && map->map[y - 1][x] &&
			map->map[y][x - 1] == '1' && map->map[y - 1][x] == '1')
	{
		if (map->map[y - 1][x - 1] && map->map[y - 1][x - 1] == '3')
			return (1);
	}
	if (map->map[y][x + 1] && map->map[y - 1][x] &&
			map->map[y][x + 1] == '1' && map->map[y - 1][x] == '1')
	{
		if (map->map[y - 1][x + 1] && map->map[y - 1][x + 1] == '3')
			return (1);
	}
	if (map->map[y + 1][x] && map->map[y][x - 1] &&
			map->map[y + 1][x] == '1' && map->map[y][x - 1] == '1')
	{
		if (map->map[y + 1][x - 1] && map->map[y + 1][x - 1] == '3')
			return (1);
	}
	if (map->map[y + 1][x] && map->map[y][x + 1] &&
			map->map[y + 1][x] == '1' && map->map[y][x + 1] == '1')
	{
		if (map->map[y + 1][x + 1] && map->map[y + 1][x + 1] == '3')
			return (1);
	}
	return (0);
}

static void		check_corners(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (y < all->map->height)
	{
		x = 0;
		while (x < all->map->width)
		{
			if (all->map->map[y][x] == '0' && corner_empty(y, x, all->map))
				clean_exit("Corner problem in the map\n", all);
			x++;
		}
		y++;
	}
}

static int		copy_map(t_all *all, int width, char *line)
{
	static int	i = 0;
	int			j;

	j = 0;
	all->map->map[i] = NULL;
	if (!(all->map->map[i] = malloc(sizeof(char) * width + 1)))
	{
		all->error_map = 1;
		return (0);
	}
	while (line[j] == ' ')
		all->map->map[i][j++] = '3';
	while (line[j])
	{
		all->map->map[i][j] = line[j];
		j++;
	}
	while (j <= (width - 1))
	{
		all->map->map[i][j] = '3';
		j++;
	}
	all->map->map[i][j] = '\0';
	i++;
	return (1);
}

int				gnl_map(char *file, t_all *all, int ret)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(file, O_RDONLY);
	all->map->map_init = 0;
	if (!(all->map->map = malloc(sizeof(char *) * (all->map->height + 1))))
		clean_exit("Problem during map allocation\n", all);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (is_map_beginning(all, line))
			all->map->map_init = 1;
		if (all->map->map_init == 1 && !is_empty_line(line))
			copy_map(all, all->map->width, line);
		free(line);
	}
	close(fd);
	all->map->map[all->map->height] = NULL;
	if (is_error(all))
		clean_exit("Problem during parsing\n", all);
	check_surrounded_map(all);
	get_player(all);
	check_corners(all);
	return (1);
}

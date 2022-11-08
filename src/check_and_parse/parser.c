/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:43:29 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:54:19 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int		check_if_map_and_store(t_all *all, char *line)
{
	if (is_map_beginning(all, line) && all->map->map_init == 0)
		all->map->map_init = 1;
	else if (!is_map_beginning(all, line) && all->map->map_init == 0)
		all->error_map = 1;
	if (all->map->map_init == 1 && is_map_line(line))
	{
		all->map->tmp_map = ft_strjoindup(all->map->tmp_map, line);
		all->map->tmp_map = ft_strjoindup(all->map->tmp_map, "\n");
	}
	else if (all->map->map_init == 1 && !is_map_line(line))
		all->error_map = 1;
	return (1);
}

static void		parser(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'R')
		parse_resolution(all, line);
	if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' &&
				line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E') ||
			(line[i] == 'E' && line[i + 1] == 'A'))
		dispatch_texture(all, i, line);
	else if (line[i] == 'S' && line[i + 1] != 'O')
		parse_sprite(all, line);
	else if (line[i] == 'F' || line[i] == 'C')
		parse_color(all, i, line);
	else if (line[i] == ' ' || !(line[i]))
	{
		if (all->map->map_init == 1)
			(check_if_map_and_store(all, line));
		else
			while (line[i] && (line[i] == ' '))
				i++;
	}
	else if (line[i] == '1')
		check_if_map_and_store(all, line);
}

static int		is_valid_cubline(t_all *all, char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if ((line[i] != 'R' && line[i] != 'N' && line[i] != 'S' &&
		line[i] != 'W' && line[i] != 'E' && line[i] != 'F' &&
		line[i] != 'C' && line[i] != '1' && line[i] != ' ' &&
		line[i] != '\t' && line[i] != '\n' && line[i] != '\0') ||
		(line[i] == '1' && missing_flag(all)))
	{
		all->error_wrong_cubline = 1;
		return (0);
	}
	parser(all, line);
	return (1);
}

int				read_cubfile(t_all *all, char *file, int ret, char *line)
{
	int		fd;

	init_error_types(all);
	if ((fd = open(file, O_RDONLY)) == -1)
		clean_exit("Could not open the file\n", all);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (is_valid_cubline(all, line))
		{
			if (all->map->map_init == 1 && is_empty_line(line))
				all->map->nb_empty_lines++;
			if (ret == 0 && all->map->tmp_map != NULL)
				get_map_info(all);
			else if (ret == 0 && all->map->tmp_map == NULL)
				all->error_flag = 1;
		}
		free(line);
	}
	close(fd);
	if (ret < 0 || is_error(all))
		clean_exit("Problem during parsing\n", all);
	ret = 1;
	gnl_map(file, all, ret);
	return (1);
}

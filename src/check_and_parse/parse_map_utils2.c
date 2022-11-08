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

int			is_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0' &&
				line[i] != '1' && line[i] != '2' && line[i] != 'N' &&
				line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

int			is_empty_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\t' && line[i] != ' ' && line[i] != '\0'
				&& line[i] != '\n' && line[i] != '\r' && line[i] != '\v'
				&& line[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}

int			check_last_line(char *tmp_map)
{
	int		i;

	i = ft_strlen(tmp_map) - 1;
	while (tmp_map[i] && (tmp_map[i] == ' ' || tmp_map[i] == '\t'
				|| tmp_map[i] == '\n'))
		i--;
	while (tmp_map[i] != '\n')
	{
		if (tmp_map[i] != ' ' && tmp_map[i] != '\t' && tmp_map[i] != '1')
			return (0);
		i--;
	}
	return (1);
}

int			is_map_beginning(t_all *all, char *line)
{
	int		i;
	int		cnt_i;
	int		cnt_sp;
	int		cnt_others;

	i = 0;
	cnt_i = 0;
	cnt_sp = 0;
	cnt_others = 0;
	while (line[i])
	{
		if (line[i] == '1')
			cnt_i++;
		else if (line[i] == ' ')
			cnt_sp++;
		else
			cnt_others++;
		i++;
	}
	if (!missing_flag(all) && cnt_i > 0 && cnt_others == 0)
		return (1);
	return (0);
}

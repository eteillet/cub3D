/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:17:29 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 17:08:57 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char		*store_texture_path(char *store, char *path)
{
	int	i;

	i = -1;
	if (!(store = malloc(sizeof(char) * (ft_strlen(path) + 1))))
		return (NULL);
	while (path[++i])
		store[i] = path[i];
	store[i] = '\0';
	return (store);
}

static void		dispatch_texture_path(t_all *all, int direction, char *path)
{
	if (direction == 1)
		all->texture_no->path = store_texture_path(all->texture_no->path, path);
	else if (direction == 2)
		all->texture_so->path = store_texture_path(all->texture_so->path, path);
	else if (direction == 3)
		all->texture_we->path = store_texture_path(all->texture_we->path, path);
	else if (direction == 4)
		all->texture_ea->path = store_texture_path(all->texture_ea->path, path);
}

void			parse_texture(t_all *all, char *line, int direction)
{
	char	**split;
	char	*path;
	int		len;
	int		i;

	split = ft_split_set(line, " \t");
	if (count_split(split) != 2)
		all->error_text_sp = 1;
	if (count_split(split) == 2 && split[1])
	{
		len = ft_strlen(split[1]);
		if (!(path = malloc(sizeof(char) * (len + 1))))
			all->error_text_sp = 1;
		i = 0;
		while (split[1][i])
		{
			path[i] = split[1][i];
			i++;
		}
		path[i] = '\0';
		dispatch_texture_path(all, direction, path);
		free(path);
	}
	free_split(split);
}

static void		dispatch_texture_2(t_all *all, int i, char *line)
{
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		if (all->texture_we->path != NULL)
			all->error_text_sp = 1;
		else
			parse_texture(all, line, 3);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		if (all->texture_ea->path != NULL)
			all->error_text_sp = 1;
		else
			parse_texture(all, line, 4);
	}
}

void			dispatch_texture(t_all *all, int i, char *line)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		if (all->texture_no->path != NULL)
			all->error_text_sp = 1;
		else
			parse_texture(all, line, 1);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		if (all->texture_so->path != NULL)
			all->error_text_sp = 1;
		else
			parse_texture(all, line, 2);
	}
	dispatch_texture_2(all, i, line);
}

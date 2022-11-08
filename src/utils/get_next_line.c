/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:23:20 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:23:28 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		save_line_and_next(char **save, char **line, int index)
{
	char	*swap;

	*line = ft_substr(*save, 0, index);
	swap = ft_strdup(&(*save)[index + 1]);
	free(*save);
	*save = swap;
	return (1);
}

int		treat_last_normal_line(char **save, char **line)
{
	*line = ft_strdup(*save);
	free(*save);
	*save = NULL;
	return (0);
}

int		treat_last_empty_line(char **save, char **line)
{
	*line = ft_strdup("");
	free(*save);
	*save = NULL;
	return (0);
}

int		entire_buf_read(char **save, char **line)
{
	int		index;

	if (!(*save))
	{
		*line = ft_strdup("");
		return (0);
	}
	if (*save && (index = backslash_finder(*save)) >= 0)
		return (save_line_and_next(save, line, index));
	else if (*save[0] != '\0')
		return (treat_last_normal_line(save, line));
	return (treat_last_empty_line(save, line));
}

int		get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*save[4096];
	int			ret;
	int			index;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		save[fd] = ft_strjoindup(save[fd], buffer);
		index = backslash_finder(save[fd]);
		if (index >= 0)
			return (save_line_and_next(&save[fd], line, index));
	}
	if (ret < 0)
		return (-1);
	return (entire_buf_read(&save[fd], line));
}

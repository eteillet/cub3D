/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:16:19 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 11:16:54 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void		parse_sprite(t_all *all, char *line)
{
	char	**split;
	int		len;
	int		i;

	split = ft_split_set(line, " \t");
	if (all->sprite->path != NULL || count_split(split) != 2)
		all->error_text_sp = 1;
	if (split[1])
	{
		len = ft_strlen(split[1]);
		if (all->sprite->path == NULL)
			all->sprite->path = malloc(sizeof(char) * (len + 1));
		i = 0;
		while (split[1][i])
		{
			all->sprite->path[i] = split[1][i];
			i++;
		}
		all->sprite->path[i] = '\0';
	}
	if (all->sprite->path == NULL)
		all->error_text_sp = 1;
	free_split(split);
}

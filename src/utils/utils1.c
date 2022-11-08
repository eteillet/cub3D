/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:08:52 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/07 14:09:14 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		is_error(t_all *all)
{
	if (all->error_wrong_cubline != 0 || all->error_flag != 0 ||
		all->error_map != 0 || all->error_res != 0 ||
		all->error_color != 0 || all->error_text_sp != 0)
		return (1);
	return (0);
}

int		is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		missing_flag(t_all *all)
{
	if (all->window->res_x == -1 ||
			all->window->res_y == -1 ||
			all->texture_no->path == NULL ||
			all->texture_so->path == NULL ||
			all->texture_we->path == NULL ||
			all->texture_ea->path == NULL ||
			all->sprite->path == NULL ||
			all->color->floor == -1 ||
			all->color->ceiling == -1)
		return (1);
	return (0);
}

int		backslash_finder(char *save)
{
	int i;

	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoindup(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		new[i] = s1[i];
	free(s1);
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

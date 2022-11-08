/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:36:52 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:38:01 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void		free_split_color(t_all *all, char **split, int i)
{
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (i != 3)
		all->error_color = 1;
}

static void		check_if_valid_color(t_all *all, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		all->error_color = 1;
}

static int		check_and_store(char *line, t_all *all, int i)
{
	char	*trim;
	char	**split;
	int		dot;

	dot = 0;
	trim = ft_strtrim(line, " \tFC");
	while (trim[i++])
		if (trim[i] == ',')
			dot++;
	if (dot != 2)
		all->error_color = 1;
	split = ft_split_set(trim, " ,");
	free(trim);
	if (count_split(split) == 3)
	{
		all->color->r = ft_atoi(split[0]);
		all->color->g = ft_atoi(split[1]);
		all->color->b = ft_atoi(split[2]);
	}
	else
		all->error_color = 1;
	check_if_valid_color(all, all->color->r, all->color->g, all->color->b);
	free_split_color(all, split, 0);
	return (1);
}

static int		create_rgb(int r, int g, int b)
{
	int		rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void			parse_color(t_all *all, int i, char *line)
{
	int		rgb;
	int		index;
	int		j;

	rgb = 0;
	j = 0;
	if (!check_and_store(line, all, j))
		all->error_color = 1;
	index = i;
	rgb = create_rgb(all->color->r, all->color->g, all->color->b);
	if (line[index] == 'F')
		all->color->floor = rgb;
	else if (line[index] == 'C')
		all->color->ceiling = rgb;
}

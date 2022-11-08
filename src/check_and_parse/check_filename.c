/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:18:40 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/05 10:20:39 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		check_save_name(char *argv)
{
	int i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == 'e' && argv[i - 1] == 'v' && argv[i - 2] == 'a'
			&& argv[i - 3] == 's' && argv[i - 4] == '-'
			&& argv[i - 5] == '-' && argv[i - 5])
		return (1);
	return (0);
}

int		check_cub_name(char *argv)
{
	int i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == 'b' && argv[i - 1] == 'u' && argv[i - 2] == 'c' &&
			argv[i - 3] == '.' && argv[i - 4])
		return (1);
	return (0);
}

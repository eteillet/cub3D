/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_differential_analysis.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:07:51 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 15:11:03 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** jump to next map square until a ray hits a wall
*/

static void		incr_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		if ((ray->map_x + ray->step_x) < 0)
			ray->map_x = 0;
		else
			ray->map_x += ray->step_x;
		if (ray->step_x == -1)
			ray->side = 0;
		else
			ray->side = 1;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		if ((ray->map_y + ray->step_y) < 0)
			ray->map_y = 0;
		else
			ray->map_y += ray->step_y;
		if (ray->step_y == -1)
			ray->side = 2;
		else
			ray->side = 3;
	}
}

void			raycast_hit(t_map *map, t_ray *ray)
{
	while (ray->hit != 1)
	{
		incr_ray(ray);
		if (map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

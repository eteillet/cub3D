/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:56:04 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 17:00:07 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	raycast_walldist(t_ray *ray, t_player *player, t_window *window)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - player->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else if (ray->side == 2 || ray->side == 3)
		ray->perp_wall_dist = (ray->map_y - player->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(window->res_y / ray->perp_wall_dist);
	if (ray->side == 0 || ray->side == 1)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->z_buffer[ray->x] = ray->perp_wall_dist;
}

static void	raycast_step_sidedist(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x - player->pos_x + 1.0)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y - player->pos_y + 1.0)
			* ray->delta_dist_y;
	}
}

static void	raycast_deltadist(t_ray *ray)
{
	if (ray->ray_dir_y == 0)
		ray->delta_dist_x = 0;
	else if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1;
	else
		ray->delta_dist_x = sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y)
				/ (ray->ray_dir_x * ray->ray_dir_x));
	if (ray->ray_dir_x == 0)
		ray->delta_dist_y = 0;
	else if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1;
	else
		ray->delta_dist_y = sqrt(1 + (ray->ray_dir_x * ray->ray_dir_x)
				/ (ray->ray_dir_y * ray->ray_dir_y));
}

static void	raycast_init(t_ray *ray, t_player *player, t_window *window)
{
	ray->camera_x = (2 * ray->x / (double)window->res_x) - 1;
	ray->ray_dir_x = player->dir_x + player->plan_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plan_y * ray->camera_x;
	ray->hit = 0;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->line_height = 0;
	ray->y = 0;
}

void		raycasting(t_all *all, t_player *player, t_window *window,
		t_ray ray)
{
	if (!(ray.z_buffer = (double *)malloc(sizeof(double) * window->res_x)))
		clean_exit("During allocation of z.buffer\n", all);
	ft_bzero(ray.z_buffer, sizeof(double) * window->res_x);
	ray.x = 0;
	while (ray.x < window->res_x)
	{
		raycast_init(&ray, player, window);
		raycast_deltadist(&ray);
		raycast_step_sidedist(&ray, player);
		raycast_hit(all->map, &ray);
		raycast_walldist(&ray, player, window);
		draw_vertical_line(all, window, &ray);
		ray.x++;
	}
	if (count_sprites(all->map, all))
		treat_sprites(all, &ray);
	free(ray.z_buffer);
	if (all->save == 1)
		display_bmp(all);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
			all->image->img_ptr, 0, 0);
}

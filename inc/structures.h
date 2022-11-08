/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:44:38 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/07 14:51:09 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
**	camera_x = camera plan : left screen=-1, middle=0, right=1
**	perp_wall_dist = distance from the camera plane (and not the player to avoid
**  fish eye effect) to the impact point on wall
**	ray_dir_x = horizontal direction of ray (x)
**	ray_dir_y = vertical direction of ray (y)
**	side_dist_x = distance x to the 1st vertical intersection point
**	side_dist_y = distance y to the 1st horizontal intersection point
**	delta_dist_x = length of the ray between each vertical intersection point
**	delta_dist_y = length of the ray between each horizontal intersection point
**	step_x = -1 if we jump in the negativ x direction, +1 in positiv x direction
**	step_y = -1 if we jump in the negativ y direction, +1 in positiv y direction
**	hit = 1 if a wall has been hit otherwise 0
**	side = side hitted by a ray -> 0=WE 1=EA 2=NO 3=SO
**	line_height = height of vertical line to draw on screen
**	text_x = part x of the texture we are going to render
**	text_y = part y of the texture we are going to render
**	wall_x = where exactly the wall is hit (x coordinate on the texture)
**	*z_buffer = used to store the perp_wall_dist of sprites to draw them
*/

typedef struct	s_ray
{
	int			x;
	int			y;
	double		camera_x;
	double		perp_wall_dist;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			text_x;
	int			text_y;
	double		wall_x;
	double		*z_buffer;
}				t_ray;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	char		dir;
	double		speed;
	double		rot_speed;
}				t_player;

typedef struct	s_key
{
	int			left;
	int			right;
	int			up;
	int			down;
	int			w;
	int			a;
	int			s;
	int			d;
	int			esc;
}				t_key;

typedef struct	s_texture
{
	char		*path;
	void		*img_ptr;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;

}				t_texture;

typedef struct	s_window
{
	long int	res_x;
	long int	res_y;
	void		*mlx_ptr;
	void		*win_ptr;

}				t_window;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
	int			floor;
	int			ceiling;
}				t_color;

typedef struct	s_map
{
	char		*tmp_map;
	char		**map;
	int			map_init;
	int			nb_empty_lines;
	int			emptyline;
	int			width;
	int			height;
	int			dir_player;
}				t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct	s_spinfos
{
	double		sprite_x;
	double		sprite_y;
	double		invdet;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			height;
	int			width;
	int			drawstart_x;
	int			drawstart_y;
	int			drawend_x;
	int			drawend_y;
	int			tex_x;
	int			tex_y;
}				t_spinfos;

typedef struct	s_all
{
	int			save;
	int			music;
	int			error_wrong_cubline;
	int			error_flag;
	int			error_res;
	int			error_color;
	int			error_text_sp;
	int			error_map;
	int			nb_sprites;
	t_sprite	*tab_sp;
	t_spinfos	spinfos;
	t_ray		ray;
	t_key		*key;
	t_window	*window;
	t_player	*player;
	t_texture	*image;
	t_texture	*texture_no;
	t_texture	*texture_so;
	t_texture	*texture_we;
	t_texture	*texture_ea;
	t_texture	*sprite;
	t_color		*color;
	t_map		*map;
}				t_all;

#endif

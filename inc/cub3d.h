/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:43:51 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/07 14:58:45 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "constants.h"
# include "structures.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

/*
** Initialization structures
*/
t_all			*init_all_struct(void);
t_key			*init_struct_key(void);
t_window		*init_struct_window(void);
t_player		*init_struct_player(void);
t_texture		*init_struct_texture(void);
t_color			*init_struct_color(void);
t_map			*init_struct_map(void);
void			init_error_types(t_all *all);

/*
** Checks and parsing
*/
int				read_cubfile(t_all *all, char *file, int ret, char *line);
void			parse_color(t_all *all, int i, char *line);
void			parse_resolution(t_all *all, char *line);
void			adjust_resolution(t_all *all);
void			parse_sprite(t_all *all, char *line);
void			parse_texture(t_all *all, char *line, int direction);
void			dispatch_texture(t_all *all, int i, char *line);
int				check_cub_name(char *argv);
int				check_save_name(char *argv);
int				is_in_player_list(char c);
void			get_texture(t_all *all);

/*
** Map utils
*/
int				gnl_map(char *file, t_all *all, int ret);
void			get_map_info(t_all *all);
int				is_map_line(char *line);
int				is_empty_line(char *line);
int				check_last_line(char *tmp_map);
int				is_map_beginning(t_all *all, char *line);
void			get_player(t_all *all);
void			check_surrounded_map(t_all *all);

/*
** MLX
*/
void			raycasting(t_all *all, t_player *player, t_window *window,
		t_ray ray);
void			raycast_hit(t_map *map, t_ray *ray);
void			draw_vertical_line(t_all *all, t_window *window, t_ray *ray);
void			draw_texture(t_all *all, t_texture *texture,
		t_ray *ray);

/*
** Sprites
*/
void			treat_sprites(t_all *all, t_ray *ray);
void			display_sprite(t_all *all, double *buf);
void			calculate_sprite(t_all *all, t_player *player, int i);
int				count_sprites(t_map *map, t_all *all);

/*
** Key events
*/
int				key_press(int key, t_all *all);
int				key_release(int key, t_all *all);
void			key_move(t_all *all);

/*
** Movements camera and player
*/
void			move_forward(t_map *map, t_player *player);
void			move_backward(t_map *map, t_player *player);
void			move_left(t_map *map, t_player *player);
void			move_right(t_map *map, t_player *player);
void			rot_left(t_player *player);
void			rot_right(t_player *player);

/*
** Bitmap
*/
void			display_bmp(t_all *all);

/*
** Free and exit
*/
void			free_struct(t_all *all);
void			clean_exit(char *error, t_all *all);
int				destroy(t_all *all);

/*
** Utils
*/
int				get_next_line(int fd, char **line);
int				is_error(t_all *all);
int				is_space(int c);
int				missing_flag(t_all *all);
int				backslash_finder(char *save);
char			*ft_strjoindup(char *s1, char *s2);
int				count_split(char **split);
void			free_split(char **split);

/*
** Bonus
*/
void			hud(t_window *window);
void			minimap(t_all *all);

#endif

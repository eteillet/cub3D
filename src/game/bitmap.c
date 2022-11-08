/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:44:02 by eteillet          #+#    #+#             */
/*   Updated: 2021/01/06 14:47:37 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** bmp file format = file header (14 bytes) + image header (40) +
** color (optional 4) + image
** we fill the image starting with the bottom left corner
*/

static void		create_header_file(t_all *all, int fd)
{
	int		total_size;
	int		image_beginning;

	total_size = 14 + 40 + 4 + (all->window->res_x * all->window->res_y) * 4;
	image_beginning = 14 + 40 + 4;
	write(fd, "BM", 2);
	write(fd, &total_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &image_beginning, 4);
}

static void		create_header_image(t_all *all, int fd)
{
	int		header_image_size;
	int		nb_plan;
	int		i;

	header_image_size = 40;
	nb_plan = 1;
	write(fd, &header_image_size, 4);
	write(fd, &all->window->res_x, 4);
	write(fd, &all->window->res_y, 4);
	write(fd, &nb_plan, 2);
	write(fd, &all->image->bpp, 2);
	i = 0;
	while (i++ < 28)
		write(fd, "\0", 1);
}

void			display_bmp(t_all *all)
{
	int		fd;
	int		x;
	int		y;

	if ((fd = open("./cub3D.bmp", O_RDWR)) == -1)
		fd = open("./cub3D.bmp", O_CREAT | O_RDWR);
	if (fd == -1)
		clean_exit("Can't create the .bmp file\n", all);
	create_header_file(all, fd);
	create_header_image(all, fd);
	y = all->window->res_y;
	while (y)
	{
		x = 0;
		while (x < all->window->res_x)
		{
			write(fd, &all->image->data[y * all->image->size_line
					+ x * all->image->bpp / 8], 4);
			x++;
		}
		y--;
	}
	close(fd);
	clean_exit(NULL, all);
}

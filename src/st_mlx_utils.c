/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:07:07 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/30 05:13:55 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_st_mlx(t_mlx *st_mlx)
{
	if (st_mlx->no_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->no_texture);
	if (st_mlx->so_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->so_texture);
	if (st_mlx->we_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->we_texture);
	if (st_mlx->ea_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->ea_texture);
	if (st_mlx->screen_img)
		mlx_destroy_image(st_mlx->mlx, st_mlx->screen_img);
	mlx_destroy_window(st_mlx->mlx, st_mlx->win);
	mlx_destroy_display(st_mlx->mlx);
	free(st_mlx->mlx);
}

int	rgb_to_int(int t, int r, int g, int b)
{
	int	dec;

	dec = t << 24 | r << 16 | g << 8 | b;
	return (dec);
}

void	set_mlx_images(t_mlx *st_mlx, t_file *st_file)
{
	int		size;

	size = TEXTURE_SIZE;
	st_mlx->no_texture = mlx_xpm_file_to_image(
			st_mlx->mlx, st_file->no_texture, &size, &size);
	st_mlx->so_texture = mlx_xpm_file_to_image(
			st_mlx->mlx, st_file->so_texture, &size, &size);
	st_mlx->we_texture = mlx_xpm_file_to_image(
			st_mlx->mlx, st_file->we_texture, &size, &size);
	st_mlx->ea_texture = mlx_xpm_file_to_image(
			st_mlx->mlx, st_file->ea_texture, &size, &size);
	st_mlx->screen_img_addr = mlx_get_data_addr(st_mlx->screen_img,
			&st_mlx->screen_img_bpp, &st_mlx->line_length,
			&st_mlx->screen_img_endian);
}

t_mlx	*build_st_mlx(t_file *st_file, t_coord *st_coord,
		int screen_width, int screen_height)
{
	t_mlx	*st_mlx;

	st_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!st_mlx)
	{
		put_error("Could not allocate memory for mlx struct", NULL);
		return (NULL);
	}
	st_mlx->mlx = mlx_init();
	st_mlx->win = mlx_new_window(
			st_mlx->mlx, screen_width, screen_height, "cub3d");
	st_mlx->screen_img = mlx_new_image(
			st_mlx->mlx, screen_width, screen_height);
	st_mlx->screen_width = screen_width;
	st_mlx->screen_height = screen_height;
	st_mlx->c_color = rgb_to_int(0, st_file->c_color[0], st_file->c_color[1],
			st_file->c_color[2]);
	st_mlx->f_color = rgb_to_int(0, st_file->f_color[0], st_file->f_color[1],
			st_file->f_color[2]);
	set_mlx_images(st_mlx, st_file);
	st_mlx->st_file = st_file;
	st_mlx->st_coord = st_coord;
	return (st_mlx);
}

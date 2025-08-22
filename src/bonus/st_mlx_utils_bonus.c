/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_mlx_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:07:07 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 04:41:20 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	rgb_to_int(int t, int r, int g, int b)
{
	int	dec;

	dec = t << 24 | r << 16 | g << 8 | b;
	return (dec);
}

void	set_mlx_images_addr(t_mlx *st_mlx)
{
	st_mlx->screen->img_addr = mlx_get_data_addr(st_mlx->screen->img,
			&st_mlx->screen->bpp, &st_mlx->screen->size_line,
			&st_mlx->screen->endian);
	st_mlx->no_texture->img_addr = mlx_get_data_addr(st_mlx->no_texture->img,
			&st_mlx->no_texture->bpp, &st_mlx->no_texture->size_line,
			&st_mlx->no_texture->endian);
	st_mlx->so_texture->img_addr = mlx_get_data_addr(st_mlx->so_texture->img,
			&st_mlx->so_texture->bpp, &st_mlx->so_texture->size_line,
			&st_mlx->so_texture->endian);
	st_mlx->we_texture->img_addr = mlx_get_data_addr(st_mlx->we_texture->img,
			&st_mlx->we_texture->bpp, &st_mlx->we_texture->size_line,
			&st_mlx->we_texture->endian);
	st_mlx->ea_texture->img_addr = mlx_get_data_addr(st_mlx->ea_texture->img,
			&st_mlx->ea_texture->bpp, &st_mlx->ea_texture->size_line,
			&st_mlx->ea_texture->endian);
}

void	set_mlx_images(t_mlx *st_mlx, t_file *st_file,
		int screen_width, int screen_height)
{
	st_mlx->screen = (t_img *)malloc(sizeof(t_img));
	st_mlx->no_texture = (t_img *)malloc(sizeof(t_img));
	st_mlx->so_texture = (t_img *)malloc(sizeof(t_img));
	st_mlx->we_texture = (t_img *)malloc(sizeof(t_img));
	st_mlx->ea_texture = (t_img *)malloc(sizeof(t_img));
	st_mlx->screen->img = mlx_new_image(
			st_mlx->mlx, screen_width, screen_height);
	st_mlx->no_texture->img = mlx_xpm_file_to_image(st_mlx->mlx,
			st_file->no_texture, &st_mlx->no_texture->width,
			&st_mlx->no_texture->height);
	st_mlx->so_texture->img = mlx_xpm_file_to_image(st_mlx->mlx,
			st_file->so_texture, &st_mlx->so_texture->width,
			&st_mlx->so_texture->height);
	st_mlx->we_texture->img = mlx_xpm_file_to_image(st_mlx->mlx,
			st_file->we_texture, &st_mlx->we_texture->width,
			&st_mlx->we_texture->height);
	st_mlx->ea_texture->img = mlx_xpm_file_to_image(st_mlx->mlx,
			st_file->ea_texture, &st_mlx->ea_texture->width,
			&st_mlx->ea_texture->height);
}

void	init_keys_and_anim(t_mlx *st_mlx)
{
	st_mlx->key_w = 0;
	st_mlx->key_a = 0;
	st_mlx->key_s = 0;
	st_mlx->key_d = 0;
	st_mlx->key_left = 0;
	st_mlx->key_right = 0;
	st_mlx->mouse_x = 0;
	st_mlx->is_invert = 0;
	st_mlx->curtain_y = 0;
	st_mlx->is_curtain = 0;
	st_mlx->curtain_dir = 0;
	st_mlx->is_invert_prep = 0;
}

// mlx_mouse_hide(st_mlx->mlx, st_mlx->win);
t_mlx	*build_st_mlx(t_file *st_file, t_coord *st_coord)
{
	t_mlx	*st_mlx;

	st_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!st_mlx)
	{
		put_error("Could not allocate memory for mlx struct", NULL);
		return (NULL);
	}
	st_mlx->mlx = mlx_init();
	st_mlx->screen_width = 1920;
	st_mlx->screen_height = 1080;
	st_mlx->win = mlx_new_window(st_mlx->mlx, st_mlx->screen_width,
			st_mlx->screen_height, "cub3d");
	st_mlx->c_color = rgb_to_int(0, st_file->c_color[0], st_file->c_color[1],
			st_file->c_color[2]);
	st_mlx->f_color = rgb_to_int(0, st_file->f_color[0], st_file->f_color[1],
			st_file->f_color[2]);
	set_mlx_images(st_mlx, st_file, st_mlx->screen_width,
		st_mlx->screen_height);
	set_mlx_images_addr(st_mlx);
	init_keys_and_anim(st_mlx);
	st_mlx->st_file = st_file;
	st_mlx->st_coord = st_coord;
	return (st_mlx);
}

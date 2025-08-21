/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_mlx_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:07:07 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/20 16:31:39 by hebatist         ###   ########.fr       */
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

void	find_sprite_pos(t_spr *st_spr, char **map, char c)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == c)
			{
				st_spr->x = x;
				st_spr->y = y;
			}
		}
	}
}

t_spr	*build_orb(t_mlx *st_mlx, char *orb_path, char c)
{
	t_spr	*st_spr;

	st_spr = (t_spr *)malloc(sizeof(t_spr));
	
	st_spr->sprite = (t_img *)malloc(sizeof(t_img));
	st_spr->sprite->img = mlx_xpm_file_to_image(st_mlx->mlx, orb_path, &st_spr->sprite->width, &st_spr->sprite->height);

	st_spr->sprite->img_addr = mlx_get_data_addr(st_spr->sprite->img, 
		&st_spr->sprite->bpp, &st_spr->sprite->size_line, &st_spr->sprite->endian);
	
	find_sprite_pos(st_spr, st_mlx->st_file->map, c);

	st_spr->pos_x = st_spr->x + 0.5;
	st_spr->pos_y = st_spr->y + 0.5;

	st_spr->spr_x = 0.0;
	st_spr->spr_y = 0.0;

	st_spr->cam_spac = 0.0;

	st_spr->transform_x = 0.0;
	st_spr->transform_y = 0.0;

	st_spr->spr_screen_x = 0;

	st_spr->spr_width = 0;
	st_spr->draw_start_x = 0;
	st_spr->draw_end_x = 0;

	st_spr->spr_height = 0;
	st_spr->draw_start_y = 0;
	st_spr->draw_end_y = 0;
	return (st_spr);
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
}

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
	st_mlx->screen_width = 1368;
	st_mlx->screen_height = 720;
	st_mlx->win = mlx_new_window(st_mlx->mlx, st_mlx->screen_width,
			st_mlx->screen_height, "cub3d");
	mlx_mouse_hide(st_mlx->mlx, st_mlx->win);
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

	st_mlx->st_spr1 = build_orb(st_mlx, "assets/painting.xpm", 'G');
	st_mlx->st_spr2 = build_orb(st_mlx, "assets/orb.xpm", 'g');

	return (st_mlx);
}

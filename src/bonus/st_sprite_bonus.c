/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sprite_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:51:01 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/08 14:04:11 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	find_sprite_pos(t_spr *st_spr, char **map, char c)
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

static t_img	**build_rot_orb(t_mlx *st_mlx)
{
	t_img	**rot_orb;	

	rot_orb = (t_img **)malloc(sizeof(rot_orb) * 4);
	rot_orb[0] = (t_img *)malloc(sizeof(t_img));
	rot_orb[1] = (t_img *)malloc(sizeof(t_img));
	rot_orb[2] = (t_img *)malloc(sizeof(t_img));
	rot_orb[3] = NULL;
	rot_orb[0]->img = mlx_xpm_file_to_image(st_mlx->mlx, "assets/rot-0.xpm",
			&rot_orb[0]->width, &rot_orb[0]->height);
	rot_orb[1]->img = mlx_xpm_file_to_image(st_mlx->mlx, "assets/rot-1.xpm",
			&rot_orb[1]->width, &rot_orb[1]->height);
	rot_orb[2]->img = mlx_xpm_file_to_image(st_mlx->mlx, "assets/rot-2.xpm",
			&rot_orb[2]->width, &rot_orb[2]->height);
	rot_orb[0]->img_addr = mlx_get_data_addr(rot_orb[0]->img, &rot_orb[0]->bpp,
			&rot_orb[0]->size_line, &rot_orb[0]->endian);
	rot_orb[1]->img_addr = mlx_get_data_addr(rot_orb[1]->img, &rot_orb[1]->bpp,
			&rot_orb[1]->size_line, &rot_orb[1]->endian);
	rot_orb[2]->img_addr = mlx_get_data_addr(rot_orb[2]->img, &rot_orb[2]->bpp,
			&rot_orb[2]->size_line, &rot_orb[2]->endian);
	return (rot_orb);
}

t_spr	*build_orb(t_mlx *st_mlx, char c)
{
	t_spr	*st_spr;
	t_img	**rot_orb;	

	st_spr = (t_spr *)malloc(sizeof(t_spr));
	if (!st_spr)
		return (NULL);
	ft_memset(st_spr, 0, sizeof(t_spr));
	rot_orb = build_rot_orb(st_mlx);
	if (!rot_orb)
		return (NULL);
	st_spr->sprites = rot_orb;
	find_sprite_pos(st_spr, st_mlx->st_file->map, c);
	st_spr->pos_x = st_spr->x + 0.5;
	st_spr->pos_y = st_spr->y + 0.5;
	return (st_spr);
}

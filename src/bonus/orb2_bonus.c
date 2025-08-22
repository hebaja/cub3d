/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:51:21 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 04:19:19 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	ft_mlx_pixel_get(t_img *st_img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= st_img->width || y < 0 || y >= st_img->height)
		return (0);
	dst = st_img->img_addr + (y * st_img->size_line + x * (st_img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	put_orb_pixel(t_mlx *st_mlx, t_spr *st_spr, int y, int line)
{
	int	scaled_top_dist;
	int	color;

	scaled_top_dist = (y - st_mlx->screen_height / 2
			+ st_spr->spr_height / 2) * 256;
	st_spr->tex_y = ((scaled_top_dist * st_spr->curr_sprite->height)
			/ st_spr->spr_height) / 256;
	color = ft_mlx_pixel_get(st_spr->curr_sprite,
			st_spr->tex_x, st_spr->tex_y);
	if ((color & 0x00FFFFFF) != 0)
		ft_mlx_pixel_put(st_mlx->screen, line, y, color);
}

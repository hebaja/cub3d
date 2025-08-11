/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:10:39 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/11 13:40:02 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	*build_colors(void)
{
	int *colors;

	colors = malloc(sizeof(int) * 19);
	if (colors == NULL)
		return (NULL);
	colors[0]  = 0xffff00;
	colors[1]  = 0xf3ff00;
	colors[2]  = 0xe7ff00;
	colors[3]  = 0xdbff00;
	colors[4]  = 0xcfff00;
	colors[5]  = 0xc3ff00;
	colors[6]  = 0xb7ff00;
	colors[7]  = 0xabff00;
	colors[8]  = 0x9fff00;
	colors[9]  = 0x93ff00;
	colors[10] = 0x87ff00;
	colors[11] = 0x7bff00;
	colors[12] = 0x6fff00;
	colors[13] = 0x63ff00;
	colors[14] = 0x57ff00;
	colors[15] = 0x4bff00;
	colors[16] = 0x3fff00;
	colors[17] = 0x33ff00;
	colors[18] = 0x00ff00;
	return (colors);
}

int	init_minimap(t_mlx *st_mlx)
{
	int	mm_size;

	mm_size = (int)(st_mlx->screen_height * 0.28) - 1;
	st_mlx->minimap = (t_img *)malloc(sizeof(t_img));
	if (st_mlx->minimap == NULL)
		return (0);
	st_mlx->minimap_colors = build_colors();
	if (st_mlx->minimap_colors == NULL)
		return (0);
	st_mlx->minimap_counter = 0;
	st_mlx->minimap_anim_dir = 0;
	st_mlx->minimap_frame = 0;
	st_mlx->minimap_time = 0;
	st_mlx->minimap->width = mm_size;
	st_mlx->minimap->height = mm_size;
	st_mlx->minimap->img = mlx_new_image(st_mlx->mlx, mm_size, mm_size);
	st_mlx->minimap->img_addr = mlx_get_data_addr(st_mlx->minimap->img, \
		&st_mlx->minimap->bpp, \
		&st_mlx->minimap->size_line, \
		&st_mlx->minimap->endian);
	st_mlx->minimap_size = 7;
	st_mlx->minimap_block_size = st_mlx->minimap->width / st_mlx->minimap_size;
	return (1);
}

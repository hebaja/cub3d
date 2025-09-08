/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sprite_clean_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:43:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/08 14:05:02 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	clean_st_spr(t_mlx *st_mlx, t_spr *st_spr)
{
	int	i;

	i = -1;
	while (++i <= 2)
	{
		mlx_destroy_image(st_mlx->mlx, st_spr->sprites[i]->img);
		free(st_spr->sprites[i]);
	}
	free(st_spr->sprites);
	st_spr->sprites = NULL;
}

void	clean_sprites(t_mlx *st_mlx)
{
	if (st_mlx->st_spr1)
	{
		clean_st_spr(st_mlx, st_mlx->st_spr1);
		free(st_mlx->st_spr1);
		st_mlx->st_spr1 = NULL;
	}
	if (st_mlx->st_spr2)
	{
		clean_st_spr(st_mlx, st_mlx->st_spr2);
		free(st_mlx->st_spr2);
		st_mlx->st_spr2 = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_st_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:02:10 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 04:39:25 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_common.h"

void	clean_st_spr(t_mlx *st_mlx, t_spr *st_spr)
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

void	clean_st_file(t_file *st_file)
{
	if (st_file)
	{
		if (st_file->no_texture)
			free(st_file->no_texture);
		if (st_file->so_texture)
			free(st_file->so_texture);
		if (st_file->we_texture)
			free(st_file->we_texture);
		if (st_file->ea_texture)
			free(st_file->ea_texture);
		if (st_file->file_content)
			clean_file_content(st_file->file_content);
		if (st_file->map)
			clean_file_content(st_file->map);
		if (st_file->inv_map)
			clean_file_content(st_file->inv_map);
		free(st_file);
		st_file = NULL;
	}
}

// mlx_mouse_show(st_mlx->mlx, st_mlx->win);
void	clean_st_mlx(t_mlx *st_mlx)
{
	if (st_mlx->screen)
		mlx_destroy_image(st_mlx->mlx, st_mlx->screen->img);
	if (st_mlx->no_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->no_texture->img);
	if (st_mlx->so_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->so_texture->img);
	if (st_mlx->we_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->we_texture->img);
	if (st_mlx->ea_texture)
		mlx_destroy_image(st_mlx->mlx, st_mlx->ea_texture->img);
	if (st_mlx->minimap)
		mlx_destroy_image(st_mlx->mlx, st_mlx->minimap->img);
	mlx_destroy_window(st_mlx->mlx, st_mlx->win);
	mlx_destroy_display(st_mlx->mlx);
	free(st_mlx->minimap_colors);
	free(st_mlx->minimap);
	free(st_mlx->screen);
	free(st_mlx->no_texture);
	free(st_mlx->so_texture);
	free(st_mlx->we_texture);
	free(st_mlx->ea_texture);
	free(st_mlx->mlx);
	free(st_mlx);
}

void	clean_all(t_mlx *st_mlx)
{
	if (st_mlx)
	{
		if (st_mlx->st_coord)
			free(st_mlx->st_coord);
		clean_st_file(st_mlx->st_file);
		clean_sprites(st_mlx);
		clean_st_mlx(st_mlx);
	}
}

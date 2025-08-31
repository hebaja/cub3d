/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:21:01 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/31 22:33:07 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_not_valid_move(double new_x, double new_y, t_mlx *st_mlx)
{
	t_file	*st_file;
	char	**map;
	int		map_x;
	int		map_y;

	st_file = st_mlx->st_file;
	map = st_file->map;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (new_x < 0 || new_y < 0)
		return (1);
	if (map_y < 0 || map_y >= st_file->height)
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(map[map_y]))
		return (1);
	if (map[(int)(new_y + RADIUS)][(int)(new_x + RADIUS)] == '1'
	|| map[(int)(new_y - RADIUS)][(int)(new_x - RADIUS)] == '1'
	|| map[(int)(new_y + RADIUS)][(int)(new_x - RADIUS)] == '1'
	|| map[(int)(new_y - RADIUS)][(int)(new_x + RADIUS)] == '1')
		return (1);
	if (map[map_y][map_x] == '1' || map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

void	check_inversion(t_mlx *st_mlx)
{
	if (!st_mlx->is_invert
		&& (int)st_mlx->st_coord->p_posx == (int)st_mlx->st_spr1->pos_x
		&& (int)st_mlx->st_coord->p_posy == (int)st_mlx->st_spr1->pos_y)
		st_mlx->is_invert_prep = 1;
	else if (st_mlx->is_invert
		&& (int)st_mlx->st_coord->p_posx == (int)st_mlx->st_spr2->pos_x
		&& (int)st_mlx->st_coord->p_posy == (int)st_mlx->st_spr2->pos_y)
		st_mlx->is_invert_prep = 1;
}

void	move_player(t_mlx *st_mlx, double move_x, double move_y)
{
	if (!is_not_valid_move(st_mlx->st_coord->p_posx + move_x,
			st_mlx->st_coord->p_posy, st_mlx))
		st_mlx->st_coord->p_posx += move_x;
	if (!is_not_valid_move(st_mlx->st_coord->p_posx,
			st_mlx->st_coord->p_posy + move_y, st_mlx))
		st_mlx->st_coord->p_posy += move_y;
}

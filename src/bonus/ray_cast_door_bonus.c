/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_door_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:42:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/01 14:22:04 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	calculate_perp_door_dist(t_mlx *st_mlx)
{
	if (st_mlx->st_coord->side_hit == 0)
		st_mlx->st_file->doors->perp_door_dist = (st_mlx->st_file->doors->door_map_x
				- st_mlx->st_coord->p_posx
				+ (1 - st_mlx->st_coord->step_x) / 2)
			/ st_mlx->st_coord->ray_dir_x;
	else
		st_mlx->st_file->doors->perp_door_dist = (st_mlx->st_file->doors->door_map_y
				- st_mlx->st_coord->p_posy
				+ (1 - st_mlx->st_coord->step_y) / 2)
			/ st_mlx->st_coord->ray_dir_y;
}

void	set_door_coord(t_mlx *st_mlx, int *curr_map_x, int *curr_map_y)
{
	st_mlx->st_file->doors->is_door_col = 1;
	st_mlx->st_file->doors->door_map_x = *curr_map_x;
	st_mlx->st_file->doors->door_map_y = *curr_map_y;
	st_mlx->st_file->doors->door_side = st_mlx->st_coord->side_hit;
	calculate_perp_door_dist(st_mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_coord_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:44:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/30 05:15:14 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_common.h"

char	get_player_dir(char **map)
{
	int		i;
	int		j;
	char	res;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				res = map[i][j];
				break ;
			}
		}
	}
	return (res);
}

void	set_dir_vec(char dir, t_coord *st_coord)
{
	if (dir == 'N')
	{
		st_coord->dir_vec_x = 0;
		st_coord->dir_vec_y = -1;
	}
	if (dir == 'S')
	{
		st_coord->dir_vec_x = 0;
		st_coord->dir_vec_y = 1;
	}
	if (dir == 'W')
	{
		st_coord->dir_vec_x = -1;
		st_coord->dir_vec_y = 0;
	}
	if (dir == 'E')
	{
		st_coord->dir_vec_x = 1;
		st_coord->dir_vec_y = 0;
	}
}

void	set_cam_plane(char dir, t_coord *st_coord)
{
	if (dir == 'N')
	{
		st_coord->cam_plane_x = 0.66;
		st_coord->cam_plane_y = 0;
	}
	if (dir == 'S')
	{
		st_coord->cam_plane_x = -0.66;
		st_coord->cam_plane_y = 0;
	}
	if (dir == 'W')
	{
		st_coord->cam_plane_x = 0;
		st_coord->cam_plane_y = -0.66;
	}
	if (dir == 'E')
	{
		st_coord->cam_plane_x = 0;
		st_coord->cam_plane_y = 0.66;
	}
}

t_coord	*build_st_coord(t_file *st_file)
{
	t_coord	*st_coord;

	st_coord = (t_coord *)malloc(sizeof(t_coord));
	if (!st_coord)
	{
		put_error("Could not allocate memory for coord struct", NULL);
		return (NULL);
	}
	st_coord->player_dir = get_player_dir(st_file->map);
	st_coord->p_posx = (double)st_file->player_x + 0.5;
	st_coord->p_posy = (double)st_file->player_y + 0.5;
	st_coord->curr_map_x = st_file->player_x;
	st_coord->curr_map_y = st_file->player_y;
	set_dir_vec(st_coord->player_dir, st_coord);
	set_cam_plane(st_coord->player_dir, st_coord);
	return (st_coord);
}

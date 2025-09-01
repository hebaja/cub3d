/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:57:07 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/31 21:13:43 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_common.h"

void	add_door(int x, int y, t_file *st_file)
{
	t_door *new_door;
	t_door *temp;
	
	new_door = (t_door *)malloc(sizeof(t_door));
	if (!new_door)
	{
		put_error("Memory allocation failed for door", NULL);
		return ;
	}
	new_door->door_map_x = x;
	new_door->door_map_y = y;
	new_door->door_side = 0;
	new_door->is_door_col = 0;
	new_door->is_door_open = 0;
	new_door->is_door_anim = 0;
	new_door->door_dir = 0;
	new_door->door_offset = 0;
	new_door->perp_door_dist = 0;
	new_door->door_tex_x = 0;
	new_door->door_tex_step = 0;
	new_door->door_tex_pos = 0;
	new_door->next = NULL;
	if (!st_file->doors)
		st_file->doors = new_door;
	else
	{
		temp = st_file->doors;
		while (temp->next)
			temp = temp->next;
		temp->next = new_door;
	}
}

void    get_door(t_file *st_file)
{
    int	x;
	int	y;

	y = 0;
	while (st_file->map[y])
	{
		x = 0;
		while (st_file->map[y][x])
		{
			if (st_file->map[y][x] == 'D')
				add_door(x, y, st_file);
			x++;
		}
		y++;
	}
}

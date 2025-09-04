/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:57:07 by dbatista          #+#    #+#             */
/*   Updated: 2025/09/03 22:33:55 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

t_door	*find_door(int x, int y, t_file *st_file)
{
	t_door	*current;

	current = st_file->doors;
	while (current)
	{
		if (current->door_map_x == x && current->door_map_y == y)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	add_door(int x, int y, t_file *st_file)
{
	t_door	*new_door;
	t_door	*temp;
 
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

void	get_door(t_file *st_file)
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

void	free_doors(t_file *st_file)
{
	t_door	*current;
	t_door	*next;

	current = st_file->doors;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	st_file->doors = NULL;
}

void print_doors(t_file *st_file)
{
	t_door	*current;

	current = st_file->doors;
	while (current)
	{
		printf("Porta encontrada nas posições: (%d, %d) - door_anim: '%d'\n", current->door_map_x, current->door_map_y, current->is_door_anim);
		current = current->next;
	}
}

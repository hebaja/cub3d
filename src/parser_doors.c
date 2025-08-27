/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:46:23 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/26 20:30:58 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	add_door(t_file *st_file, int x, int y, double offset)
{
	t_door	*new_door;

	new_door = (t_door *)malloc(sizeof(t_door));
	if (!new_door)
	{
		put_error("Could not allocate memory for door", NULL);
		return ;
	}
	new_door->x = x;
	new_door->y = y;
	new_door->direction = 0;
	new_door->offset = offset;
	new_door->speed = 0.005;
	new_door->is_opening = 0;
	new_door->is_closing = 0;
	new_door->next = NULL;
	if (st_file->map[y + 1][x] == '1' && st_file->map[y - 1][x] == '1')
		new_door->direction = 0;
	else
		new_door->direction = 1;
	st_file->door_count++;
	if (!st_file->door)
		st_file->door = new_door;
	else
	{
		t_door *temp = st_file->door;
		while (temp->next)
			temp = temp->next;
		temp->next = new_door;
	}
}

void	get_door(t_file *st_file)
{
	int	y;
	int	x;

	y = 0;
	while (st_file->map[y])
	{
		x = 0;
		while (st_file->map[y][x])
		{
			if (st_file->map[y][x] == 'D')
				add_door(st_file, x, y, 0);
			x++;
		}
		y++;
	}
}

void	print_doors(t_door *door)
{
	while (door)
	{
		printf("Porta na Posição: (%d, %d) with offset %.2f\n", door->x, door->y, door->offset);
		door = door->next;
	}
}
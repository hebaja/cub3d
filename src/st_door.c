/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_door.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:47:52 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/26 15:47:32 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_door(t_file *st_file)
{
	t_door	*door;

	door = st_file->door;
	while (door)
	{
		if (door->is_opening)
		{
			door->offset += door->speed;
			if (door->offset >= 1.0)
			{
				door->offset = 1.0;
				door->is_opening = 0;
			}
		}
		else if (door->is_closing)
		{
			door->offset -= door->speed;
			if (door->offset <= 0.0)
			{
				door->offset = 0.0;
				door->is_closing = 0;
			}
		}
		door = door->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:48:05 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/08 03:42:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_blank_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	elements_complete(t_file *st_file)
{
	if (st_file->no_texture != NULL && st_file->so_texture != NULL
		&& st_file->we_texture != NULL && st_file->ea_texture
		&& st_file->c_color[0] != -1 && st_file->f_color[0] != -1)
		return (1);
	return (0);
}

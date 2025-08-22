/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:50:29 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 03:52:27 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

char	*build_inv_line(char *line, int width)
{
	int		line_len;
	int		count;
	char	*inv_line;

	line_len = ft_strlen(line);
	inv_line = (char *)ft_calloc(width + 1, sizeof(char));
	count = -1;
	while (--width > 0)
	{
		if (width >= line_len)
			inv_line[++count] = ' ';
		else
			inv_line[++count] = line[width - 1];
	}
	inv_line[++count] = '\n';
	return (inv_line);
}

char	**build_inv_map(t_file *st_file)
{
	char	**inv_map;
	int		i;

	i = -1;
	inv_map = (char **)ft_calloc(st_file->map_height + 1, sizeof(char *));
	while (st_file->map[++i])
		inv_map[i] = build_inv_line(st_file->map[i], st_file->map_width);
	return (inv_map);
}

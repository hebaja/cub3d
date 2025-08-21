/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:03:06 by dbatista          #+#    #+#             */
/*   Updated: 2025/07/23 22:59:12 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_common.h"

int	get_width_map(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_height_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**fill_duplicate_map(int height, int width)
{
	int		i;
	int		j;
	char	**dup_map;

	dup_map = ft_calloc(height + 3, sizeof(char *));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (i < height + 2)
	{
		dup_map[i] = ft_calloc(width + 3, sizeof(char));
		if (!dup_map[i])
		{
			clean_map(dup_map);
			return (NULL);
		}
		j = 0;
		while (j < width + 1)
			dup_map[i][j++] = '-';
		dup_map[i][j] = '\0';
		i++;
	}
	return (dup_map);
}

void	expanded_map(char **map, t_file *st_file)
{
	int		i;
	int		j;
	int		height;
	int		width;

	height = get_height_map(map);
	width = get_width_map(map);
	st_file->dup_map = fill_duplicate_map(height, width);
	if (!st_file->dup_map)
		return ;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			st_file->dup_map[i + 1][j + 1] = map[i][j];
			j++;
		}
		i++;
	}
	st_file->dup_map[height + 2] = NULL;
}

int	map_flood_fill(char **map, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == '\0')
		return (1);
	if (map[y][x] == '-' || map[y][x] == ' ')
		map[y][x] = 'x';
	else if (map[y][x] == '1')
		return (1);
	else if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'E' || map[y][x] == 'W')
	{
		map[y][x] = 'x';
		return (0);
	}
	else if (map[y][x] == 'x')
		return (1);
	return (map_flood_fill(map, x + 1, y)
		&& map_flood_fill(map, x - 1, y)
		&& map_flood_fill(map, x, y + 1)
		&& map_flood_fill(map, x, y - 1));
}

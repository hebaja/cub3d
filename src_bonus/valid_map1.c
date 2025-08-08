/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:03:29 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/08 03:43:47 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	space_in_map(int i, int *j, int last, char **map)
{
	int	k;
	int	height;

	k = *j;
	height = get_height_map(map);
	while (k < last && map[i][k])
	{
		if (map[i][k] && map[i][k] == '0' && map[i][k + 1] == ' ')
			return (0);
		if (map[i][k] == ' ')
		{
			k++;
			while (map[i][k] == ' ')
				k++;
			if (ft_strchr("0NSEW", map[i][k]))
				return (0);
			if (i > 0 && ft_strchr("0NSEW", map[i - 1][k - 1]))
				return (0);
			if (i < height - 1 && ft_strchr("0NSEW", map[i + 1][k - 1]))
				return (0);
		}
		k++;
	}
	return (1);
}

int	valid_character(char **map)
{
	int	i;
	int	j;
	int	last;

	i = 0;
	while (map[i])
	{
		j = 0;
		last = get_last_valid(map[i]);
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				j++;
				if (!space_in_map(i, &j, last, map))
					return (0);
			}
			if (map[i][j] != '\0' && map[i][j] != '\n'
					&& !ft_strchr("01NSEW ", map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	valid_border(char **map, t_file *st_file)
{
	expanded_map(map, st_file);
	if (!map_flood_fill(st_file->dup_map, 0, 0))
	{
		clean_map(st_file->dup_map);
		return (0);
	}
	clean_map(st_file->dup_map);
	return (1);
}

static int	valid_position_player(char **map, t_file *st_file)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				st_file->player_pos = map[i][j];
				st_file->player_x = j;
				st_file->player_y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count == 1);
}

int	valid_map(t_file *st_file)
{
	if (!valid_character(st_file->map))
	{
		put_error("Map has invalid character", NULL);
		return (0);
	}
	if (!valid_border(st_file->map, st_file))
	{
		put_error("Leak in the map, invalid border", NULL);
		return (0);
	}
	if (!valid_position_player(st_file->map, st_file))
	{
		put_error("Player error", NULL);
		return (0);
	}
	return (1);
}

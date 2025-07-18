/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:31:49 by dbatista          #+#    #+#             */
/*   Updated: 2025/07/17 21:01:03 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	valid_character(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '\0' && map[i][j] != '\n' && !ft_strchr("01NSEW", map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	has_empty_line(char **map)
{
	int	i;
	int	empty_line;

	i = 0;
	empty_line = 0;
	while (map[i])
	{
		if (map[i][0] == '\0' || map[i][0] == '\n')
		{
			if (empty_line)
				return (1);
			else
				empty_line = 1;
		}
		i++;
	}
	return (0);
}

static int	valid_border(char **map)
{
	//char	**map_filled;

	if (!has_empty_line(map))
		return (print_error("Map has a empty_line"));
	return (1);
}

static int	valid_position_player(char **map, t_map *st_map)
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
				st_map->player_pos = map[i][j];
				st_map->player_x = j;
				st_map->player_y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count == 1);
}

int	valid_map(t_map	*st_map)
{
	if (!valid_character(st_map->map))
		return (print_error("Error character"));
	if (!valid_border(st_map->map))
		return (print_error("Error Border\n"));
	if (!valid_position_player(st_map->map, st_map))
		return (print_error("Error position player\n"));
	return (1);
}

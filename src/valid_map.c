/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:31:49 by dbatista          #+#    #+#             */
/*   Updated: 2025/07/18 20:34:12 by dbatista         ###   ########.fr       */
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

char	**flood_fill_map(char **map)
{
	int		i;
	int		j;
	int		width;
	char	**map_filled;

	i = 0;
	width = get_width_map(map);
	while (map[i])
		i++;
	map_filled = malloc(sizeof(char *) * (i + 1));
	if (!map_filled)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map_filled[i] = malloc(sizeof(char) * (width + 1));
		if (!map_filled[i])
			return (NULL);
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			map_filled[i][j] = map[i][j];
			j++;
		}
		while (j < width)
		{
			map_filled[i][j] = '-';
			j++;
		}
		map_filled[i][j] = '\0';
		i++;
	}
	map_filled[i] = NULL;
	return (map_filled);
}

static int	valid_border(char **map)
{
	char	**map_filled;
	int		i;

	map_filled = flood_fill_map(map);
	i = 0;
	ft_printf("---Map Filled---\n");
	while (map_filled[i])
	{
		ft_printf("map_filled[%d]: %s\n", i, map_filled[i]);
		i++;
	}
	if (!map_filled)
		return (print_error("Error: flood fill failure\n"));
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
		return (print_error("Error: Invalid character\n"));
	if (!valid_border(st_map->map))
		return (print_error("Error: Invalid Border\n"));
	if (!valid_position_player(st_map->map, st_map))
		return (print_error("Error: Has more than one player\n"));
	return (1);
}

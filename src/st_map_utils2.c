/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_map_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:30:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/07/17 20:31:07 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int	is_texture_and_color(char *line)
{
	if (ft_strncmp("NO ", line, 3) == 0 || ft_strncmp("SO ", line, 3) == 0
		|| ft_strncmp("WE ", line, 3) == 0 || ft_strncmp("EA ", line, 3) == 0
		|| ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0)
		return (1);
	return (0);
}

int	find_line_map(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i][0] == '\n')
		{
			i++;
			continue ;
		}
		if (!is_texture_and_color(line[i]))
			break ;
		i++;
	}
	return (i);
}

void	clean_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	map = NULL;
}

void	clean_st_map(t_map *st_map)
{
	if (st_map)
	{
		free(st_map->no_texture);
		free(st_map->so_texture);
		free(st_map->we_texture);
		free(st_map->ea_texture);
		clean_map(st_map->file_map);
		free(st_map);
		st_map = NULL;
	}
}
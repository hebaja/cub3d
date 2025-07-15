/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/13 19:12:15 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_st_map_texture(char *elem, char *path, t_map *st_map)
{
	if (ft_strncmp(elem, "NO", 2) == 0)
		st_map->no_texture = ft_strtrim(path, "\n");
	if (ft_strncmp(elem, "SO", 2) == 0)
		st_map->so_texture = ft_strtrim(path, "\n");
	if (ft_strncmp(elem, "WE", 2) == 0)
		st_map->we_texture = ft_strtrim(path, "\n");
	if (ft_strncmp(elem, "EA", 2) == 0)
		st_map->ea_texture = ft_strtrim(path, "\n");
}

int	check_texture_element(char *elem, char *line, t_map *st_map)
{
	int		i;
	char	**args;
	(void)st_map;

	i = -1;
	if (ft_strncmp(line, elem, 2) == 0)
	{
		args = ft_split(line, ' ');
		if (ft_strcmp(args[0], elem) == 0 
			&& (args[1] != NULL && ft_strcmp(args[1], "\n") != 0
			&& (args[2] == NULL || ft_strcmp(args[2], "\n") == 0)))
			update_st_map_texture(elem, args[1], st_map);
		while (args[++i])
			free(args[i]);
		free(args);
	}
	return (1);
}



/* TODO Need to check empty files and files with blank lines & invalid lines */
int	parse_elements(t_map *st_map)
{
	char	**map;

	map = st_map->map;
	while (*map)
	{
		check_texture_element("NO", *map, st_map);
		check_texture_element("SO", *map, st_map);	
		check_texture_element("WE", *map, st_map);	
		check_texture_element("EA", *map, st_map);	
		map++;
	}
	ft_printf("%s\n", st_map->no_texture);
	ft_printf("%s\n", st_map->so_texture);
	ft_printf("%s\n", st_map->we_texture);
	ft_printf("%s\n", st_map->ea_texture);
	return (1);
}

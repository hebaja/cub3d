/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/18 16:19:53 by dbatista         ###   ########.fr       */
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

int	is_map(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	if (ft_strncmp("NO ", line, 3) == 0 || ft_strncmp("SO ", line, 3) == 0
		|| ft_strncmp("WE ", line, 3) == 0 || ft_strncmp("EA ", line, 3) == 0
		|| ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0)
		return (0);
	return (1);
}

/* TODO Need to check empty files and files with blank lines & invalid lines */
int	parse_elements(t_map *st_map)
{
	char	**map;
	int		i;

	map = st_map->file_map;
	i = 0;
	while (*map)
	{
		check_texture_element("NO", *map, st_map);
		check_texture_element("SO", *map, st_map);
		check_texture_element("WE", *map, st_map);
		check_texture_element("EA", *map, st_map);
		if (is_map(*map))
		{
			if (st_map->map_finish)
			{
				ft_printf("invalid Map ❌\n");
				ft_printf("the map has empty line\n");
				exit(1);
			}
			st_map->map_start = 1;
			st_map->map[i] = ft_strdup(*map);
			i++;
		}
		else if (st_map->map_start)
			st_map->map_finish = 1;
		map++;
	}
	st_map->map[i] = NULL;
	/*ft_printf("%s\n", st_map->no_texture);
	ft_printf("%s\n", st_map->so_texture);
	ft_printf("%s\n", st_map->we_texture);
	ft_printf("%s\n\n", st_map->ea_texture);*/
	i = 0;
	ft_printf("----Map Validation----\n");
	while (st_map->map[i])
	{
		ft_printf("%s", st_map->map[i]);
		i++;
	}
	ft_printf("\n");
	if (!valid_map(st_map))
	{
		ft_printf("invalid Map ❌ ");
		exit(1);
	}
	ft_printf("Valid Map ✅");
	return (1);
}

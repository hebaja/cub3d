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

int	invalid_line(char *line)
{
	char	*origin_line;

	if (*line != 'N' && *line != 'S' && *line != 'W' && *line != 'E'
		&& *line != 'F' && *line != 'C' && *line != '\n')
	{
		line++;
		while (*line)
			if (*line != ' ' && *line != '\n')
			{
				origin_line = ft_strtrim(line, "\n");
				put_error("invalid line", origin_line);
				free(origin_line);
				return (1);
			}
		line++;
	}
	return (0);
}

int	parse_elements(t_map *st_map)
{
	int		i;

	char	**map;

	i = -1;

	map = st_map->map;
	while (*map)
	{
		if (!check_texture_element("NO", *map, st_map)
			|| !check_texture_element("SO", *map, st_map)
			|| !check_texture_element("WE", *map, st_map)
			|| !check_texture_element("EA", *map, st_map)
			|| !check_color_element('F', *map, st_map)
			|| !check_color_element('C', *map, st_map)
			|| invalid_line(*map))
			return (0);
		map++;
	}
	//Debug
	// ft_printf("%s\n", st_map->no_texture);
	// ft_printf("%s\n", st_map->so_texture);
	// ft_printf("%s\n", st_map->we_texture);
	// ft_printf("%s\n", st_map->ea_texture);
	// ft_printf("F -> ");
	// while (++i < 3)
	// 	ft_printf("%d ", st_map->f_color[i]);
	// ft_printf("\n");
	// i = -1;

	ft_printf("C -> ");
	while (++i < 3)
		ft_printf("%d ", st_map->c_color[i]);
	// ft_printf("\n");
	return (1);
}

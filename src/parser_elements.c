/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/19 11:32:00 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	invalid_line(char *line)
{
	char	*origin_line;

	if (*line != 'N' && *line != 'S' && *line != 'W' && *line != 'E'
		&& *line != 'F' && *line != 'C' && *line != '\n')
	{
		while (*line)
		{
			if (*line != ' ' && *line != '\n')
			{
				origin_line = ft_strtrim(line, "\n");
				put_error("invalid line", origin_line);
				free(origin_line);
				return (1);
			}
		}
		line++;
	}
	return (0);
}

int	check_color_elements_size(int rgb_values[3], char *elem)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			put_error("RGB values must range between 0 and 255", elem);
			return (0);
		}
	}
	return (1);
}

int	check_c_color_element(char elem, char *line, t_map *st_map)
{
	char	**args;

	(void)elem;
	if (*line == 'C')
	{
		if (st_map->c_color[0] != -1)
		{
			put_error("Repated color element", "C");
			return (0);
		}
		if (!check_color_line(line))
			return (0);
		line++;
		args = ft_split(line, ',');
		st_map->c_color[0] = ft_atoi(args[0]);
		st_map->c_color[1] = ft_atoi(args[1]);
		st_map->c_color[2] = ft_atoi(args[2]);
		clean_args(args);
		if (!check_color_elements_size(st_map->c_color, "C"))
			return (0);
	}
	return (1);
}

int	check_f_color_element(char elem, char *line, t_map *st_map)
{
	char	**args;

	(void)elem;
	if (*line == 'F')
	{
		if (st_map->f_color[0] != -1)
		{
			put_error("Repated color element", "F");
			return (0);
		}
		if (!check_color_line(line))
			return (0);
		line++;
		args = ft_split(line, ',');
		st_map->f_color[0] = ft_atoi(args[0]);
		st_map->f_color[1] = ft_atoi(args[1]);
		st_map->f_color[2] = ft_atoi(args[2]);
		clean_args(args);
		if (!check_color_elements_size(st_map->f_color, "F"))
			return (0);
	}
	return (1);
}

int	parse_elements(t_map *st_map)
{
	char	**map;

	map = st_map->map;
	while (*map)
	{
		if (!check_texture_element("NO", *map, st_map)
			|| !check_texture_element("SO", *map, st_map)
			|| !check_texture_element("WE", *map, st_map)
			|| !check_texture_element("EA", *map, st_map)
			|| !check_f_color_element('F', *map, st_map)
			|| !check_c_color_element('C', *map, st_map)
			|| invalid_line(*map))
			return (0);
		map++;
	}
	return (1);
}

/*
	//Debug
	int		i;
	i = -1;
	ft_printf("%s\n", st_map->no_texture);
	ft_printf("%s\n", st_map->so_texture);
	ft_printf("%s\n", st_map->we_texture);
	ft_printf("%s\n", st_map->ea_texture);
	ft_printf("F -> ");
	while (++i < 3)
		ft_printf("%d ", st_map->f_color[i]);
	ft_printf("\n");
	i = -1;
	ft_printf("C -> ");
	while (++i < 3)
		ft_printf("%d ", st_map->c_color[i]);
	ft_printf("\n");
*/

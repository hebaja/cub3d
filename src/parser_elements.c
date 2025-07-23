/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/23 05:18:51 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	invalid_line(char *line)
{
	char	*origin_line;

	origin_line = line;
	if (*line != 'N' && *line != 'S' && *line != 'W' && *line != 'E'
		&& *line != 'F' && *line != 'C' && *line != '\n')
	{
		while (*line)
		{
			if (*line != ' ' && *line != '\n')
			{
				origin_line = ft_strtrim(origin_line, "\n");
				put_error("invalid line", origin_line);
				free(origin_line);
				return (1);
			}
			line++;
		}
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
		if (!check_color_line(line, elem))
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
		if (!check_color_line(line, elem))
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

int	elements_complete(t_map *st_map)
{
	if (st_map->no_texture != NULL && st_map->so_texture != NULL
		&& st_map->we_texture != NULL && st_map->ea_texture
		&& st_map->c_color[0] != -1 && st_map->f_color[0] != -1)
		return (1);
	return (0);
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

int	parse_elements(t_map *st_map)
{
	char	**file_content;
	int		i;

	file_content = st_map->file_content;
	while (*file_content)
	{
		if (!check_texture_element("NO", *file_content, st_map)
			|| !check_texture_element("SO", *file_content, st_map)
			|| !check_texture_element("WE", *file_content, st_map)
			|| !check_texture_element("EA", *file_content, st_map)
			|| !check_f_color_element('F', *file_content, st_map)
			|| !check_c_color_element('C', *file_content, st_map)
			|| invalid_line(*file_content))
			return (0);
		file_content++;
		if (elements_complete(st_map))
			break ;
	}
	if (!elements_complete(st_map))
	{
		put_error("An element is missing", NULL);
		return (0);
	}

	i = 0;
	while (*file_content)
	{
		if (is_map(*file_content))
		{
			if (st_map->map_finish)
			{
				ft_printf("invalid Map ❌\n");
				ft_printf("the map has empty line\n");
				exit(1);
			}
			st_map->map_start = 1;
			st_map->map[i] = ft_strdup(*file_content);
			i++;
		}
		else if (st_map->map_start)
			st_map->map_finish = 1;
		file_content++;
	}
	st_map->map[i] = NULL;
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
		ft_printf("Invalid Map ❌ ");
		clean_st_map(st_map);
		exit(1);
	}
	ft_printf("Valid Map ✅");
	return (1);
}

/*
	//Debug print elements
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

/* Debug print map validation
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
		ft_printf("Invalid Map ❌ ");
		clean_st_map(st_map);
		exit(1);
	}
	ft_printf("Valid Map ✅");
	return (1);
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:11 by hebatist          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/20 17:36:05 by hebatist         ###   ########.fr       */
=======
/*   Updated: 2025/07/22 20:50:35 by dbatista         ###   ########.fr       */
>>>>>>> valid_map
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
<<<<<<< HEAD
	int	i;
=======
	int		i;
	char	**args;
>>>>>>> valid_map

	(void)st_map;
	i = -1;
	while (++i < 3)
	{
<<<<<<< HEAD
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			put_error("RGB values must range between 0 and 255", elem);
			return (0);
		}
=======
		args = ft_split(line, ' ');
		if (ft_strcmp(args[0], elem) == 0
			&& (args[1] != NULL && ft_strcmp(args[1], "\n") != 0
				&& (args[2] == NULL || ft_strcmp(args[2], "\n") == 0)))
			update_st_map_texture(elem, args[1], st_map);
		while (args[++i])
			free(args[i]);
		free(args);
>>>>>>> valid_map
	}
	return (1);
}

<<<<<<< HEAD
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
=======
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
>>>>>>> valid_map

int	parse_elements(t_map *st_map)
{
<<<<<<< HEAD
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
	st_map->map = (char **)malloc(sizeof(char *) * 6);
	i = -1;
	while (*file_content)
	{
		st_map->map[++i] = ft_strdup(*file_content);
		file_content++;
	}
	st_map->map[++i] = NULL;
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
=======
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
		ft_printf("Invalid Map ❌ ");
		clean_st_map(st_map);
		exit(1);
	}
	ft_printf("Valid Map ✅");
	return (1);
}
>>>>>>> valid_map

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

int	validate_texture_element(char *elem, char *str, t_map *st_map)
{
	char	*path;
	char	*xpm_ext;

	path = ft_strtrim(str, "\n");
	if (access(path, F_OK) == 0)
	{
		xpm_ext = ft_strrchr(path, '.');
		if (ft_strcmp(xpm_ext, ".xpm") == 0)
			update_st_map_texture(elem, path, st_map);
		else
		{
			ft_putendl_fd("You need to load xpm texture files", 2);
			free(path);
			return (0);
		}
	}
	else
	{
		perror(path);
		free(path);
		return (0);
	}
	free(path);
	return (1);

}

void	clean_args(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

int	check_texture_element(char *elem, char *line, t_map *st_map)
{
	char	**args;

	if (ft_strncmp(line, elem, 2) == 0)
	{
		args = ft_split(line, ' ');
		if (ft_strcmp(args[0], elem) == 0 
			&& (args[1] != NULL && ft_strcmp(args[1], "\n") != 0
			&& (args[2] == NULL || ft_strcmp(args[2], "\n") == 0)))
		{
			if (!validate_texture_element(elem, args[1], st_map))
			{
				clean_args(args);
				return (0);
			}	
		}
		clean_args(args);
	}
	return (1);
}

int	validate_color(char *str_color)
{
	int	i;
	int	len;
	int	color;	

	i = -1;
	len = ft_strlen(str_color);
	color = 0;
	while (*str_color && ++i < len)
	{
		if (str_color[i] == ' ' || str_color[i] == ',' || str_color[i] == '\n')
			break ;
		if (!ft_isdigit(str_color[i]) || i > 2)
		// TODO error msg here
			return (-1);
		//TODO i > 2 too long element error msg
	}
	color = ft_atoi(str_color);
	return (color);
}

int	valid_color_line(char *line)
{
	while (*line)
	{
		if (*line != 'F' && *line != 'C' && *line != ' ' && *line != ','
			&& *line != '\n' && !ft_isdigit(*line))
			//TODO error msg here
			return (0);
		line++;
	}
	return (1);
}

int	check_color_element(char elem, char *line, t_map *st_map)
{
	int	i;
	int	tmp_color;

	i = -1;
	if (elem == line[0] && line[1] == ' ')
	{
		if (!valid_color_line(line))
			return (0);
		line++;
		while (++i < 3)
		{
			while (!ft_isdigit(*line))
				line++;
			tmp_color = validate_color(line);
			if (tmp_color < 0)
				return (0);
			if (elem == 'F')
				st_map->f_color[i] = tmp_color;
			else
				st_map->c_color[i] = tmp_color;
			while (ft_isdigit(*line))
				line++;
		}
	}
	return (1);
}

/* TODO Need to check empty files and files with blank lines & invalid lines */
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
			|| !check_texture_element("EA", *map, st_map))
			return (0);
		if (!check_color_element('F', *map, st_map))
		{
			ft_putendl_fd("Invalid F color element", 2);
			return (0);
		}
		if (!check_color_element('C', *map, st_map))
		{
			ft_putendl_fd("Invalid C color element", 2);
			return (0);
		}
		map++;
	}
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
	return (1);
}

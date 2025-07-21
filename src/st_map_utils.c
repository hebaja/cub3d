/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:09:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/20 17:27:48 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_file_content(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
	lines = NULL;
}

void	clean_st_map(t_map *st_map)
{
	if (st_map)
	{
		if (st_map->no_texture)
			free(st_map->no_texture);
		if (st_map->so_texture)
			free(st_map->so_texture);
		if (st_map->we_texture)
			free(st_map->we_texture);
		if (st_map->ea_texture)
			free(st_map->ea_texture);
		if (st_map->file_content)
			clean_file_content(st_map->file_content);
		if (st_map->map)
			clean_file_content(st_map->map);
		free(st_map);
		st_map = NULL;
	}
}

int	get_file_content_height(char *map_path, t_map *st_map)
{
	int		fd;
	char	*line;
	size_t	len;

	len = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		case_error_reading_file(st_map);
	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	close(fd);
	return (len);
}

char	**get_file_content(char *map_path, int height)
{
	int		fd;
	int		i;
	char	**file_content;
	char	*str;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		open_map_error();
	file_content = ft_calloc(height + 1, sizeof(char *));
	if (file_content == NULL)
		return (NULL);
	i = -1;
	str = get_next_line(fd);
	while (str != NULL)
	{
		file_content[++i] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (file_content);
}

t_map	*build_st_map(char *map_path)
{
	t_map	*st_map;

	st_map = (t_map *)malloc(sizeof(t_map));
	st_map->path = map_path;
	st_map->no_texture = NULL;
	st_map->so_texture = NULL;
	st_map->we_texture = NULL;
	st_map->ea_texture = NULL;
	st_map->file_content = NULL;
	st_map->map = NULL;
	st_map->f_color[0] = -1;
	st_map->c_color[0] = -1;
	st_map->height = get_file_content_height(map_path, st_map);
	st_map->file_content = get_file_content(map_path, st_map->height);
	return (st_map);
}

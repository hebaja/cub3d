/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_map_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:09:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/23 04:09:12 by hebatist         ###   ########.fr       */
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

void	get_coord_height(t_map *st_map)
{
	int	start;
	int	count;

	start = find_line_map(st_map->map);
	count = 0;
	while (st_map->map[start + count])
	{
		if (is_map(st_map->map[start + count]))
			count++;
		else
			break ;
	}
	st_map->map = ft_calloc(count + 1, sizeof(char *));
	if (!st_map->map)
		return ;
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
	// st_map->height = get_height_file(map_path);
	// st_map->map = get_map_content(map_path, st_map->height);
	get_coord_height(st_map);
	st_map->map_start = 0;
	st_map->map_finish = 0;
	return (st_map);
}

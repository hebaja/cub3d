/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_map_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:30:52 by dbatista          #+#    #+#             */
/*   Updated: 2025/07/18 16:04:47 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

int	get_map_height(char *map_path)
{
	int		fd;
	char	*line;
	size_t	len;

	len = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		case_error_reading_file();
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

char	**get_map_content(char *map_path, int height)
{
	int		fd;
	int		i;
	char	**map;
	char	*str;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		open_map_error();
	map = ft_calloc(height + 1, sizeof(char *));
	if (map == NULL)
		return (NULL);
	i = -1;
	str = get_next_line(fd);
	while (str != NULL)
	{
		map[++i] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (map);
}

void	get_coord_height(t_map *st_map)
{
	int	start;
	int	count;

	start = find_line_map(st_map->file_map);
	count = 0;
	while (st_map->file_map[start + count])
	{
		if (is_map(st_map->file_map[start + count]))
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
	st_map->height = get_map_height(map_path);
	st_map->file_map = get_map_content(map_path, st_map->height);
	get_coord_height(st_map);
	st_map->no_texture = NULL;
	st_map->so_texture = NULL;
	st_map->we_texture = NULL;
	st_map->f_color = -1;
	st_map->c_color = -1;
	return (st_map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:09:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/15 21:10:18 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	map = NULL;
}

void	clean_st_map(t_map *st_map)
{
	if (st_map)
	{
		free(st_map->no_texture);
		free(st_map->so_texture);
		free(st_map->we_texture);
		free(st_map->ea_texture);
		clean_map(st_map->map);
		free(st_map);
		st_map = NULL;
	}
}

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
void	get_cood_height(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if ((map[i] == ' ' || map[i] == '1') && (map[len - 1] == ' ' || map[len - 1] == '1'))
	}
}


t_map	*build_st_map(char *map_path)
{
	t_map	*st_map;

	st_map = (t_map *)malloc(sizeof(t_map));
	st_map->path = map_path;
	st_map->height = get_map_height(map_path);
	st_map->map = get_map_content(map_path, st_map->height);
	get_coord_height(st_map->map);
	st_map->no_texture = NULL;
	st_map->so_texture = NULL;
	st_map->we_texture = NULL;
	st_map->f_color = -1;
	st_map->c_color = -1;
	return (st_map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_file_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:09:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/07 14:00:32 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_file_content_height(char *map_path, t_file *st_file)
{
	int		fd;
	char	*line;
	size_t	len;

	len = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		case_error_reading_file(st_file);
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

int	find_line_map(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i][0] == '\n')
		{
			i++;
			continue ;
		}
		if (ft_strncmp("NO ", line[i], 3) != 0
			&& ft_strncmp("SO ", line[i], 3) != 0
			&& ft_strncmp("WE ", line[i], 3) != 0
			&& ft_strncmp("EA ", line[i], 3) != 0
			&& ft_strncmp("F ", line[i], 2) != 0
			&& ft_strncmp("C ", line[i], 2) != 0)
			break ;
		i++;
	}
	return (i);
}

void	alloc_map_mem(t_file *st_file)
{
	int	start;
	int	count;

	start = find_line_map(st_file->file_content);
	count = 0;
	while (st_file->file_content[start + count])
		count++;
	st_file->map = ft_calloc(count + 1, sizeof(char *));
	if (!st_file->map)
		return ;
	st_file->map_height = count;
}

t_file	*build_st_file(char *map_path)
{
	t_file	*st_file;

	st_file = (t_file *)malloc(sizeof(t_file));
	if (!st_file)
	{
		put_error("Could not allocate memory for file struct", NULL);
		return (NULL);
	}
	st_file->path = map_path;
	st_file->map = NULL;
	st_file->no_texture = NULL;
	st_file->so_texture = NULL;
	st_file->we_texture = NULL;
	st_file->ea_texture = NULL;
	st_file->file_content = NULL;
	st_file->f_color[0] = -1;
	st_file->c_color[0] = -1;
	st_file->height = get_file_content_height(map_path, st_file);
	st_file->file_content = get_file_content(map_path, st_file->height);
	alloc_map_mem(st_file);
	st_file->map_start = 0;
	st_file->map_finish = 0;
	return (st_file);
}

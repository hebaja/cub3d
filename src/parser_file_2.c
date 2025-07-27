/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:01:28 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/27 23:40:22 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	invalid_line(char *line)
{
	char	*origin_line;

	origin_line = line;
	if (*line != 'N' && *line != 'S' && *line != 'W' && *line != 'E'
		&& *line != 'F' && *line != 'C' && *line != '\n' && *line
		!= ' ' && *line != '1')
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

int	try_fill_map(char **file_content, t_file *st_file, int i)
{
	if (st_file->map_finish)
	{
		put_error("Map has an empty line", NULL);
		return (0);
	}
	st_file->map_start = 1;
	st_file->map[i] = ft_strdup(*file_content);
	return (1);
}

int	check_map(char **file_content, t_file *st_file)
{
	int	i;

	i = 0;
	while (*file_content)
	{	
		if (is_map(*file_content))
		{
			if (!try_fill_map(file_content, st_file, i))
				return (0);
			i++;
		}
		else if (st_file->map_start)
			st_file->map_finish = 1;
		else
		{
			put_error("Map has invalid character", NULL);
			return (0);
		}
		file_content++;
	}
	if (!valid_map(st_file))
		return (0);
	return (1);
}

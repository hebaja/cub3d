/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:01:28 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/24 04:01:30 by hebatist         ###   ########.fr       */
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

int	elements_complete(t_file *st_file)
{
	if (st_file->no_texture != NULL && st_file->so_texture != NULL
		&& st_file->we_texture != NULL && st_file->ea_texture
		&& st_file->c_color[0] != -1 && st_file->f_color[0] != -1)
		return (1);
	return (0);
}

int	is_blank_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	check_map(char **file_content, t_file *st_file)
{
	int	i;

	i = -1;
	while (is_blank_line(*file_content))
		file_content++;
	while (*file_content)
	{	
		// if (valid_character(file_content))
		if (is_map(*file_content))
		{
			if (st_file->map_finish)
			{
				put_error("Map has an empty line", NULL);
				//clean_st_file(st_file);
				return (0);
			}
			st_file->map_start = 1;
			st_file->map[++i] = ft_strdup(*file_content);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_elem_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:46:36 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/24 04:00:54 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_st_file_texture(char *elem, char *path, t_file *st_file)
{
	if (ft_strncmp(elem, "NO", 2) == 0)
		st_file->no_texture = ft_strtrim(path, "\n");
	if (ft_strncmp(elem, "SO", 2) == 0)
		st_file->so_texture = ft_strtrim(path, "\n");
	if (ft_strncmp(elem, "WE", 2) == 0)
		st_file->we_texture = ft_strtrim(path, "\n");
	if (ft_strncmp(elem, "EA", 2) == 0)
		st_file->ea_texture = ft_strtrim(path, "\n");
}

char	*clean_path(char *str)
{
	char	*path;
	char	*tmp1;

	tmp1 = ft_strtrim(str, "\t\n");
	path = ft_strtrim(tmp1, " ");
	free(tmp1);
	return (path);
}

int	validate_texture_element(char *elem, char *str, t_file *st_file)
{
	char	*path;
	char	*xpm_ext;

	path = ft_strtrim(str, " \t\n");
	if (access(path, F_OK) == 0 && access(path, R_OK) == 0)
	{
		xpm_ext = ft_strrchr(path, '.');
		if (ft_strcmp(xpm_ext, ".xpm") == 0)
			update_st_file_texture(elem, path, st_file);
		else
		{
			put_error("You need to load xpm texture files", path);
			free(path);
			return (0);
		}
	}
	else
	{
		put_perror(path);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

int	check_repeated_element(char *elem, t_file *st_file)
{
	if (ft_strcmp(elem, "NO") == 0)
		if (st_file->no_texture != NULL)
			return (0);
	if (ft_strcmp(elem, "SO") == 0)
		if (st_file->so_texture != NULL)
			return (0);
	if (ft_strcmp(elem, "WE") == 0)
		if (st_file->we_texture != NULL)
			return (0);
	if (ft_strcmp(elem, "EA") == 0)
		if (st_file->ea_texture != NULL)
			return (0);
	return (1);
}

int	check_texture_element(char *elem, char *line, t_file *st_file)
{
	char	**args;

	if (ft_strncmp(line, elem, 2) == 0)
	{
		if (!check_repeated_element(elem, st_file))
		{
			put_error("Repeated texture element", elem);
			return (0);
		}
		args = ft_split(line, ' ');
		if (ft_strcmp(args[0], elem) == 0
			&& (args[1] != NULL && ft_strcmp(args[1], "\n") != 0
				&& (args[2] == NULL || ft_strcmp(args[2], "\n") == 0)))
		{
			if (!validate_texture_element(elem, args[1], st_file))
			{
				clean_args(args);
				return (0);
			}
		}
		else
			put_error("Problem reading texture line", elem);
		clean_args(args);
	}
	return (1);
}

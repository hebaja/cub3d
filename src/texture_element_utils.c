/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_element_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:46:36 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/19 04:47:26 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_args(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

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
	if (access(path, F_OK) == 0 && access(path, R_OK) == 0)
	{
		xpm_ext = ft_strrchr(path, '.');
		if (ft_strcmp(xpm_ext, ".xpm") == 0)
			update_st_map_texture(elem, path, st_map);
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

int	check_repeated_element(char *elem, t_map *st_map)
{
	if (ft_strcmp(elem, "NO") == 0)
		if (st_map->no_texture != NULL)
			return (0);
	if (ft_strcmp(elem, "SO") == 0)
		if (st_map->so_texture != NULL)
			return (0);
	if (ft_strcmp(elem, "WE") == 0)
		if (st_map->we_texture != NULL)
			return (0);
	if (ft_strcmp(elem, "EA") == 0)
		if (st_map->ea_texture != NULL)
			return (0);
	return (1);
}

int	check_texture_element(char *elem, char *line, t_map *st_map)
{
	char	**args;

	if (ft_strncmp(line, elem, 2) == 0)
	{
		if (!check_repeated_element(elem, st_map))
		{
			put_error("Repeated texture element", elem);
			return (0);
		}
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
		else
			put_error("Problem reading texture line", elem);
		clean_args(args);
	}
	return (1);
}

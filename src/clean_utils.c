/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:02:10 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/31 16:49:19 by hebatist         ###   ########.fr       */
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

void	clean_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	map = NULL;
}

void	clean_file_content(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
	lines = NULL;
}

void	clean_st_file(t_file *st_file)
{
	if (st_file)
	{
		if (st_file->no_texture)
			free(st_file->no_texture);
		if (st_file->so_texture)
			free(st_file->so_texture);
		if (st_file->we_texture)
			free(st_file->we_texture);
		if (st_file->ea_texture)
			free(st_file->ea_texture);
		if (st_file->file_content)
			clean_file_content(st_file->file_content);
		if (st_file->map)
			clean_file_content(st_file->map);
		free(st_file);
		st_file = NULL;
	}
}

void	clean_all(t_mlx *st_mlx)
{
	free(st_mlx->st_coord);
	clean_st_file(st_mlx->st_file);
	clean_st_mlx(st_mlx);
}

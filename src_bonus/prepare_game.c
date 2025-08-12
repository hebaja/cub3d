/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:59:08 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/11 23:59:11 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_file	*prepare_st_file(char *file_path)
{
	t_file	*st_file;

	st_file = build_st_file(file_path);
	if (!st_file)
		return (NULL);
	if (!parse_elements(st_file))
	{
		clean_st_file(st_file);
		return (NULL);
	}
	return (st_file);
}

t_coord	*prepare_st_coord(t_file *st_file)
{
	t_coord	*st_coord;

	st_coord = build_st_coord(st_file);
	if (!st_coord)
	{
		clean_st_file(st_file);
		return (NULL);
	}
	return (st_coord);
}

t_mlx	*prepare_st_mlx(t_file *st_file, t_coord *st_coord)
{	
	t_mlx	*st_mlx;

	st_mlx = build_st_mlx(st_file, st_coord);
	if (!st_mlx)
		return (NULL);
	if (!init_minimap(st_mlx))
		return (NULL);
	return (st_mlx);
}

t_mlx	*prepare_game(char *file_path)
{
	t_mlx	*st_mlx;
	t_file	*st_file;
	t_coord	*st_coord;

	st_file = prepare_st_file(file_path);
	if (!st_file)
	{
		clean_st_file(st_file);
		return (NULL);
	}
	st_coord = prepare_st_coord(st_file);
	if (!st_coord)
	{
		free(st_coord);
		clean_st_file(st_file);
		return (NULL);
	}
	st_mlx = prepare_st_mlx(st_file, st_coord);
	if (!st_mlx)
	{
		free(st_coord);
		clean_st_file(st_file);
		return (NULL);
	}
	return (st_mlx);
}

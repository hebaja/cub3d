/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:59:08 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/20 01:30:54 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	get_highest_len(char **map)
{
	int	len;
	int	tmp_len;

	len = 0;
	while (*map)
	{
		tmp_len = ft_strlen(*map);
		if (tmp_len > len)
			len = tmp_len;
		map++;
	}
	return (len);
}

void	print_map_(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		ft_printf("%s", map[i]);
	ft_printf("\n");
}

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
	st_file->map_width = get_highest_len(st_file->map);
	st_file->inv_map = build_inv_map(st_file);
	print_map_(st_file->inv_map);
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

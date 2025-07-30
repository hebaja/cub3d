/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/30 04:49:05 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_file	*st_file;
	t_coord	*st_coord;
	t_mlx	*st_mlx;

	st_file = NULL;
	if (is_valid_map_path(argc, argv))
	{
		st_file = build_st_file(argv[1]);
		if (!st_file)
			return (1);
		parse_elements(st_file);
	}
	st_coord = build_st_coord(st_file);
	st_mlx = build_st_mlx(st_file, st_coord, 896, 640);
	ray_cast(st_mlx);
	clean_st_file(st_file);
	clean_st_mlx(st_mlx);
	free(st_coord);
	return (0);
}

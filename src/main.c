/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/04 13:50:58 by hebatist         ###   ########.fr       */
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
		if (!parse_elements(st_file))
		{
			clean_st_file(st_file);
			return (1);
		}
		st_coord = build_st_coord(st_file);
		st_mlx = build_st_mlx(st_file, st_coord, 1280, 720);
		ray_cast(st_mlx);
		init_event(st_mlx);
		// mlx_key_hook(st_mlx->win, handle_input, st_mlx);
		// mlx_hook(st_mlx->win, 17, 0, close_window, st_mlx);
		// mlx_loop(st_mlx->mlx);
		clean_all(st_mlx);
	}
	return (0);
}

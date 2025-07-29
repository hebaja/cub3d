/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/29 20:12:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_file	*st_file;
	t_mlx	*st_mlx;

	st_file = NULL;
	if (is_valid_map_path(argc, argv))
	{
		st_file = build_st_file(argv[1]);
		parse_elements(st_file);
	}

	st_mlx = build_st_mlx(st_file, 896, 640);

	int	i;
	int		dirX = 0;
	int		dirY = -1;
	float	planeX = 0.66;
	float	planeY = 0;

	i = 0;
	while (i < st_mlx->screen_width)
	{
		ray_cast(st_mlx, st_mlx->screen_width, st_mlx->screen_height, dirX, dirY, planeX, planeY, i);
		i++;
	}
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->screen_img, 0, 0);
	mlx_loop(st_mlx->mlx);
	clean_st_file(st_file);
	return (0);
}

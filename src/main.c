/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/21 15:04:55 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    put_assets(t_mlx *st_mlx, char c, int w, int h)
{
	if (c == '1')
		mlx_put_image_to_window(
			st_mlx->mlx, st_mlx->win, st_mlx->no_texture, w, h);
	if (c == 'N')
		mlx_put_image_to_window(
			st_mlx->mlx, st_mlx->win, st_mlx->no_texture, w, h);
	if (c == '0')
		mlx_put_image_to_window(
			st_mlx->mlx, st_mlx->win, st_mlx->no_texture, w, h);
}

void    draw_screen(t_mlx *st_mlx, t_map *st_map, int size)
{
	int             x;
	int             y;
	int             w;
	int             h;

	y = -1;
	h = 0;
	while (++y < st_map->height)
	{
		x = -1;
		w = 0;
		while (++y < 7)
		{
			put_assets(st_mlx, st_map->map[x][y], w, h);
			w += size;
		}
		h += size;
	}
}

void	load(t_map *st_map)
{
	t_mlx	*st_mlx;
	int		size = 256;

	st_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	st_mlx->st_map = st_map;
	st_mlx->mlx = mlx_init();
	st_mlx->win = mlx_new_window(st_mlx->mlx, 6 * 256, 6 * 256, "cub3d");
	st_mlx->no_texture = mlx_xpm_file_to_image(st_mlx->mlx, st_map->no_texture, &size, &size);

	mlx_loop(st_mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_map	*st_map;

	st_map = NULL;
	if (is_valid_map_path(argc, argv))
	{
		st_map = build_st_map(argv[1]);
		parse_elements(st_map);
	}

	load(st_map);

	clean_st_map(st_map);
	return (0);
}

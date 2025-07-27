/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/23 22:56:10 by hebatist         ###   ########.fr       */
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

void    draw_screen(t_mlx *st_mlx, t_file *st_file, int size)
{
	int             x;
	int             y;
	int             w;
	int             h;

	x = -1;
	h = 0;
	while (++x < 5)
	{
		y = -1;
		w = 0;
		while (++y < 6)
		{
			put_assets(st_mlx, st_file->map[x][y], w, h);
			w += size;
		}
		h += size;
	}
}

void	my_mlx_pixel_put(t_mlx *st_mlx, int x, int y, int color)
{
	char	*dst;

	dst = st_mlx->addr + (y * st_mlx->line_length + x * (st_mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = (unsigned int)color;
}

void	ray_cast(t_mlx *st_mlx, int width, int dirX, int dirY, float planeX, float planeY, int x)
{
	double cameraX = 2 * x / (double)width - 1;
	float rayDirX = dirX + planeX * cameraX;
	float rayDirY = dirY + planeY * cameraX;

}

void	load(t_file *st_file)
{
	t_mlx	*st_mlx;
	int		size = 128;
	int		white = 16777215;
	int		width;
	int		height;

	width = 7 * size;
	height = 5 * size;

	st_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	st_mlx->mlx = mlx_init();
	st_mlx->win = mlx_new_window(st_mlx->mlx, width, height, "cub3d");
	
	st_mlx->img = mlx_new_image(st_mlx->mlx, width, height);
	st_mlx->addr = mlx_get_data_addr(st_mlx->img, &st_mlx->bits_per_pixel, &st_mlx->line_length, &st_mlx->endian);

	// st_mlx->no_texture = mlx_xpm_file_to_image(st_mlx->mlx, st_file->no_texture, &size, &size);
	st_mlx->st_file = st_file;

	//draw_screen(st_mlx, st_mlx->st_file, size);

	int	i;
	float	p_posx = 3.5;
	float	p_posy = 4.5;

	int		dirX = 0;
	int		dirY = -1;

	float	planeX = 0.66;
	float	playeY = 0;



	i = -1;
	while (++i < height)
	{
		// mlx_pixel_put(st_mlx->mlx, st_mlx->win, 128, i, white);
		my_mlx_pixel_put(st_mlx, 128, i, white);
	}

	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->img, 0, 0);


	mlx_loop(st_mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_file	*st_file;

	st_file = NULL;
	if (is_valid_map_path(argc, argv))
	{
		st_file = build_st_file(argv[1]);
		parse_elements(st_file);
	}
	load(st_file);
	clean_st_file(st_file);
	return (0);
}

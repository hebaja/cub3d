/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/28 00:04:48 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

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

void	look(void)
{
	ft_printf("screen_color\n");
}

void	ray_cast(t_mlx *st_mlx, int width, int height, int dirX, int dirY, float planeX, float planeY, int screen_column)
{
	int		white = 16777215;
	int		brown = 10573867;
	double	p_posx;
	double	p_posy;
	int	curr_map_x;
	int	curr_map_y;

	p_posx = (double)st_mlx->st_file->player_x + 0.5;
	p_posy = (double)st_mlx->st_file->player_y + 0.5;
	curr_map_x = st_mlx->st_file->player_x;
	curr_map_y = st_mlx->st_file->player_y;

	double cameraX = 2 * screen_column / (double)width - 1;
	double rayDirX = dirX + planeX * cameraX;
	double rayDirY = dirY + planeY * cameraX;

	double	delta_dist_x = fabs(1 / rayDirX);
	double	delta_dist_y = fabs(1 / rayDirY);

	double	step_x;
	double	side_dist_x;
	double	step_y;
	double	side_dist_y;

	if (rayDirX < 0) {
		step_x = -1;
		side_dist_x = (p_posx - curr_map_x) * delta_dist_x;
	} else {
		step_x = 1;
		side_dist_x = (curr_map_x + 1.0 - p_posx) * delta_dist_x;
	}

	if (rayDirY < 0) {
		step_y = -1;
		side_dist_y = (p_posy - curr_map_y) * delta_dist_y;
	} else {
		step_y = 1;
		side_dist_y = (curr_map_y + 1.0 - p_posy) * delta_dist_y;
	}

	int hit = 0;     // Was a wall hit?
	int side;        // Was it a vertical or horizontal wall?
	while (hit == 0) {
		if (side_dist_x < side_dist_y) {
			side_dist_x += delta_dist_x;
			curr_map_x += step_x;
			side = 0;  // 0 for X-side
		} else {
			side_dist_y += delta_dist_y;
			curr_map_y += step_y;
			side = 1;  // 1 for Y-side
		}

		if (st_mlx->st_file->map[curr_map_y][curr_map_x] == '1') 
			hit = 1;
	}

	double	perp_wall_dist;
	if (side == 0)
		perp_wall_dist = (curr_map_x - p_posx + (1 - step_x) / 2) / rayDirX;
	else
		perp_wall_dist = (curr_map_y - p_posy + (1 - step_y) / 2) / rayDirY;

	int	line_height = (int)(height / perp_wall_dist);
	int	draw_ceiling = -line_height / 2 + height / 2;
	int	draw_floor = line_height / 2 + height / 2;

	// Clamp to screen bounds
	if (draw_ceiling < 0)
		draw_ceiling = 0;
	if (draw_floor >= height)
		draw_floor = height - 1;


	int	y;
	y = -1;
	while (++y < height)
	{
		if (y < draw_ceiling)
			my_mlx_pixel_put(st_mlx, screen_column, y, white);
		else if (y >= draw_ceiling && y <= draw_floor)
			my_mlx_pixel_put(st_mlx, screen_column, y, brown);
		else
			my_mlx_pixel_put(st_mlx, screen_column, y, white);
	}
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->img, 0, 0);
}

void	load(t_file *st_file)
{
	t_mlx	*st_mlx;
	int		size = 128;
	int		width;
	int		height;

	width = 7 * size;
	height = 5 * size;

	st_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	st_mlx->mlx = mlx_init();
	st_mlx->win = mlx_new_window(st_mlx->mlx, width, height, "cub3d");
	
	st_mlx->img = mlx_new_image(st_mlx->mlx, width, height);
	st_mlx->addr = mlx_get_data_addr(st_mlx->img, &st_mlx->bits_per_pixel, &st_mlx->line_length, &st_mlx->endian);
	st_mlx->st_file = st_file;

	int	i;
	int		dirX = 0;
	int		dirY = -1;
	float	planeX = 0.66;
	float	planeY = 0;

	i = 0;
	while (i < width)
	{
		ray_cast(st_mlx, width, height, dirX, dirY, planeX, planeY, i);
		i++;
	}
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

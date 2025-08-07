/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:15:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/07 17:35:33 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mlx_pixel_put(t_mlx *st_mlx, int x, int y, int color)
{
	char	*dst;

	dst = st_mlx->screen->img_addr + (
			y * st_mlx->screen->size_line + x * (st_mlx->screen->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	set_wall_texture(t_mlx *st_mlx, int wall_line_height, int c_line_height)
{
	double	wall_hit_point;

	if (st_mlx->st_coord->side_hit == 0)
		wall_hit_point = st_mlx->st_coord->p_posy
			+ (st_mlx->st_coord->perp_wall_dist * st_mlx->st_coord->ray_dir_y);
	else
		wall_hit_point = st_mlx->st_coord->p_posx
			+ (st_mlx->st_coord->perp_wall_dist * st_mlx->st_coord->ray_dir_x);
	wall_hit_point -= floor(wall_hit_point);
	st_mlx->st_coord->wall_tex_x = (int)(wall_hit_point
			* (double)st_mlx->curr_texture->width);
	if (st_mlx->st_coord->side_hit == 0 && st_mlx->st_coord->ray_dir_x > 0)
		st_mlx->st_coord->wall_tex_x = st_mlx->curr_texture->width
			- st_mlx->st_coord->wall_tex_x - 1;
	if (st_mlx->st_coord->side_hit == 1 && st_mlx->st_coord->ray_dir_y < 0)
		st_mlx->st_coord->wall_tex_x = st_mlx->curr_texture->width
			- st_mlx->st_coord->wall_tex_x - 1;
	st_mlx->st_coord->wall_tex_step = 1.0
		* st_mlx->curr_texture->height / wall_line_height;
	st_mlx->st_coord->wall_tex_pos = (c_line_height
			- (double)st_mlx->screen_height / 2 + (double)wall_line_height / 2)
		* st_mlx->st_coord->wall_tex_step;
}

void	put_wall_texture_pixel(t_mlx *st_mlx, int screen_column, int y)
{
	int				tex_y;
	int				tex_offset;
	unsigned int	color;

	tex_y = (int)st_mlx->st_coord->wall_tex_pos;
	st_mlx->st_coord->wall_tex_pos += st_mlx->st_coord->wall_tex_step;
	tex_offset = tex_y * st_mlx->curr_texture->size_line
		+ st_mlx->st_coord->wall_tex_x * (st_mlx->curr_texture->bpp / 8);
	color = *(unsigned int *)(st_mlx->curr_texture->img_addr + tex_offset);
	ft_mlx_pixel_put(st_mlx, screen_column, y, color);
}

void	set_current_texture(t_mlx *st_mlx)
{
	if (st_mlx->st_coord->hit_cell == 'D')
		st_mlx->curr_texture = st_mlx->door_texture;
	else if (st_mlx->st_coord->side_hit == 0 && st_mlx->st_coord->ray_dir_x < 0)
		st_mlx->curr_texture = st_mlx->we_texture;
	else if (st_mlx->st_coord->side_hit == 0)
		st_mlx->curr_texture = st_mlx->ea_texture;
	else if (st_mlx->st_coord->side_hit == 1 && st_mlx->st_coord->ray_dir_y < 0)
		st_mlx->curr_texture = st_mlx->no_texture;
	else
		st_mlx->curr_texture = st_mlx->so_texture;
}

void	draw_vertical_line(t_mlx *st_mlx, int screen_column)
{
	int	y;
	int	wall_line_height;
	int	c_line_height;
	int	f_line_height;

	y = -1;
	wall_line_height = (int)(st_mlx->screen_height
			/ st_mlx->st_coord->perp_wall_dist);
	c_line_height = -wall_line_height / 2 + st_mlx->screen_height / 2;
	if (c_line_height < 0)
		c_line_height = 0;
	f_line_height = wall_line_height / 2 + st_mlx->screen_height / 2;
	if (f_line_height >= st_mlx->screen_height)
		f_line_height = st_mlx->screen_height - 1;
	set_current_texture(st_mlx);
	set_wall_texture(st_mlx, wall_line_height, c_line_height);
	while (++y < st_mlx->screen_height)
	{
		if (y < c_line_height)
			ft_mlx_pixel_put(st_mlx, screen_column, y, st_mlx->c_color);
		else if (y >= c_line_height && y <= f_line_height)
			put_wall_texture_pixel(st_mlx, screen_column, y);
		else
			ft_mlx_pixel_put(st_mlx, screen_column, y, st_mlx->f_color);
	}
}

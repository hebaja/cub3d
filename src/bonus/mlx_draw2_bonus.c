#include "../../include/cub3d_bonus.h"

void	ft_mlx_pixel_put(t_img *st_img, int x, int y, int color)
{
	char	*dst;

	dst = st_img->img_addr + (
			y * st_img->size_line + x * (st_img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
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
	ft_mlx_pixel_put(st_mlx->screen, screen_column, y, color);
}

void	default_drawing(t_mlx *st_mlx, int screen_column, int c_line_height, int f_line_height)
{
	int	y;

	y = -1;
	while (++y < st_mlx->screen_height)
	{
		if (st_mlx->is_curtain && y < st_mlx->curtain_y)
			ft_mlx_pixel_put(st_mlx->screen, screen_column, y, 0x000000);
		else
		{
			if (y < c_line_height)
				ft_mlx_pixel_put(st_mlx->screen, screen_column, y, st_mlx->c_color);
			else if (y >= c_line_height && y <= f_line_height)
				put_wall_texture_pixel(st_mlx, screen_column, y);
			else
				ft_mlx_pixel_put(st_mlx->screen, screen_column, y, st_mlx->f_color);
		}
	}
}

void	invert_drawing(t_mlx *st_mlx, int screen_column, int c_line_height, int f_line_height)
{
	int	y;

	y = st_mlx->screen_height;
	while (--y >= 0)
	{
		if (st_mlx->is_curtain && y < st_mlx->curtain_y)
			ft_mlx_pixel_put(st_mlx->screen, screen_column, y, 0x000000);
		else
		{
			if (y < c_line_height)
				ft_mlx_pixel_put(st_mlx->screen, screen_column, y, st_mlx->f_color);
			else if (y >= c_line_height && y <= f_line_height)
				put_wall_texture_pixel(st_mlx, screen_column, y);
			else
				ft_mlx_pixel_put(st_mlx->screen, screen_column, y, st_mlx->c_color);
		}
	}
}

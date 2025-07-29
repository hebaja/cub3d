#include "../include/cub3d.h"
//896 x 640
t_mlx	*build_st_mlx(t_file *st_file, int screen_width, int screen_height)
{
	t_mlx	*st_mlx;

	st_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	st_mlx->mlx = mlx_init();
	st_mlx->win = mlx_new_window(st_mlx->mlx, screen_width, screen_height, "cub3d");
	st_mlx->screen_img = mlx_new_image(st_mlx->mlx, screen_width, screen_height);
	st_mlx->screen_width = screen_width;
	st_mlx->screen_height = screen_height;
	st_mlx->screen_img_addr = mlx_get_data_addr(st_mlx->screen_img, &st_mlx->screen_img_bpp, &st_mlx->line_length, &st_mlx->screen_img_endian);
	st_mlx->st_file = st_file;
	return (st_mlx);
}

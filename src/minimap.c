#include "../include/cub3d.h"

void init_minimap(t_mlx *st_mlx)
{
	int	mm_size;

	mm_size = (int)(st_mlx->screen_height * 0.28) - 1;
	st_mlx->minimap = (t_img *)malloc(sizeof(t_img));
	st_mlx->minimap->width = mm_size;
	st_mlx->minimap->height = mm_size;
	st_mlx->minimap->img = mlx_new_image(st_mlx->mlx, mm_size, mm_size);
	st_mlx->minimap->img_addr = mlx_get_data_addr(st_mlx->minimap->img,
		&st_mlx->minimap->bpp,
		&st_mlx->minimap->size_line,
		&st_mlx->minimap->endian);
	st_mlx->minimap_size = 5;
	st_mlx->minimap_block_size = st_mlx->minimap->width / st_mlx->minimap_size;
}

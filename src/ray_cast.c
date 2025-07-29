#include "../include/cub3d.h"

int	rgb_to_int(int t, int r, int g, int b)
{
	int	dec;

	dec = t << 24 | r << 16 | g << 8 | b;
	return (dec);
}

void	my_mlx_pixel_put(t_mlx *st_mlx, int x, int y, int color)
{
	char	*dst;

	dst = st_mlx->screen_img_addr + (y * st_mlx->line_length + x * (st_mlx->screen_img_bpp / 8));
	*(unsigned int*)dst = (unsigned int)color;
}

void	ray_cast(t_mlx *st_mlx, int width, int height, int dirX, int dirY, float planeX, float planeY, int screen_column)
{
	int		ceiling_color = rgb_to_int(0, st_mlx->st_file->c_color[0], st_mlx->st_file->c_color[1],st_mlx->st_file->c_color[2]);
	int		floor_color = rgb_to_int(0, st_mlx->st_file->f_color[0], st_mlx->st_file->f_color[1],st_mlx->st_file->f_color[2]);
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

	int	y;
	y = -1;
	while (++y < height)
	{
		if (y < draw_ceiling)
			my_mlx_pixel_put(st_mlx, screen_column, y, ceiling_color);
		else if (y >= draw_ceiling && y <= draw_floor)
			my_mlx_pixel_put(st_mlx, screen_column, y, brown);
		else
			my_mlx_pixel_put(st_mlx, screen_column, y, floor_color);
	}
}

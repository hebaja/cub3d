/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_moviment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:55:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/04 13:55:11 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_not_valid_move(double new_x, double new_y, t_mlx *st_mlx)
{
	t_file	*st_file;
	char	**map;
	int		map_x;
	int		map_y;

	st_file = st_mlx->st_file;
	map = st_file->map;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (new_x < 0 || new_y < 0)
		return (1);
	if (map_y < 0 || map_y >= st_file->height)
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(map[map_y]))
		return (1);
	if (map[(int)(new_y + RADIUS)][(int)(new_x + RADIUS)] == '1'
	|| map[(int)(new_y - RADIUS)][(int)(new_x - RADIUS)] == '1'
	|| map[(int)(new_y + RADIUS)][(int)(new_x - RADIUS)] == '1'
	|| map[(int)(new_y - RADIUS)][(int)(new_x + RADIUS)] == '1')
		return (1);
	if (map[map_y][map_x] == '1' || map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

static void	rotate_left(t_coord *coord)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = coord->dir_vec_x;
	coord->dir_vec_x = coord->dir_vec_x * cos(-ROTATE) - coord->dir_vec_y * sin(-ROTATE);
	coord->dir_vec_y = old_dir_x * sin(-ROTATE) + coord->dir_vec_y * cos(-ROTATE);
	old_plane_x = coord->cam_plane_x;
	coord->cam_plane_x = coord->cam_plane_x * cos(-ROTATE) - coord->cam_plane_y * sin(-ROTATE);
	coord->cam_plane_y = old_plane_x * sin(-ROTATE) + coord->cam_plane_y * cos(-ROTATE);
}

static void	rotate_right(t_coord *coord)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = coord->dir_vec_x;
	coord->dir_vec_x = coord->dir_vec_x * cos(ROTATE) - coord->dir_vec_y * sin(ROTATE);
	coord->dir_vec_y = old_dir_x * sin(ROTATE) + coord->dir_vec_y * cos(ROTATE);
	old_plane_x = coord->cam_plane_x;
	coord->cam_plane_x = coord->cam_plane_x * cos(ROTATE) - coord->cam_plane_y * sin(ROTATE);
	coord->cam_plane_y = old_plane_x * sin(ROTATE) + coord->cam_plane_y * cos(ROTATE);
}

void    move_player(t_mlx *st_mlx, double move_x, double move_y)
{
    if (!is_not_valid_move(st_mlx->st_coord->p_posx + move_x, st_mlx->st_coord->p_posy, st_mlx))
        st_mlx->st_coord->p_posx += move_x;
    if (!is_not_valid_move(st_mlx->st_coord->p_posx, st_mlx->st_coord->p_posy + move_y, st_mlx))
        st_mlx->st_coord->p_posy += move_y;
}

static int	key_handle(int key, t_mlx *st_mlx)
{
	t_coord	*coord;

	coord = st_mlx->st_coord;
	if (key == KEY_ESC)
		clean_all(st_mlx);
	if (key == KEY_UP || key == KEY_W)
        move_player(st_mlx, coord->dir_vec_x * MOVE, coord->dir_vec_y * MOVE);
	else if (key == KEY_DOWN || key == KEY_S)
        move_player(st_mlx, -coord->dir_vec_x * MOVE, -coord->dir_vec_y * MOVE);
	else if (key == KEY_D)
        move_player(st_mlx, coord->cam_plane_x * MOVE, coord->cam_plane_y * MOVE);
	else if (key == KEY_A)
        move_player(st_mlx, -coord->cam_plane_x * MOVE, -coord->cam_plane_y * MOVE);
	else if (key == KEY_LEFT)
		rotate_left(coord);
	else if (key == KEY_RIGHT)
		rotate_right(coord);
	ray_cast(st_mlx);
	return (0);
}

void	init_event(t_mlx *st_mlx)
{
	mlx_hook(st_mlx->win, KEY_PRESS, (1L << 0), key_handle, st_mlx);
	mlx_hook(st_mlx->win, 17, 0, close_window, st_mlx);
	mlx_loop(st_mlx->mlx);
}

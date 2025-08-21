/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_common.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/14 14:16:45 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_COMMON_H
# define CUB3D_COMMON_H

# include "includes.h"
# include "defines.h"
# include "structs.h"
# include "common_func.h"

t_mlx	*build_st_mlx(t_file *st_file, t_coord *st_coord);
t_mlx	*prepare_game(char *file_path);
void	init_gameplay(t_mlx *st_mlx);
void	exit_mlx(t_mlx *st_mlx);
void	clean_st_mlx(t_mlx *st_mlx);
void	draw_vertical_line(t_mlx *st_mlx, int screen_column);
void	clean_all(t_mlx *st_mlx);
void	move_player(t_mlx *st_mlx, double move_x, double move_y);
int		is_not_valid_move(double new_x, double new_y, t_mlx *st_mlx);
int		key_release(int key, t_mlx *st_mlx);
int		key_press(int key, t_mlx *st_mlx);
int		handle_input(int keycode, t_mlx *st_mlx);
int		close_window(t_mlx *st_mlx);
void	ray_cast(t_mlx *st_mlx);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:42:59 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/14 14:43:01 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_MLX_H
# define MAIN_MLX_H

# include "structs.h"

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

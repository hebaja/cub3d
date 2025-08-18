/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:01:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/18 14:40:12 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_STRUCT_H
# define BONUS_STRUCT_H

# include "common_struct.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*screen;
	t_img	*no_texture;
	t_img	*so_texture;
	t_img	*we_texture;
	t_img	*ea_texture;
	t_img	*curr_texture;
	int		screen_height;
	int		screen_width;
	int		c_color;
	int		f_color;
	int		abs_player_x;
	int		abs_player_y;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	t_file	*st_file;
	t_coord	*st_coord;
	t_img	*minimap;
	int		minimap_size;
	int		minimap_block_size;
	int		minimap_block_x;
	int		minimap_block_y;
	int		minimap_counter;
	int		minimap_frame;
	size_t	minimap_time;
	int		minimap_anim_dir;
	int		*minimap_colors;
	int		mouse_x;

	double	angle;
	int		is_flipping_prep;
	int		is_flipping;
	int		is_flipping_done;
	int		is_invert;
	size_t	anim_time;

	int		bar_color_1;
	int		bar_color_2;
	
}	t_mlx;

#endif

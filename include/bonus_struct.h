/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:01:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/20 15:16:25 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_STRUCT_H
# define BONUS_STRUCT_H

# include "common_struct.h"

typedef struct s_spr
{
	t_img	*texture;
	double	x;
	double	y;
	double	spr_x;
	double	spr_y;

	double	cam_spac;

	double	transform_x;
	double	transform_y;

	int	spr_screen_x;

	int	spr_width;
	int	spr_height;
	int	draw_start_x;
	int	draw_end_x;
	int	draw_start_y;
	int	draw_end_y;


}	t_spr;

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
	int		is_invert_prep;
	int		is_invert;
	int		is_curtain;
	int		curtain_y;
	int		curtain_dir;

	t_spr	*st_spr;	

}	t_mlx;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:01:24 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/08 15:25:02 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_STRUCT_H
# define BONUS_STRUCT_H

# include "common_struct.h"

typedef struct s_spr
{
	size_t	anim_time;
	t_img	**sprites;
	t_img	*curr_sprite;
	int		x;
	int		y;
	int		frame_pos;
	int		spr_screen_x;
	int		spr_width;
	int		spr_height;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	int		tex_x;
	int		tex_y;
	double	pos_x;
	double	pos_y;
	double	spr_x;
	double	spr_y;
	double	cam_spac;
	double	transform_x;
	double	transform_y;
}	t_spr;

typedef struct s_door
{
	int				map_x;
	int				map_y;
	int				side;
	int				is_open;
	int				is_anim;
	int				dir;
	int				offset;
	int				tex_x;
	int				line_height;
	int				ceiling_height;
	int				floor_height;
	double			perp_dist;
	double			tex_step;
	double			tex_pos;
	struct s_door	*next;
}	t_door;

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
	t_img	*door_texture;
	t_img	*minimap;
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
	int		minimap_size;
	int		minimap_block_size;
	int		minimap_block_x;
	int		minimap_block_y;
	int		minimap_counter;
	int		minimap_frame;
	int		minimap_anim_dir;
	int		*minimap_colors;
	int		mouse_x;
	int		is_invert_prep;
	int		is_invert;
	int		is_curtain;
	int		curtain_y;
	int		curtain_dir;
	int		wall_line_height;
	int		is_door_col;
	int		is_first_door;
	int		wall_ceiling_height;
	int		wall_floor_height;
	t_spr	*st_spr1;
	t_spr	*st_spr2;
	double	z_buffer[1920];
	t_door	*doors;
	t_door	*current_door;
	t_file	*st_file;
	t_coord	*st_coord;
	size_t	minimap_time;
}	t_mlx;

#endif

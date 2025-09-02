/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:42:16 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/31 22:32:46 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_FUNC_H
# define BONUS_FUNC_H

# include "includes.h"
# include "structs.h"

int		init_minimap(t_mlx *st_mlx);
void	render_minimap(t_mlx *st_mlx);
void	animate_player(t_mlx *st_mlx, int x, int y);
size_t	get_current_time(void);
int		ft_mlx_pixel_get(t_img *st_img, int x, int y);
void	start_curtain_effect(t_mlx *st_mlx);
void	prepare_for_invert(t_mlx *st_mlx);
char	**build_inv_map(t_file *st_file);
void	default_drawing(t_mlx *st_mlx, int x);
void	invert_drawing(t_mlx *st_mlx, int x);
t_spr	*build_orb(t_mlx *st_mlx, char c);
void	set_orb(t_mlx *st_mlx);
void	put_orb_pixel(t_mlx *st_mlx, t_spr *st_spr, int y, int line);
void	set_door_coord(t_mlx *st_mlx, int *curr_map_x, int *curr_map_y);
void	start_door_anim(t_mlx *st_mlx);
int		set_ceiling_color(t_mlx *st_mlx);
int		set_floor_color(t_mlx *st_mlx);
void	ft_mlx_pixel_put(t_img *st_img, int x, int y, int color);
void	put_door_texture_pixel(t_mlx *st_mlx, int screen_column, int y);
void	put_wall_texture_pixel(t_mlx *st_mlx, int screen_column, int y);
void	check_inversion(t_mlx *st_mlx);
void	clean_sprites(t_mlx *st_mlx);

#endif

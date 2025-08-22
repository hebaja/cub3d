/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:42:16 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 03:34:49 by hebatist         ###   ########.fr       */
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
void	default_drawing(t_mlx *st_mlx, int x, int c_height, int f_height);
void	invert_drawing(t_mlx *st_mlx, int x, int c_height, int f_height);
t_spr	*build_orb(t_mlx *st_mlx, char c);
void	set_orb(t_mlx *st_mlx);
void	put_orb_pixel(t_mlx *st_mlx, t_spr *st_spr, int y, int line);

#endif

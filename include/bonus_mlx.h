/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:42:16 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/14 14:42:19 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_MLX_H
# define BONUS_MLX_H

# include "includes.h"
# include "structs.h"

int		init_minimap(t_mlx *st_mlx);
void	render_minimap(t_mlx *st_mlx);
void	animate_player(t_mlx *st_mlx, int x, int y);

#endif

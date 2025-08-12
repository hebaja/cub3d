/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:02:12 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/12 12:39:45 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_mlx *st_mlx)
{
	clean_all(st_mlx);
	exit(EXIT_SUCCESS);
}

int	handle_input(int keycode, t_mlx *st_mlx)
{
	if (keycode == 65307)
		close_window(st_mlx);
	return (0);
}

#ifndef BONUS_MLX_H
# define BONUS_MLX_H

# include "includes.h"
# include "common_struct.h"

int		init_minimap(t_mlx *st_mlx);
void	render_minimap(t_mlx *st_mlx);
void	animate_player(t_mlx *st_mlx, int x, int y);

#endif

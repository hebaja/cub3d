/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/23 15:26:36 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_map
{
	char	**file_map;
	char	**map;
	char	**dup_map;
	char	*path;
	int		width;
	int		height;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		map_start;
	int		map_finish;
	int		player_pos;
	int		player_x;
	int		player_y;
	int		f_color;
	int		c_color;
}	t_map;

t_map	*build_st_map(char *map_path);
void	clean_st_map(t_map *st_map);
void	open_map_error(void);
void	case_error_reading_file(void);
void	clean_map(char **map);
int		print_error(char *str);
int		is_valid_map_path(int argc, char **argv);
int		parse_elements(t_map *st_map);
int		is_not_coord(char *line);
int		valid_map(t_map	*st_map);
int		find_line_map(char **line);
int		is_map(char *line);
int		get_height_file(char *map_path);
int		get_height_map(char **map);
int		get_width_map(char **map);
int		map_flood_fill(char **map, int x, int y);
char	**fill_duplicate_map(int height, int width);
void	expanded_map(char **map, t_map *st_map);
int		get_last_valid(char *line);

/* DEBUG */
void	print_map(char **map);

#endif

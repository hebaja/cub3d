/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/20 17:53:10 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_map
{
	char	**file_content;
	char	**map;
	char	*path;
	int		height;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color[3];
	int		c_color[3];
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*no_texture;
	t_map	*st_map;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;	

}	t_mlx;

t_map	*build_st_map(char *map_path);
void	clean_st_map(t_map *st_map);
void	open_map_error(void);
void	case_error_reading_file(void);
void	put_error(char *msg, char *data);
void	put_perror(char *msg);
void	put_error_char(char *msg, char elem);
void	clean_args(char **args);
int		is_valid_map_path(int argc, char **argv);
int		parse_elements(t_map *st_map);
int		check_texture_element(char *elem, char *line, t_map *st_map);
int		check_color_line(char *line, char elem);

/* DEBUG */
void	print_map(char **map);

#endif

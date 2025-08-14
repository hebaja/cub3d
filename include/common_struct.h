#ifndef COMMON_STRUCT_H
# define COMMON_STRUCT_H

# include "includes.h"

typedef struct s_file
{
	char	**file_content;
	char	**map;
	char	**dup_map;
	char	*path;
	int		width;
	int		height;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color[3];
	int		c_color[3];
	int		map_start;
	int		map_height;
	int		map_finish;
	int		player_pos;
	int		player_x;
	int		player_y;
}	t_file;

typedef struct s_coord
{
	int		curr_map_x;
	int		curr_map_y;
	int		side_hit;
	int		wall_tex_x;
	int		wall_tex_y;
	char	player_dir;
	double	dir_vec_x;
	double	dir_vec_y;
	double	cam_plane_x;
	double	cam_plane_y;
	double	camera_x;
	double	p_posx;
	double	p_posy;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	wall_tex_pos;
	double	wall_tex_step;	
}	t_coord;

typedef struct s_img
{
	void	*img;
	char	*img_addr;
	int		width;
	int		height;
	int		size_line;
	int		bpp;
	int		endian;
}	t_img;

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
}	t_mlx;

#ifdef CUBE3D_BONUS
typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   *screen;
    t_img   *no_texture;
    t_img   *so_texture;
    t_img   *we_texture;
    t_img   *ea_texture;
    t_img   *curr_texture;
    int     screen_height;
    int     screen_width;
    int     c_color;
    int     f_color;
    int     abs_player_x;
    int     abs_player_y;
    int     key_w;
    int     key_a;
    int     key_s;
    int     key_d;
    int     key_up;
    int     key_down;
    int     key_left;
    int     key_right;
    t_file  *st_file;
    t_coord *st_coord;
    t_img   *minimap;
    int     minimap_size;
    int     minimap_block_size;
    int     minimap_block_x;
    int     minimap_block_y;
    int     minimap_counter;
    int     minimap_frame;
    size_t  minimap_time;
    int     minimap_anim_dir;
    int     *minimap_colors;
    int     mouse_x;
    /* Extra bonus fields here */
    int     some_bonus_only_var;
}   t_mlx;
#else
typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   *screen;
    t_img   *no_texture;
    t_img   *so_texture;
    t_img   *we_texture;
    t_img   *ea_texture;
    t_img   *curr_texture;
    int     screen_height;
    int     screen_width;
    int     c_color;
    int     f_color;
    int     abs_player_x;
    int     abs_player_y;
    int     key_w;
    int     key_a;
    int     key_s;
    int     key_d;
    int     key_up;
    int     key_down;
    int     key_left;
    int     key_right;
    t_file  *st_file;
    t_coord *st_coord;
    t_img   *minimap;
    int     minimap_size;
    int     minimap_block_size;
    int     minimap_block_x;
    int     minimap_block_y;
    int     minimap_counter;
    int     minimap_frame;
    size_t  minimap_time;
    int     minimap_anim_dir;
    int     *minimap_colors;
    int     mouse_x;
}   t_mlx;
#endif

#endif

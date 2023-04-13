/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2023/04/12 17:33:12 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <float.h>
# define FALSE 0
# define TRUE 1

# define WINDOW_WIDTH 1400
# define WINDOW_HEIGHT 800

# define VERTICAL_HIT 1
# define HORIZONTAL_HIT 2

# define NORTH_WALL 1
# define SOUTH_WALL 2
# define WEST_WALL 3
# define EST_WALL 4

typedef struct s_parsing
{
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	int		rgb_floor[3];
	int		rgb_plafond[3];
	int		map_height;
	int		*map_width;
	int		**map;
}				t_parsing;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}			t_mlx;

typedef struct s_texture
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
}			t_texture;

typedef struct s_cub
{
	t_parsing	parsing;
	t_mlx		mlx;
	t_texture	texture;
	double		distance;
	double		player_x;
	double		player_y;
	double		vision;
	double		vision_incr;
	double		move_incr;
}				t_cub;

typedef struct s_dda
{
	double	angle;
	double	x_cos;
	double	y_sin;
	double	x_scale;
	double	y_scale;

	double	x_horizontal;
	double	y_horizontal;
	double	delta_dist_hori;
	double	horizontal_length;

	double	x_vertical;
	double	y_vertical;
	double	delta_dist_verti;
	double	vertical_length;

	int		quartile;
}				t_dda;

typedef struct s_dda_return
{
	double	distance;
	int		wall_orientation;
	double	index_hit;
}				t_dda_return;

typedef struct s_draw
{
	double	wall_height;
	double	angle;
	double	angle_dif;
	int		x_pixel_draw;
	int		y_pixel_draw;
	int		hit_value;
	int		wall_pixel_y;
	t_img	texture;
}				t_draw;

int				init_mlx(t_cub *cub);
// **************************** //
//			parsing             //
// **************************** //
int				parser(t_parsing *parsing, char *path);
int				check_valid_map(t_parsing *parsing);
int				check_extension(char *file_name, char *extension);
int				check_all_composant(int i);
int				check_player_composant(int i);
int				check_void_around(int i, int j, t_parsing *parsing);
int				check_first_and_last_wall(int *line, int end_line);
int				check_wall(int *line, int end_line);
int				check_wall_up_down(t_parsing *parsing, int i);
void			identifier_manager(t_parsing *parsing, char *line);
int				check_valid_identifier(t_parsing *parsing);
int				check_map_line(char *line);
int				init_map(t_parsing *parsing);
void			create_map_line_manage(t_parsing *parsing, char *line, int fd);
int				create_map_tab(t_parsing *parsing, char *line);
// **************************** //
//			utils               //
// **************************** //
int				str_search(const char *big, const char *little, size_t len);
char			*strdup_no_breakline(char *line);
void			error_message(char *message);
void			free_split(char **arr);
void			free_struct(t_cub *cub);
void			free_error_tab(t_parsing *parsing, char *line, int fd);
void			free_mlx(t_cub *cub);
// **************************** //
//			dda algo            //
// **************************** //
t_dda_return	*get_dist(double x, double y, double angle, t_cub *cub);
// **************************** //
//			get_intersec        //
// **************************** //
void			get_first_vertical_intersec(t_dda *data);
void			get_next_vertical_intersec(t_dda *data);
void			get_first_horizontal_intersec(t_dda *data);
void			get_next_horizontal_intersec(t_dda *data);
// **************************** //
//			projection          //
// **************************** //
int				draw(t_cub *cub);
void			img_pix_put(t_img *img, int x, int y, int color);
int				convert_color(int *color_tab);
double			get_player_position_x(t_parsing *parsing);
double			get_player_position_y(t_parsing *parsing);
double			get_player_position_vision(t_parsing *parsing);
void			draw_wall(t_cub *cub, t_draw *draw, t_dda_return *dda_return);
// **************************** //
//			event               //
// **************************** //
int				deal_key(int key, t_cub *cub);
int				ft_close(t_cub *cub);
void			move_right(t_cub *cub);
void			move_left(t_cub *cub);
void			move_backward(t_cub *cub);
void			move_forward(t_cub *cub);

#endif
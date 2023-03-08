#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
// # include "mlx/mlx_int.h"
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx/mlx.h"
# include <stdlib.h>
# include <math.h>

# define FALSE 0
# define TRUE 1

# define WINDOW_WIDTH 1400
# define WINDOW_HEIGHT 800

typedef struct	s_parsing
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
}	t_parsing;

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

typedef	struct s_cub
{
	t_parsing	parsing;
	t_mlx		mlx;
	double		distance;
	double		player_x;
	double		player_y;
	double		vision;
	double		vision_incr;
	double		move_incr;
}				t_cub;

typedef	struct s_dda
{
	double	x_cos;
	double	y_sin;
	double	x_scale; // x scale to move 1 y
	double	y_scale; // y scale to move 1 x

	double	x_horizontal;
	double	y_horizontal;
	double	horizontal_length;

	double	x_vertical;
	double	y_vertical;
	double	vertical_length;

	int quartile;
}				t_dda;

// **************************** //
//			parsing             //
// **************************** //
int		parser(t_parsing *parsing, char *path);
int		check_valid_map(t_parsing *parsing);
int		check_extension(char *file_name);
int		check_all_composant(int i);
int		check_player_composant(int i);
int		check_void_around(int i, int j, t_parsing *parsing);
int		check_first_and_last_wall(int *line, int end_line);
int		check_wall(int *line, int end_line);
int		check_wall_up_down(t_parsing *parsing, int i);
void	identifier_manager(t_parsing *parsing, char *line);
int		check_valid_identifier(t_parsing *parsing);
int		check_map_line(char *line);
// **************************** //
//			utils               //
// **************************** //
int		str_search(const char *big, const char *little, size_t len);
char	*strdup_no_breakline(char *line);
void	error_message(char *message);
void	free_split(char **arr);
void	free_struct(t_cub **cub);
// **************************** //
//			dda algo            //
// **************************** //
double get_vector_distance(double playerX, double playerY, double angle, t_parsing parsing);
// **************************** //
//			projection          //
// **************************** //
int		draw(t_cub **cub);
void	img_pix_put(t_img *img, int x, int y, int color);
double	get_player_position_x(t_parsing *parsing);
double	get_player_position_y(t_parsing *parsing);
double	get_player_position_vision(t_parsing *parsing);
// **************************** //
//			event               //
// **************************** //
int		deal_key(int key, t_cub **cub);
int		ft_close(t_cub **cub);
void	move_right(t_cub **cub);
void	move_left(t_cub **cub);
void	move_backward(t_cub **cub);
void	move_forward(t_cub **cub);



int	draw_test_move(t_cub **cub);

#endif
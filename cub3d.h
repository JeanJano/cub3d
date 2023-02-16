#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>

# define FALSE 0
# define TRUE 1

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

void	parser(t_parsing *parsing, char *path);
int		check_valid_map(t_parsing *parsing);
int		check_extension(char *file_name);
int		check_all_composant(int i);
int		check_player_composant(int i);
int		check_void_around(int i, int j, t_parsing *parsing);
int		check_first_and_last_wall(int *line, int end_line);
int		check_wall(int *line, int end_line);
int		check_wall_up_down(t_parsing *parsing, int i);
void	identifier_manager(t_parsing *parsing, char *line);
int		check_map_line(char *line);

int		str_search(const char *big, const char *little, size_t len);
char	*strdup_no_breakline(char *line);
void	error_message(char *message);

void	free_split(char **arr);
void	free_struct(t_parsing *parsing);

#endif
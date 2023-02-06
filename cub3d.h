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

int		str_search(const char *big, const char *little, size_t len);
char	*strdup_no_breakline(char *line);

void	free_split(char **arr);

#endif
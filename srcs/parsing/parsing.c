/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:14:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/16 15:07:21 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_orientation(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (TRUE);
	return (FALSE);
}

void	create_map_tab(t_parsing *parsing, char *line)
{
	static int	i;
	int			j;
	int			k;
	int			space;

	j = 1;
	space = 0;
	while (line[j])
		j++;
	j--;
	if (line[j] != '\n')
		j++;
	parsing->map[i] = malloc(sizeof(int *) * j);
	parsing->map_width[i] = j;
	j = 0;
	k = 0;
	while (line[j])
	{
		if (line[j] == ' ')
			parsing->map[i][j] = 676;
		else if (is_player_orientation(line[j]) == TRUE)
			parsing->map[i][j] = line[j];
		else
			parsing->map[i][j] = line[j] - 48;
		j++;
	}
	i++;
}

void	parser(t_parsing *parsing, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		identifier_manager(parsing, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	parsing->map_width = malloc(sizeof(int) * parsing->map_height);
	parsing->map = malloc(sizeof(int *) * parsing->map_height);
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (check_map_line(line) == TRUE)
			create_map_tab(parsing, line);
		// printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

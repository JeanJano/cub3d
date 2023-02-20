/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:14:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/20 20:04:46 by jsauvage         ###   ########.fr       */
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

	j = 1;
	while (line[j])
		j++;
	j--;
	if (line[j] != '\n')
		j++;
	parsing->map[i] = malloc(sizeof(int *) * j);
	parsing->map_width[i] = j;
	j = 0;
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

int	parser(t_parsing *parsing, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FALSE);
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
	int i = 0;
	while (line)
	{
		if (i > 0 && line[0] == '\n')
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			parsing->map_height = i;
			return (FALSE);
		}
		if (check_map_line(line) == TRUE)
		{
			create_map_tab(parsing, line);
			i++;	
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:14:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/23 18:47:51 by jsauvage         ###   ########.fr       */
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



int	parser_map(char *line, t_parsing *parsing, int fd)
{
	int	i;
	int	test = 0;

	i = 0;
	while (line)
	{
		if (i > 0 && line[0] == '\n')
		{
			while (line)
			{
				if (line[0] != '\n')
					test = 1;
				free(line);
				line = get_next_line(fd);
			}
			parsing->map_height = i;
			if (test == 1)
				return (error_message("Incorrect character after map"), 2);
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
	return (TRUE);
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
	int	map = parser_map(line, parsing, fd);
	if (map == FALSE)
		return (FALSE);
	if (map == 2)
		return (2);
	close(fd);
	return (TRUE);
}

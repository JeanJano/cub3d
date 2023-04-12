/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:14:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/12 19:56:11 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_orientation(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (TRUE);
	return (FALSE);
}

int	create_map_tab(t_parsing *parsing, char *line)
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
	if (!parsing->map[i])
		return (1);
	parsing->map_width[i] = j;
	j = -1;
	while (line[++j])
	{
		if (line[j] == ' ')
			parsing->map[i][j] = 676;
		else if (is_player_orientation(line[j]) == TRUE)
			parsing->map[i][j] = line[j];
		else
			parsing->map[i][j] = line[j] - 48;
	}
	i++;
	return (0);
}

int	error_char_after_map(int fd, char *line)
{
	int	count;

	count = 0;
	while (line)
	{
		if (line[0] != '\n')
			count = 1;
		free(line);
		line = get_next_line(fd);
	}
	if (count == 1)
		return (TRUE);
	return (FALSE);
}

int	parser_map(t_parsing *parsing, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i > 0 && line[0] == '\n')
		{
			parsing->map_height = i;
			if (error_char_after_map(fd, line) == TRUE)
				return (error_message("Incorrect character after map"), 2);
			return (FALSE);
		}
		if (check_map_line(line) == TRUE)
		{
			create_map_line_manage(parsing, line, fd);
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
	int		map;

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
	if (init_map(parsing) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	map = parser_map(parsing, fd);
	close(fd);
	if (map == FALSE)
		return (FALSE);
	if (map == 2)
		return (2);
	return (TRUE);
}

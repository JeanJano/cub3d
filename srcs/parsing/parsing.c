/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:14:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/13 21:18:39 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_string_in_identifier(char **identifier, char *info)
{
	char	**info_split;

	info_split = ft_split(info, ' ');
	*identifier = strdup_no_breakline(info_split[1]);
	free_split(info_split);
}

void	save_rgb_in_indentifier(int *identifier, char *info)
{
	char	**info_split;
	char	**rgb_split;

	info_split = ft_split(info, ' ');
	rgb_split = ft_split(info_split[1], ',');
	identifier[0] = ft_atoi(rgb_split[0]);
	identifier[1] = ft_atoi(rgb_split[1]);
	identifier[2] = ft_atoi(rgb_split[2]);
	free_split(info_split);
	free_split(rgb_split);
}

int	check_map_line(char *line)
{
	if (str_search(line, "\n", 1) == TRUE)
		return (FALSE);
	else if (str_search(line, "NO", 2) == TRUE)
		return (FALSE);
	else if (str_search(line, "SO", 2) == TRUE)
		return (FALSE);
	else if (str_search(line, "WE", 2) == TRUE)
		return (FALSE);
	else if (str_search(line, "EA", 2) == TRUE)
		return (FALSE);
	else if (str_search(line, "F", 1) == TRUE)
		return (FALSE);
	else if (str_search(line, "C", 1) == TRUE)
		return (FALSE);
	return	(TRUE);
}

void	identifier_manager(t_parsing *parsing, char *line)
{
	if (str_search(line, "NO", 2) == TRUE)
		save_string_in_identifier(&parsing->path_north, line);
	else if (str_search(line, "SO", 2) == TRUE)
		save_string_in_identifier(&parsing->path_south, line);
	else if (str_search(line, "WE", 2) == TRUE)
		save_string_in_identifier(&parsing->path_west, line);
	else if (str_search(line, "EA", 2) == TRUE)
		save_string_in_identifier(&parsing->path_east ,line);
	else if (str_search(line, "F", 1) == TRUE)
		save_rgb_in_indentifier(parsing->rgb_floor, line);
	else if (str_search(line, "C", 1) == TRUE)
		save_rgb_in_indentifier(parsing->rgb_plafond, line);
	else if (check_map_line(line) == TRUE)
		parsing->map_height++;
}

int	is_player_orientation(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (TRUE);
	return (FALSE);
}

void create_map_tab(t_parsing *parsing, char *line)
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

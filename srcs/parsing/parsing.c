/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:14:46 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/06 19:30:56 by jsauvage         ###   ########.fr       */
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
	// calculer la hauteur de la carte et 
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
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

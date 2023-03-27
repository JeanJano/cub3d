/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:35:55 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/27 14:24:26 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_string_in_identifier(char **identifier, char *info)
{
	char	**info_split;

	info_split = ft_split(info, ' ');
	if (*identifier == NULL)
		*identifier = strdup_no_breakline(info_split[1]);
	free_split(info_split);
}

void	save_rgb_in_indentifier(int *identifier, char *info)
{
	char	**info_split;
	char	**rgb_split;
	int		count;

	info_split = ft_split(info, ' ');
	rgb_split = ft_split(info_split[1], ',');
	count = 0;
	while (rgb_split[count])
		count++;
	if (count < 3)
	{
		free_split(info_split);
		free_split(rgb_split);
		return ;
	}
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
	return (TRUE);
}

void	identifier_manager(t_parsing *parsing, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (str_search(line, "NO", 2) == TRUE)
		save_string_in_identifier(&parsing->path_north, line);
	else if (str_search(line, "SO", 2) == TRUE)
		save_string_in_identifier(&parsing->path_south, line);
	else if (str_search(line, "WE", 2) == TRUE)
		save_string_in_identifier(&parsing->path_west, line);
	else if (str_search(line, "EA", 2) == TRUE)
		save_string_in_identifier(&parsing->path_east, line);
	else if (str_search(line, "F", 1) == TRUE)
		save_rgb_in_indentifier(parsing->rgb_floor, line);
	else if (str_search(line, "C", 1) == TRUE)
		save_rgb_in_indentifier(parsing->rgb_plafond, line);
	else if (check_map_line(line) == TRUE)
		parsing->map_height++;
}

int	check_valid_identifier(t_parsing *parsing)
{
	if (parsing->path_east == NULL)
		return (FALSE);
	if (parsing->path_north == NULL)
		return (FALSE);
	if (parsing->path_south == NULL)
		return (FALSE);
	if (parsing->path_west == NULL)
		return (FALSE);
	if (parsing->rgb_floor[0] > 255 || parsing->rgb_floor[0] < 0)
		return (FALSE);
	if (parsing->rgb_floor[1] > 255 || parsing->rgb_floor[1] < 0)
		return (FALSE);
	if (parsing->rgb_floor[2] > 255 || parsing->rgb_floor[2] < 0)
		return (FALSE);
	if (parsing->rgb_plafond[0] > 255 || parsing->rgb_plafond[0] < 0)
		return (FALSE);
	if (parsing->rgb_plafond[1] > 255 || parsing->rgb_plafond[1] < 0)
		return (FALSE);
	if (parsing->rgb_plafond[2] > 255 || parsing->rgb_plafond[2] < 0)
		return (FALSE);
	return (TRUE);
}

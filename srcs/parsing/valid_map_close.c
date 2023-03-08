/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:30:56 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/08 15:02:55 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_void_around(int i, int j, t_parsing *parsing)
{
	if (i < parsing->map_height - 1 && i > 0 && j < parsing->map_width[i - 1]
		&& parsing->map[i - 1][j] == 0)
		return (FALSE);
	if (i < parsing->map_height - 1 && j < parsing->map_width[i + 1]
		&& parsing->map[i + 1][j] == 0)
		return (FALSE);
	if (j > 0 && parsing->map[i][j - 1] == 0)
		return (FALSE);
	if (j < parsing->map_width[i] - 1 && parsing->map[i][j + 1] == 0)
		return (FALSE);
	return (TRUE);
}

int	check_first_and_last_wall(int *line, int end_line)
{
	int	i;

	i = 0;
	while (i < end_line)
	{
		if (line[i] != 1 && line[i] != 676)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_wall(int *line, int end_line)
{
	int	i;

	i = 0;
	while (i < end_line - 1 || (line[i] != 1 && line[i] != 676))
	{
		if (line[i] == 0)
			break ;
		i++;
	}
	if (i == end_line || line[i - 1] != 1)
		return (FALSE);
	i = end_line;
	while (i > 0 || (line[i] != 1 && line[i] != 676))
	{
		if (line[i] == 0)
			break ;
		i--;
	}
	if (i == 0 || line[i + 1] != 1)
		return (FALSE);
	return (TRUE);
}

int	check_wall_up_down(t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	while (j < parsing->map_width[i])
	{
		if (j > parsing->map_width[i - 1] - 1 && parsing->map[i][j] == 0)
			return (FALSE);
		if (j > parsing->map_width[i + 1] - 1 && parsing->map[i][j] == 0)
			return (FALSE);
		j++;
	}
	return (TRUE);
}

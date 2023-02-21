/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:39:05 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/21 15:53:43 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_number_player(t_parsing *parsing)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_player_composant(parsing->map[i][j]) == TRUE)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_map_composant(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_all_composant(parsing->map[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_map_wall(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < parsing->map_height)
	{
		if (i == 0 || i == parsing->map_height - 1)
		{
			if (check_first_and_last_wall(parsing->map[i],
					parsing->map_width[i]) == FALSE)
				return (FALSE);
		}
		else
		{
			if (check_wall(parsing->map[i], parsing->map_width[i]) == FALSE)
				return (FALSE);
			if (check_wall_up_down(parsing, i) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_void_map(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (parsing->map[i][j] == 676)
			{
				if (check_void_around(i, j, parsing) == FALSE)
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_valid_map(t_parsing *parsing)
{
	if (check_map_composant(parsing) == FALSE)
		return (error_message("Incorrect composant in the map"), FALSE);
	if (get_number_player(parsing) != 1)
		return (error_message("Incorrect number of player"), FALSE);
	if (check_void_map(parsing) == FALSE)
		return (error_message("Incorrect void next to space"), FALSE);
	if (check_map_wall(parsing) == FALSE)
		return (error_message("Incorrect close wall"), FALSE);
	if (check_valid_identifier(parsing) == FALSE)
		return (error_message("Incorrect identifier"), FALSE);
	return (TRUE);
}

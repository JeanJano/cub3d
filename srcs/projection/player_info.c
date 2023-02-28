/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:28:38 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/28 19:30:03 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_player_position_x(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_player_composant(parsing->map[i][j]) == TRUE)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

double	get_player_position_y(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_player_composant(parsing->map[i][j]) == TRUE)
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

double	get_player_position_vision(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_player_composant(parsing->map[i][j]) == TRUE)
				return (parsing->map[i][j]);
			j++;
		}
		i++;
	}
	return (-1);
}

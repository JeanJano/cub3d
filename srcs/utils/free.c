/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:45:29 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/16 15:23:59 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_int_arr(int **arr, int number_of_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < number_of_line)
	{
		free(arr[i]);
		// j = 0;
		// while (j < ligne_length[i])
		// {
		// 	free
		// 	j++;
		// }
		i++;
	}
	free(arr);
}

void	free_struct(t_parsing *parsing)
{
	free(parsing->path_east);
	free(parsing->path_north);
	free(parsing->path_south);
	free(parsing->path_west);
	free_int_arr(parsing->map, parsing->map_height);
	free(parsing->map_width);
}
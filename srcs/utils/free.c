/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:45:29 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/18 16:39:31 by jsauvage         ###   ########.fr       */
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

	(void)j;
	i = 0;
	while (i < number_of_line)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_struct(t_cub *cub)
{
	free(cub->parsing.path_east);
	free(cub->parsing.path_north);
	free(cub->parsing.path_south);
	free(cub->parsing.path_west);
	free_int_arr(cub->parsing.map, cub->parsing.map_height);
	free(cub->parsing.map_width);
}

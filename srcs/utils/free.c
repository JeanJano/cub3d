/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:45:29 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/12 19:41:56 by jsauvage         ###   ########.fr       */
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

void	free_error_tab(t_parsing *parsing, char *line, int fd)
{
	free(parsing->map_width);
	free(parsing->map);
	free(parsing->path_east);
	free(parsing->path_west);
	free(parsing->path_north);
	free(parsing->path_south);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	free_mlx(t_cub *cub)
{
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img.mlx_img);
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.north.mlx_img);
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.east.mlx_img);
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.south.mlx_img);
	mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.west.mlx_img);
	mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
	mlx_destroy_display(cub->mlx.mlx_ptr);
	free(cub->mlx.mlx_ptr);
}

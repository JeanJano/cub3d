/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:25 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/28 18:00:05 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_key(int key, t_cub **cub)
{
	if (key == XK_w && (*cub)->parsing.map[(int)(*cub)->player_x + 1][(int)(*cub)->player_y] != 1)
	{
		printf("map: %d\n", (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y]);
		(*cub)->player_x += 0.2;
	}
	if (key == XK_s && (*cub)->parsing.map[(int)(*cub)->player_x - 1][(int)(*cub)->player_y] != 1)
	{
		printf("map: %d\n", (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y]);
		(*cub)->player_x -= 0.2;
	}
	if (key == XK_a && (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y - 1] != 1)
	{
		printf("map: %d\n", (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y]);
		(*cub)->player_y -= 0.2;
	}
	if (key == XK_d && (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y + 1] != 1)
	{
		printf("map: %d\n", (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y]);
		(*cub)->player_y += 0.2;
	}
}

int	deal_key(int key, t_cub **cub)
{
	if (key == XK_Escape)
	{
		mlx_destroy_image((*cub)->mlx.mlx_ptr, (*cub)->mlx.img.mlx_img);
		mlx_destroy_window((*cub)->mlx.mlx_ptr, (*cub)->mlx.win_ptr);
		mlx_destroy_display((*cub)->mlx.mlx_ptr);
		free((*cub)->mlx.mlx_ptr);
		free_struct(cub);
		exit(0);
	}
	// printf("key: %d\n", key);
	move_key(key, cub);
	return (0);
}

int	ft_close(t_cub **cub)
{
	deal_key(XK_Escape, cub);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:25 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/08 15:32:55 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_key(int key, t_cub *cub)
{
	if (key == XK_w /* && (*cub)->parsing.map[(int)(*cub)->player_x + 1][(int)(*cub)->player_y] != 1 */)
	{
		printf("w\n");
		move_forward(cub);
	}
	if (key == XK_s /* && (*cub)->parsing.map[(int)(*cub)->player_x - 1][(int)(*cub)->player_y] != 1 */)
	{
		printf("s\n");
		move_backward(cub);
	}
	if (key == XK_a /* && (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y - 1] != 1 */)
	{
		printf("a\n");
		move_left(cub);
	}
	if (key == XK_d /* && (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y + 1] != 1 */)
	{
		printf("d\n");
		move_right(cub);
	}

	if (key == XK_Left)
	{
		printf("vision: %f\n", cub->vision);
		cub->vision -= cub->vision_incr;
		if (cub->vision <= 0)
			cub->vision = 360;
	}
	if (key == XK_Right)
	{
		printf("vision: %f\n", cub->vision);
		cub->vision += cub->vision_incr;
		if (cub->vision >= 360)
			cub->vision = 0;
	}
}

int	deal_key(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img.mlx_img);
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		mlx_destroy_display(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
		exit(0);
	}
	// printf("key: %d\n", key);
	move_key(key, cub);
	return (0);
}

int	ft_close(t_cub *cub)
{
	deal_key(XK_Escape, cub);
	return (0);
}

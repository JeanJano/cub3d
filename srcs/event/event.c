/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:25 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/27 18:40:04 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_key(int key, t_cub *cub)
{
	if (key == XK_w)
	{
		printf("w\n");
		move_forward(cub);
	}
	if (key == XK_s)
	{
		printf("s\n");
		move_backward(cub);
	}
	if (key == XK_a)
	{
		printf("a\n");
		move_left(cub);
	}
	if (key == XK_d)
	{
		printf("d\n");
		move_right(cub);
	}

	if (key == XK_Left)
	{
		cub->vision -= cub->vision_incr;
		if (cub->vision < 0)
			cub->vision += 360;
		printf("vision: %f x=%f y=%f\n", cub->vision, cub->player_x, cub->player_y);
	}
	if (key == XK_Right)
	{
		cub->vision += cub->vision_incr;
		if (cub->vision >= 360)
			cub->vision -= 360;
		printf("vision: %f x=%f y=%f\n", cub->vision, cub->player_x, cub->player_y);
	}
}

int	deal_key(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->mlx.img.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.north.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.east.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.south.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.west.mlx_img);
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		mlx_destroy_display(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
		free_struct(cub);
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

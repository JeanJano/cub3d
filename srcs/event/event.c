/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:25 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/12 14:35:43 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_key(int key, t_cub *cub)
{
	if (key == XK_w)
		move_forward(cub);
	if (key == XK_s)
		move_backward(cub);
	if (key == XK_a)
		move_left(cub);
	if (key == XK_d)
		move_right(cub);
	if (key == XK_Left)
	{
		cub->vision -= cub->vision_incr;
		if (cub->vision < 0)
			cub->vision += 360;
	}
	if (key == XK_Right)
	{
		cub->vision += cub->vision_incr;
		if (cub->vision >= 360)
			cub->vision -= 360;
	}
	draw(cub);
}

int	deal_key(int key, t_cub *cub)
{
	if (key == XK_Escape)
	{
		free_mlx(cub);
		free_struct(cub);
		exit(0);
	}
	move_key(key, cub);
	return (0);
}

int	ft_close(t_cub *cub)
{
	deal_key(XK_Escape, cub);
	return (0);
}

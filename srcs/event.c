/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:25 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/20 15:41:59 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	deal_key(int key, t_cub **cub)
{
	if (key == XK_Escape)
	{
		mlx_destroy_image((*cub)->mlx.mlx_ptr, (*cub)->mlx.img.mlx_img);
		mlx_destroy_window((*cub)->mlx.mlx_ptr, (*cub)->mlx.win_ptr);
		mlx_destroy_display((*cub)->mlx.mlx_ptr);
		free((*cub)->mlx.mlx_ptr);
		exit(0);
	}
	// printf("key: %d\n", key);
	if (key == XK_w)
		(*cub)->distance -= 2;
	if (key == XK_s)
		(*cub)->distance += 2;
	return (0);
}

int	ft_close(t_cub **cub)
{
	deal_key(XK_Escape, cub);
	return (0);
}

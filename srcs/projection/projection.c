/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/28 18:54:41 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_backgroud(t_cub **cub)
{
	int	x;
	int	y;

	y = 0;
	while (y <= WINDOW_WIDTH)
	{
		x = 0;
		while (x <= WINDOW_HEIGHT)
		{
			img_pix_put(&(*cub)->mlx.img, y, x, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_line(t_cub **cub)
{
	int		i;
	int		j;
	double	angle;
	double	wall_heigth;

	i = 0;
	angle = 0;
	while (i < WINDOW_WIDTH)
	{
		(*cub)->distance = get_vector_distance(3, 3, angle, (*cub)->parsing);
		// printf("distance: %f\n", (*cub)->distance);
		wall_heigth = (10 / (*cub)->distance) * 300;
		// printf("wall_height: %f\n", wall_heigth);
		j = (WINDOW_HEIGHT / 2) - ((int)wall_heigth / 2);
		// printf("j: %d\n", j);
		while (j < (int)wall_heigth)
		{
			img_pix_put(&(*cub)->mlx.img, i, j, 0x00FF6F06);
			j++;
		}

		i++;
		angle += 0.0428;
	}
}

void	move_player(t_cub **cub)
{
	
	printf("x: %f, y: %f, vision: %f\n", (*cub)->player_x, (*cub)->player_y, (*cub)->vision);
}

int	draw(t_cub **cub)
{
	draw_backgroud(cub);
	move_player(cub);
	draw_line(cub);
	mlx_put_image_to_window((*cub)->mlx.mlx_ptr, (*cub)->mlx.win_ptr, (*cub)->mlx.img.mlx_img, -1, 0);
	return (0);
}

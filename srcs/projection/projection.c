/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/14 19:27:20 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil(t_cub *cub, int i, int j)
{
	int incr;

	incr = 0;
	while (incr < j)
	{
		img_pix_put(&cub->mlx.img, i, incr, convert_color(cub->parsing.rgb_plafond));
		incr++;
	}
}

void	draw_floor(t_cub *cub, int i, int j)
{
	while (j < WINDOW_HEIGHT)
	{
		img_pix_put(&cub->mlx.img, i, j, convert_color(cub->parsing.rgb_floor));
		j++;
	}
}

void    draw_wall(t_cub *cub, int i, int j, double wall_heigth, int wall_orientation)
{
    while (j < (int)wall_heigth)
    {
        if (wall_orientation == VERTICAL_HIT)
            img_pix_put(&cub->mlx.img, i, j, 0x00FF0000);
        else
            img_pix_put(&cub->mlx.img, i, j, 0x000000FF);
        j++;
    }
}

void	draw_line(t_cub *cub)
{
	int		i;
	int		j;
	double	angle;
	double	wall_heigth;
	double angle_dif = 30;
	t_dda_return *dda_return;

	i = 0;
	angle = cub->vision - 30;
	if (angle < 0)
		angle += 360;
	// printf("angle: %f\n", cub->vision);
	// printf("------------------------------------------------\n");
	while (i < WINDOW_WIDTH)
	{
		if (angle >= 360)
		{
			angle = angle - 360;
			continue;
		}
		if (angle < 0)
		{
			angle = angle + 360;
			continue;
		}
		dda_return = get_vector_distance(cub->player_x, cub->player_y, angle, cub->parsing);
		dda_return->distance = sin((90 - angle_dif) * (M_PI / 180)) * dda_return->distance;
		// if (i == WINDOW_WIDTH / 2)
		// 	printf("FUUUUUUUUUUUUUUUUUUUUUUCKED UP WALL HERE :");
		// printf("x=%f y=%f angle=%f distance: %f\n", cub->player_x, cub->player_y, angle, distance);
		wall_heigth = (10 / dda_return->distance) * 225;
		if (wall_heigth < 300)
			wall_heigth = 300;
		// printf("wall_height: %f\n", wall_heigth);
		j = (WINDOW_HEIGHT / 2) - (int)(wall_heigth / 2);
		// printf("j: %d\n", j);
		draw_ceil(cub, i, j);
		draw_wall(cub, i, j, wall_heigth, dda_return->wall_orientation);
		draw_floor(cub, i, wall_heigth);
		i++;
		angle += 0.0428;
		angle_dif -= 0.0428;
	}
}

int	draw(t_cub *cub)
{
	// printf("x: %f, y: %f, vision: %f\n", cub->player_x, cub->player_y, cub->vision);
	draw_line(cub);
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
	return (0);
}

int	draw_test_move(t_cub *cub)
{
	int i = 350;
	int j;
	// draw_backgroud(cub);
	printf("x: %f, y: %f, vision: %f\n", cub->player_x * 20, cub->player_y * 20, cub->vision);
	while (i < 400)
	{
		j = 450;
		while (j < 500)
		{
			img_pix_put(&cub->mlx.img, (cub->player_x * 30 + i), (cub->player_y * 30 + j),  0x00FF6F06);
			j++;
		}
		i++;
	}
	// while (i < 400)
	// {
	// 	j = 450;
	// 	while (j < 500)
	// 	{
	// 		img_pix_put(&cub->mlx.img, cub->player_x + i, cub->player_y + j,  0x00FF6F06);
	// 		j++;
	// 	}
	// 	i++;
	// }
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
	return (0);
}

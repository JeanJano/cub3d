/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/17 16:57:35 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil(int x_pixel_draw, int *y_pixel_draw, int size, t_cub *cub)
{
	while (*y_pixel_draw < size)
	{
		// printf("%d\n", *y_pixel_draw);
		img_pix_put(&cub->mlx.img, x_pixel_draw, *y_pixel_draw, convert_color(cub->parsing.rgb_plafond));
		(*y_pixel_draw)++;
	}
}

void	draw_floor(int x_pixel_draw, int y_pixel_draw, int size, t_cub *cub)
{
	int drawn_pixel = 0;

	while (drawn_pixel <= size)
	{
		img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, convert_color(cub->parsing.rgb_floor));
		y_pixel_draw--;
		drawn_pixel++;
	}
}

void    draw_wall(t_cub *cub, int x_pixel_draw, int y_pixel_draw, int wall_heigth, int wall_orientation)
{
	int drawn_pixel = 0;

    while (drawn_pixel <= wall_heigth)
    {
        if (wall_orientation == VERTICAL_HIT)
            img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, 0x00FF0000);
        else
            img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, 0x000000FF);
        y_pixel_draw++;
		drawn_pixel++;
    }
}

void	draw_line(t_cub *cub)
{
	int		i;
	double	angle;
	double	wall_heigth;
	double angle_dif = 30;
	t_dda_return *dda_return;
	int y_pixel_draw;
	i = 0;
	angle = cub->vision - 30;
	if (angle < 0)
		angle += 360;
	// printf("angle: %f\n", cub->vision);
	// printf("------------------------------------------------\n");
	while (i < WINDOW_WIDTH)
	{
		y_pixel_draw = 0;
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
		wall_heigth = 64 / dda_return->distance * 20;
		// if (wall_heigth < 300)
		// 	wall_heigth = 300;
		// printf("wall_height: %f\n", wall_heigth);
		// printf("j: %d\n", j);
		draw_ceil(i, &y_pixel_draw, ((WINDOW_HEIGHT - (int)(wall_heigth)) / 2), cub);
		draw_wall(cub, i, y_pixel_draw, (int)wall_heigth, dda_return->wall_orientation);
		draw_floor(i, WINDOW_HEIGHT, ((WINDOW_HEIGHT - (int)(wall_heigth)) / 2), cub);
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

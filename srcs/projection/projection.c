/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/29 15:00:13 by jsauvage         ###   ########.fr       */
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

void draw_pix(int x, int y, int *pixel_ptr, t_cub *cub, int size)
{
	for (int i = 0; i < size ; i++)
		img_pix_put(&cub->mlx.img, x, y + i, *pixel_ptr);
}

int get_hit_value(double hit_coord)
{
	hit_coord = (hit_coord - floor(hit_coord)) * 100;
	hit_coord = round(hit_coord);
	hit_coord = hit_coord / 100 * 64;
	if (hit_coord >= 64)
		return (63);
	return((int)hit_coord);
}

void draw_column(int x_pixel_draw, int y_pixel_draw, int *pixel_ptr, t_cub *cub, int height)
{
	int increment_value;
	double pixel_ratio;

	increment_value = cub->texture.north.line_len / 4;
	if (height > increment_value)
	{
		pixel_ratio = height / (double)increment_value;
		pixel_ratio = ceil(pixel_ratio);
		// printf("ceil=%f int=%d\n", pixel_ratio, (int)pixel_ratio);
		for (int y = y_pixel_draw ; y < y_pixel_draw + height ; y += (int)pixel_ratio)
		{
			draw_pix(x_pixel_draw, y, pixel_ptr, cub, (int)pixel_ratio);
			pixel_ptr += increment_value;
			// printf("y=%d\n", y);
		}
	}
	else
	{
		pixel_ratio = floor(1 / (double)height * 64);
		printf("%f\n", pixel_ratio);
		for (int y = y_pixel_draw ; y < y_pixel_draw + height ; y++)
		{
			draw_pix(x_pixel_draw, y, pixel_ptr, cub, 1);
			pixel_ptr += increment_value * (int)pixel_ratio;
		}
	}
	// printf("len=%d\n", cub->texture.north.line_len / 4);
	// for (int y = y_pixel_draw ; y < y_pixel_draw + height && y < WINDOW_HEIGHT ; y++)
	// 	img_pix_put(&cub->mlx.img, x_pixel_draw, y, 0x00FFFFFF);
}

int	draw_test_move(int x_pixel_draw, int y_pixel_draw, int wall_heigth, double index_hit, t_cub *cub)
{
	// draw_backgrdoud(cub);
	int	*pixel_cpy;
	int	*pixel_ptr;

	pixel_cpy = (int *)(cub->texture.north.addr);
	pixel_ptr = pixel_cpy;
	// for (int y = 0 ; y < 64 * 4 ; y += 4)
	// {
	// 	for (int x = 0 ; x < 64 * 1 ; x += 4)
	// 	{
	// 		draw_pix(x, y, pixel_ptr, cub, 4);
	// 		pixel_ptr++;
	// 	}
	// }
	int hit_value = get_hit_value(index_hit);
	// int wall_heigth = 50;
	pixel_ptr = pixel_cpy;
	pixel_ptr += hit_value;
	draw_column(x_pixel_draw, y_pixel_draw, pixel_ptr, cub, wall_heigth);
	// for (int i = 0;i < 60;i++)
	// 	img_pix_put(&cub->mlx.img, 397, i, 0x00FFFFFF);

	
	// mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
	return (0);
}

void	draw_wall(t_cub *cub, int x_pixel_draw, int y_pixel_draw, int wall_heigth, int wall_orientation, int i, double index_hit)
{
	int	drawn_pixel;

	drawn_pixel = 0;
	if (wall_orientation == NORTH_WALL)
		draw_test_move(x_pixel_draw, y_pixel_draw, wall_heigth, index_hit, cub);
	else
	{
		while (drawn_pixel <= wall_heigth && drawn_pixel <= WINDOW_HEIGHT)
		{
			if (wall_orientation == SOUTH_WALL)
			{
				img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, 0x00da291a);
			}
			else if (wall_orientation == EST_WALL)
			{
				img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, 0x00720117);
			}
			else if (wall_orientation == WEST_WALL)
			{
				img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, 0x007ddc1f);
			}
			y_pixel_draw++;
			drawn_pixel++;
		}
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
	int		line_len = 0;

	i = 0;
	angle = cub->vision - 30;
	if (angle < 0)
		angle += 360;
	// printf("test: %f\n", 64 / 0);
	// printf("------------------------------------------------\n");
	// printf("player x=%f y=%f", cub->player_x, cub->player_y);
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
		if (dda_return->distance == 0)
			wall_heigth = WINDOW_HEIGHT;
		else
			wall_heigth = 64 / dda_return->distance * 20;
		// printf("angle=%f dist=%f wall_h=%f\n", angle, dda_return->distance, wall_heigth);

		draw_ceil(i, &y_pixel_draw, ((WINDOW_HEIGHT - (int)(wall_heigth)) / 2), cub);
		draw_wall(cub, i, y_pixel_draw, (int)wall_heigth, dda_return->wall_orientation2, line_len, dda_return->index_hit_column);
		draw_floor(i, WINDOW_HEIGHT, ((WINDOW_HEIGHT - (int)(wall_heigth)) / 2), cub);
		i++;
		angle += 0.0428;
		angle_dif -= 0.0428;
		line_len++;
		if (line_len >= cub->texture.north.line_len / 5)
			line_len = 0;
		free(dda_return);
	}
}

int	draw(t_cub *cub)
{
	// printf("x: %f, y: %f, vision: %f\n", cub->player_x, cub->player_y, cub->vision);
	draw_line(cub);
	// mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->texture.north, 3, 3);
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
	return (0);
}

static void	draw_backgroud(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y <= WINDOW_WIDTH)
	{
		x = 0;
		while (x <= WINDOW_HEIGHT)
		{
			img_pix_put(&cub->mlx.img, y, x, 0x00000000);
			x++;
		}
		y++;
	}
}

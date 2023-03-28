/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/28 19:54:55 by jsauvage         ###   ########.fr       */
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

void	draw_wall(t_cub *cub, int x_pixel_draw, int y_pixel_draw, int wall_heigth, int wall_orientation, int i, double index_hit)
{
	int	drawn_pixel = 0;
	int	*north_ptr;
	int	*south_ptr;
	int	*east_ptr;
	int	*west_ptr;
	int	col;


	(void)i;
	//mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->texture.north, x_pixel_draw, y_pixel_draw);
	north_ptr = ((int *)cub->texture.north.addr);
	south_ptr = ((int *)cub->texture.south.addr);
	east_ptr = ((int *)cub->texture.east.addr);
	west_ptr = ((int *)cub->texture.west.addr);
	// printf("bpp: %d\n", cub->texture.north.bpp);
	// printf("line len: %d\n", cub->texture.north.line_len);
	// printf("line_len: %d\n", line_len);
	// printf("%d\n", *(north_ptr + (int)(((float)drawn_pixel / wall_heigth) * 50700)));
	// printf("ratio: %d\n", 255 / cub->texture.north.bpp);
	while (drawn_pixel <= wall_heigth)
	{
		// printf("%f\n", (float)drawn_pixel / wall_heigth);
		// printf("ratio: %f\n", ((float)drawn_pixel / wall_heigth) * 100000);
		// col = *(north_ptr + ((drawn_pixel / wall_heigth) * 1000));
		if (wall_orientation == NORTH_WALL)
		{
			// printf("i: %d\n", i);
			// col = *(north_ptr + (int)(((float)drawn_pixel / wall_heigth) * 50000));
			col = *(north_ptr + (int)(((float)drawn_pixel / wall_heigth) * index_hit));
			img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, col);
		}
		// else if (wall_orientation == SOUTH_WALL)
		// {
		// 	col = *(south_ptr + (int)(((float)drawn_pixel / wall_heigth) * 50000));
		// 	img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, col);
		// }
		// else if (wall_orientation == EST_WALL)
		// {
		// 	col = *(east_ptr + (int)(((float)drawn_pixel / wall_heigth) * 50000));
		// 	img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, col);
		// }
		// else if (wall_orientation == WEST_WALL)
		// {
		// 	col = *(west_ptr + (int)(((float)drawn_pixel / wall_heigth) * 50000));
		// 	img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, col);
		// }
		y_pixel_draw++;
		drawn_pixel++;
	}
	//mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->texture.north.mlx_img, 0, 0);
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
		// mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->texture.north, i, y_pixel_draw);
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

int	draw_test_move(t_cub *cub)
{
	int i = 0;
	int j;
	draw_backgroud(cub);
	int col;
	int	*north_ptr;

	north_ptr = ((int *)cub->texture.north.addr);
	while (north_ptr)
	{
		printf("%x\n", north_ptr);
		north_ptr++;
	}
	int height;
	int width;

	// void	*img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, "./assets/dirt.xpm", &height, &width);
	// mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, img, 10, 10);
	//image
	// while (i < 800)
	// {
	// 	j = 0;
	// 	while (j < 500)
	// 	{
	// 		col = *(north_ptr + (int)(((float)i / j) * 0.1 * 50000));
	// 		img_pix_put(&cub->mlx.img, i, j, col);
	// 		j++;
	// 	}
	// 	i++;
	// }

	// deplacement
	// printf("x: %f, y: %f, vision: %f\n", cub->player_x * 20, cub->player_y * 20, cub->vision);
	// while (i < 400)
	// {
	// 	j = 450;
	// 	while (j < 500)
	// 	{
	// 		img_pix_put(&cub->mlx.img, (cub->player_x * 30 + i), (cub->player_y * 30 + j),  0x00FF6F06);
	// 		j++;
	// 	}
	// 	i++;
	// }
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

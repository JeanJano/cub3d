/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/03 14:43:20 by jsauvage         ###   ########.fr       */
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
	// printf("ceil size=%d\n", size);
}

void	draw_floor(int x_pixel_draw, int y_pixel_draw, t_cub *cub)
{
	while (y_pixel_draw < WINDOW_HEIGHT)
	{
		img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw, convert_color(cub->parsing.rgb_floor));
		y_pixel_draw++;
	}
	// printf("floor size=%d\n---\n", size);
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

int *get_corresponding_pixel(int *pixel_ptr, int line, int increment_value)
{
	int *return_value;

	if (line == 64)
		line = 63;
	// printf("%d\n", line);
	return_value = pixel_ptr + (line * increment_value);
	return (return_value);
}

void overwall_skip(int *y, int wall_height)
{
	int overwall;

	overwall = (wall_height - WINDOW_HEIGHT) / 2;
	while (*y < overwall)
		(*y)++;
}

void draw_column(int x_pixel_draw, int *y_pixel_draw, int wall_height, double index_hit, t_cub *cub, char *texture)
{
	int y;
	int hit_value;
	int	*pixel_ptr;
	int increment_value;
	int *corresponding_pixel;
	int wall_pixel_y;

	y = 0;
	wall_pixel_y = 0;
	pixel_ptr = (int *)texture;
	hit_value = get_hit_value(index_hit);
	pixel_ptr += hit_value;
	increment_value = cub->texture.north.line_len / 4; // to change

	if (wall_height > WINDOW_HEIGHT)
		overwall_skip(&wall_pixel_y, wall_height);
	while (y < wall_height && *y_pixel_draw < WINDOW_HEIGHT)
	{
		corresponding_pixel = get_corresponding_pixel(pixel_ptr, (int)(((double)wall_pixel_y / ((double)wall_height - 1)) * 64), increment_value);
		img_pix_put(&cub->mlx.img, x_pixel_draw, *y_pixel_draw, *corresponding_pixel);
		wall_pixel_y++;
		y++;
		(*y_pixel_draw)++;
	}
}

void	draw_wall(t_cub *cub, int x_pixel_draw, int *y_pixel_draw, int wall_height, int wall_orientation, int i, double index_hit)
{
	int	drawn_pixel;

	drawn_pixel = 0;
	if (wall_orientation == NORTH_WALL)
		draw_column(x_pixel_draw, y_pixel_draw, wall_height, index_hit, cub, cub->texture.north.addr);
	else if (wall_orientation == SOUTH_WALL)
		draw_column(x_pixel_draw, y_pixel_draw, wall_height, index_hit, cub, cub->texture.south.addr);
	else if (wall_orientation == EST_WALL)
		draw_column(x_pixel_draw, y_pixel_draw, wall_height, index_hit, cub, cub->texture.east.addr);
	else if (wall_orientation == WEST_WALL)
		draw_column(x_pixel_draw, y_pixel_draw, wall_height, index_hit, cub, cub->texture.west.addr);
}

void	draw_line(t_cub *cub)
{
	int		i;
	double	angle;
	double	wall_height;
	double angle_dif = 30;
	t_dda_return *dda_return;
	int y_pixel_draw;
	int		line_len = 0;

	i = 0;
	angle = cub->vision - 30;
	if (angle < 0)
		angle += 360;

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
			wall_height = WINDOW_HEIGHT;
		else
			wall_height = 64 / dda_return->distance * 20;
		if ((int)wall_height % 2 == 1)
			wall_height++;
		draw_ceil(i, &y_pixel_draw, ((WINDOW_HEIGHT - (int)(wall_height)) / 2), cub);
		draw_wall(cub, i, &y_pixel_draw, (int)wall_height, dda_return->wall_orientation2, line_len, dda_return->index_hit_column);
		draw_floor(i, y_pixel_draw, cub);
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
	draw_line(cub);
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

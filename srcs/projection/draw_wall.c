/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:51:07 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/11 18:14:11 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_hit_value(double hit_coord)
{
	hit_coord = (hit_coord - floor(hit_coord)) * 100;
	hit_coord = round(hit_coord);
	hit_coord = hit_coord / 100 * 64;
	if (hit_coord >= 64)
		return (63);
	return ((int)hit_coord);
}

int	*get_corresponding_pixel(int *pixel_ptr, int line, int increment_value)
{
	int	*return_value;

	if (line == 64)
		line = 63;
	return_value = pixel_ptr + (line * increment_value);
	return (return_value);
}

void	overwall_skip(int *y, int wall_height)
{
	int	overwall;

	overwall = (wall_height - WINDOW_HEIGHT) / 2;
	*y += overwall;
}

void	draw_column(t_draw *draw, double index_hit, t_cub *cub, char *texture)
{
	int	y;
	int	*pixel_ptr;
	int	increment_value;
	int	*corresponding_pixel;

	y = 0;
	draw->wall_pixel_y = 0;
	pixel_ptr = (int *)texture;
	draw->hit_value = get_hit_value(index_hit);
	pixel_ptr += draw->hit_value;
	increment_value = cub->texture.north.line_len / 4;
	if (draw->wall_height > WINDOW_HEIGHT)
		overwall_skip(&draw->wall_pixel_y, draw->wall_height);
	while (y < draw->wall_height && draw->y_pixel_draw < WINDOW_HEIGHT)
	{
		corresponding_pixel = get_corresponding_pixel(pixel_ptr,
				(int)(((double)draw->wall_pixel_y / (draw->wall_height - 1))
					* 64), increment_value);
		img_pix_put(&cub->mlx.img, draw->x_pixel_draw, draw->y_pixel_draw,
			*corresponding_pixel);
		draw->wall_pixel_y++;
		y++;
		(draw->y_pixel_draw)++;
	}
}

void	draw_wall(t_cub *cub, t_draw *draw, t_dda_return *dda_return)
{
	int	drawn_pixel;

	drawn_pixel = 0;
	if (dda_return->wall_orientation2 == NORTH_WALL)
		draw_column(draw,
			dda_return->index_hit_column, cub, cub->texture.north.addr);
	else if (dda_return->wall_orientation2 == SOUTH_WALL)
		draw_column(draw,
			dda_return->index_hit_column, cub, cub->texture.south.addr);
	else if (dda_return->wall_orientation2 == EST_WALL)
		draw_column(draw,
			dda_return->index_hit_column, cub, cub->texture.east.addr);
	else if (dda_return->wall_orientation2 == WEST_WALL)
		draw_column(draw,
			dda_return->index_hit_column, cub, cub->texture.west.addr);
}

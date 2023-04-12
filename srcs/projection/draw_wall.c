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

	overwall = (int)((wall_height - WINDOW_HEIGHT) / 2);
	*y += overwall;
}

void	draw_column(t_draw *draw, int wall_height, double index_hit, t_cub *cub)
{
	int	y;
	int	*pixel_ptr;
	int	increment_value;
	int	*corresponding_pixel;
	int	line;

	y = 0;
	draw->wall_pixel_y = 0;
	pixel_ptr = (int *)draw->texture.addr;
	pixel_ptr += get_hit_value(index_hit);
	increment_value = draw->texture.line_len / 4;
	if (wall_height > WINDOW_HEIGHT)
		overwall_skip(&draw->wall_pixel_y, wall_height);
	while (y < WINDOW_HEIGHT && y < wall_height)
	{
		line = (int)(((double)draw->wall_pixel_y / ((double)wall_height - 1))
				* 64);
		img_pix_put(&cub->mlx.img, draw->x_pixel_draw, draw->y_pixel_draw,
			*get_corresponding_pixel(pixel_ptr, line, increment_value));
		draw->wall_pixel_y++;
		y++;
		draw->y_pixel_draw++;
	}
}

void	draw_wall(t_cub *cub, t_draw *draw, t_dda_return *dda_return)
{
	int	drawn_pixel;

	drawn_pixel = 0;
	if (dda_return->wall_orientation == NORTH_WALL)
		draw->texture = cub->texture.north;
	else if (dda_return->wall_orientation == SOUTH_WALL)
		draw->texture = cub->texture.south;
	else if (dda_return->wall_orientation == EST_WALL)
		draw->texture = cub->texture.east;
	else if (dda_return->wall_orientation == WEST_WALL)
		draw->texture = cub->texture.west;
	draw_column(draw, draw->wall_height, dda_return->index_hit, cub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:06 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/12 17:39:49 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil(t_draw *draw, int wall_height, t_cub *cub)
{
	int	size;

	if ((int)(wall_height) >= WINDOW_HEIGHT)
		return ;
	size = ((WINDOW_HEIGHT - (int)(wall_height)) / 2);
	while (draw->y_pixel_draw < size)
	{
		img_pix_put(&cub->mlx.img, draw->x_pixel_draw, draw->y_pixel_draw,
			convert_color(cub->parsing.rgb_plafond));
		draw->y_pixel_draw++;
	}
}

void	draw_floor(int x_pixel_draw, int y_pixel_draw, t_cub *cub)
{
	while (y_pixel_draw < WINDOW_HEIGHT)
	{
		img_pix_put(&cub->mlx.img, x_pixel_draw, y_pixel_draw,
			convert_color(cub->parsing.rgb_floor));
		y_pixel_draw++;
	}
}

int	draw_init(t_draw *draw, int i)
{
	draw->y_pixel_draw = 0;
	draw->x_pixel_draw = i;
	draw->hit_value = 0;
	if (draw->angle >= 360)
	{
		draw->angle = draw->angle - 360;
		return (0);
	}
	if (draw->angle < 0)
	{
		draw->angle = draw->angle + 360;
		return (0);
	}
	return (1);
}

int	draw_line(t_cub *cub, t_draw *draw, t_dda_return *dda_return, int i)
{
	int	y;

	y = 0;
	dda_return = get_dist(cub->player_x, cub->player_y,
			draw->angle, cub->parsing);
	dda_return->distance = sin((90 - draw->angle_dif) * (M_PI / 180))
		* dda_return->distance;
	if (dda_return->distance == 0)
		draw->wall_height = WINDOW_HEIGHT;
	else
		draw->wall_height = 64 / dda_return->distance * 20;
	if ((int)draw->wall_height % 2 == 1)
		draw->wall_height++;
	draw_ceil(draw, (int)draw->wall_height, cub);
	draw_wall(cub, draw, dda_return);
	draw_floor(i, draw->y_pixel_draw, cub);
	free(dda_return);
	return (1);
}

int	draw(t_cub *cub)
{
	t_dda_return	*dda_return;
	t_draw			draw;
	int				i;

	i = 0;
	draw.angle = cub->vision - 30;
	if (draw.angle < 0)
		draw.angle += 360;
	draw.angle_dif = 30;
	while (i < WINDOW_WIDTH)
	{
		if (draw_init(&draw, i) == 0)
			continue ;
		if (draw_line(cub, &draw, dda_return, i) == 0)
			continue ;
		draw.angle += 0.0428;
		draw.angle_dif -= 0.0428;
		i++;
	}
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr,
		cub->mlx.img.mlx_img, -1, 0);
	return (0);
}

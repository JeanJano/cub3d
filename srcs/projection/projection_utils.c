/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:53:58 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/11 18:32:07 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || x < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	convert_color(int *color_tab)
{
	int	color;

	color = color_tab[2];
	color += color_tab[1] << 8;
	color += color_tab[0] << 16;
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:25:38 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/12 15:43:27 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_move_right(t_cub *cub, double x_move_to, double y_move_to)
{
	if (cub->parsing.map[(int)y_move_to][(int)x_move_to] == 1)
		return (1);
	return (0);
}

void	calculate_move(t_cub *cub, double *x_move_to, double *y_move_to)
{
	if (cub->vision > 0 && cub->vision < 90)
	{
		*x_move_to -= sin(cub->vision * (M_PI / 180)) * cub->move_incr;
		*y_move_to += cos(cub->vision * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 90 && cub->vision < 180)
	{
		*x_move_to -= sin((180 - cub->vision) * (M_PI / 180)) * cub->move_incr;
		*y_move_to -= cos((180 - cub->vision) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 180 && cub->vision < 270)
	{
		*x_move_to -= sin(cub->vision * (M_PI / 180)) * cub->move_incr;
		*y_move_to += cos(cub->vision * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 270 && cub->vision < 360)
	{
		*x_move_to -= sin((cub->vision) * (M_PI / 180)) * cub->move_incr;
		*y_move_to += cos((cub->vision) * (M_PI / 180)) * cub->move_incr;
	}
}

void	move_right(t_cub *cub)
{
	double	x_move_to;
	double	y_move_to;

	x_move_to = cub->player_x;
	y_move_to = cub->player_y;
	calculate_move(cub, &x_move_to, &y_move_to);
	if (cub->vision == 0 || cub->vision == 360)
		y_move_to += cub->move_incr;
	else if (cub->vision == 90)
		x_move_to -= cub->move_incr;
	else if (cub->vision == 180)
		y_move_to -= cub->move_incr;
	else if (cub->vision == 270)
		x_move_to += cub->move_incr;
	if (check_move_right(cub, x_move_to, y_move_to))
		return ;
	cub->player_x = x_move_to;
	cub->player_y = y_move_to;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:25:38 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/08 15:27:10 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub *cub)
{
	double x_move_to = cub->player_x;
	double y_move_to = cub->player_y;

	printf("MOVE FORWARD\n");
	if (cub->vision > 0 && cub->vision < 90)
	{
		x_move_to += sin(((90 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((90 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 90 && cub->vision < 180)
	{
		x_move_to -= sin(((cub->vision) - 90) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((cub->vision) - 90) * (M_PI / 180)) * cub->move_incr;

	}
	else if (cub->vision > 180 && cub->vision < 270)
	{
		x_move_to -= sin(((270 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos(((270 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 270 && cub->vision < 360)
	{
		x_move_to += sin((cub->vision - 270) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos((cub->vision - 270) * (M_PI / 180)) * cub->move_incr;	
	}
	else if (cub->vision == 0 || cub->vision == 360)
		x_move_to += cub->move_incr;
	else if (cub->vision == 90)
		y_move_to += cub->move_incr;
	else if (cub->vision == 180)
		x_move_to -= cub->move_incr;
	else if (cub->vision == 270)
		y_move_to -= cub->move_incr;

	if (cub->parsing.map[(int)y_move_to][(int)x_move_to] == 1)
	{
		printf("CANT GO WALL\n");
		return ;
	}
	cub->player_x = x_move_to;
	cub->player_y = y_move_to;
	printf("x=%f y=%f int_x=%d int_y=%d map_value=%d\n", cub->player_x, cub->player_y, (int)cub->player_x, (int)cub->player_y, cub->parsing.map[(int)y_move_to][(int)x_move_to]);
}

void	move_backward(t_cub *cub)
{
	double x_move_to = cub->player_x;
	double y_move_to = cub->player_y;

	if (cub->vision > 0 && cub->vision < 90)
	{
		x_move_to -= sin(((90 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos(((90 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 90 && cub->vision < 180)
	{
		x_move_to += sin(((cub->vision) - 90) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos(((cub->vision) - 90) * (M_PI / 180)) * cub->move_incr;

	}
	else if (cub->vision > 180 && cub->vision < 270)
	{
		x_move_to += sin(((270 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((270 - cub->vision)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 270 && cub->vision < 360)
	{
		x_move_to -= sin((cub->vision - 270) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos((cub->vision - 270) * (M_PI / 180)) * cub->move_incr;	
	}
	else if (cub->vision == 0 || cub->vision == 360)
		x_move_to -= cub->move_incr;
	else if (cub->vision == 90)
		y_move_to -= cub->move_incr;
	else if (cub->vision == 180)
		x_move_to += cub->move_incr;
	else if (cub->vision == 270)
		y_move_to += cub->move_incr;
	
	if (cub->parsing.map[(int)y_move_to][(int)x_move_to] == 1)
	{
		printf("CANT GO WALL\n");
		return ;
	}
	cub->player_x = x_move_to;
	cub->player_y = y_move_to;
	printf("x=%f y=%f int_x=%d int_y=%d map_value=%d\n", cub->player_x, cub->player_y, (int)cub->player_x, (int)cub->player_y, cub->parsing.map[(int)y_move_to][(int)x_move_to]);
}

void	move_left(t_cub *cub)
{
	double x_move_to = cub->player_x;
	double y_move_to = cub->player_y;

	if (cub->vision > 0 && cub->vision < 90)
	{
		x_move_to += sin(((cub->vision + 270) - 270) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos(((cub->vision + 270) - 270) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 90 && cub->vision < 180)
	{
		x_move_to += sin(((90 - (cub->vision - 90))) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((90 - (cub->vision - 90))) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 180 && cub->vision < 270)
	{
		x_move_to -= sin((((cub->vision) - 90) - 90) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos((((cub->vision) - 90) - 90) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 270 && cub->vision < 360)
	{
		x_move_to -= sin(((270 - (cub->vision) + 90)) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos(((270 - (cub->vision) + 90)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision == 0 || cub->vision == 360)
		y_move_to -= cub->move_incr;
	else if (cub->vision == 90)
		x_move_to += cub->move_incr;
	else if (cub->vision == 180)
		y_move_to += cub->move_incr;
	else if (cub->vision == 270)
		x_move_to -= cub->move_incr;

	if (cub->parsing.map[(int)y_move_to][(int)x_move_to] == 1)
	{
		printf("CANT GO WALL\n");
		return ;
	}
	cub->player_x = x_move_to;
	cub->player_y = y_move_to;
	printf("x=%f y=%f int_x=%d int_y=%d map_value=%d\n", cub->player_x, cub->player_y, (int)cub->player_x, (int)cub->player_y, cub->parsing.map[(int)y_move_to][(int)x_move_to]);
}

void	move_right(t_cub *cub)
{
	double x_move_to = cub->player_x;
	double y_move_to = cub->player_y;
	
	if (cub->vision > 0 && cub->vision < 90)
	{
		x_move_to -= sin(((cub->vision + 270) - 270) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((cub->vision + 270) - 270) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 90 && cub->vision < 180)
	{
		x_move_to -= sin(((90 - (cub->vision - 90))) * (M_PI / 180)) * cub->move_incr;
		y_move_to -= cos(((90 - (cub->vision - 90))) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 180 && cub->vision < 270)
	{
		x_move_to -= sin(((cub->vision)) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((cub->vision)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision > 270 && cub->vision < 360)
	{
		x_move_to += sin(((270 - (cub->vision) + 90)) * (M_PI / 180)) * cub->move_incr;
		y_move_to += cos(((270 - (cub->vision) + 90)) * (M_PI / 180)) * cub->move_incr;
	}
	else if (cub->vision == 0 || cub->vision == 360)
		y_move_to += cub->move_incr;
	else if (cub->vision == 90)
		x_move_to -= cub->move_incr;
	else if (cub->vision == 180)
		y_move_to -= cub->move_incr;
	else if (cub->vision == 270)
		x_move_to += cub->move_incr;

	if (cub->parsing.map[(int)y_move_to][(int)x_move_to] == 1)
	{
		printf("CANT GO WALL\n");
		return ;
	}
	cub->player_x = x_move_to;
	cub->player_y = y_move_to;
	printf("x=%f y=%f int_x=%d int_y=%d map_value=%d\n", cub->player_x, cub->player_y, (int)cub->player_x, (int)cub->player_y, cub->parsing.map[(int)y_move_to][(int)x_move_to]);
}

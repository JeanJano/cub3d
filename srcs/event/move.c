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

void	move_forward(t_cub **cub)
{
	if ((*cub)->vision > 0 && (*cub)->vision < 90)
	{
		(*cub)->player_x += sin(((90 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos(((90 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 90 && (*cub)->vision < 180)
	{
		(*cub)->player_x -= sin((((*cub)->vision) - 90) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos((((*cub)->vision) - 90) * (M_PI / 180)) * (*cub)->move_incr;

	}
	else if ((*cub)->vision > 180 && (*cub)->vision < 270)
	{
		(*cub)->player_x -= sin(((270 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos(((270 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 270 && (*cub)->vision < 360)
	{
		(*cub)->player_x += sin(((*cub)->vision - 270) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos(((*cub)->vision - 270) * (M_PI / 180)) * (*cub)->move_incr;	
	}
	else if ((*cub)->vision == 0 || (*cub)->vision == 360)
		(*cub)->player_x += (*cub)->move_incr;
	else if ((*cub)->vision == 90)
		(*cub)->player_y += (*cub)->move_incr;
	else if ((*cub)->vision == 180)
		(*cub)->player_x -= (*cub)->move_incr;
	else if ((*cub)->vision == 270)
		(*cub)->player_y -= (*cub)->move_incr;
}

void	move_backward(t_cub **cub)
{
	if ((*cub)->vision > 0 && (*cub)->vision < 90)
	{
		(*cub)->player_x -= sin(((90 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos(((90 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 90 && (*cub)->vision < 180)
	{
		(*cub)->player_x += sin((((*cub)->vision) - 90) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos((((*cub)->vision) - 90) * (M_PI / 180)) * (*cub)->move_incr;

	}
	else if ((*cub)->vision > 180 && (*cub)->vision < 270)
	{
		(*cub)->player_x += sin(((270 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos(((270 - (*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 270 && (*cub)->vision < 360)
	{
		(*cub)->player_x -= sin(((*cub)->vision - 270) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos(((*cub)->vision - 270) * (M_PI / 180)) * (*cub)->move_incr;	
	}
	else if ((*cub)->vision == 0 || (*cub)->vision == 360)
		(*cub)->player_x -= (*cub)->move_incr;
	else if ((*cub)->vision == 90)
		(*cub)->player_y -= (*cub)->move_incr;
	else if ((*cub)->vision == 180)
		(*cub)->player_x += (*cub)->move_incr;
	else if ((*cub)->vision == 270)
		(*cub)->player_y += (*cub)->move_incr;
}

void	move_left(t_cub **cub)
{
	if ((*cub)->vision > 0 && (*cub)->vision < 90)
	{
		(*cub)->player_x += sin((((*cub)->vision + 270) - 270) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos((((*cub)->vision + 270) - 270) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 90 && (*cub)->vision < 180)
	{
		(*cub)->player_x += sin(((90 - ((*cub)->vision - 90))) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos(((90 - ((*cub)->vision - 90))) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 180 && (*cub)->vision < 270)
	{
		(*cub)->player_x -= sin(((((*cub)->vision) - 90) - 90) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos(((((*cub)->vision) - 90) - 90) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 270 && (*cub)->vision < 360)
	{
		(*cub)->player_x -= sin(((270 - ((*cub)->vision) + 90)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos(((270 - ((*cub)->vision) + 90)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision == 0 || (*cub)->vision == 360)
		(*cub)->player_y -= (*cub)->move_incr;
	else if ((*cub)->vision == 90)
		(*cub)->player_x += (*cub)->move_incr;
	else if ((*cub)->vision == 180)
		(*cub)->player_y += (*cub)->move_incr;
	else if ((*cub)->vision == 270)
		(*cub)->player_x -= (*cub)->move_incr;
}

void	move_right(t_cub **cub)
{
	if ((*cub)->vision > 0 && (*cub)->vision < 90)
	{
		(*cub)->player_x -= sin((((*cub)->vision + 270) - 270) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos((((*cub)->vision + 270) - 270) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 90 && (*cub)->vision < 180)
	{
		(*cub)->player_x -= sin(((90 - ((*cub)->vision - 90))) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y -= cos(((90 - ((*cub)->vision - 90))) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 180 && (*cub)->vision < 270)
	{
		(*cub)->player_x -= sin((((*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos((((*cub)->vision)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision > 270 && (*cub)->vision < 360)
	{
		(*cub)->player_x += sin(((270 - ((*cub)->vision) + 90)) * (M_PI / 180)) * (*cub)->move_incr;
		(*cub)->player_y += cos(((270 - ((*cub)->vision) + 90)) * (M_PI / 180)) * (*cub)->move_incr;
	}
	else if ((*cub)->vision == 0 || (*cub)->vision == 360)
		(*cub)->player_y += (*cub)->move_incr;
	else if ((*cub)->vision == 90)
		(*cub)->player_x -= (*cub)->move_incr;
	else if ((*cub)->vision == 180)
		(*cub)->player_y -= (*cub)->move_incr;
	else if ((*cub)->vision == 270)
		(*cub)->player_x += (*cub)->move_incr;
}

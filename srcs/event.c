/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:25 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/06 18:35:10 by jsauvage         ###   ########.fr       */
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
	else if ((*cub)->vision == 0)
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
	else if ((*cub)->vision == 0)
		(*cub)->player_x -= (*cub)->move_incr;
	else if ((*cub)->vision == 90)
		(*cub)->player_y -= (*cub)->move_incr;
	else if ((*cub)->vision == 180)
		(*cub)->player_x += (*cub)->move_incr;
	else if ((*cub)->vision == 270)
		(*cub)->player_y += (*cub)->move_incr;
}

void	move_key(int key, t_cub **cub)
{
	if (key == XK_w /* && (*cub)->parsing.map[(int)(*cub)->player_x + 1][(int)(*cub)->player_y] != 1 */)
	{
		printf("w\n");
		move_forward(cub);
	}
	if (key == XK_s /* && (*cub)->parsing.map[(int)(*cub)->player_x - 1][(int)(*cub)->player_y] != 1 */)
	{
		printf("s\n");
		move_backward(cub);
	}
	
	// if (key == XK_a && (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y - 1] != 1)
	// {
	// 	// printf("map: %d\n", (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y]);
	// 	(*cub)->player_y -= (*cub)->move_incr;
	// }
	// if (key == XK_d && (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y + 1] != 1)
	// {
	// 	// printf("map: %d\n", (*cub)->parsing.map[(int)(*cub)->player_x][(int)(*cub)->player_y]);
	// 	(*cub)->player_y += (*cub)->move_incr;
	// }

	if (key == XK_Left)
	{
		printf("vision: %f\n", (*cub)->vision);
		(*cub)->vision -= (*cub)->vision_incr;
		if ((*cub)->vision <= 0)
			(*cub)->vision = 360;
	}
	if (key == XK_Right)
	{
		printf("vision: %f\n", (*cub)->vision);
		(*cub)->vision += (*cub)->vision_incr;
		if ((*cub)->vision >= 360)
			(*cub)->vision = 0;
	}
}

int	deal_key(int key, t_cub **cub)
{
	if (key == XK_Escape)
	{
		mlx_destroy_image((*cub)->mlx.mlx_ptr, (*cub)->mlx.img.mlx_img);
		mlx_destroy_window((*cub)->mlx.mlx_ptr, (*cub)->mlx.win_ptr);
		mlx_destroy_display((*cub)->mlx.mlx_ptr);
		free((*cub)->mlx.mlx_ptr);
		free_struct(cub);
		exit(0);
	}
	// printf("key: %d\n", key);
	move_key(key, cub);
	return (0);
}

int	ft_close(t_cub **cub)
{
	deal_key(XK_Escape, cub);
	return (0);
}

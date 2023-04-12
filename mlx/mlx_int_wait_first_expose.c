/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_wait_first_expose.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2023/02/09 17:08:48 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_int_wait_first_expose.c for minilibx in 
** 
** Made by olivier crouzet
** Login   <ol@epita.fr>
** 
** Started on  Tue Oct 17 09:26:45 2000 olivier crouzet
** Last update Fri Feb 23 17:27:10 2001 Charlie Root
*/



#include	"mlx_int.h"



int	mlx_int_wait_first_expose(t_xvar *xvar,Window win)
{
  XEvent	ev;

  XWindowEvent(xvar->display,win,ExposureMask,&ev);
  XPutBackEvent(xvar->display,&ev);
}

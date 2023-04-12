/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2023/02/09 17:08:48 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_destroy_window.c for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Tue Mar 12 10:25:15 2002 Charlie Root
** Last update Tue May 15 16:46:08 2007 Olivier Crouzet
*/


#include	"mlx_int.h"


int	mlx_destroy_window(t_xvar *xvar,t_win_list *win)
{
  t_win_list	*w;
  t_win_list	*prev;
  t_win_list	first;

  first.next = xvar->win_list;
  prev = &first;
  w = prev->next;
  while (w)
    {
      if (w==win)
	prev->next = w->next;
      else
	prev = w;
      w = w->next;
    }
  xvar->win_list = first.next;
  XDestroyWindow(xvar->display,win->window);
  XFreeGC(xvar->display,win->gc);
  free(win);
  if (xvar->do_flush)
    XFlush(xvar->display);
}

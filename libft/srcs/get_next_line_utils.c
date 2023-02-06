/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:57:36 by jsauvage          #+#    #+#             */
/*   Updated: 2022/08/31 15:29:27 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	found_nl(t_gnl *tmp)
{
	int		i;
	t_gnl	*current;

	if (tmp == NULL)
		return (0);
	current = ft_lstlast_gnl(tmp);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_gnl	*ft_lstlast_gnl(t_gnl *tmp)
{
	t_gnl	*current;

	current = tmp;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(char **line, t_gnl *tmp)
{
	int	i;
	int	len;

	len = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		tmp = tmp->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_tmp(t_gnl *tmp)
{
	t_gnl	*current;
	t_gnl	*next;

	current = tmp;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

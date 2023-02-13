/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:39:05 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/13 18:43:01 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to do :
// 	la carte doit etre uniquement compose de : 0; 1; N; S; E; W; ' '
// 	la carte doit etre entoure de mur

int	check_valid_map(t_parsing *parsing)
{
	return (TRUE);
}

void	error_message(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	check_extension(char *file_name)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strchr(file_name, '.');
	if (str == NULL)
		return (error_message("wrong extension file"), FALSE);
	if (str[0] == '.' && str[1] == 'c' && str[2] == 'u' && str[3] == 'b' && str[4] == '\0')
		return (TRUE);
	if (*str == '.')
		str++;
	check_extension(str);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:34:07 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/20 18:50:58 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_all_composant(int i)
{
	if (i == 0 || i == 1 || i == 676 || i == 78 || i == 87 || i == 69
		|| i == 83)
		return (TRUE);
	return (FALSE);
}

int	check_player_composant(int i)
{
	if (i == 78 || i == 87 || i == 69 || i == 83)
		return (TRUE);
	return (FALSE);
}

int	check_extension(char *file_name)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strchr(file_name, '.');
	if (str == NULL)
		return (FALSE);
	if (str[0] == '.' && str[1] == 'c' && str[2] == 'u' && str[3] == 'b'
		&& str[4] == '\0')
		return (TRUE);
	if (*str == '.')
		str++;
	check_extension(str);
	return (FALSE);
}

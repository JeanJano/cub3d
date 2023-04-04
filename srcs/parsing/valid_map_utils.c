/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:34:07 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/04 16:09:18 by jsauvage         ###   ########.fr       */
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

int	check_extension(char *file_name, char *extension)
{
	char	*str;

	if (file_name[0] == extension[0] && file_name[1] == extension[1]
		&& file_name[2] == extension[2] && file_name[3] == extension[3]
		&& file_name[4] == '\0')
		return (FALSE);
	str = ft_strrchr(file_name, '.');
	if (str == NULL)
		return (FALSE);
	if (str[0] == extension[0] && str[1] == extension[1]
		&& str[2] == extension[2] && str[3] == extension[3]
		&& str[4] == '\0')
		return (TRUE);
	return (FALSE);
}

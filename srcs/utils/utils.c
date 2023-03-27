/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:23:57 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/27 17:44:17 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_search(const char *big, const char *little, size_t len)
{
	size_t	l;
	int		i;

	while (*big == ' ')
		big++;
	l = len;
	i = 0;
	if (little[0] == 0)
		return (FALSE);
	while (*big && len)
	{
		if (*big == *little && !ft_strncmp(big, little, ft_strlen(little)) && (i
				+ ft_strlen(little) - 1) < l)
			return (TRUE);
		big++;
		len--;
		i++;
	}
	return (FALSE);
}

char	*strdup_no_breakline(char *line)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	error_message(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

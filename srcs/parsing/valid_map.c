/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:39:05 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/14 16:51:09 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to do :
// 	aucun vide ne peut toucher de zero

void	error_message(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	check_all_composant(int i)
{
	if (i == 0 || i == 1 || i == 676 || i ==  78 || i == 87 || i == 69
		|| i == 83)
		return (TRUE);
	return (FALSE);
}

int check_player_composant(int i)
{
	if (i ==  78 || i == 87 || i == 69 || i == 83)
		return (TRUE);
	return (FALSE);
}

int	get_number_player(t_parsing *parsing)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_player_composant(parsing->map[i][j]) == TRUE)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_map_composant(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			if (check_all_composant(parsing->map[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_first_and_last_wall(int *line, int end_line)
{
	int	i;

	i = 0;
	while (i < end_line)
	{
		if (line[i] != 1 && line[i] != 676)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_wall(int *line, int end_line)
{
	int	i;

	i = 0;
	while (i < end_line || (line[i] != 1 && line[i] != 676))
	{
		if (line[i] == 0)
			break ;
		i++;
	}
	if (i == end_line || line[i - 1] != 1)
		return (FALSE);
	i = end_line;
	while (i > 0 || (line[i] != 1 && line[i] != 676))
	{
		if (line[i] == 0)
			break ;
		i--;
	}
	if (i == 0 || line[i + 1] != 1)
		return (FALSE);
	return (TRUE);
}

int	check_map_wall(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	while (i < parsing->map_height)
	{
		if (i == 0 || i == parsing->map_height - 1)
		{
			if (check_first_and_last_wall(parsing->map[i], parsing->map_width[i]) == FALSE)
				return (FALSE);
		}
		else
		{
			if (check_wall(parsing->map[i], parsing->map_width[i]) == FALSE)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_valid_map(t_parsing *parsing)
{
	if (check_map_composant(parsing) == FALSE)
		return (error_message("Incorrect composant in the map"), FALSE);
	if (get_number_player(parsing) != 1)
		return (error_message("Incorrect number of player"), FALSE);
	if (check_map_wall(parsing) == FALSE)
		return (error_message("Incorrect close wall"), FALSE);
	return (TRUE);
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

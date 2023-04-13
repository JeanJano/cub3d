/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:13:31 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/12 18:14:54 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parsing_struct(t_parsing *parsing)
{
	ft_memset(parsing, 0, sizeof(*parsing));
	parsing->map_height = 0;
	parsing->rgb_floor[0] = -1;
	parsing->rgb_floor[1] = -1;
	parsing->rgb_floor[2] = -1;
	parsing->rgb_plafond[0] = -1;
	parsing->rgb_plafond[1] = -1;
	parsing->rgb_plafond[2] = -1;
}

void	init_player(t_cub *cub)
{
	cub->player_x = get_player_position_x(&cub->parsing) + 0.5;
	cub->player_y = get_player_position_y(&cub->parsing) + 0.5;
	cub->vision = get_player_position_vision(&cub->parsing);
	if (cub->vision == 78)
		cub->vision = 270;
	if (cub->vision == 69)
		cub->vision = 0;
	if (cub->vision == 87)
		cub->vision = 180;
	if (cub->vision == 83)
		cub->vision = 90;
	cub->vision_incr = 4;
	cub->move_incr = 0.125;
}

int	init_manager(t_cub *cub, char **av)
{
	int	parser_return;

	init_parsing_struct(&cub->parsing);
	parser_return = parser(&cub->parsing, av[1]);
	if (parser_return == -1)
		return (FALSE);
	if (parser_return == 2)
	{
		free_struct(cub);
		return (FALSE);
	}
	if (check_valid_map(&cub->parsing) == FALSE)
	{
		free_struct(cub);
		return (FALSE);
	}
	init_player(cub);
	if (init_mlx(cub) == FALSE)
	{
		free_struct(cub);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return (error_message("Wrong number of argument"), 1);
	if (check_extension(av[1], ".cub") == FALSE)
		return (error_message("Wrong extension map file"), 1);
	if (init_manager(&cub, av) == FALSE)
		return (1);
	draw(&cub);
	mlx_hook(cub.mlx.win_ptr, KeyPress, KeyPressMask, deal_key, &cub);
	mlx_hook(cub.mlx.win_ptr, 33, 0, ft_close, &cub);
	mlx_loop(cub.mlx.mlx_ptr);
	return (0);
}

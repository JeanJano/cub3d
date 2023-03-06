/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:13:31 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/06 16:40:38 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parsing(t_parsing *parsing)
{
	printf("NO: %s\n", parsing->path_north);
	printf("SO: %s\n", parsing->path_south);
	printf("WE: %s\n", parsing->path_west);
	printf("EA: %s\n", parsing->path_east);
	printf("floor: %d %d %d\n", parsing->rgb_floor[0], parsing->rgb_floor[1], parsing->rgb_floor[2]);
	printf("plafond: %d %d %d\n", parsing->rgb_plafond[0], parsing->rgb_plafond[1], parsing->rgb_plafond[2]);
	printf("map height: %d\n", parsing->map_height);
	printf("map width: ");
	int i = 0;
	while (i < parsing->map_height)
	{
		printf("%d ", parsing->map_width[i]);
		i++;
	}
	printf("\n");
	i = 0;
	int j;
	while (i < parsing->map_height)
	{
		j = 0;
		while (j < parsing->map_width[i])
		{
			printf("%d", parsing->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	init_parsing_struct(t_parsing *parsing)
{
	parsing->map = NULL;
	parsing->path_east = NULL;
	parsing->path_north = NULL;
	parsing->path_south = NULL;
	parsing->path_west = NULL;
	parsing->map_height = 0;
	parsing->map_width = NULL;
	parsing->rgb_floor[0] = -1;
	parsing->rgb_floor[1] = -1;
	parsing->rgb_floor[2] = -1;
	parsing->rgb_plafond[0] = -1;
	parsing->rgb_plafond[1] = -1;
	parsing->rgb_plafond[2] = -1;
}

int	init_mlx(t_cub *cub)
{
	cub->mlx.mlx_ptr = mlx_init();
	if (cub->mlx.mlx_ptr == NULL)
		return (FALSE);
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (cub->mlx.win_ptr == NULL)
	{
		free(cub->mlx.mlx_ptr);
		return (FALSE);
	}
	return (TRUE);
}

void	init_player(t_cub *cub)
{
	cub->player_x = get_player_position_x(&cub->parsing);
	cub->player_y = get_player_position_y(&cub->parsing);
	cub->vision = get_player_position_vision(&cub->parsing);
	if (cub->vision == 78)
		cub->vision = 270;
	if (cub->vision == 69)
		cub->vision = 0;
	if (cub->vision == 87)
		cub->vision = 180;
	if (cub->vision == 83)
		cub->vision = 90;
	cub->vision_incr = 1;
	cub->move_incr = 0.2;
}

int	main(int ac, char **av)
{
	t_cub		*cub;
	t_parsing	parsing;

	if (ac != 2)
		return (error_message("wrong number of argument"), 1);
	if (check_extension(av[1]) == FALSE)
		return (error_message("wrong extension file"), 1);
	init_parsing_struct(&parsing);
	cub = malloc(sizeof(t_cub));
	cub->parsing = parsing;
	if (parser(&cub->parsing, av[1]) == 2)
	{
		free_struct(&cub);
		return (1);
	}
	if (check_valid_map(&cub->parsing) == FALSE)
	{
		free_struct(&cub);
		return (1);
	}
	get_vector_distance(5.4, 4, 0, cub->parsing);
	if (init_mlx(cub) == FALSE)
	{
		free_struct(&cub);
		return (1);
	}
	init_player(cub);
	cub->mlx.img.mlx_img = mlx_new_image(cub->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->mlx.img.addr = mlx_get_data_addr(cub->mlx.img.mlx_img, &cub->mlx.img.bpp, &cub->mlx.img.line_len, &cub->mlx.img.endian);
	// mlx_loop_hook(cub->mlx.mlx_ptr, draw, &cub);
	mlx_loop_hook(cub->mlx.mlx_ptr, draw_test_move, &cub);
	mlx_hook(cub->mlx.win_ptr, KeyPress, KeyPressMask, deal_key, &cub);
	mlx_hook(cub->mlx.win_ptr, 33, 0, ft_close, &cub);
	mlx_loop(cub->mlx.mlx_ptr);

	// free_struct(&cub);
	return (0);
}

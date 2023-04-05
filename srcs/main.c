/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:13:31 by jsauvage          #+#    #+#             */
/*   Updated: 2023/03/29 14:59:41 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parsing(t_parsing *parsing)
{
	printf("NO: %s\n", parsing->path_north);
	printf("SO: %s\n", parsing->path_south);
	printf("WE: %s\n", parsing->path_west);
	printf("EA: %s\n", parsing->path_east);
	// printf("floor: %d %d %d\n", parsing->rgb_floor[0], parsing->rgb_floor[1], parsing->rgb_floor[2]);
	// printf("plafond: %d %d %d\n", parsing->rgb_plafond[0], parsing->rgb_plafond[1], parsing->rgb_plafond[2]);
	// printf("map height: %d\n", parsing->map_height);
	// printf("map width: ");
	// int i = 0;
	// while (i < parsing->map_height)
	// {
	// 	printf("%d ", parsing->map_width[i]);
	// 	i++;
	// }
	// printf("\n");
	// i = 0;
	// int j;
	// while (i < parsing->map_height)
	// {
	// 	j = 0;
	// 	while (j < parsing->map_width[i])
	// 	{
	// 		printf("%d", parsing->map[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
}

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

int	xpm_to_image(t_cub *cub)
{
	int width;
	int	height;

	cub->texture.north.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, cub->parsing.path_north, &width, &height);
	cub->texture.north.addr = mlx_get_data_addr(cub->texture.north.mlx_img, &cub->texture.north.bpp, &cub->texture.north.line_len, &cub->texture.north.endian);
	cub->texture.south.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, cub->parsing.path_south, &width, &height);
	cub->texture.south.addr = mlx_get_data_addr(cub->texture.south.mlx_img, &cub->texture.south.bpp, &cub->texture.south.line_len, &cub->texture.south.endian);
	cub->texture.east.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, cub->parsing.path_east, &width, &height);
	cub->texture.east.addr = mlx_get_data_addr(cub->texture.east.mlx_img, &cub->texture.east.bpp, &cub->texture.east.line_len, &cub->texture.east.endian);
	cub->texture.west.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr, cub->parsing.path_west, &width, &height);
	cub->texture.west.addr = mlx_get_data_addr(cub->texture.west.mlx_img, &cub->texture.west.bpp, &cub->texture.west.line_len, &cub->texture.east.endian);
	if (!cub->texture.north.mlx_img || !cub->texture.south.mlx_img || !cub->texture.east.mlx_img || !cub->texture.west.mlx_img)
		return (error_message("Invalid path texture"), FALSE);
	return (TRUE);
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
	if (xpm_to_image(cub) == FALSE)
		return (FALSE);
	cub->mlx.img.mlx_img = mlx_new_image(cub->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->mlx.img.addr = mlx_get_data_addr(cub->mlx.img.mlx_img, &cub->mlx.img.bpp, &cub->mlx.img.line_len, &cub->mlx.img.endian);
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
	cub->vision_incr = 4;
	cub->move_incr = 0.125;
}

int	main(int ac, char **av)
{
	t_cub		cub;

	if (ac != 2)
		return (error_message("wrong number of argument"), 1);
	if (check_extension(av[1]) == FALSE)
		return (error_message("wrong extension file"), 1);

	init_parsing_struct(&cub.parsing);
	if (parser(&cub.parsing, av[1]) == 2)
	{
		free_struct(&cub);
		return (1);
	}
	print_parsing(&cub.parsing);
	if (check_valid_map(&cub.parsing) == FALSE)
	{
		free_struct(&cub);
		return (1);
	}

	// for (double i = 0; i < 360; i += 0.06)
		// get_vector_distance(6, 5, 252.4, cub.parsing);

	init_player(&cub);
	if (init_mlx(&cub) == FALSE)
	{
		free_struct(&cub);
		return (1);
	}
	// printf("x=%f y=%f\n", cub.player_x, cub.player_y);
	mlx_loop_hook(cub.mlx.mlx_ptr, draw, &cub);
	// mlx_loop_hook(cub.mlx.mlx_ptr, draw_test_move, &cub);
	mlx_hook(cub.mlx.win_ptr, KeyPress, KeyPressMask, deal_key, &cub);
	mlx_hook(cub.mlx.win_ptr, 33, 0, ft_close, &cub);
	mlx_loop(cub.mlx.mlx_ptr);

	// free_struct(&cub);
	return (0);
}

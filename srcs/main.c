/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:13:31 by jsauvage          #+#    #+#             */
/*   Updated: 2023/02/21 15:51:41 by jsauvage         ###   ########.fr       */
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

void	init_parsing(t_parsing *parsing)
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

//fenetre

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || x < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

static void	draw_backgroud(t_cub **cub)
{
	int	x;
	int	y;

	y = 0;
	while (y <= WINDOW_WIDTH)
	{
		x = 0;
		while (x <= WINDOW_HEIGHT)
		{
			img_pix_put(&(*cub)->mlx.img, y, x, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_line(t_cub **cub)
{
	int	i;
	int	j;

	i = (*cub)->init_distance;
	// printf("distance: %d\n", (*cub)->distance);
	while (i > (*cub)->distance - 250)
	{
		j = 500;
		while (j < 700)
		{
			img_pix_put(&(*cub)->mlx.img, j, i, 0x00FFFF00);
			j++;
		}
		i--;
	}
}

int	draw(t_cub **cub)
{
	draw_backgroud(cub);
	draw_line(cub);
	mlx_put_image_to_window((*cub)->mlx.mlx_ptr, (*cub)->mlx.win_ptr, (*cub)->mlx.img.mlx_img, -1, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub		*cub;
	t_parsing	parsing;

    double playerX = 5.0;
    double playerY = 5.0;
	double angle = atof(av[1]);
   
    for (double angle = 0; angle < 60; angle += 0.06)
	{
		get_vector_distance(playerX, playerY, angle);
		// draw_line(distance, x);
    }

	// if (ac != 2)
	// 	return (error_message("wrong number of argument"), 1);
	// if (check_extension(av[1]) == FALSE)
	// 	return (error_message("wrong extension file"), 1);
	// cub = malloc(sizeof(t_cub));
	// init_parsing(&parsing);
	// cub->parsing = parsing;
	// cub->distance = 500;
	// cub->init_distance = 500;
	// parser(&cub->parsing, av[1]);
	// // print_parsing(&cub->parsing);
	// if (check_valid_map(&cub->parsing) == FALSE)
	// {
	// 	free_struct(&cub);
	// 	return (1);
	// }
	// if (init_mlx(cub) == FALSE)
	// {
	// 	free_struct(&cub);
	// 	return (1);
	// }
	// cub->mlx.img.mlx_img = mlx_new_image(cub->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// cub->mlx.img.addr = mlx_get_data_addr(cub->mlx.img.mlx_img, &cub->mlx.img.bpp, &cub->mlx.img.line_len, &cub->mlx.img.endian);
	// mlx_loop_hook(cub->mlx.mlx_ptr, draw, &cub);
	// mlx_key_hook(cub->mlx.win_ptr, deal_key, &cub);
	// mlx_hook(cub->mlx.win_ptr, 33, 0, ft_close, &cub);
	// mlx_loop(cub->mlx.mlx_ptr);
	// return (0);
}

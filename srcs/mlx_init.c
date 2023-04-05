/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:23:16 by jsauvage          #+#    #+#             */
/*   Updated: 2023/04/05 15:41:48 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_xpm_extension(t_cub *cub)
{
	if (check_extension(cub->parsing.path_north, ".xpm") == FALSE)
		return (FALSE);
	if (check_extension(cub->parsing.path_south, ".xpm") == FALSE)
		return (FALSE);
	if (check_extension(cub->parsing.path_east, ".xpm") == FALSE)
		return (FALSE);
	if (check_extension(cub->parsing.path_west, ".xpm") == FALSE)
		return (FALSE);
	return (TRUE);
}

int	xpm_to_image2(t_cub *cub, int height, int width)
{
	cub->texture.east.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,
			cub->parsing.path_east, &width, &height);
	if (!cub->texture.east.mlx_img)
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.north.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.south.mlx_img);
		return (error_message("Invalid path texture"), FALSE);
	}
	cub->texture.east.addr = mlx_get_data_addr(cub->texture.east.mlx_img,
			&cub->texture.east.bpp, &cub->texture.east.line_len,
			&cub->texture.east.endian);
	cub->texture.west.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,
			cub->parsing.path_west, &width, &height);
	if (!cub->texture.west.mlx_img)
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.north.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.south.mlx_img);
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.east.mlx_img);
		return (error_message("Invalid path texture"), FALSE);
	}
	cub->texture.west.addr = mlx_get_data_addr(cub->texture.west.mlx_img,
			&cub->texture.west.bpp, &cub->texture.west.line_len,
			&cub->texture.east.endian);
	return (TRUE);
}

int	xpm_to_image(t_cub *cub)
{
	int	width;
	int	height;

	cub->texture.north.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,
			cub->parsing.path_north, &width, &height);
	if (!cub->texture.north.mlx_img)
		return (error_message("Invalid path texture"), FALSE);
	cub->texture.north.addr = mlx_get_data_addr(cub->texture.north.mlx_img,
			&cub->texture.north.bpp, &cub->texture.north.line_len,
			&cub->texture.north.endian);
	cub->texture.south.mlx_img = mlx_xpm_file_to_image(cub->mlx.mlx_ptr,
			cub->parsing.path_south, &width, &height);
	if (!cub->texture.south.mlx_img)
	{
		mlx_destroy_image(cub->mlx.mlx_ptr, cub->texture.north.mlx_img);
		return (error_message("Invalid path texture"), FALSE);
	}
	cub->texture.south.addr = mlx_get_data_addr(cub->texture.south.mlx_img,
			&cub->texture.south.bpp, &cub->texture.south.line_len,
			&cub->texture.south.endian);
	if (xpm_to_image2(cub, height, width) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	xpm_manage(t_cub *cub)
{
	if (check_xpm_extension(cub) == FALSE)
	{
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		mlx_destroy_display(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
		return (error_message("Wrong extension texture file"), FALSE);
	}
	if (xpm_to_image(cub) == FALSE)
	{
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		mlx_destroy_display(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
		return (FALSE);
	}
	return (TRUE);
}

int	init_mlx(t_cub *cub)
{
	cub->mlx.mlx_ptr = mlx_init();
	if (cub->mlx.mlx_ptr == NULL)
		return (FALSE);
	cub->mlx.win_ptr = mlx_new_window(cub->mlx.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
	if (cub->mlx.win_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr);
		mlx_destroy_display(cub->mlx.mlx_ptr);
		free(cub->mlx.mlx_ptr);
		return (FALSE);
	}
	if (xpm_manage(cub) == FALSE)
		return (FALSE);
	cub->mlx.img.mlx_img = mlx_new_image(cub->mlx.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	cub->mlx.img.addr = mlx_get_data_addr(cub->mlx.img.mlx_img,
			&cub->mlx.img.bpp, &cub->mlx.img.line_len, &cub->mlx.img.endian);
	return (TRUE);
}

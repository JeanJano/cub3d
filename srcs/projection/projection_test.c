// #include "cub3d.h"

// void draw_pix(int x, int y, int *pixel_ptr, t_cub *cub, int size)
// {
// 	for (int i = 0; i < size ; i++)
// 	{
// 		for (int j = 0; j < size ; j++)
// 			img_pix_put(&cub->mlx.img, x + j, y + i, *pixel_ptr);
// 	}
// }

// int get_hit_value(double hit_coord)
// {
// 	hit_coord = (hit_coord - floor(hit_coord)) * 100;
// 	hit_coord = round(hit_coord);
// 	hit_coord = hit_coord / 100 * 64;
// 	if (hit_coord >= 64)
// 		return (63);
// 	return((int)hit_coord);
// }

// void draw_bigger_wall(int *pixel_ptr, t_cub *cub, int height, int x_pos, int increment_value)
// {
// 	int y = 0;
// 	double pixels_to_draw;
// 	double demi_pixel_increment;
// 	double demi_pixel_value = 0;

// 	pixels_to_draw = height / (double)increment_value;
// 	demi_pixel_increment = pixels_to_draw - floor(pixels_to_draw);
// 	pixels_to_draw = floor(pixels_to_draw);
// 	// printf("ceil=%f int=%d\n", pixels_to_draw, (int)pixels_to_draw);
// 	while (y < height)
// 	{
// 		if (demi_pixel_value >= 2)
// 		{
// 			draw_pix(x_pos, y, pixel_ptr, cub, (int)pixels_to_draw + 2);
// 			// demi_pixel_value = 0;
// 			demi_pixel_value = demi_pixel_value - 2;
// 			y += (int)pixels_to_draw + 2;
// 			if (y + (int)pixels_to_draw + 2 > height)
// 				break ;
// 		}
// 		else
// 		{
// 			draw_pix(x_pos, y, pixel_ptr, cub, (int)pixels_to_draw);
// 			y += (int)pixels_to_draw;
// 			if (y + (int)pixels_to_draw > height)
// 				break ;
// 		}
// 		demi_pixel_value += demi_pixel_increment;
// 		pixel_ptr += increment_value;
// 	}
// 	draw_pix(x_pos, y, pixel_ptr, cub, height - y);
// 	// printf("%d\n", y);
// }

// void draw_column(int *pixel_ptr, t_cub *cub, int height, int x_pos)
// {
// 	int increment_value;
// 	double pixels_to_draw;

// 	int test = 0;

// 	increment_value = cub->texture.north.line_len / 4;
// 	if (height > increment_value)
// 		draw_bigger_wall(pixel_ptr, cub, height, x_pos, increment_value);
// 	else
// 	{
// 		pixels_to_draw = floor(1 / (double)height * 64);
// 		printf("%f\n", pixels_to_draw);
// 		for (int y = 0 ; y < height ; y++)
// 		{
// 			draw_pix(x_pos, y, pixel_ptr, cub, 1);
// 			pixel_ptr += increment_value * (int)pixels_to_draw;
// 		}
// 	}
// 	// printf("len=%d\n", cub->texture.north.line_len / 4);
// }

// int	draw_test_move(t_cub *cub)
// {
// 	// draw_backgrdoud(cub);
// 	int	*pixel_cpy;
// 	int	*pixel_ptr;

// 	pixel_cpy = (int *)(cub->texture.north.addr);
// 	pixel_ptr = pixel_cpy;
// 	for (int y = 0 ; y < 64 * 4 ; y += 4)
// 	{
// 		for (int x = 0 ; x < 64 * 4 ; x += 4)
// 		{
// 			draw_pix(x, y, pixel_ptr, cub, 4);
// 			pixel_ptr++;
// 		}
// 	}
// 	int hit_value = get_hit_value(5);
// 	int wall_height = 700;
// 	pixel_ptr = pixel_cpy;
// 	pixel_ptr += hit_value;
// 	// for (int i = 0 ; i < 700 ; i++)
// 	// 	img_pix_put(&cub->mlx.img, 399, i, 0x00FFFFFF);
// 	// draw_column(pixel_ptr, cub, wall_height, 400);
// 	// pixel_ptr = pixel_cpy;
// 	for (int i = 0 ; i < 600 ; i++)
// 		img_pix_put(&cub->mlx.img, 419, i, 0x00FFFFFF);
// 	draw_column(pixel_ptr, cub, 600, 420);

	
// 	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
// 	return (0);
// }

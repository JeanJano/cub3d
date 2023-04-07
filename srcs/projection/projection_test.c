// #include "cub3d.h"

// void draw_pix(int x, int y, int *pixel_ptr, t_cub *cub, int size)
// {
// 	for (int i = 0; i < size ; i++)
// 		for (int j = 0; j < 10 ; j++)
// 			img_pix_put(&cub->mlx.img, x + j, y + i, *pixel_ptr);
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

// int *get_corresponding_pixel(int *pixel_ptr, int line, int increment_value)
// {
// 	int *return_value;

// 	printf("line=%d incr=%d\n", line, increment_value);
// 	return_value = pixel_ptr + (line * increment_value);
// 	return (return_value);
// }

// void test_1(int *pixel_ptr, t_cub *cub, int height, int x_pixel_draw, int increment_value)
// {
// 	int y = 0;
// 	int *corresponding_pixel;

// 	while (y < height && y < WINDOW_HEIGHT)
// 	{
// 		corresponding_pixel = get_corresponding_pixel(pixel_ptr, (int)(((double)y / (double)height) * 64), increment_value);
// 		// printf("pixel=%d\n", *corresponding_pixel);
// 		// draw_pix(x_pixel_draw, y, corresponding_pixel, cub, 1);
// 		img_pix_put(&cub->mlx.img, x_pixel_draw, y, *corresponding_pixel);
// 		y++;
// 	}
// }

// void draw_column(int *pixel_ptr, t_cub *cub, int height, int x_pos)
// {
// 	int increment_value;
// 	double pixels_to_draw;

// 	increment_value = cub->texture.north.line_len / 4;
// 	test_1(pixel_ptr, cub, height, x_pos, increment_value);
// 	// printf("len=%d\n", cub->texture.north.line_len / 4);
// }

// // void draw_texture_preview(int *texture_ptr, t_cub *cub)
// // {
// // 	for (int y = 0 ; y < 64 * 4 ; y += 4)
// // 	{
// // 		for (int x = 0 ; x < 64 * 4 ; x += 4)
// // 		{
// // 			draw_pix(x, y, texture_ptr, cub, 10);
// // 			texture_ptr++;
// // 		}
// // 	}
// // }

// int	draw_test_move(t_cub *cub)
// {
// 	int *texture_start_ptr;

// 	texture_start_ptr = (int *)(cub->texture.north.addr);
// 	draw_texture_preview(texture_start_ptr, cub);

// 	int hit_value = get_hit_value(0);
// 	int wall_height = 640;

// 	for (int i = 0 ; i < wall_height ; i++)
// 		img_pix_put(&cub->mlx.img, 419, i, 0x00FFFFFF);
// 	texture_start_ptr = (int *)(cub->texture.north.addr);
// 	texture_start_ptr += hit_value;
// 	for (int i = 0;i<64;i++)
// 	{
// 		draw_column(texture_start_ptr, cub, wall_height, 420 + i);
// 		texture_start_ptr += 1;
// 	}

// 	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
// 	return (0);
// }

#include "cub3d.h"

void draw_pix(int x, int y, int *pixel_ptr, t_cub *cub, int size)
{
	for (int i = 0; i < size ; i++)
	{
		for (int j = 0; j < size ; j++)
			img_pix_put(&cub->mlx.img, x + j, y + i, *pixel_ptr);
	}
}

int get_hit_value(double hit_coord)
{
	hit_coord = (hit_coord - floor(hit_coord)) * 100;
	hit_coord = round(hit_coord);
	hit_coord = hit_coord / 100 * 64;
	if (hit_coord >= 64)
		return (63);
	return((int)hit_coord);
}

void draw_column(int *pixel_ptr, t_cub *cub, int height)
{
	int increment_value;
	double pixel_ratio;

	increment_value = cub->texture.north.line_len / 4;
	if (height > increment_value)
	{
		pixel_ratio = height / (double)increment_value;
		pixel_ratio = ceil(pixel_ratio);
		// printf("ceil=%f int=%d\n", pixel_ratio, (int)pixel_ratio);
		for (int y = 0 ; y < height ; y += (int)pixel_ratio)
		{
			draw_pix(400, y, pixel_ptr, cub, (int)pixel_ratio);
			pixel_ptr += increment_value;
			// printf("y=%d\n", y);
		}
	}
	else
	{
		pixel_ratio = floor(1 / (double)height * 64);
		printf("%f\n", pixel_ratio);
		for (int y = 0 ; y < height ; y++)
		{
			draw_pix(400, y, pixel_ptr, cub, 1);
			pixel_ptr += increment_value * (int)pixel_ratio;
		}
	}
	// printf("len=%d\n", cub->texture.north.line_len / 4);
}

int	draw_test_move(t_cub *cub)
{
	// draw_backgrdoud(cub);
	int	*pixel_cpy;
	int	*pixel_ptr;

	pixel_cpy = (int *)(cub->texture.north.addr);
	pixel_ptr = pixel_cpy;
	for (int y = 0 ; y < 64 * 4 ; y += 4)
	{
		for (int x = 0 ; x < 64 * 4 ; x += 4)
		{
			draw_pix(x, y, pixel_ptr, cub, 4);
			pixel_ptr++;
		}
	}
	int hit_value = get_hit_value(5);
	int wall_height = 50;
	pixel_ptr = pixel_cpy;
	pixel_ptr += hit_value;
	draw_column(pixel_ptr, cub, wall_height);
	// for (int i = 0;i < 60;i++)
	// 	img_pix_put(&cub->mlx.img, 397, i, 0x00FFFFFF);

	
	mlx_put_image_to_window(cub->mlx.mlx_ptr, cub->mlx.win_ptr, cub->mlx.img.mlx_img, -1, 0);
	return (0);
}

#include "cub3d.h"

// const int MAP_WIDTH = 10;
// const int MAP_HEIGHT = 10;

// int map[10][10] = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

void get_next_vertical_intersec(double *x, double *y, double y_scale, int quartile)
{
	if (quartile == 1 || quartile == 4)
		*x = *x + 1;
	else
		*x = *x - 1;
	if (quartile == 1 || quartile == 4)
		*y = *y + y_scale;
	else if (quartile == 2)
		*y = *y + (y_scale * -1);
	else
		*y = *y - y_scale;
	printf("checked in 1 x=%f y=%f xIndex=%d yIndex=%d\n", *x, *y, (int)*x, (int)*y);
}

void get_next_horizontal_intersec(double *x, double *y, double x_scale, int quartile)
{
	if (quartile == 1)
		*x = *x + x_scale;
	else if (quartile == 2)
		*x = *x + x_scale;
	else if (quartile == 3)
		*x = *x - x_scale;
	else
		*x = *x + -x_scale;
	if (quartile == 1 || quartile == 2)
		*y = *y + 1;
	else
		*y = *y - 1;
	printf("checked in 2 x=%f y=%f xIndex=%d yIndex=%d\n", *x, *y, (int)*x, (int)*y);
}

// void get_first_vertical_intersec()

double get_vector_distance(double playerX, double playerY, double angle, t_parsing parsing)
{
	t_dda data;

	data.x_cos  = cos(angle * ( M_PI / 180));
    data.y_sin = sin(angle * (M_PI / 180));
	data.x_scale = (1 / data.y_sin) * data.x_cos; // x scale to move 1 y
	data.y_scale = (1 / data.x_cos) * data.y_sin; // y scale to move 1 x

	printf("x_cos=%f y_sin=%f\n", data.x_cos, data.y_sin);
	// printf("x_scale=%f y_scale=%f\n", data.x_scale, data.y_scale);

    data.x_horizontal = playerX;
    data.y_horizontal = playerY;
	data.horizontal_length = 0;

	data.x_vertical = playerX;
	data.y_vertical = playerY;
	data.vertical_length = 0;

	int quartile;

	if (angle >= 0 && angle <= 90)
		quartile = 1;
	else if (angle >= 91 && angle <= 180)
		quartile = 2;
	else if (angle >= 181 && angle <= 270)
		quartile = 3;
	else if (angle >= 271 && angle <= 360)
		quartile = 4;

	int map_height = 0;
	int map_width = 0;

    while (data.x_vertical >= 0 && data.x_vertical < parsing.map_width[(int)data.y_vertical] && data.y_vertical >= 0 && data.y_vertical < parsing.map_height)
    {
			get_next_vertical_intersec(&data.x_vertical, &data.y_vertical, data.y_scale, quartile);
			if (data.x_vertical < 0 || data.x_vertical > parsing.map_width[(int)data.y_vertical] || data.y_vertical < 0 || data.y_vertical > parsing.map_height)
				break ;
			if (quartile == 1)
			{
				if (parsing.map[(int)data.y_vertical][(int)data.x_vertical] == 1)
					break ;
			}
			else if (quartile == 2)
			{
				if (parsing.map[(int)data.y_vertical][(int)data.x_vertical - 1] == 1)
					break ;
			}
			else if (quartile == 3)
			{
				if (parsing.map[(int)data.y_vertical][(int)data.x_vertical - 1] == 1)
					break ;
			}
			else if (quartile == 4)
			{
				if (parsing.map[(int)data.y_vertical][(int)data.x_vertical] == 1)
					break ;
			}
    }
	data.vertical_length = fabs(data.x_vertical - playerX) * fabs(data.x_cos) + fabs(data.y_vertical - playerY) * fabs(data.y_sin);
    while (data.x_horizontal >= 0 && data.x_horizontal < parsing.map_width[(int)data.y_vertical] && data.y_horizontal >= 0 && data.y_horizontal < parsing.map_height)
    {
			get_next_horizontal_intersec(&data.x_horizontal, &data.y_horizontal, data.x_scale, quartile);
			if (data.x_horizontal < 0 || data.x_horizontal > parsing.map_width[(int)data.y_vertical] || data.y_horizontal < 0 || data.y_horizontal > parsing.map_height)
				break ;
			if (quartile == 1)
			{
				if (parsing.map[(int)data.y_horizontal][(int)data.x_horizontal] == 1)
					break ;
			}
			else if (quartile == 2)
			{
				// printf("ici--------------------\n");
				if (parsing.map[(int)data.y_horizontal][(int)data.x_horizontal] == 1)
					break ;
			}
			else if (quartile == 3)
			{
				// printf("FOUND AT %d, %d or %f, %f\n", (int)ceil(data.x_horizontal) - 1, (int)data.y_horizontal - 1, data.x_horizontal, data.y_horizontal);
				if (parsing.map[(int)data.y_horizontal - 1][(int)ceil(data.x_horizontal) - 1] == 1)
					break ;
			}
			else if (quartile == 4)
			{
				if (parsing.map[(int)data.y_horizontal - 1][(int)data.x_horizontal] == 1)
					break ;
			}
    }
	data.horizontal_length = fabs(data.x_horizontal - playerX) * fabs(data.x_cos) + fabs(data.y_horizontal - playerY) * fabs(data.y_sin);
	if (data.vertical_length > data.horizontal_length)
	{
		printf("horizontal_length=%f at: %f, %f\n", data.horizontal_length, data.x_horizontal, data.y_horizontal);
		return (data.horizontal_length);
	}
	else
	{
		printf("vertical_length=%f at: %f, %f\n", data.vertical_length, data.x_vertical, data.y_vertical);
		return (data.vertical_length);
	}
}
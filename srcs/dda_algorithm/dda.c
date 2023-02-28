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
	printf("ratio=%f\n", y_scale);
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

int check_map_vertical(int x, int y, int quartile, t_parsing parsing_struct)
{
	if (y < 0 || y >= parsing_struct.map_height || x < 0 || x > parsing_struct.map_width[(int)y])
		return (1);
	if (quartile == 1)
	{
		// printf("found wall in x=%d y=%d\n", (int)x - 1, (int)y);
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (1);
	}
	else if (quartile == 2)
	{
		if (parsing_struct.map[(int)y][(int)x - 1] == 1)
			return (1);
	}
	else if (quartile == 3)
	{
		if (parsing_struct.map[(int)y][(int)x - 1] == 1)
		{

			return (1);
		}
	}
	else if (quartile == 4)
	{
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (1);
	}
	return (0);
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
	// printf("checked in 2 x=%f y=%f xIndex=%d yIndex=%d\n", *x, *y, (int)*x, (int)*y);
}

int check_map_horizontal(int x, int y, int quartile, t_parsing parsing_struct)
{
	if (y < 0 || y >= parsing_struct.map_height || x < 0 || x > parsing_struct.map_width[(int)y])
		return (1);
	if (quartile == 1)
	{
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (1);
	}
	else if (quartile == 2)
	{
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (1);
	}
	else if (quartile == 3)
	{
		if (parsing_struct.map[(int)y - 1][(int)ceil(x) - 1] == 1)
			return (1);
	}
	else if (quartile == 4)
	{
		if (parsing_struct.map[(int)y - 1][(int)x] == 1)
			return (1);
	}
	return (0);
}

void get_first_vertical_intersec(double x, double y, double angle)
{
	double dx = ((int)x + 1) - x;
	double dy = dx / tan(angle * (M_PI / 180));
	x = x + dx;
	// y = y + 
	// printf("dx=%f dy=%f\n", dx, dy);

}

double get_vector_distance(double playerX, double playerY, double angle, t_parsing parsing_struct) {
    double x_cos = cos(angle * ( M_PI / 180));
    double y_sin = sin(angle * (M_PI / 180));
	double x_scale = (1 / y_sin) * x_cos; // x scale to move 1 y
	double y_scale = (1 / x_cos) * y_sin; // y scale to move 1 x
 
	// printf("x_cos=%f y_sin=%f\n", x_cos, y_sin);
	// printf("x_scale=%f y_scale=%f test=%f\n", x_scale, y_scale, (1 / -0.0) * y_sin);

    double x_horizontal = playerX;
    double y_horizontal = playerY;
	double horizontal_length = 0;

	double x_vertical = playerX;
	double y_vertical = playerY;
	double vertical_length = 0;

	int quartile;
	// GET QUARTILE
	if (angle >= 0 && angle < 90)
		quartile = 1;
	else if (angle >= 90 && angle < 180)
		quartile = 2;
	else if (angle >= 180 && angle < 270)
		quartile = 3;
	else if (angle >= 270 && angle < 360)
		quartile = 4;
	// VERTICAL CHECK
	// printf("quartile=%d", quartile);
	get_first_vertical_intersec(x_vertical, y_vertical, angle);
    // while (y_vertical >= 0 && y_vertical < parsing_struct.map_height && x_vertical >= 0 && x_vertical < parsing_struct.map_width[(int)y_vertical])
    // {
		// if (check_map_vertical(x_vertical, y_vertical, quartile, parsing_struct))
			// break ;
	// 	get_next_vertical_intersec(&x_vertical, &y_vertical, y_scale, quartile);
    // }
	// vertical_length = fabs(x_vertical - playerX) * fabs(x_cos) + fabs(y_vertical - playerY) * fabs(y_sin);
	// HORIZONTAL CHECK
	// while (y_horizontal >= 0 && y_horizontal < parsing_struct.map_height && x_horizontal >= 0 && x_horizontal < parsing_struct.map_width[(int)y_horizontal])
	// {
	// 	if (check_map_horizontal(x_horizontal, y_horizontal, quartile, parsing_struct))
	// 		break ;
	// 	get_next_horizontal_intersec(&x_horizontal, &y_horizontal, x_scale, quartile);
	// }
	// horizontal_length = fabs(x_horizontal - playerX) * fabs(x_cos) + fabs(y_horizontal - playerY) * fabs(y_sin);
	// GET BEST LENGTH
	// printf("vertical_length=%f at: %f, %f\n", vertical_length, x_vertical, y_vertical);
	// printf("horizontal_length=%f at: %f, %f\n", horizontal_length, x_horizontal, y_horizontal);
	// if (vertical_length > horizontal_length)
	// {
	// 	return (horizontal_length);
	// }
	// else
	// {
	// 	return (vertical_length);
	// }
}
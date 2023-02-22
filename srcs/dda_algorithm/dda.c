#include <stdio.h>
#include <math.h>
#include <stdlib.h>
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

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
	// printf("checked in 1 x=%f y=%f xIndex=%d yIndex=%d\n", *x, *y, (int)*x, (int)*y);
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

struct myStructure {
  int myNum;
  char myLetter;
  char myString[30]; // String
};

double get_vector_distance(double playerX, double playerY, double angle) {
    double x_cos = cos(angle * ( M_PI / 180));
    double y_sin = sin(angle * (M_PI / 180));
	double x_scale = (1 / y_sin) * x_cos; // x scale to move 1 y
	double y_scale = (1 / x_cos) * y_sin; // y scale to move 1 x

	// printf("x_cos=%f y_sin=%f\n", x_cos, y_sin);
	// printf("x_scale=%f y_scale=%f\n", x_scale, y_scale);

    double x_horizontal = playerX;
    double y_horizontal = playerY;
	double horizontal_length = 0;

	double x_vertical = playerX;
	double y_vertical = playerY;
	double vertical_length = 0;

	int quartile;

	if (angle >= 0 && angle <= 90)
		quartile = 1;
	else if (angle >= 91 && angle <= 180)
		quartile = 2;
	else if (angle >= 181 && angle <= 270)
		quartile = 3;
	else if (angle >= 271 && angle <= 360)
		quartile = 4;

    while (x_vertical >= 0 && x_vertical < MAP_WIDTH && y_vertical >= 0 && y_vertical < MAP_HEIGHT)
    {
			get_next_vertical_intersec(&x_vertical, &y_vertical, y_scale, quartile);
			if (x_vertical < 0 || x_vertical > MAP_WIDTH || y_vertical < 0 || y_vertical > MAP_HEIGHT)
				break ;
			if (quartile == 1)
			{
				if (map[(int)y_vertical][(int)x_vertical] == 1)
					break ;
			}
			else if (quartile == 2)
			{
				if (map[(int)y_vertical][(int)x_vertical - 1] == 1)
					break ;
			}
			else if (quartile == 3)
			{
				// printf("FOUND AT %d, %d or %f, %f\n", (int)x_vertical-1, (int)y_vertical, x_vertical - 1, y_vertical);
				if (map[(int)y_vertical][(int)x_vertical - 1] == 1)
					break ;
			}
			else if (quartile == 4)
			{
				if (map[(int)y_vertical][(int)x_vertical] == 1)
					break ;
			}
    }
	// printf("deltaX=%f deltaY=%f\n", fabs(x_vertical - playerX), fabs(y_vertical - playerY));
	// printf("dest=%f\n", fabs(x_vertical - playerX) * fabs(x_cos) + fabs(y_vertical - playerY) * fabs(y_sin));
	vertical_length = fabs(x_vertical - playerX) * fabs(x_cos) + fabs(y_vertical - playerY) * fabs(y_sin);
	// printf("vertical_length=%f at: %f, %f\n", vertical_length, x, y);
    while (x_horizontal >= 0 && x_horizontal < MAP_WIDTH && y_horizontal >= 0 && y_horizontal < MAP_HEIGHT)
    {
			get_next_horizontal_intersec(&x_horizontal, &y_horizontal, x_scale, quartile);
			if (x_horizontal < 0 || x_horizontal > MAP_WIDTH || y_horizontal < 0 || y_horizontal > MAP_HEIGHT)
				break ;
			if (quartile == 1)
			{
				if (map[(int)y_horizontal][(int)x_horizontal] == 1)
					break ;
			}
			else if (quartile == 2)
			{
				// printf("ici--------------------\n");
				if (map[(int)y_horizontal][(int)x_horizontal] == 1)
					break ;
			}
			else if (quartile == 3)
			{
				// printf("FOUND AT %d, %d or %f, %f\n", (int)ceil(x_horizontal) - 1, (int)y_horizontal - 1, x_horizontal, y_horizontal);
				if (map[(int)y_horizontal - 1][(int)ceil(x_horizontal) - 1] == 1)
					break ;
			}
			else if (quartile == 4)
			{
				if (map[(int)y_horizontal - 1][(int)x_horizontal] == 1)
					break ;
			}
    }
	horizontal_length = fabs(x_horizontal - playerX) * fabs(x_cos) + fabs(y_horizontal - playerY) * fabs(y_sin);
	// printf("horizontal_length=%f at: %f, %f\n", horizontal_length, x_horizontal, y_horizontal);
	if (vertical_length > horizontal_length)
	{
		// printf("horizontal_length=%f at: %f, %f\n", horizontal_length, x_horizontal, y_horizontal);
		return (horizontal_length);
	}
	else
	{
		// printf("vertical_length=%f at: %f, %f\n", vertical_length, x_vertical, y_vertical);
		return (vertical_length);
	}
}
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

void get_next1_point(double *x, double *y, double y_scal, int quartile)
{
	// printf("ratio=%f\n", y_scal);
	if (quartile == 1 || quartile == 4)
		*x = *x + 1;
	else
		*x = *x - 1;
	if (quartile == 1 || quartile == 4)
		*y = *y + y_scal;
	else if (quartile == 2)
		*y = *y + (y_scal * -1);
	else
		*y = *y - y_scal;
	printf("checked in 1 x=%f y=%f xIndex=%d yIndex=%d\n", *x, *y, (int)*x, (int)*y);
}

void get_next2_point(double *x, double *y, double x_scal, int quartile)
{
	// printf("ratio=%f\n", x_scal);
	if (quartile == 1)
		*x = *x + x_scal;
	else if (quartile == 2)
		*x = *x + x_scal;
	else if (quartile == 3)
		*x = *x - x_scal;
	else
		*x = *x + -x_scal;
	if (quartile == 1 || quartile == 2)
		*y = *y + 1;
	else
		*y = *y - 1;
	printf("checked in 2 x=%f y=%f xIndex=%d yIndex=%d\n", *x, *y, (int)*x, (int)*y);
}

struct myStructure {
  int myNum;
  char myLetter;
  char myString[30]; // String
};

double get_vector_distance(double playerX, double playerY, double angle) {
    double x_cos = cos(angle * ( M_PI / 180));
    double y_sin = sin(angle * (M_PI / 180));
	double x_scal = (1 / y_sin) * x_cos;
	double y_scal = (1 / x_cos) * y_sin;

	printf("x_cos=%f y_sin=%f\n", x_cos, y_sin);
	// printf("x_scal=%f y_scal=%f\n", x_scal, y_scal);
    double x = playerX;
    double y = playerY;
	double length = 0;

    double x2 = playerX;
    double y2 = playerY;
	int quartile;

	double length2 = 0;
	if (angle >= 0 && angle <= 90)
	{
		// printf("%f bas droite x++ y++\n", angle);
		quartile = 1;
	}
	else if (angle >= 91 && angle <= 180)
	{
		// printf("%f bas gauche x-- y++\n", angle);
		quartile = 2;
	}
	else if (angle >= 181 && angle <= 270)
	{
		// printf("%f haut gauche x-- y--\n", angle);
		quartile = 3;
	}
	else if (angle >= 271 && angle <= 360)
	{
		// printf("%f haut droite x++ y--\n", angle);
		quartile = 4;
	}
    while (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
    {
			get_next1_point(&x, &y, y_scal, quartile);
			if (x < 0 || x > MAP_WIDTH || y < 0 || y > MAP_HEIGHT)
				break ;
			if (quartile == 1)
			{
				if (map[(int)y][(int)x] == 1)
					break ;
			}
			else if (quartile == 2)
			{
				if (map[(int)y][(int)x - 1] == 1)
					break ;
			}
			else if (quartile == 3)
			{
				// printf("FOUND AT %d, %d or %f, %f\n", (int)x-1, (int)y, x - 1, y);
				if (map[(int)y][(int)x - 1] == 1)
					break ;
			}
			else if (quartile == 4)
			{
				if (map[(int)y][(int)x] == 1)
					break ;
			}
    }
	length = sqrt((y - playerY) * (y - playerY) + (x - playerY) * (x - playerY));
	// printf("length1=%f at: %f, %f\n", length, x, y);
    while (x2 >= 0 && x2 < MAP_WIDTH && y2 >= 0 && y2 < MAP_HEIGHT)
    {
			get_next2_point(&x2, &y2, x_scal, quartile);
			if (x2 < 0 || x2 > MAP_WIDTH || y2 < 0 || y2 > MAP_HEIGHT)
				break ;
			if (quartile == 1)
			{
				if (map[(int)y2][(int)x2] == 1)
					break ;
			}
			else if (quartile == 2)
			{
				// printf("ici--------------------\n");
				if (map[(int)y2][(int)x2] == 1)
					break ;
			}
			else if (quartile == 3)
			{
				// x_cos = ceil(x_cos);
				// y_sin = ceil(y_sin);
				// printf("FOUND AT %d, %d or %f, %f\n", (int)ceil(x2) - 1, (int)y2 - 1, x2, y2);
				if (map[(int)y2 - 1][(int)ceil(x2) - 1] == 1)
					break ;
			}
			else if (quartile == 4)
			{
				if (map[(int)y2 - 1][(int)x2] == 1)
					break ;
			}
    }
	// printf("wsh\n");
	length2 = sqrt((y2 - playerY) * (y2 - playerY) + (x2 - playerY) * (x2 - playerY));
	// printf("length2=%f at: %f, %f\n", length2, x2, y2);
	if (length > length2)
		return (printf("length2=%f at: %f, %f\n", length2, x2, y2), length2);
	else
		return (printf("length=%f at: %f, %f\n", length, x, y), length);
}

// int main(int argc, char **argv)
// {
//     double playerX = 5.0;
//     double playerY = 5.0;
// 	double angle = atof(argv[1]);
   
//     // for (double angle = 0; angle < 60; angle += 0.06) {
// 		get_vector_distance(playerX, playerY, angle);
//     // }
// 	// ft_ceil(1.654);
//     return 0;
// }
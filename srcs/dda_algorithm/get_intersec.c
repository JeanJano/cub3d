#include "cub3d.h"

void get_first_vertical_intersec(double *x, double *y, t_dda dda_data)
{
	double dx;

	if (dda_data.quartile == 1)
	{
		// printf("1=%f 2=%f\n", ((int)*x + 1) - *x, (floor(*x) + 1) - *x);
		dx = ((int)*x + 1) - *x;
		*y = *y + dda_data.y_scale * dx;
		*x = *x + ((int)*x + 1) - *x;
	}
	else if (dda_data.quartile == 2)
	{
		dx = *x - (int)*x;
		*y = *y - dda_data.y_scale * dx;
		*x = *x - dx;
	}
	else if (dda_data.quartile == 3) // same as 2
	{
		dx = *x - (int)*x;
		*y = *y - dda_data.y_scale * dx;
		*x = *x - dx;
	}
	else // same as 1
	{
		dx = ((int)*x + 1) - *x;
		*y = *y + dda_data.y_scale * dx;
		*x = *x + ((int)*x + 1) - *x;
	}
	// printf("first vertical intersec x=%f test=%f\n", *x, *y);
}

void get_next_vertical_intersec(double *x, double *y, double y_scale, int quartile)
{
	// printf("ratio=%f\n", y_scale);
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

void get_first_horizontal_intersec(double *x, double *y, double x_scale, int quartile)
{
	double dy;
	
	if (quartile == 1)
	{
		dy = ((int)*y + 1) - *y;
		*y = *y + dy;
		*x = *x + (dy * x_scale);
	}
	else if (quartile == 2)
	{
		dy = ((int)*y + 1) - *y;
		*y = *y + dy;
		*x = *x + x_scale * dy;
	}
	else if (quartile == 3)
	{
		dy = *y - (int)*y;
		// if (dy == 0)
		// 	dy = 1;
		*y = *y - dy;
		*x = *x - x_scale * dy;
	}
	else
	{
		dy = *y - (int)*y;
		// if (dy == 0)
		// 	dy = 1;
		*y = *y - dy;
		*x = *x - x_scale * dy;
	}
	// printf("first horizontal intersec x=%f y=%f dy=%f\n", *x, *y, dy);
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

#include "cub3d.h"

void get_first_vertical_intersec(double *x, double *y, t_dda *dda_data)
{
	double dx;

	if (dda_data->angle == 90 || dda_data->angle == 270)
	{
		dda_data->vertical_length = DBL_MAX;
		// printf("NOT HITTING ANY VERTICAL length=%f\n", dda_data->vertical_length);
		return ; 
	}
	if (dda_data->quartile == 1)
	{
		dx = ((int)*x + 1) - *x;
		*y = *y + dda_data->y_scale * dx;
		*x = *x + ((int)*x + 1) - *x;
	}
	else if (dda_data->quartile == 2)
	{
		dx = *x - (int)*x;
		*y = *y - dda_data->y_scale * dx;
		*x = *x - dx;
	}
	else if (dda_data->quartile == 3) // same as 2
	{
		dx = *x - (int)*x;
		*y = *y - dda_data->y_scale * dx;
		*x = *x - dx;
	}
	else // same as 1
	{
		dx = ((int)*x + 1) - *x;
		*y = *y + dda_data->y_scale * dx;
		*x = *x + ((int)*x + 1) - *x;
	}
	dda_data->vertical_length = fabs(dx / fabs(sin((90 - dda_data->angle) * ( M_PI / 180))));
	// printf("first vertical intersec x=%f y=%f length=%f\n", *x, *y, dda_data->vertical_length);
}

void get_next_vertical_intersec(double *x, double *y, t_dda *dda_data)
{
	if (dda_data->quartile == 1 || dda_data->quartile == 4)
		*x = *x + 1;
	else
		*x = *x - 1;
	if (dda_data->quartile == 1 || dda_data->quartile == 4)
		*y = *y + dda_data->y_scale;
	else if (dda_data->quartile == 2)
		*y = *y + (dda_data->y_scale * -1);
	else
		*y = *y - dda_data->y_scale;
	dda_data->vertical_length += dda_data->delta_dist_vertical;
	// printf("next vertical intersec x=%f y=%f length=%f\n", *x, *y, dda_data->vertical_length);
}

void get_first_horizontal_intersec(double *x, double *y, t_dda *dda_data)
{
	double dy;
	
	if (dda_data->angle == 0 || dda_data->angle == 180)
	{
		dda_data->horizontal_length = DBL_MAX;
		// printf("NOT HITTING ANY HORIZONTAL length=%f\n", dda_data->horizontal_length);
		return ;
	}
	if (dda_data->quartile == 1)
	{
		dy = ((int)*y + 1) - *y;
		*y = *y + dy;
		*x = *x + (dy * dda_data->x_scale);
	}
	else if (dda_data->quartile == 2)
	{
		dy = ((int)*y + 1) - *y;
		*y = *y + dy;
		*x = *x + dda_data->x_scale * dy;
	}
	else if (dda_data->quartile == 3)
	{
		dy = *y - (int)*y;
		// if (dy == 0)
		// 	dy = 1;
		*y = *y - dy;
		*x = *x - dda_data->x_scale * dy;
	}
	else
	{
		dy = *y - (int)*y;
		// if (dy == 0)
		// 	dy = 1;
		*y = *y - dy;
		*x = *x - dda_data->x_scale * dy;
	}
	dda_data->horizontal_length = fabs(dy / fabs(cos((90 - dda_data->angle) * ( M_PI / 180))));
	// printf("first horizontal intersec x=%f y=%f length=%f\n", *x, *y, dda_data->horizontal_length);
}

void get_next_horizontal_intersec(double *x, double *y, t_dda *dda_data)
{
	if (dda_data->quartile == 1)
		*x = *x + dda_data->x_scale;
	else if (dda_data->quartile == 2)
		*x = *x + dda_data->x_scale;
	else if (dda_data->quartile == 3)
		*x = *x - dda_data->x_scale;
	else
		*x = *x + -dda_data->x_scale;
	if (dda_data->quartile == 1 || dda_data->quartile == 2)
		*y = *y + 1;
	else
		*y = *y - 1;
	dda_data->horizontal_length += dda_data->delta_dist_horizontal;
	// printf("next horizontal intersec x=%f y=%f length=%f\n", *x, *y, dda_data->horizontal_length);
}

#include "cub3d.h"

void	get_first_vertical_intersec(double *x, double *y, t_dda *data)
{
	double	dx;

	if (data->angle == 90 || data->angle == 270)
		return ((void)(data->vertical_length = DBL_MAX));
	if (data->quartile == 1 || data->quartile == 4)
	{
		dx = (floor(*x) + 1) - *x;
		*y = *y + data->y_scale * dx;
		*x = floor(*x) + 1;
	}
	else if (data->quartile == 2)
	{
		dx = *x - (int)*x;
		*y = *y - data->y_scale * dx;
		*x = *x - dx;
	}
	else
	{
		dx = *x - (int)*x;
		*y = *y - data->y_scale * dx;
		*x = *x - dx;
	}
	data->vertical_length = \
		fabs(dx / fabs(sin((90 - data->angle) * (M_PI / 180))));
}

void	get_next_vertical_intersec(double *x, double *y, t_dda *data)
{
	if (data->quartile == 1 || data->quartile == 4)
		*x = *x + 1;
	else
		*x = *x - 1;
	if (data->quartile == 1 || data->quartile == 4)
		*y = *y + data->y_scale;
	else if (data->quartile == 2)
		*y = *y + (data->y_scale * -1);
	else
		*y = *y - data->y_scale;
	data->vertical_length += data->delta_dist_verti;
}

void	get_first_horizontal_intersec(double *x, double *y, t_dda *data)
{
	double	dy;

	if (data->angle == 0 || data->angle == 180)
		return ((void)(data->horizontal_length = DBL_MAX));
	if (data->quartile == 1)
	{
		dy = ((int)*y + 1) - *y;
		*y = *y + dy;
		*x = *x + (dy * data->x_scale);
	}
	else if (data->quartile == 2)
	{
		dy = ((int)*y + 1) - *y;
		*y = *y + dy;
		*x = *x + data->x_scale * dy;
	}
	else
	{
		dy = *y - (int)*y;
		*y = *y - dy;
		*x = *x - data->x_scale * dy;
	}
	data->horizontal_length = \
		fabs(dy / fabs(cos((90 - data->angle) * (M_PI / 180))));
}

void	get_next_horizontal_intersec(double *x, double *y, t_dda *data)
{
	if (data->quartile == 1)
		*x = *x + data->x_scale;
	else if (data->quartile == 2)
		*x = *x + data->x_scale;
	else if (data->quartile == 3)
		*x = *x - data->x_scale;
	else
		*x = *x + -data->x_scale;
	if (data->quartile == 1 || data->quartile == 2)
		*y = *y + 1;
	else
		*y = *y - 1;
	data->horizontal_length += data->delta_dist_hori;
}

#include "cub3d.h"

void	get_first_vertical_intersec(t_dda *data)
{
	double	dx;

	if (data->angle == 90 || data->angle == 270)
		return ((void)(data->vertical_length = DBL_MAX));
	if (data->quartile == 1 || data->quartile == 4)
	{
		dx = (floor(data->x_vertical) + 1) - data->x_vertical;
		data->y_vertical += data->y_scale * dx;
		data->x_vertical = floor(data->x_vertical) + 1;
	}
	else if (data->quartile == 2)
	{
		dx = data->x_vertical - (int)data->x_vertical;
		data->y_vertical -= data->y_scale * dx;
		data->x_vertical -= dx;
	}
	else
	{
		dx = data->x_vertical - (int)data->x_vertical;
		data->y_vertical -= data->y_scale * dx;
		data->x_vertical -= dx;
	}
	data->vertical_length = \
		fabs(dx / fabs(sin((90 - data->angle) * (M_PI / 180))));
}

void	get_next_vertical_intersec(t_dda *data)
{
	if (data->quartile == 1 || data->quartile == 4)
		data->x_vertical += 1;
	else
		data->x_vertical -= 1;
	if (data->quartile == 1 || data->quartile == 4)
		data->y_vertical += data->y_scale;
	else if (data->quartile == 2)
		data->y_vertical += (data->y_scale * -1);
	else
		data->y_vertical -= data->y_scale;
	data->vertical_length += data->delta_dist_verti;
}

void	get_first_horizontal_intersec(t_dda *data)
{
	double	dy;

	if (data->angle == 0 || data->angle == 180)
		return ((void)(data->horizontal_length = DBL_MAX));
	if (data->quartile == 1)
	{
		dy = ((int)data->y_horizontal + 1) - data->y_horizontal;
		data->y_horizontal += dy;
		data->x_horizontal += (dy * data->x_scale);
	}
	else if (data->quartile == 2)
	{
		dy = ((int)data->y_horizontal + 1) - data->y_horizontal;
		data->y_horizontal += dy;
		data->x_horizontal += data->x_scale * dy;
	}
	else
	{
		dy = data->y_horizontal - (int)data->y_horizontal;
		data->y_horizontal -= dy;
		data->x_horizontal -= data->x_scale * dy;
	}
	data->horizontal_length = \
		fabs(dy / fabs(cos((90 - data->angle) * (M_PI / 180))));
}

void	get_next_horizontal_intersec(t_dda *data)
{
	if (data->quartile == 1)
		data->x_horizontal += data->x_scale;
	else if (data->quartile == 2)
		data->x_horizontal += data->x_scale;
	else if (data->quartile == 3)
		data->x_horizontal -= data->x_scale;
	else
		data->x_horizontal += -data->x_scale;
	if (data->quartile == 1 || data->quartile == 2)
		data->y_horizontal += 1;
	else
		data->y_horizontal -= 1;
	data->horizontal_length += data->delta_dist_hori;
}

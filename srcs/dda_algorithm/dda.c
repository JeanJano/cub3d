#include "cub3d.h"

void	init_struct(t_dda *data, double player_x, double player_y, double angle)
{
	data->angle = angle;
	data->x_cos = cos(angle * (M_PI / 180));
	data->y_sin = sin(angle * (M_PI / 180));
	data->x_scale = (1 / data->y_sin) * data->x_cos;
	data->y_scale = (1 / data->x_cos) * data->y_sin;
	data->x_vertical = player_x;
	data->y_vertical = player_y;
	data->delta_dist_verti = fabs(1 / fabs(sin((90 - angle) * (M_PI / 180))));
	data->vertical_length = 0;
	data->x_horizontal = player_x;
	data->y_horizontal = player_y;
	data->delta_dist_hori = fabs(1 / fabs(cos((90 - angle) * (M_PI / 180))));
	data->horizontal_length = 0;
	if (angle >= 0 && angle < 90)
		data->quartile = 1;
	else if (angle >= 90 && angle < 180)
		data->quartile = 2;
	else if (angle >= 180 && angle < 270)
		data->quartile = 3;
	else if (angle >= 270 && angle < 360)
		data->quartile = 4;
}

int	check_map_vertical(double x, double y, t_dda data, t_parsing parsing_struct)
{	
	if (data.quartile == 1)
		y = floor(y);
	else if (data.quartile == 2)
	{
		x = x - 1;
		y = floor(y);
	}
	else if (data.quartile == 3)
	{
		x = x - 1;
		y = floor(y);
	}
	else
		y = floor(y);
	if ((int)y < 0 || (int)x < 0)
		return (0);
	if ((int)y >= parsing_struct.map_height || (int)x >= parsing_struct.map_width[(int)y])
		return (0);
	if (parsing_struct.map[(int)y][(int)x] == 1)
		return (1);
	return (0);
}

int	check_map_horizontal(double x, double y, t_dda data, t_parsing parsing_struct)
{
	if (data.quartile == 1)
		x = floor(x);
	else if (data.quartile == 2)
		x = floor(x);
	else if (data.quartile == 3)
	{
		x = floor(x);
		y = y - 1;
	}
	else
	{
		x = floor(x);
		y = y - 1;
	}
	if ((int)y < 0 || (int)x < 0)
		return (0);
	if ((int)y >= parsing_struct.map_height || (int)x >= parsing_struct.map_width[(int)y])
		return (0);
	if (parsing_struct.map[(int)y][(int)x] == 1)
		return (1);
	return (0);
}

void	get_hit_data(t_dda data, int hit_dir, t_dda_return *dda_return)
{
	if (hit_dir == VERTICAL_HIT)
	{
		dda_return->wall_orientation = VERTICAL_HIT;
		if (data.quartile == 1 || data.quartile == 4)
			dda_return->wall_orientation2 = WEST_WALL;
		else
			dda_return->wall_orientation2 = EST_WALL;
		dda_return->index_hit_column = data.y_vertical - floor(data.y_vertical);
		dda_return->distance = data.vertical_length;
	}
	else
	{
		dda_return->wall_orientation = HORIZONTAL_HIT;
		if (data.quartile == 1 || data.quartile == 2)
			dda_return->wall_orientation2 = NORTH_WALL;
		else
			dda_return->wall_orientation2 = SOUTH_WALL;
		dda_return->index_hit_column = data.x_horizontal - floor(data.x_horizontal);
		dda_return->distance = data.horizontal_length;
	}
}

t_dda_return	*get_vector_distance(double player_x, double player_y, double angle, t_parsing parsing_struct)
{
	t_dda			data;
	t_dda_return	*dda_return;

	dda_return = malloc(sizeof(t_dda_return));
	init_struct(&data, player_x, player_y, angle);
	get_first_vertical_intersec(&data.x_vertical, &data.y_vertical, &data);
	get_first_horizontal_intersec(&data.x_horizontal, &data.y_horizontal, &data);
	while (1)
	{
		if (check_map_vertical(data.x_vertical, data.y_vertical, data, parsing_struct) && data.vertical_length < data.horizontal_length)
		{
			get_hit_data(data, VERTICAL_HIT, dda_return);
			return (dda_return);
		}
		if (check_map_horizontal(data.x_horizontal, data.y_horizontal, data, parsing_struct) && data.horizontal_length < data.vertical_length)
		{
			get_hit_data(data, HORIZONTAL_HIT, dda_return);
			return (dda_return);
		}
		if (data.vertical_length < data.horizontal_length)
			get_next_vertical_intersec(&data.x_vertical, &data.y_vertical, &data);
		else
			get_next_horizontal_intersec(&data.x_horizontal, &data.y_horizontal, &data);
	}
	return (0);
}

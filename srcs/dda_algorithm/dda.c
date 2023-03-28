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

void init_dda_struct(t_dda *dda_data, double player_x, double player_y, double angle)
{
	dda_data->angle = angle;
	dda_data->x_cos = cos(angle * ( M_PI / 180));
    dda_data->y_sin = sin(angle * (M_PI / 180));
	dda_data->x_scale = (1 / dda_data->y_sin) * dda_data->x_cos; // x scale to move 1 y
	dda_data->y_scale = (1 / dda_data->x_cos) * dda_data->y_sin; // y scale to move 1 x

	dda_data->x_vertical = player_x;
	dda_data->y_vertical = player_y;
	dda_data->delta_dist_vertical = fabs(1 / fabs(sin((90 - angle) * ( M_PI / 180))));
	// printf("delta dist vertical=%f\n", dda_data->delta_dist_vertical);
	dda_data->vertical_length = 0;

    dda_data->x_horizontal = player_x;
    dda_data->y_horizontal = player_y;
	dda_data->delta_dist_horizontal = fabs(1 / fabs(cos((90 - angle) * ( M_PI / 180))));
	// printf("delta dist hori=%f\n", dda_data->delta_dist_horizontal);
	dda_data->horizontal_length = 0;

	if (angle >= 0 && angle < 90)
	{
		dda_data->quartile = 1;
	}
	else if (angle >= 90 && angle < 180)
	{
		dda_data->quartile = 2;
	}
	else if (angle >= 180 && angle < 270)
	{
		dda_data->quartile = 3;
	}
	else if (angle >= 270 && angle < 360)
	{
		dda_data->quartile = 4;
	}
}

int check_map_vertical(double x, double y, t_dda dda_data, t_parsing parsing_struct)
{	
	if (dda_data.quartile == 1)
	{
		//x = x;
		y = floor(y);
	}
	else if (dda_data.quartile == 2)
	{
		x = x - 1;
		y = floor(y);
	}
	else if (dda_data.quartile == 3)
	{
		x = x - 1;
		y = floor(y);
	}
	else
	{
	//	x = x;
		y = floor(y);
	}
	if ((int)y < 0 || (int)x < 0 || (int)y >= parsing_struct.map_height || (int)x >= parsing_struct.map_width[(int)y])
		return (0);
	// printf("CHECKING VERTI x=%d y=%d map_value=%d\n", (int)x, (int)y, parsing_struct.map[(int)y][(int)x]);
	if (parsing_struct.map[(int)y][(int)x] == 1)
	{
		// printf("TROUVE\n");
		return (1);
	}
	return (0);
}

int check_map_horizontal(double x, double y, t_dda dda_data, t_parsing parsing_struct)
{
	if (dda_data.quartile == 1)
	{
		x = floor(x);
	}
	else if (dda_data.quartile == 2)
	{
		x = floor(x);
	}
	else if (dda_data.quartile == 3)
	{
		x = floor(x);
		y = y - 1;
	}
	else
	{
		x = floor(x);
		y = y - 1;
	}
	if ((int)y < 0 || (int)x < 0  || (int)y >= parsing_struct.map_height || (int)x >= parsing_struct.map_width[(int)y])
		return (0);
	// printf("CHECKING HORI x=%d y=%d\n----------------\n", (int)x, (int)y);
	if (parsing_struct.map[(int)y][(int)x] == 1)
	{
		// printf("TROUVE\n");
		return (1);
	}
	return (0);
}

void get_hit_data(t_dda dda_data, int hit_dir, t_dda_return *dda_return)
{
	if (hit_dir == VERTICAL_HIT)
	{
		dda_return->wall_orientation = VERTICAL_HIT;
		if (dda_data.quartile == 1 || dda_data.quartile == 4)
		{
			dda_return->wall_orientation2 = WEST_WALL;
		}
		else
			dda_return->wall_orientation2 = EST_WALL;
		dda_return->index_hit_column = dda_data.y_vertical - floor(dda_data.y_vertical);
	}
	else
	{
		dda_return->wall_orientation = HORIZONTAL_HIT;
		if (dda_data.quartile == 1 || dda_data.quartile == 2)
			dda_return->wall_orientation2 = NORTH_WALL;
		else
			dda_return->wall_orientation2 = SOUTH_WALL;
		dda_return->index_hit_column = dda_data.x_horizontal - floor(dda_data.x_horizontal);
	}
	// printf("INDEX=%f\n", dda_return->index_hit_column);
}

t_dda_return *get_vector_distance(double player_x, double player_y, double angle, t_parsing parsing_struct)
{
	t_dda dda_data;
	t_dda_return *dda_return = malloc(sizeof(t_dda_return));

	init_dda_struct(&dda_data, player_x, player_y, angle);
	// printf("x_cos=%f y_sin=%f\n", x_cos, y_sin);
	// printf("x_scale=%f y_scale=%f\n", x_scale, y_scale);

	get_first_vertical_intersec(&dda_data.x_vertical, &dda_data.y_vertical, &dda_data);
	get_first_horizontal_intersec(&dda_data.x_horizontal, &dda_data.y_horizontal, &dda_data);
	// printf("delta_dist_vertical=%f delta_dist_horizontal=%f\n", dda_data.delta_dist_vertical, dda_data.delta_dist_horizontal);
	while (1)
	{
		if (check_map_vertical(dda_data.x_vertical, dda_data.y_vertical, dda_data, parsing_struct) && dda_data.vertical_length < dda_data.horizontal_length)
		{
			dda_return->distance = dda_data.vertical_length;
			// printf("result verti angle=%f x=%f y%f length=%f\n", angle, dda_data.x_vertical, dda_data.y_vertical, dda_data.vertical_length);
			get_hit_data(dda_data, VERTICAL_HIT, dda_return);

			return (dda_return);
		}
		if (check_map_horizontal(dda_data.x_horizontal, dda_data.y_horizontal, dda_data, parsing_struct) && dda_data.horizontal_length < dda_data.vertical_length)
		{
			dda_return->distance = dda_data.horizontal_length;
			get_hit_data(dda_data, HORIZONTAL_HIT, dda_return);
			// printf("result hori angle=%f x=%f y%f length=%f\n", angle, dda_data.x_horizontal, dda_data.y_horizontal, dda_data.horizontal_length);
			return (dda_return);
		}

		if (dda_data.vertical_length < dda_data.horizontal_length)
			get_next_vertical_intersec(&dda_data.x_vertical, &dda_data.y_vertical, &dda_data);
		else
			get_next_horizontal_intersec(&dda_data.x_horizontal, &dda_data.y_horizontal, &dda_data);
	}
	return 0;
}
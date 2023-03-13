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

int check_map_vertical(double x, double y, int quartile, t_parsing parsing_struct)
{	
	if (quartile == 1)
	{
		x = x;
		y = floor(y);
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x, (int)y);
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (/* printf("TROUVE\n"), */ 1);
	}
	else if (quartile == 2)
	{
		x = x;
		y = floor(y);
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x - 1, (int)y);
		if (parsing_struct.map[(int)y][(int)x - 1] == 1)
			return (/* printf("TROUVE\n"), */1);
	}
	else if (quartile == 3)
	{
		x = x;
		y = floor(y);
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x - 1, (int)y);
		if (parsing_struct.map[(int)y][(int)x - 1] == 1)
			return (/* printf("TROUVE\n"), */1);
	}
	else
	{
		x = x;
		y = floor(y);
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x, (int)y);
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (/* printf("TROUVE\n"), */1);
	}
	return (0);
}

int check_map_horizontal(int x, int y, int quartile, t_parsing parsing_struct)
{
	if (quartile == 1)
	{
		x = floor(x);
		y = y;
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x, (int)y);
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (/* printf("TROUVE"), */ 1);
	}
	else if (quartile == 2)
	{
		x = floor(x);
		y = y;
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x, (int)y);
		if (parsing_struct.map[(int)y][(int)x] == 1)
			return (/* printf("TROUVE"), */ 1);
	}
	else if (quartile == 3)
	{
		x = floor(x);
		y = y;
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x - 1, (int)y - 1);
		if (parsing_struct.map[(int)y - 1][(int)x - 1] == 1)
			return (/* printf("TROUVE"), */ 1);
	}
	else
	{
		x = floor(x);
		y = y;
		// printf("CHECKING x=%d y=%d\n----------------\n", (int)x, (int)y - 1);
		if (parsing_struct.map[(int)y - 1][(int)x] == 1)
			return (/* printf("TROUVE"), */ 1);
	}
	return (0);
}

void init_dda_struct(t_dda *dda_data, double player_x, double player_y, double angle)
{
	dda_data->x_cos = cos(angle * ( M_PI / 180));
    dda_data->y_sin = sin(angle * (M_PI / 180));
	dda_data->x_scale = (1 / dda_data->y_sin) * dda_data->x_cos; // x scale to move 1 y
	dda_data->y_scale = (1 / dda_data->x_cos) * dda_data->y_sin; // y scale to move 1 x

	dda_data->x_vertical = player_x;
	dda_data->y_vertical = player_y;
	dda_data->vertical_length = 0;

    dda_data->x_horizontal = player_x;
    dda_data->y_horizontal = player_y;
	dda_data->horizontal_length = 0;

	// int map_x = (int)player_x;
	// int step_x;
	// int map_y = (int)player_y;
	// int step_y;

	if (angle >= 0 && angle < 90)
	{
		// step_x = 1;
		// step_y = 1;
		dda_data->quartile = 1;
	}
	else if (angle >= 90 && angle < 180)
	{
		// step_x = -1;
		// step_y = 1;
		dda_data->quartile = 2;
	}
	else if (angle >= 180 && angle < 270)
	{
		// step_x = -1;
		// step_y = -1;
		dda_data->quartile = 3;
	}
	else if (angle >= 270 && angle < 360)
	{
		// step_x = 1;
		// step_y = -1;
		dda_data->quartile = 4;
	}
}

double vertical_check(t_dda dda_data, t_parsing parsing_struct)
{
	double	x_vertical = dda_data.x_vertical;
	double	y_vertical = dda_data.y_vertical;
	double	quartile = dda_data.quartile;
	double	y_scale = dda_data.y_scale;

	get_first_vertical_intersec(&x_vertical, &y_vertical, dda_data);
	// printf("first vertical intersec x=%f y=%f\n", x_vertical, y_vertical);
    while (y_vertical >= 0 && y_vertical < parsing_struct.map_height && x_vertical >= 0 && x_vertical < parsing_struct.map_width[(int)y_vertical])
    {
		if (check_map_vertical(x_vertical, y_vertical, quartile, parsing_struct))
			break ;
		get_next_vertical_intersec(&x_vertical, &y_vertical, y_scale, quartile);
		// printf("next vertical intersec x=%f y=%f\n", x_vertical, y_vertical);
    }
	return (fabs(x_vertical - dda_data.player_x) * fabs(x_cos) + fabs(y_vertical - player_y) * fabs(y_sin));
}

double horizontal_check(t_dda dda_data, t_parsing parsing_struct)
{
	double	x_horizontal = dda_data.x_vertical;
	double	y_horizontal = dda_data.y_vertical;
	double	quartile = dda_data.quartile;
	double	x_scale = dda_data.y_scale;

	get_first_horizontal_intersec(&x_horizontal, &y_horizontal, x_scale, quartile);
	// printf("first horizontal intersec x=%f y=%f\n", x_horizontal, y_horizontal);
	while (y_horizontal >= 0 && y_horizontal < parsing_struct.map_height && x_horizontal >= 0 && x_horizontal < parsing_struct.map_width[(int)y_horizontal])
	{
		if (check_map_horizontal(x_horizontal, y_horizontal, quartile, parsing_struct))
			break ;
		get_next_horizontal_intersec(&x_horizontal, &y_horizontal, x_scale, quartile);
		// printf("next horizontal intersec x=%f y=%f\n", x_horizontal, y_horizontal);
	}
	horizontal_length = fabs(x_horizontal - player_x) * fabs(x_cos) + fabs(y_horizontal - player_y) * fabs(y_sin);
	return (horizontal_length);
}


double get_vector_distance(double player_x, double player_y, double angle, t_parsing parsing_struct)
{
	t_dda dda_data;
 
	init_dda_struct(&dda_data, player_x, player_y, angle);
	// printf("x_cos=%f y_sin=%f\n", x_cos, y_sin);
	// printf("x_scale=%f y_scale=%f\n", x_scale, y_scale);

	// VERTICAL CHECK
	// printf("--------------------------------------\n|           VERTICAL CHECK           |\n--------------------------------------\n");
	dda_data.vertical_length = vertical_check(dda_data, parsing_struct);
	// HORIZONTAL CHECK
	// printf("--------------------------------------\n|          HORIZONTAL CHECK          |\n--------------------------------------\n");
	dda_data.horizontal_length = horizontal_check(dda_data, parsing_struct);
	// GET BEST LENGTH
	if (dda_data.vertical_length > dda_data.horizontal_length)
		return (dda_data.horizontal_length);
	else
		return (dda_data.vertical_length);
}
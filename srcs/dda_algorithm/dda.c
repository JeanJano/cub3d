/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2023/04/12 17:37:08 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_map_vertical(t_dda data, t_parsing parsing_struct)
{
	int	x;
	int	y;

	if (data.vertical_length > data.horizontal_length)
		return (0);
	x = (int)data.x_vertical;
	if (data.quartile == 2 || data.quartile == 3)
		x = (int)(data.x_vertical - 1);
	y = (int)floor(data.y_vertical);
	if (y < 0 || x < 0)
		return (0);
	if (y >= parsing_struct.map_height || x >= parsing_struct.map_width[y])
		return (0);
	if (parsing_struct.map[y][x] == 1)
		return (1);
	return (0);
}

int	check_map_horizontal(t_dda data, t_parsing parsing_struct)
{
	int	x;
	int	y;

	if (data.horizontal_length > data.vertical_length)
		return (0);
	y = (int)data.y_horizontal;
	if (data.quartile == 3 || data.quartile == 4)
		y = (int)(data.y_horizontal - 1);
	x = (int)floor(data.x_horizontal);
	if (y < 0 || x < 0)
		return (0);
	if (y >= parsing_struct.map_height || x >= parsing_struct.map_width[y])
		return (0);
	if (parsing_struct.map[y][x] == 1)
		return (1);
	return (0);
}

void	get_hit_data(t_dda data, int hit_dir, t_dda_return *dda_return)
{
	if (hit_dir == VERTICAL_HIT)
	{
		dda_return->wall_orientation = VERTICAL_HIT;
		if (data.quartile == 1 || data.quartile == 4)
			dda_return->wall_orientation = WEST_WALL;
		else
			dda_return->wall_orientation = EST_WALL;
		dda_return->index_hit = data.y_vertical - floor(data.y_vertical);
		dda_return->distance = data.vertical_length;
	}
	else
	{
		dda_return->wall_orientation = HORIZONTAL_HIT;
		if (data.quartile == 1 || data.quartile == 2)
			dda_return->wall_orientation = NORTH_WALL;
		else
			dda_return->wall_orientation = SOUTH_WALL;
		dda_return->index_hit = data.x_horizontal - floor(data.x_horizontal);
		dda_return->distance = data.horizontal_length;
	}
}

t_dda_return	*get_dist(double x, double y, double angle, t_parsing parsing)
{
	t_dda			data;
	t_dda_return	*dda_return;

	dda_return = malloc(sizeof(t_dda_return));
	init_struct(&data, x, y, angle);
	get_first_vertical_intersec(&data);
	get_first_horizontal_intersec(&data);
	while (1)
	{
		if (check_map_vertical(data, parsing))
		{
			get_hit_data(data, VERTICAL_HIT, dda_return);
			return (dda_return);
		}
		if (check_map_horizontal(data, parsing))
		{
			get_hit_data(data, HORIZONTAL_HIT, dda_return);
			return (dda_return);
		}
		if (data.vertical_length < data.horizontal_length)
			get_next_vertical_intersec(&data);
		else
			get_next_horizontal_intersec(&data);
	}
	return (0);
}

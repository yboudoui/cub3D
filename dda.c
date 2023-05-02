/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 16:04:59 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
static t_dda	dda_horizontal(t_vec2f pos, float angle)
{
	t_dda	out;

	if (180 > angle && angle > 0)
	{
		out.point.y = round(pos.y) - 1;
		out.pad.y = -1;
	}
	else
	{
		out.point.y = round(pos.y) + 1;
		out.pad.y = 1;
	}
	angle =  (angle * M_PI / 180.0);
	out.point.x = pos.x + (pos.y - out.point.y) / tanf(angle);
	out.pad.x = 1 / tanf(angle);
	return (out);
}

static t_dda	dda_vertical(t_vec2f pos, float angle)
{
	t_dda	out;

	if (270 < angle && angle > 90)
	{
		out.point.x = round(pos.x) - 1;
		out.pad.x = 1;
	}
	else
	{
		out.point.x = round(pos.x) + 1;
		out.pad.x = -1;
	}
	angle =  (angle * M_PI / 180.0);
	out.point.y = pos.y + (pos.x - out.point.x) * tanf(angle);
	out.pad.y = 1 * tanf(angle);
	return (out);
}

static bool	map_hit(t_map map, t_vec2 point)
{
	map.size = add_vec2(map.size, vec2(-1, -1));
	return (0
			|| !vec2i_in_range(point, vec2(0,0), map.size)
			|| map.data[point.y][point.x] == '1');
}


float	dda_checker(t_vec2f pos, float angle, t_map map)
{
	t_dda	horizontal;
	t_dda	vertical;

	t_vec2f	new_h;
	t_vec2f	new_v;

	float	dist_h;
	float	dist_v;

	float	total_len;

	total_len = 0;

	horizontal = dda_horizontal(pos, angle);
	vertical = dda_vertical(pos, angle);


//	new_h = vec2f_add(pos, horizontal.pad);
//	new_v = vec2f_add(pos, vertical.pad);

	new_h = horizontal.point;
	new_v = vertical.point;

	while (!map_hit(map, vec2f_floor(pos)))
	{
		dist_h = vec2f_dist(pos, new_h);
		dist_v = vec2f_dist(pos, new_v);
		if (dist_h < dist_v)
		{
			pos = new_h;
			new_h = vec2f_add(pos, horizontal.pad);
			total_len += dist_h;
		}
		else
		{
			pos = new_v;
			new_v = vec2f_add(pos, vertical.pad);
			total_len += dist_v;
		}
	}
	return (total_len);
}
*/

/* static float	dda_horizontal(t_vec2f pos, float angle, t_map map, t_screen *screen) */
/* { */
/* 	t_dda	out; */
/* 	float	len; */
/* 	t_vec2	p; */

/* 	t_quad	block; */

/* 	t_data	*data; */
/* 	data = screen->data; */

/* 	if (angle == 180 || angle == 0) */
/* 		return (INFINITY); */
/* 	if (180 > angle)// && angle > 0) */
/* 	{ */
/* 		out.point.y = round(pos.y); */
/* 		out.pad.y = -1; */
/* 	} */
/* 	else */
/* 	{ */
/* 		out.point.y = round(pos.y) - 1; */
/* 		out.pad.y = 1; */
/* 	} */
/* 	angle =  tanf(angle * M_PI / 180.0); */
/* 	out.point.x = pos.x + (pos.y - out.point.y) / angle; */
/* 	out.pad.x = 1 / angle; */

/* 	p = (t_vec2){ */
/* 		.x = (int)out.point.x, */
/* 		.y = (int)out.point.y, */
/* 	}; */
/* 	while (vec2i_in_range(p, vec2(0,0), map.size)) */
/* 	{ */
/* 		block = rectangle(mul_vec2(p, (t_vec2){16, 16}), (t_vec2){3, 3}, (t_color){.raw = 0}); */
/* 		image_put_empty_quad(data->dda_debugger, block); */

/* 		len = vec2f_dist(out.point, pos); */
/* 		if (map.data[p.y][p.x] == '1') */
/* 		{ */

/* //			printf("[%d %d] = %c\n", p.x, p.y, map.data[p.y][p.x]); */
/* 			return(len); */
/* 		} */
/* 		out.point = vec2f_add(out.point, out.pad); */
/* / 		p = (t_vec2){ *1/ */
/* 			.x = (int)out.point.x, */
/* 			.y = (int)out.point.y, */
/* 		}; */
/* 	} */
/* 	return (INFINITY); */
/* } */

bool player_is_facing_right(float angle)
{
	return (angle < 90 || angle > 270);
}

float angle_to_rad(float angle)
{
	return (angle * (M_PI / 180.0));
}

bool is_wall(t_map map, t_dda dda)
{
	int grid_x;
	int grid_y;

	grid_x = (int)dda.point.x / TILE_SIZE; 
	grid_y = (int)dda.point.y / TILE_SIZE;
	if (grid_x < 0 || grid_y < 0 || grid_x >= map.size.x || grid_y >= map.size.y)
		return (true);
	/* printf("grid_x = %d, grid_y = %d\n", grid_x, grid_y); */
	return (map.data[grid_y][grid_x] == '1');
}

float euclidean_dist_to_wall(t_dda dda, t_vec2f player_pos) // euclidean distance can be used in all direction
{
	float x_diff;
	float y_diff;

	x_diff = dda.point.x - player_pos.x;
	y_diff = dda.point.y - player_pos.y;
	return (sqrtf(x_diff * x_diff + y_diff * y_diff));//sum of two value squared is always positive
}

t_vec2 pl_gridpos_to_worldpos(t_vec2f player_pos)
{
	return ((t_vec2){
		.x = (int)player_pos.x * TILE_SIZE,
		.y = (int)player_pos.y * TILE_SIZE,
	});
}

static float	dda_vertical(t_vec2f player_pos, float angle, t_map map, t_screen *screen)
{
	t_dda	out;
	t_data *data;
	/* t_quad	block; */
	data = screen->data;


	/* p_world_pos = pl_gridpos_to_worldpos(player_pos); */
	/* printf("p_world_pos = [%d %d]\n", p_world_pos.x, p_world_pos.y); */
	if (player_is_facing_right(angle))
	{
		out.point.x = (player_pos.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		out.pad.x = TILE_SIZE;
	}
	else
	{
		out.point.x = (player_pos.x / TILE_SIZE) * TILE_SIZE - 1;
		out.pad.x = -TILE_SIZE;
	}
	out.point.y = player_pos.y + (player_pos.x - out.point.x) * tanf(angle_to_rad(angle));
	out.pad.y = TILE_SIZE * tanf(angle_to_rad(angle));
	while (!is_wall(map, out))
	{
		/* printf("player.x = %d, player.y = %d\n", p_world_pos.x, p_world_pos.y); */
		/* block = rectangle(mul_vec2(p, (t_vec2){16, 16}), (t_vec2){3, 3}, (t_color){.raw = 0}); */
		/* image_put_empty_quad(data->dda_debugger, block); */
		out.point.x = out.point.x + out.pad.x;
		out.point.y = out.point.y + out.pad.y;
	}
	return (euclidean_dist_to_wall(out, player_pos));
}

bool player_is_facing_up(float angle)
{
	return (angle > 0 && angle < 180);
}

bool player_is_facing_left(float angle)
{
	return (angle > 90 && angle < 270);
}

static float dda_horizontal(t_vec2f player_pos, float angle, t_map map, t_screen *screen)
{
	t_dda	out;
	t_data	*data;
	/* t_quad	block; */
	data = screen->data;

	/* printf("p_world_pos = [%d %d]\n", p_world_pos.x, p_world_pos.y); */
	if (player_is_facing_up(angle))
	{
		out.point.y = (player_pos.y / TILE_SIZE) * TILE_SIZE - 1;
		out.pad.y = -TILE_SIZE;
	}
	else
	{
		out.point.y = (player_pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		out.pad.y = TILE_SIZE;
	}
	out.point.x = player_pos.x + (player_pos.y - out.point.y) / tanf(angle_to_rad(angle));
	out.pad.x = TILE_SIZE / tanf(angle_to_rad(angle));

	if (player_is_facing_left(angle))
	{
		out.pad.x = -out.pad.x;
	}

	while (!is_wall(map, out))
	{
		/* printf("player.x = %f, player.y = %f\n", player_pos.x, player_pos.y); */
		/* block = rectangle(mul_vec2(p, (t_vec2){16, 16}), (t_vec2){3, 3}, (t_color){.raw = 0}); */
		/* image_put_empty_quad(data->dda_debugger, block); */
		out.point.x = out.point.x + out.pad.x;
		out.point.y = out.point.y + out.pad.y;
	}
	return (euclidean_dist_to_wall(out, player_pos));
}

/* static float	dda_vertical(t_vec2f pos, float angle, t_map map, t_screen *screen) */
/* { */
/* 	t_dda	out; */
/* 	float	len; */
/* 	t_vec2	p; */

/* 	t_data	*data; */
/* 	t_quad	block; */
/* 	data = screen->data; */


/* 	if (270 == angle || angle == 90) */
/* 		return (INFINITY); */
/* 	if (270 > angle && angle > 90) */
/* 	{ */
/* 		out.point.x = round(pos.x) - 1; */
/* 		out.pad.x = -1; */
/* 	} */
/* 	else */
/* 	{ */
/* 		out.point.x = round(pos.x); */
/* 		out.pad.x = 1; */
/* 	} */
/* 	angle =  tanf(angle * M_PI / 180.0); */
/* 	out.point.y = pos.y + (pos.x - out.point.x) * angle; */
/* 	out.pad.y = 1 * angle; */

/* 	p = (t_vec2){ */
/* 		.x = (int)out.point.x, */
/* 		.y = (int)out.point.y, */
/* 	}; */

/* //	printf("_____________\n"); */
/* //	printf("%f %f\n", out.point.x, out.point.y); */
/* //	printf("%d %d\n", p.x, p.y); */
/* //	printf("%f %f\n", out.pad.x, out.pad.y); */

/* 	while (vec2i_in_range(p, vec2(0,0), map.size)) */
/* 	{ */
/* 		block = rectangle(mul_vec2(p, (t_vec2){16, 16}), (t_vec2){3, 3}, (t_color){.raw = 0}); */
/* 		image_put_empty_quad(data->dda_debugger, block); */
/* 		len = vec2f_dist(out.point, pos); */
/* 		if (map.data[p.y][p.x] == '1') */
/* 		{ */
/* 			printf("[%d %d] = %c\n", p.x, p.y, map.data[p.y][p.x]); */
/* 			return(len); */
/* 		} */
/* 		out.point = vec2f_add(out.point, out.pad); */
/* 		p = (t_vec2){ */
/* 			.x = (int)out.point.x, */
/* 			.y = (int)out.point.y, */
/* 		}; */
/* 	} */
/* 	return (INFINITY); */
/* } */

float	dda_checker(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	float	dist_h;
	float	dist_v;
	t_data	*data;

	data = screen->data;

//	printf("%f\n", angle);
	map.size = add_vec2(map.size, vec2(-1, -1));
	/* image_clear(data->dda_debugger, (t_color){.raw = 0xFFFFFFFF}); */
	dist_h = dda_horizontal(pos, angle, map, screen);
	dist_v = dda_vertical(pos, angle, map, screen);
	/* printf("dist_v = %f, dist_h = %f\n", dist_v, dist_h); */
	/* printf("%f %f\n", dist_h, dist_v); */
	if (dist_h < dist_v)
		return (dist_h);
	return (dist_v);
}

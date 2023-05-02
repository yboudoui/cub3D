/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 17:23:37 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_screen *s, t_color ground, t_color ceiling)
{
	t_quad	g;
	t_quad	c;

	g = rectangle(vec2(0,0), vec2(s->size.x, s->size.y / 2), ground);
	c = rectangle(vec2(0,s->size.y / 2), vec2(s->size.x, s->size.y / 2), ceiling);
	image_put_quad(s->img, c);
	image_put_quad(s->img, g);
}

#define DIST 800

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}


void draw_minimap(t_screen *screen, t_vec2f player_pos)
{
    t_data *data = screen->data;
    t_map map = data->map;
    int tile_width = 16; // Width of a tile in pixels
    int tile_height = 16; // Height of a tile in pixels

    image_clear(data->mini_map, (t_color){.raw = 0xFFFFFF});
    for (int y = 0; y < map.size.y; y++)
    {
        for (int x = 0; x < map.size.x; x++)
        {
            t_quad block;
            t_color color;

            if (map.data[y][x] == '1')
            {
                color.raw = 0x000000; // Black color for walls
            }
            else
            {
                color.raw = 0xFFFFFF; // White color for empty spaces
            }

            block = rectangle((t_vec2){x * tile_width, y * tile_height}, (t_vec2){tile_width, tile_height}, color);
            image_put_empty_quad(data->mini_map, block);
        }
    }

    // Draw grid lines
    t_color grid_color = {.raw = 0xAAAAAA}; // Gray color for grid lines
    for (int x = 0; x <= map.size.x; x++)
    {
        t_pixel start = pixel((t_vec2){x * tile_width, 0}, grid_color);
        t_pixel end = pixel((t_vec2){x * tile_width, map.size.y * tile_height}, grid_color);
        image_put_line(data->mini_map, start, end);
    }
    for (int y = 0; y <= map.size.y; y++)
    {
        t_pixel start = pixel((t_vec2){0, y * tile_height}, grid_color);
        t_pixel end = pixel((t_vec2){map.size.x * tile_width, y * tile_height}, grid_color);
        image_put_line(data->mini_map, start, end);
    }
    // Draw black walls and red player position
    for (int y = 0; y < map.size.y; y++)
    {
        for (int x = 0; x < map.size.x; x++)
        {
            if (map.data[y][x] == '1')
            {
                t_quad block;
                t_color color;

                color.raw = 0x000000; // Black color for walls
                block = rectangle((t_vec2){x * tile_width, y * tile_height}, (t_vec2){tile_width, tile_height}, color);
                image_put_empty_quad(data->mini_map, block);
            }
        }
    }
    // Draw the player position on the minimap
    int player_x = (int)(player_pos.x);
    int player_y = (int)(player_pos.y);
    t_quad player_block = rectangle((t_vec2){player_x * tile_width, player_y * tile_height}, (t_vec2){tile_width, tile_height}, (t_color){.raw = 0xFF0000}); // Red color for the player
    image_put_empty_quad(data->mini_map, player_block);
}

t_vec2f cast_ray(t_vec2f player_pos, float angle, t_map map, t_screen *screen)
{
    float distance_to_wall = dda_checker(player_pos, angle, map, screen);

    t_vec2f ray_end;
    ray_end.x = player_pos.x + cosf(angle_to_rad(angle)) * distance_to_wall;
    ray_end.y = player_pos.y + sinf(angle_to_rad(angle)) * distance_to_wall;

    return (ray_end);
}

void update_map(t_screen *screen, t_vec2f player_pos, float player_view, int num_rays, float fov)
{
    t_data *data = screen->data;

    // Clear the minimap and draw the walls, empty spaces, and grid lines
    draw_minimap(screen, player_pos);

    // Draw the player position on the minimap
    int player_x = (int)(player_pos.x);
    int player_y = (int)(player_pos.y);
    t_quad player_block = rectangle((t_vec2){player_x * 16, player_y * 16}, (t_vec2){16, 16}, (t_color){.raw = 0xFF0000}); // Red color for the player
    image_put_empty_quad(data->mini_map, player_block);

    // Draw rays being launched from the player's position on the minimap
    float angle_step = fov / num_rays;
    float angle = player_view - (fov / 2);
    t_color ray_color = {.raw = 0x0000FF}; // Blue color for the rays

    for (int i = 0; i < num_rays; i++)
    {
        t_vec2f ray_end = cast_ray(player_pos, angle, screen->data->map, screen); // Assuming you have a function to cast a ray and get the endpoint
        t_pixel start = pixel((t_vec2){player_x * 16 + 8, player_y * 16 + 8}, ray_color);
        t_pixel end = pixel((t_vec2){ray_end.x * 16 + 8, ray_end.y * 16 + 8}, ray_color);
        image_put_line(data->mini_map, start, end);
        angle += angle_step;
    }
}

/* void	draw_minimap_grid(t_screen *screen) */
/* { */
/* 	t_data	*data; */
/* 	t_quad	block; */
/* 	const t_vec2	block_size = {16, 16}; */
/* 	t_vec2	pos; */

/* 	data = screen->data; */
/* 	pos = (t_vec2){0, 0}; */
/* 	while (pos.y < data->map.size.y) */
/* 	{ */
/* 		pos.x = 0; */
/* 		while (pos.x < data->map.size.x) */
/* 		{ */
/* 			block = rectangle(mul_vec2(pos, block_size), block_size, (t_color){.raw = 0xDDDDDD}); */
/* 			image_put_empty_quad(data->mini_map, block); */
/* 			pos.x += 1; */
/* 		} */
/* 		pos.y += 1; */
/* 	} */
/* //	image_put_to_image(data->mini_map, screen->img); */
/* } */


/* void	draw_minimap(t_screen *screen) */
/* { */
/* 	t_data	*data; */
/* 	t_quad	block; */
/* 	const t_vec2	block_size = {16, 16}; */
/* 	t_vec2	pos; */

/* 	data = screen->data; */
/* 	image_clear(data->mini_map, (t_color){.raw = 0xFFFFFF}); */
/* 	draw_minimap_grid(screen); */
/* 	pos = (t_vec2){0, 0}; */
/* 	while (pos.y < data->map.size.y) */
/* 	{ */
/* 		pos.x = 0; */
/* 		while (pos.x < data->map.size.x) */
/* 		{ */
/* 			if (data->map.data[pos.y][pos.x] == '1') */
/* 			{ */
/* 				block = rectangle(mul_vec2(pos, block_size), block_size, (t_color){.raw = 0x0}); */
/* 				image_put_empty_quad(data->mini_map, block); */
/* 			} */
/* 			pos.x += 1; */
/* 		} */
/* 		pos.y += 1; */
/* 	} */
/* } */

/* void	update_minimap(t_screen *screen) */
/* { */
/* 	int	index; */
/* 	t_data	*data; */
/* 	t_pixel	new; */
/* 	t_pixel	pos; */

/* 	draw_minimap(screen); */
/* 	data = screen->data; */
/* 	index = 0; */
/* 	pos.color.raw = 0xFF0000; */
/* 	pos.coord.x = (data->player.pos.x * 16); */
/* 	pos.coord.y = (data->player.pos.y * 16); */
/* 	while (index < screen->size.x) */
/* 	{ */
/* 		new = pos; */
/* 		new.coord.x += cos(deg_to_rad(data->walls[index].angle)) * (data->walls[index].distance * 16); */
/* 		new.coord.y -= sin(deg_to_rad(data->walls[index].angle)) * (data->walls[index].distance * 16); */
/* 		image_put_line(data->mini_map, pos, new); */
/* 		index += 1; */
/* 	} */
/* } */

void	update_wall_distance(t_screen *screen)
{
	t_data	*data;
	int		index;
	float	angle;
	float	pad = 60.0 / screen->size.x;

	data = screen->data;
	/* screen->size.x = 1; */
	index = 0;
	while (index < screen->size.x)
	{
//		angle = (data->player.view) + (pad * index);
		angle = (data->player.view - 30) + (pad * index);
		data->walls[index].distance = dda_checker(data->player.tiled_pos, angle, data->map, screen);
		data->walls[index].angle = angle;
		index += 1;
	}
}

/* void draw_minimap(t_screen *screen, t_vec2f player_pos) */
/* { */
/*     t_data *data = screen->data; */
/*     t_map map = data->map; */
/*     int tile_width = 16; // Width of a tile in pixels */
/*     int tile_height = 16; // Height of a tile in pixels */

/*     image_clear(data->mini_map, (t_color){.raw = 0xFFFFFF}); */

/*     // Draw the white background and grid lines */
/*     for (int y = 0; y < map.size.y; y++) */
/*     { */
/*         for (int x = 0; x < map.size.x; x++) */
/*         { */
/*             t_quad block; */
/*             t_color color; */

/*             color.raw = 0xFFFFFF; // White color for empty spaces */
/*             block = rectangle((t_vec2){x * tile_width, y * tile_height}, (t_vec2){tile_width, tile_height}, color); */
/*             image_put_empty_quad(data->mini_map, block); */
/*         } */
/*     } */

/*     // Draw grey grid lines */
/*     /1* t_color grey = {.raw = 0x808080}; *1/ */
/*     for (int y = 0; y <= map.size.y; y++) */
/*     { */
/*         image_put_line(data->mini_map, (t_vec2){0, y * tile_height}, (t_vec2){map.size.x * tile_width, y * tile_height}); */
/*     } */
/*     for (int x = 0; x <= map.size.x; x++) */
/*     { */
/*         image_put_line(data->mini_map, (t_vec2){x * tile_width, 0}, (t_vec2){x * tile_width, map.size.y * tile_height}); */
/*     } */

/*     // Draw black walls and red player position */
/*     for (int y = 0; y < map.size.y; y++) */
/*     { */
/*         for (int x = 0; x < map.size.x; x++) */
/*         { */
/*             if (map.data[y][x] == '1') */
/*             { */
/*                 t_quad block; */
/*                 t_color color; */

/*                 color.raw = 0x000000; // Black color for walls */
/*                 block = rectangle((t_vec2){x * tile_width, y * tile_height}, (t_vec2){tile_width, tile_height}, color); */
/*                 image_put_empty_quad(data->mini_map, block); */
/*             } */
/*         } */
/*     } */

    // Draw the player position on the minimap
    /* int player_x = (int)(player_pos.x); */
    /* int player_y = (int)(player_pos.y); */
    /* t_quad player_block = rectangle((t_vec2){player_x * tile_width, player_y * tile_height}, (t_vec2){tile_width, tile_height}, (t_color){.raw = 0xFF0000}); // Red color for the player */
    /* image_put_empty_quad(data->mini_map, player_block); */
/* } */

/* void draw_minimap(t_screen *screen, t_vec2f player_pos) */
/* { */
/*     t_data *data = screen->data; */
/* 		t_map map = data->map; */
/*     int tile_width = 16; // Width of a tile in pixels */
/*     int tile_height = 16; // Height of a tile in pixels */

/* 		image_clear(data->mini_map, (t_color){.raw = 0xFFFFFF}); */
/*     for (int y = 0; y < map.size.y; y++) */
/*     { */
/*         for (int x = 0; x < map.size.x; x++) */
/*         { */
/*             t_quad block; */
/*             t_color color; */

/*             if (map.data[y][x] == '1') */
/*             { */
/*                 color.raw = 0x000000; // Black color for walls */
/*             } */
/*             else */
/*             { */
/*                 color.raw = 0xFFFFFF; // White color for empty spaces */
/*             } */

/*             block = rectangle((t_vec2){x * tile_width, y * tile_height}, (t_vec2){tile_width, tile_height}, color); */
/*             image_put_empty_quad(data->mini_map, block); */
/*         } */
/*     } */

/*     // Draw the player position on the minimap */
/*     int player_x = (int)(player_pos.x); */
/*     int player_y = (int)(player_pos.y); */
/*     t_quad player_block = rectangle((t_vec2){player_x * tile_width, player_y * tile_height}, (t_vec2){tile_width, tile_height}, (t_color){.raw = 0xFF0000}); // Red color for the player */
/*     image_put_empty_quad(data->mini_map, player_block); */
/* } */

void	draw_image(t_screen *screen)
{
	t_data	*data;
	float	dist_to_wall;
	int wall_height;
	int		index;
	float	pad = 60.0 / screen->size.x;
	float projection_plane_dist = (screen->size.x / 2) / tan(deg_to_rad(30));

	data = screen->data;
	index = 0;
	draw_floor_and_ceiling(screen, (t_color){.raw = 0xFF00FF}, (t_color){.raw = 0x0000FF});
	update_wall_distance(screen);
	draw_minimap(screen, data->player.pos);
	while (index < screen->size.x)
	{
		dist_to_wall = data->walls[index].distance;
		wall_height *= cosf(deg_to_rad(-30 + (index * pad))); //fish_eye correcteur
		wall_height = 64 / dist_to_wall * projection_plane_dist;
		/* printf("wall_height: %d\n", wall_height); */
		image_put_line(screen->img,
			(t_pixel){.coord = (t_vec2){index, screen->center.y + (wall_height / 2)}, .color.raw = 0xFFFF00},
			(t_pixel){.coord = (t_vec2){index, screen->center.y - (wall_height / 2)}, .color.raw = 0x00FFFF});
		index += 1;
	}
	/* update_minimap(screen); */


	/* image_put_to_image(data->dda_debugger, data->mini_map); */
	image_put_to_image(data->mini_map, screen->img);
//	image_put_to_image(data->dda_debugger, screen->img);
}

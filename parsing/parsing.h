/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:00:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/04 12:38:47 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "vec2.h"
# include "str.h"
# include "lst.h"
# include "file.h"
# include "is_charset.h"
# include "color.h"

# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_config
{
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	t_vec2f player_pos;
	float player_angle;
	bool set_floor_color;
	bool set_ceiling_color;
	t_color floor_color;
	t_color ceiling_color;
	char **map;
}	t_config;

int ft_error(char *str);
bool parser(char *filename, t_config *config);


// Texture parsing
bool check_texture_name(char const *line, char const *texture_name);
char *get_texture_path(char const *line, char const *texture_name);
bool parse_texture_north(t_list *head, t_config *config);
bool parse_texture_south(t_list *head, t_config *config);
bool parse_texture_west(t_list *head, t_config *config);
bool parse_texture_west(t_list *head, t_config *config);
bool parse_texture(t_list *head, t_config *config);

// Color parsing
char *get_color_path(char *line, char *color_name);
bool parse_color_path(char *color_path, t_color *trgb_color, bool *set_color);
bool parse_floor_color(t_list *head, t_config *config);
bool parse_ceiling_color(t_list *head, t_config *config);
bool parse_colors(t_list *head, t_config *config);


// Debug
void print_line(void *str);
void print_texture(t_config *config);
void print_colors(t_config *config);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:00:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/06 16:40:58 by kdhrif           ###   ########.fr       */
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
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_vec2f	player_pos;
	float	player_angle;
	bool	set_floor_color;
	bool	set_ceiling_color;
	t_color	floor_color;
	t_color	ceiling_color;
	char	**map;
}	t_config;

bool	ft_error(char *str);
bool	parser(char *filename, t_config *config);

// Texture parsing
bool	check_texture_name(char const *line, char const *texture_name);
bool	valid_texture_name(char *str);
char	*get_texture_path(char const *line, char const *texture_name);
bool	parse_texture_north(t_list *head, t_config *config);
bool	parse_texture_south(t_list *head, t_config *config);
bool	parse_texture_west(t_list *head, t_config *config);
bool	parse_texture_east(t_list *head, t_config *config);
bool	parse_texture(t_list *head, t_config *config);

// Color parsing
char	*get_color_path(char *line, char *color_name);
bool	parse_color_path(char *color_path, \
		t_color *trgb_color, bool *set_color);
bool	parse_floor_color(t_list *head, t_config *config);
bool	parse_ceiling_color(t_list *head, t_config *config);
bool	parse_colors(t_list *head, t_config *config);

// Player parsing
bool	check_number_of_players(t_list *submap);
void	get_player_angle(float *player_angle, char c);
bool	get_player_position(t_list *submap, t_config *config, int i);
bool	parse_map_players(t_list *submap, t_config *config);

// Map parsing
t_list	*get_equal_lines(t_list *tmp, int max);
t_list	*parse_submap(t_list *head, int out, char *str);
void	map_str_transform(void *tmp);
t_list	*get_equal_lines(t_list *tmp, int max);
int		get_longest_line(t_list *tmp);
void	get_player_angle(float *player_angle, char c);
bool	check_number_of_players(t_list *submap);
bool	parse_map_illegal_instruction(t_list *map);
bool	parse_legal_map_characters(char c);
bool	parse_map_illegal_character(t_list *map);
bool	parse_map_closed(t_list *submap);
bool	parse_map_into_charmap(t_list *submap, t_config *config);
bool	parse_map(t_list *head, t_config *config);
bool	zero_or_player(char c);

// Parsing utils
bool	wrong_chars(char *str);
bool	check_syntax(char c);
int		open_file(char *filename);
bool	ends_with(char *str, char *end);
void	init_config(t_config *config);

// Debug
void	print_line(void *str);
void	print_texture(t_config *config);
void	print_colors(t_config *config);
void	print_player(t_config *config);
void	print_map(t_config *config);
void	debug(t_config *config);
#endif

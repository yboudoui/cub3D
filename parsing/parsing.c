/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:08:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/03 17:23:07 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

// Initialize the configuration structure with default values
void	init_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->set_floor_color = false;
	config->set_ceiling_color = false;
	config->floor_color = (t_color){{1, 1, 1}};
	config->ceiling_color = (t_color){{1, 1, 1}};
	config->map = NULL;
	config->player_pos.x = -1;
	config->player_pos.y = -1;
	config->player_angle = -1;
	return ;
}

// Check if the configuration is valid
// If not, return an error message
// If yes, return NULL
// The configuration is valid if:
// - all the required fields are filled
// - the map is surrounded by walls
// - the map only contains valid characters
// - the map contains only one player
// - the player is looking in a valid direction
// - the map is rectangular
// - the map is at least 3x3
// - the map is closed
bool ends_with(char *str, char *end)
{
	int	str_len;
	int	end_len;

	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (str_len < end_len)
		return (false);
	if (ft_strncmp(str + str_len - end_len, end, end_len) == 0)
		return (true);
	return (false);
}

int open_file(char *filename)
{
	int	fd;

	if ((open(filename, O_DIRECTORY)) != -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

bool check_syntax(char c)
{
	if (ft_isalnum(c) || ft_is_nl_comma_fslash_dot(c) || ft_isspace(c))
		return (true);
	return (false);
}

bool wrong_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!check_syntax(str[i]))
			return (false);
		i++;
	}
	return (true);
}


char *get_color_path(char *line, char *color_name)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue;
		}
		if (ft_strncmp(line + i, color_name, 1) == 0)
		{
			i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			return (ft_strdup(line + i));
		}
		i++;
	}
	return (NULL);
}

bool parse_color_path(char *color_path, t_config *config)
{
	int	i;
	int	j;
	int	color[3];

	i = 0;
	j = 0;
	while (color_path[i])
	{
		if (ft_isdigit(color_path[i]))
		{
			color[j] = ft_atoi(color_path + i);
			j++;
			while (ft_isdigit(color_path[i]))
				i++;
			if (color_path[i] == ',')
				i++;
			else if (color_path[i] != '\0')
				return (false);
		}
		else if (ft_isspace(color_path[i]))
			i++;
		else
			return (false);
	}	
	printf("color: %d %d %d\n", color[0], color[1], color[2]);
	if (j != 3)
		return (false);
	if (color[0] < 0 || color[0] > 255)
		return (false);
	if (color[1] < 0 || color[1] > 255)
		return (false);
	if (color[2] < 0 || color[2] > 255)
		return (false);
	/* config->floor_color.r = color[0]; */
	/* config->floor_color.g = color[1]; */
	/* config->floor_color.b = color[2]; */
	config->set_floor_color = true;
	return (true);
}

bool parse_floor_color(t_list *head, t_config *config)
{
	t_list *tmp;
	char *str;
	char *color_path;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "F") == true)
		{
			color_path = get_color_path(str, "F");
			if (color_path == NULL)
				return (false);
			if (parse_color_path(color_path, config) == false)
				return (false);
			printf("color_path: %s\n", color_path);
			if (config->set_floor_color)
				return (false);
		}
		tmp = tmp->next;
	}
	if (config->set_floor_color)
		return (true);
	return (false);
}

/* bool parse_ceiling_color(t_list *head, t_config *config) */
/* { */
/* 	t_list *tmp; */
/* 	char *str; */

/* 	tmp = head; */
/* 	while (tmp) */
/* 	{ */
/* 		str = (char *)tmp->content; */
/* 		if (check_texture_name(str, "C") == true) */
/* 		{ */
/* 			if (config->ceiling_color) */
/* 				return (false); */
/* 			config->ceiling_color = get_texture_path(str, "C"); */
/* 		} */
/* 		tmp = tmp->next; */
/* 	} */
/* 	if (config->ceiling_color) */
/* 		return (true); */
/* 	return (false); */
/* } */

bool parse_colors(t_list *head, t_config *config)
{
	if (parse_floor_color(head, config) == false)
		return (false);
	/* if (parse_ceiling_color(head, config) == false) */
	/* 	return (false); */
	return (true);
}


void print_line(void *str)
{
	printf("%s", (char *)str);
}

void print_texture(t_config *config)
{
	if (config->north_texture)
		printf("north_texture: %s\n", config->north_texture);
	if (config->south_texture)
		printf("south_texture: %s\n", config->south_texture);
	if (config->west_texture)
		printf("west_texture: %s\n", config->west_texture);
	if (config->east_texture)
		printf("east_texture: %s\n", config->east_texture);
}

bool parser(char *filename, t_config *config)
{
	int	fd;
	t_list *head;

	init_config(config);
	if (!ends_with(filename, ".cub"))
	{
		ft_error("Error\nInvalid file extension\n");
		return (false);
	}
	fd = open_file(filename);
	if (fd < 0)
	{
		ft_error("Error\nInvalid file\n");
		return (false);
	}
	head = read_file_2(fd, wrong_chars, free);
	if (!head)
		return (false);
	if (parse_texture(head, config) == false)
	{
		ft_error("Error\nInvalid texture\n");
		return (false);
	}
	if (parse_colors(head, config) == false)
	{
		ft_error("Error\nInvalid colors\n");
		return (false);
	}
	/* print_texture(config); */
	/* lst_iter(head, print_line); */
	exit(0);
}

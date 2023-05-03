/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:08:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/03 22:12:58 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

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

t_list *parse_submap(t_list *head)
{
	t_list *tmp;
	t_list *out;
	char *str;
	int i;

	tmp = head;
	out = NULL;
	while (tmp)
	{
		i = 0;
		str = tmp->content;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] && (str[i] == '1' || str[i] == '0'))
			break ;
		tmp = tmp->next;
	}
	while (tmp)
	{
		lst_add_back(&out, lst_new(tmp->content));
		tmp = tmp->next;
	}
	if (!out)
		return (NULL);
	return (out);
}

bool parse_map_illegal_instruction(t_list *map)
{
	t_list *tmp;
	char *str;

	tmp = map;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "NO") == true)
			return (false);
		if (check_texture_name(str, "SO") == true)
			return (false);
		if (check_texture_name(str, "WE") == true)
			return (false);
		if (check_texture_name(str, "EA") == true)
			return (false);
		if (check_texture_name(str, "F") == true)
			return (false);
		if (check_texture_name(str, "C") == true)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

bool parse_legal_map_characters(char c)
{
	if (ft_isspace(c) || c == '1' || \
			c == '0' || c == 'N' || c == 'S' || \
			c == 'W' || c == 'E')
		return (true);
	return (false);
}

bool parse_map_illegal_character(t_list *map)
{
	t_list *tmp;
	char *str;
	int i;

	tmp = map;
	while (tmp)
	{
		i = 0;
		str = (char *)tmp->content;
		while (str[i])
		{
			if (parse_legal_map_characters(str[i]) == false)
				return (false);
			i++;
		}
		tmp = tmp->next;
	}
	return (true);
}


bool parse_map(t_list *head, t_config *config)
{
	t_list *submap;

	submap = NULL;
	submap = parse_submap(head);
	if (parse_map_illegal_instruction(submap) == false)
		return (false);
	if (parse_map_illegal_character(submap) == false)
		return (false);
	config->map = (char **)malloc(sizeof(char *) * (lst_size(submap) + 1));
	lst_iter(submap, print_line);
	exit(0);
	/* if (parse_map_size(head, config) == false) */
	/* 	return (false); */
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
	if (parse_map(head, config) == false)
	{
		ft_error("Error\nInvalid map\n");
		return (false);
	}
	/* print_colors(config); */
	/* print_texture(config); */
	/* lst_iter(head, print_line); */
	exit(0);
}

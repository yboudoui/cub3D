
typedef struct s_dda {
	t_vec2f	point;
	t_vec2f	step;
}	t_dda;

static t_dda	dda_h(t_vec2f player_pos, float angle_view)
{
	t_dda	out;

	out = (t_dda){0};
	if (180 < angle_view && angle_view < 0)
	{
		out.point.y = round(player_pos.y) - 1;
		out.step.y = -1;
	}
	else
	{
		out.point.y = round(player_pos.y) + 1;
		out.step.y = 1;
	}
	out.point.x = player_pos.x + (player_pos.y - out.point.y) / tan(angle_view);
	out.step.x = tan(angle_view);
	return (out);
}

static t_dda	dda_v(t_vec2f player_pos, float angle_view)
{
	t_dda	out;

	out = (t_dda){0};
	if (angle_view > 90 && angle_view < 270)
	{
		out.point.x = round(player_pos.x) - 1;
		out.step.x = 1;
	}
	else
	{
		out.point.x = round(player_pos.x) - 1;
		out.step.x = -1;
	}
	out.point.y = player_pos.y + (player_pos.x - out.point.x) * tan(angle_view);
	out.step.y = tan(angle_view);
	return (out);
}

t_vec2f	add_vec2f(t_vec2f a, t_vec2f b)
{
	t_vec2f	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	return (out);
}

float	vec2f_dist(t_vec2f a, t_vec2f b)
{
	t_vec2f	dist;

	dist.x = fabsf(a.x - b.x);
	dist.y = fabsf(a.y - b.y);
	return (sqrtf(powf(dist.x, 2) + powf(dist.y, 2)));
}

float	dda_checker(t_vec2f pos, float angle, char **map)
{
	t_dda	dda[2];
	t_vec2f	new[2];
	float	len[2];
	bool	hit[2];

	angle =  (angle * M_PI / 180.0);
	dda[0] = dda_h(pos, angle);
	dda[1] = dda_v(pos, angle);
	len[0] = vec2f_dist(pos, dda[0].point);
	len[1] = vec2f_dist(pos, dda[1].point);
	hit[0] = false;
	hit[1] = false;
	while (true)
	{
		hit[0] = (map[(int)dda[0].point.y][(int)dda[0].point.x] == '1');
		hit[1] = (map[(int)dda[1].point.y][(int)dda[1].point.x] == '1');
		if (hit[0] || hit[1])
			break ;
		new[0] = add_vec2f(dda[0].point, dda[1].step);
		new[1] = add_vec2f(dda[1].point, dda[1].step);
		len[0] += vec2f_dist(dda[0].point, new[0]);
		len[1] += vec2f_dist(dda[1].point, new[1]);
		dda[0].point = new[0];
		dda[1].point = new[1];
	}
	if (hit[0] && !hit[1])
		return (len[0]);
	if (hit[1] && !hit[0])
		return (len[1]);
	if (len[0] < len[1])
		return (len[0]);
	return (len[1]);
}

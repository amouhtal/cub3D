/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:52:40 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/07 11:04:34 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		count_width(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i])
			i++;
	}
	return (i);
}

void	ft_get_player_angle(char angle, t_mlx *m)
{
	if (angle == 'N')
		m->s_map.angle = M_PI * 3 / 2;
	if (angle == 'S')
		m->s_map.angle = M_PI / 2;
	if (angle == 'E')
		m->s_map.angle = M_PI;
	if (angle == 'W')
		m->s_map.angle = 0;
}

int		the_longest_line_in_2d(char **tab)
{
	int	i;
	int	j;
	int	the_longest_line;

	i = 0;
	j = 0;
	the_longest_line = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			j++;
		if (j > the_longest_line)
			the_longest_line = j;
		i++;
	}
	return (the_longest_line);
}

int		check_player_nbr(t_mlx *m, int i, int nbrs_player)
{
	int o;

	m->s_map.rows = count_table(m->s_map.map);
	m->s_map.coloms = ft_strlen(m->s_map.map[0]);
	while (++i < m->s_map.rows)
	{
		o = -1;
		while (++o < m->s_map.coloms)
		{
			if (m->s_map.map[i][o] == 'N' || m->s_map.map[i][o] == 'S'
			|| m->s_map.map[i][o] == 'W' || m->s_map.map[i][o] == 'E')
			{
				if (m->s_map.map[i + 1][o] == ' ' || m->s_map.map[i - 1][o]
				== ' ' || m->s_map.map[i][o + 1] == ' '
				|| m->s_map.map[i][o - 1] == ' ')
					nbrs_player = 2;
				ft_get_player_angle(m->s_map.map[i][o], m);
				m->s_map.map[i][o] = '5';
				nbrs_player++;
			}
		}
	}
	if (nbrs_player != 1)
		write(1, "Error\ncheck nombre of players", 29);
	return (nbrs_player);
}

int		map_is_last(t_mlx *m)
{
	if (m->s_path && m->witdth && m->height && m->west
	&& m->south && m->south && m->north
	&& m->east && m->ccolor.c && m->ccolor.f)
		return (1);
	return (0);
}

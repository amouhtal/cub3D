/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:52:35 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/09 14:33:34 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_map_line_get_takeing(char *line, int i, int j)
{
	char *new_tab;

	new_tab = (char *)malloc(sizeof(char) * (ft_strlen(line)) + 1);
	if (new_tab == NULL)
	{
		free(new_tab);
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'E'
		|| line[i] == ' ' || line[i] == 'S' || line[i] == 'W' || line[i] == '2')
		{
			new_tab[j] = line[i];
			j++;
		}
		else if (line[i] != '\0')
		{
			free(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[j] = '\0';
	return (new_tab);
}

int		ft_fill_mape(t_mlx *m, char *line)
{
	int		i;
	char	*str;
	int		width;

	width = 0;
	str = NULL;
	i = 0;
	while (line[i] == ' ' && !m->s_map.map[0])
		i++;
	if (line[0] == '\0')
		line[0] = ' ';
	if (line[i])
	{
		str = ft_map_line_get_takeing(line, 0, 0);
	}
	if (str == NULL)
		return (3);
	if (str)
		m->s_map.map = ft_join_to_table(m->s_map.map, str);
	i = 0;
	free(str);
	return (0);
}

int		ft_check_parse_file(t_mlx *m, char *line)
{
	int ret;

	ret = 0;
	if (line[0] == 'R' && line[1] == ' ')
		ret = ft_res(m, line);
	else if ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' ') || (line[0] == 'W'
	&& line[1] == 'E' && line[2] == ' ') ||
	(line[0] == 'E' && line[1] == 'A' && line[2] == ' '))
		ret = check_textures(m, line);
	else if (line[0] == 'S' && line[1] == ' ')
		ret = check_sprite(m, line);
	else if (line[0] == 'F' && line[1] == ' ' && !m->ccolor.f)
		ret = ft_floor(m, line, 2);
	else if (line[0] == 'C' && line[1] == ' ' && !m->ccolor.c)
		ret = ft_ceil(m, line, 2);
	else if ((line[0] == ' ' || line[0] == '1'
	|| line[0] == '0' || line[0] == '\0') && map_is_last(m))
		ret = ft_fill_mape(m, line);
	else if (line[0] == '\0' && (m->s_map.map[0] != NULL))
		ret = 0;
	else if (line[0])
		ret = 4;
	return (ret);
}

int		ft_check_map(t_mlx *m, int i)
{
	int		last_indice_i;
	char	**tmp;

	last_indice_i = count_table(m->s_map.map);
	tmp = m->s_map.map;
	if (!(m->s_map.map = ft_remplir_tab(m->s_map.map,
	the_longest_line_in_2d(m->s_map.map), count_table(m->s_map.map), -1)))
		return (-1);
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	i = 0;
	if (ft_check_sp_or_1_line(m->s_map.map, 0, 1) == 0)
		return (-1);
	if (ft_check_sp_or_1_line(m->s_map.map,
	last_indice_i - 1, last_indice_i - 2) == 0)
		return (-1);
	if (ft_check_horizontal_line(m->s_map.map, 1,
	last_indice_i - 2, the_longest_line_in_2d(m->s_map.map)) == 0)
		return (-1);
	if (ft_check_vertical_line(m->s_map.map, 0,
	the_longest_line_in_2d(m->s_map.map), last_indice_i) == 0)
		return (-1);
	return (0);
}

int		parse(int ac, char **av, t_mlx *m)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	line = NULL;
	if ((ac < 1 || ac > 3 || (fd = open(av[1],
	O_RDONLY)) == -1) || !check_exte(av[1], 2))
	{
		write(1, "Error\ncheck arguments", 21);
		return (-2);
	}
	mlx_init1(m, &i, &ret);
	get_and_check(m, &ret, line, fd);
	check_color_resolution(m, &ret);
	if ((line && ret) || (m->s_map.map[0] == NULL))
		return (-1);
	if (ft_check_map(m, -1) == -1)
	{
		write(1, "Error\nMap error", 15);
		return (-1);
	}
	if (check_player_nbr(m, -1, 0) != 1)
		return (-1);
	return (0);
}

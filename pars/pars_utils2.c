/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:13:36 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/09 15:00:33 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		bypass_space2(char *str, int i)
{
	while (str[i] == ' ')
		(i)++;
	return (i);
}

int		check_sprite(t_mlx *mlx, char *line)
{
	char *tmp;

	if (line[0] == 'S' && line[1] == ' ')
	{
		tmp = mlx->s_path;
		mlx->s_path = ft_strdup(&line[bypass_space2(line, 1)]);
		free(tmp);
	}
	return (0);
}

int		check_textures(t_mlx *mlx, char *line)
{
	if (line[0] == 'S' && line[1] == 'O' && !mlx->south)
		mlx->south = ft_strdup(&line[bypass_space2(line, 2)]);
	else if (line[0] == 'N' && !mlx->north)
		mlx->north = ft_strdup(&line[bypass_space2(line, 2)]);
	else if (line[0] == 'W' && !mlx->west)
		mlx->west = ft_strdup(&line[bypass_space2(line, 2)]);
	else if (line[0] == 'E' && !mlx->east)
		mlx->east = ft_strdup(&line[bypass_space2(line, 2)]);
	else
		return (4);
	return (0);
}

int		ft_check_horizontal_line(char **tab,
int first, int befor_last, int lenght)
{
	int i;
	int l;

	l = lenght;
	while (first <= befor_last)
	{
		lenght = l;
		i = 0;
		i = bypass_space(tab[first], &i);
		if (tab[first][i] != '1' && tab[first][i] != '\0')
			return (0);
		while ((tab[first][lenght] == ' ' ||
		tab[first][lenght] == '\0') && lenght > 0)
			lenght--;
		if (tab[first][lenght] != '1' && tab[first][lenght] !=
		'\0' && tab[first][lenght] != ' ')
			return (0);
		i = 0;
		while (tab[first][++i] && i < lenght)
			if ((tab[first][i] == ' ' && tab[first][i - 1] == '0')
			|| (tab[first][i] == ' ' && tab[first][i + 1] == '0'))
				return (0);
		first++;
	}
	return (1);
}

int		ft_check_vertical_line(char **tab,
int first, int last, int lenght_vert)
{
	int i;
	int lenght;

	lenght_vert--;
	while (first < last)
	{
		i = 0;
		lenght = lenght_vert;
		while (tab[++i][first] == ' ' && i < lenght_vert)
			;
		if (tab[i][first] == '0' && tab[i - 1][first] == ' ')
			return (0);
		while (tab[lenght][first] == ' ' && lenght > 0)
			lenght--;
		if (tab[lenght][first] == '0' && tab[i + 1][first] == ' ')
			return (0);
		i = -1;
		while (++i < count_table(tab))
			if (i > 0 && i < count_table(tab) - 1)
				if ((tab[i][first] == ' ' && tab[i - 1][first] == '0')
				|| (tab[i][first] == ' ' && tab[i + 1][first] == '0'))
					return (0);
		first++;
	}
	return (1);
}
